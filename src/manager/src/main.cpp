//
// Created by vogje01 on 21/12/2022.
// Copyright 2022, 2023 Jens Vogt
//
// This file is part of aws-mock.
//
// aws-mock is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// aws-mock is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with aws-mock.  If not, see <http://www.gnu.org/licenses/>.

// C includes
#include <unistd.h>
#include <cstdlib>

// C++ standard includes
#include <iostream>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/TaskManager.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/config/Configuration.h>
#include <awsmock/controller/Router.h>
#include <awsmock/controller/RestService.h>
#include <awsmock/service/CognitoServer.h>
#include <awsmock/service/DynamoDbServer.h>

namespace AwsMock {

  /**
   * Main application class.
   */
  class AwsMockServer : public Poco::Util::ServerApplication {

    public:
    AwsMockServer() : _logger(Core::LogStream(Poco::Logger::get("AwsMockManager"))) {}

    protected:

    /**
     * Initialization callback from Poco Application class.
     *
     * @param self application reference.
     */
    [[maybe_unused]] void initialize(Application &self) override {

      InitializeMonitoring();
      InitializeIndexes();
      InitializeCurl();
      log_info_stream(_logger) << "Starting " << Configuration::GetAppName() << " " << Configuration::GetVersion() << " pid: " << getpid() << " loglevel: "
                               << _configuration.getString("awsmock.log.level") << std::endl;
      log_info_stream(_logger) << "Configuration file: " << _configuration.GetFilename() << std::endl;
      Poco::Util::ServerApplication::initialize(self);
    }

    /**
     * Shutdown the application. Gets called when the application is about to stop.
     */
    [[maybe_unused]] void uninitialize() override {

      // Shutdown all services
      StopServices();

      // Stop HTTP manager
      _restService.StopServer();

      // Shutdown monitoring
      _metricService.ShutdownServer();

      log_debug_stream(_logger) << "Bye, bye and thanks for all the fish" << std::endl;
    }

    /**
     * Define the command line options.
     *
     * @param options Poco options class.
     */
    [[maybe_unused]] void defineOptions(Poco::Util::OptionSet &options) override {

      Poco::Util::ServerApplication::defineOptions(options);
      options.addOption(Poco::Util::Option("config", "", "set the configuration file").required(false).repeatable(false).argument("value").callback(
        Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
      options.addOption(Poco::Util::Option("loglevel", "", "set the log level").required(false).repeatable(false).argument("value").callback(
        Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
      options.addOption(Poco::Util::Option("logfile", "", "set the log file").required(false).repeatable(false).argument("value").callback(
        Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
      options.addOption(Poco::Util::Option("version", "", "display version information").required(false).repeatable(false).callback(
        Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
      options.addOption(Poco::Util::Option("help", "", "display help information").required(false).repeatable(false).callback(
        Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
    }

    /**
     * Handles the command line options. Uses Poco command line optios handling.
     *
     * @param name command line option name.
     * @param value command line option value.
     */
    void handleOption(const std::string &name, const std::string &value) override {

      if (name == "help") {

        Poco::Util::HelpFormatter helpFormatter(options());
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("OPTIONS");
        helpFormatter.setHeader("AwsMock - AWS simulation written in C++ v" + Configuration::GetVersion());
        helpFormatter.format(std::cout);
        stopOptionsProcessing();
        exit(0);

      } else if (name == "config") {

        _configuration.SetFilename(value);

      } else if (name == "version") {

        std::cout << Configuration::GetAppName() << " v" << Configuration::GetVersion() << std::endl;
        exit(0);

      } else if (name == "loglevel") {

        _configuration.setString("awsmock.log.level", value);
        Poco::Logger::root().setLevel(value);

      } else if (name == "logfile") {

        _logger.setFileChannel(value);
      }
    }

    /**
     * Initialize the Prometheus monitoring counters and StartServer the prometheus manager.
     */
    void InitializeMonitoring() {

      _metricService.Initialize();
      _metricService.StartServer();
    }

    /**
     * Initialize database indexes
     */
    void InitializeIndexes() {

      // Create database indexes
      //_database.CreateIndexes();
      log_debug_stream(_logger) << "Database indexes created" << std::endl;
    }

    /**
     * Initialize CURL library
     */
    void InitializeCurl() {
      curl_global_init(CURL_GLOBAL_ALL);
      log_debug_stream(_logger) << "Curl library initialized" << std::endl;

    }

    void StartServices() {

      // Handle environment variables
      if (_configuration.has("awsmock.mongodb.active") && _configuration.getBool("awsmock.mongodb.active")) {
        _moduleDatabase.SetStatus("database", Database::Entity::Module::ModuleStatus::ACTIVE);
        //_database.StartDatabase();
      }
      if (_configuration.has("awsmock.service.sqs.active") && _configuration.getBool("awsmock.service.sqs.active")) {
        _moduleDatabase.SetStatus("sqs", Database::Entity::Module::ModuleStatus::ACTIVE);
      }
      if (_configuration.has("awsmock.service.s3.active") && _configuration.getBool("awsmock.service.s3.active")) {
        _moduleDatabase.SetStatus("s3", Database::Entity::Module::ModuleStatus::ACTIVE);
      }
      if (_configuration.has("awsmock.service.sns.active") && _configuration.getBool("awsmock.service.sns.active")) {
        _moduleDatabase.SetStatus("sns", Database::Entity::Module::ModuleStatus::ACTIVE);
      }
      if (_configuration.has("awsmock.service.lambda.active") && _configuration.getBool("awsmock.service.lambda.active")) {
        _moduleDatabase.SetStatus("lambda", Database::Entity::Module::ModuleStatus::ACTIVE);
      }
      if (_configuration.has("awsmock.service.transfer.active") && _configuration.getBool("awsmock.service.transfer.active")) {
        _moduleDatabase.SetStatus("transfer", Database::Entity::Module::ModuleStatus::ACTIVE);
      }
      if (_configuration.has("awsmock.service.cognito.active") && _configuration.getBool("awsmock.service.cognito.active")) {
        _moduleDatabase.SetStatus("cognito", Database::Entity::Module::ModuleStatus::ACTIVE);
      }
      if (_configuration.has("awsmock.service.dynamodb.active") && _configuration.getBool("awsmock.service.dynamodb.active")) {
        _moduleDatabase.SetStatus("dynamodb", Database::Entity::Module::ModuleStatus::ACTIVE);
      }
      if (_configuration.has("awsmock.service.gateway.active") && _configuration.getBool("awsmock.service.gateway.active")) {
        _moduleDatabase.SetStatus("gateway", Database::Entity::Module::ModuleStatus::ACTIVE);
      }

      // Get last module configuration
      Database::Entity::Module::ModuleList modules = _moduleDatabase.ListModules();
      for (const auto &module : modules) {
        if (module.name == "s3" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _s3Server = new Service::S3Server(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(*_s3Server);
          _serverMap[module.name] = _s3Server;
        } else if (module.name == "sqs" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _sqsServer = new Service::SQSServer(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(*_sqsServer);
          _serverMap[module.name] = _sqsServer;
        } else if (module.name == "sns" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _snsServer = new Service::SNSServer(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(*_snsServer);
          _serverMap[module.name] = _snsServer;
        } else if (module.name == "lambda" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _lambdaServer = new Service::LambdaServer(_configuration, _metricService, _createQueue, _invokeQueue);
          Poco::ThreadPool::defaultPool().start(*_lambdaServer);
          _serverMap[module.name] = _lambdaServer;
        } else if (module.name == "transfer" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _transferServer = new Service::TransferServer(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(*_transferServer);
          _serverMap[module.name] = _transferServer;
        } else if (module.name == "cognito" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _cognitoServer = new Service::CognitoServer(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(*_cognitoServer);
          _serverMap[module.name] = _cognitoServer;
        } else if (module.name == "dynamodb" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _dynamoDbServer = new Service::DynamoDbServer(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(*_dynamoDbServer);
          _serverMap[module.name] = _dynamoDbServer;
        } else if (module.name == "gateway" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
          _gatewayServer = new Service::GatewayServer(_configuration, _metricService);
          Poco::ThreadPool::defaultPool().start(*_gatewayServer);
          _serverMap[module.name] = _gatewayServer;
        }
        log_debug_stream(_logger) << "Module " << module.name << " started" << std::endl;
      }
    }

    void StopServices() {

      Database::Entity::Module::ModuleList modules = _moduleDatabase.ListModules();
      for (const auto &module : modules) {
        if (module.state == Database::Entity::Module::ModuleState::RUNNING) {
          log_info_stream(_logger) << "Stopping module: " << module.name << std::endl;
          if (module.name == "s3") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            auto *s3Server = (Service::S3Server *) _serverMap[module.name];
            s3Server->StopMonitoringServer();
            s3Server->StopServer();
          } else if (module.name == "sqs") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            auto *sqsServer = (Service::SQSServer *) _serverMap[module.name];
            sqsServer->StopMonitoringServer();
            sqsServer->StopServer();
          } else if (module.name == "sns") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            auto *snsServer = (Service::SNSServer *) _serverMap[module.name];
            snsServer->StopMonitoringServer();
            snsServer->StopServer();
          } else if (module.name == "lambda") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            auto *lambdaServer = (Service::LambdaServer *) _serverMap[module.name];
            lambdaServer->StopMonitoringServer();
            lambdaServer->StopServer();
          } else if (module.name == "transfer") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            auto *transferServer = (Service::LambdaServer *) _serverMap[module.name];
            transferServer->StopServer();
          } else if (module.name == "cognito") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            auto *cognitoServer = (Service::CognitoServer *) _serverMap[module.name];
            cognitoServer->StopServer();
          } else if (module.name == "dynamodb") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            _serverMap[module.name]->StopServer();
          } else if (module.name == "gateway") {
            _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
            auto *gatewayServer = (Service::GatewayServer *) _serverMap[module.name];
            gatewayServer->StopServer();
          }
          log_debug_stream(_logger) << "Module " << module.name << " stopped" << std::endl;
        }
      }
    }

    /**
     * Main routine.
     *
     * @param args command line arguments.
     * @return system exit code.
     */
    int main([[maybe_unused]]const ArgVec &args) override {

      log_debug_stream(_logger) << "Entering main routine" << std::endl;

      // Start module and worker. Services needed to StartServer first, as the worker could possibly use the services.
      StartServices();

      // Start HTTP manager
      _restService.setRouter(_router);
      _restService.StartServer();

      // Wait for termination
      this->waitForTerminationRequest();
      log_debug_stream(_logger) << "Starting termination" << std::endl;

      return Application::EXIT_OK;
    }

    private:

    /**
     * Logger
     */
    Core::LogStream _logger = Core::LogStream(Poco::Logger::root());

    /**
     * Application configuration
     */
    Configuration _configuration = Configuration(CONFIGURATION_BASE_PATH);

    /**
     * Monitoring module
     */
    Core::MetricService _metricService = Core::MetricService(_configuration);

    /**
     * Gateway router
     */
    std::shared_ptr<Controller::Router> _router = std::make_shared<Controller::Router>(_configuration, _metricService, _serverMap);

    /**
     * S3 module
     */
    Service::S3Server *_s3Server{};

    /**
     * SQS module
     */
    Service::SQSServer *_sqsServer{};

    /**
     * SNS module
     */
    Service::SNSServer *_snsServer{};

    /**
     * Lambda module
     */
    Service::LambdaServer *_lambdaServer{};

    /**
     * Transfer module
     */
    Service::TransferServer *_transferServer{};

    /**
     * Cognito module
     */
    Service::CognitoServer *_cognitoServer{};

    /**
     * DynamoDb module
     */
    Service::DynamoDbServer *_dynamoDbServer{};

    /**
     * Request gateway module
     */
    Service::GatewayServer *_gatewayServer{};

    /**
     * Create notification queue
     */
    Poco::NotificationQueue _createQueue;

    /**
     * Invoke notification queue
     */
    Poco::NotificationQueue _invokeQueue;

    /**
     * Gateway controller
     */
    RestService _restService = RestService(_configuration);

    /**
     * Service database
     */
    Database::ModuleDatabase &_moduleDatabase = Database::ModuleDatabase::instance();

    /**
     * Server map
     */
    Service::ServerMap _serverMap;
  };

} // namespace AwsMock

#ifndef TESTING

POCO_SERVER_MAIN (AwsMock::AwsMockServer)

#endif
