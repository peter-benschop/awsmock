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
#include <Poco/TaskManager.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/controller/Router.h>
#include <awsmock/controller/RestService.h>

#define DEFAULT_CONFIG_FILE "/etc/aws-mock.properties"
#define DEFAULT_LOG_LEVEL  "debug"

namespace AwsMock {

    /**
     * Main application class.
     */
    class AwsMockServer : public Poco::Util::ServerApplication {

    public:
        AwsMockServer() = default;

    protected:

        /**
         * Initialization callback from Poco Application class.
         *
         * @param self application reference.
         */
        [[maybe_unused]] void initialize(Application &self) override {

            IntializeConfig();
            IntializeLogging();
            InitializeMonitoring();
            InitializeIndexes();
            InitializeCurl();
            log_info << "Starting " << Core::Configuration::GetAppName() << " " << Core::Configuration::GetVersion()
                     << " pid: " << getpid() << " loglevel: " << _configuration.getString("awsmock.log.level");
            log_info << "Configuration file: " << _configuration.GetFilename();
            Poco::Util::ServerApplication::initialize(self);
        }

        /**
         * Shutdown the application. Gets called when the application is about to stop.
         */
        [[maybe_unused]] void uninitialize() override {

            // Shutdown all services
            StopServices();
            log_debug << "Service stopped";

            // Stop HTTP manager
            _restService.StopServer();
            log_debug << "Gateway stopped";

            // Shutdown monitoring
            _metricService.Shutdown();
            log_debug << "Monitoring stopped";

            log_debug << "Bye, bye and thanks for all the fish";
        }

        /**
         * Define the command line options.
         *
         * @param options Poco options class.
         */
        [[maybe_unused]] void defineOptions(Poco::Util::OptionSet &options) override {

            Poco::Util::ServerApplication::defineOptions(options);
            options.addOption(Poco::Util::Option("config", "", "set the configuration file").required(false).repeatable(
                    false).argument("value").callback(
                    Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
            options.addOption(
                    Poco::Util::Option("loglevel", "", "set the log level").required(false).repeatable(false).argument(
                            "value").callback(
                            Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
            options.addOption(
                    Poco::Util::Option("logfile", "", "set the log file").required(false).repeatable(false).argument(
                            "value").callback(
                            Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
            options.addOption(
                    Poco::Util::Option("version", "", "display version information").required(false).repeatable(
                            false).callback(
                            Poco::Util::OptionCallback<AwsMockServer>(this, &AwsMockServer::handleOption)));
            options.addOption(Poco::Util::Option("help", "", "display help information").required(false).repeatable(
                    false).callback(
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
                helpFormatter.setHeader(
                        "AwsMock - AWS simulation written in C++ v" + Core::Configuration::GetVersion());
                helpFormatter.format(std::cout);
                stopOptionsProcessing();
                exit(0);

            } else if (name == "config") {

                _configuration.SetFilename(value);

            } else if (name == "version") {

                std::cout << Core::Configuration::GetAppName() << " v" << Core::Configuration::GetVersion()
                          << std::endl;
                exit(0);

            } else if (name == "loglevel") {

                _configuration.setString("awsmock.log.level", value);
                plog::get()->setMaxSeverity(plog::severityFromString(value.c_str()));

            } else if (name == "logfile") {

                //_logger.setFileChannel(value);
            }
        }

        /**
         * Initialize the configuration
         */
        void IntializeConfig() {
            _configuration.SetFilename(DEFAULT_CONFIG_FILE);
        }

        /**
         * Initialize the logging
         */
        void IntializeLogging() {
            std::string logLevel = _configuration.getString("awsmock.log.level", DEFAULT_LOG_LEVEL);
            plog::get()->setMaxSeverity(plog::severityFromString(logLevel.c_str()));
        }

        /**
         * Initialize the Prometheus monitoring counters and StartServer the prometheus manager.
         */
        void InitializeMonitoring() {
            _metricService.Start();
        }

        /**
         * Initialize database indexes
         */
        void InitializeIndexes() {

            // Create database indexes
            _moduleDatabase.CreateIndexes();
            log_debug << "Database indexes created";
        }

        /**
         * Initialize CURL library
         */
        static void InitializeCurl() {
            curl_global_init(CURL_GLOBAL_ALL);
            log_debug << "Curl library initialized";
        }

        void StartServices() {

            // Handle environment variables
            if (_configuration.has("awsmock.mongodb.active") && _configuration.getBool("awsmock.mongodb.active")) {
                _moduleDatabase.SetStatus("database", Database::Entity::Module::ModuleStatus::ACTIVE);
                //_database.StartDatabase();
            }
            if (_configuration.has("awsmock.service.sqs.active") &&
                _configuration.getBool("awsmock.service.sqs.active")) {
                _moduleDatabase.SetStatus("sqs", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.s3.active") &&
                _configuration.getBool("awsmock.service.s3.active")) {
                _moduleDatabase.SetStatus("s3", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.sns.active") &&
                _configuration.getBool("awsmock.service.sns.active")) {
                _moduleDatabase.SetStatus("sns", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.lambda.active") &&
                _configuration.getBool("awsmock.service.lambda.active")) {
                _moduleDatabase.SetStatus("lambda", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.transfer.active") &&
                _configuration.getBool("awsmock.service.transfer.active")) {
                _moduleDatabase.SetStatus("transfer", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.cognito.active") &&
                _configuration.getBool("awsmock.service.cognito.active")) {
                _moduleDatabase.SetStatus("cognito", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.dynamodb.active") &&
                _configuration.getBool("awsmock.service.dynamodb.active")) {
                _moduleDatabase.SetStatus("dynamodb", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.secretsmanager.active") &&
                _configuration.getBool("awsmock.service.secretsmanager.active")) {
                _moduleDatabase.SetStatus("secretsmanager", Database::Entity::Module::ModuleStatus::ACTIVE);
            }
            if (_configuration.has("awsmock.service.gateway.active") &&
                _configuration.getBool("awsmock.service.gateway.active")) {
                _moduleDatabase.SetStatus("gateway", Database::Entity::Module::ModuleStatus::ACTIVE);
            }

            // Get last module configuration
            Database::Entity::Module::ModuleList modules = _moduleDatabase.ListModules();
            for (const auto &module: modules) {
                if (module.name == "s3" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _s3Server = std::make_shared<Service::S3Server>(_configuration);
                    _s3Server->Start();
                    _serverMap[module.name] = _s3Server;
                } else if (module.name == "sqs" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _sqsServer = std::make_shared<Service::SQSServer>(_configuration);
                    _sqsServer->Start();
                    _serverMap[module.name] = _sqsServer;
                } else if (module.name == "sns" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _snsServer = std::make_shared<Service::SNSServer>(_configuration);
                    _snsServer->Start();
                    _serverMap[module.name] = _snsServer;
                } else if (module.name == "lambda" && module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _lambdaServer = std::make_shared<Service::LambdaServer>(_configuration);
                    _lambdaServer->Start();
                    _serverMap[module.name] = _lambdaServer;
                } else if (module.name == "transfer" &&
                           module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _transferServer = std::make_shared<Service::TransferServer>(_configuration, _metricService);
                    _transferServer->Start();
                    _serverMap[module.name] = _transferServer;
                } else if (module.name == "cognito" &&
                           module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _cognitoServer = std::make_shared<Service::CognitoServer>(_configuration, _metricService);
                    _cognitoServer->Start();
                    _serverMap[module.name] = _cognitoServer;
                } else if (module.name == "dynamodb" &&
                           module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _dynamoDbServer = std::make_shared<Service::DynamoDbServer>(_configuration);
                    _dynamoDbServer->Start();
                    _serverMap[module.name] = _dynamoDbServer;
                } else if (module.name == "secretsmanager" &&
                           module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _secretsManagerServer = std::make_shared<Service::SecretsManagerServer>(_configuration,
                                                                                            _metricService);
                    _secretsManagerServer->Start();
                    _serverMap[module.name] = _secretsManagerServer;
                } else if (module.name == "gateway" &&
                           module.status == Database::Entity::Module::ModuleStatus::ACTIVE) {
                    _gatewayServer = std::make_shared<Service::GatewayServer>(_configuration, _metricService);
                    _gatewayServer->Start();
                    _serverMap[module.name] = _gatewayServer;
                }
                log_debug << "Module " << module.name << " started";
            }
        }

        void StopServices() {

            Database::Entity::Module::ModuleList modules = _moduleDatabase.ListModules();
            for (const auto &module: modules) {
                if (module.state == Database::Entity::Module::ModuleState::RUNNING) {
                    log_info << "Stopping module: " << module.name;
                    if (module.name == "s3") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        auto s3Server = _serverMap[module.name];
                        s3Server->StopServer();
                    } else if (module.name == "sqs") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        auto sqsServer = _serverMap[module.name];
                        sqsServer->StopServer();
                    } else if (module.name == "sns") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        auto snsServer = _serverMap[module.name];
                        snsServer->StopServer();
                    } else if (module.name == "lambda") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        auto lambdaServer = _serverMap[module.name];
                        lambdaServer->StopServer();
                    } else if (module.name == "transfer") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        auto transferServer = _serverMap[module.name];
                        transferServer->StopServer();
                    } else if (module.name == "cognito") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        auto cognitoServer = _serverMap[module.name];
                        cognitoServer->StopServer();
                    } else if (module.name == "dynamodb") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        _serverMap[module.name]->StopServer();
                    } else if (module.name == "gateway") {
                        _moduleDatabase.SetState(module.name, Database::Entity::Module::ModuleState::STOPPED);
                        auto gatewayServer = _serverMap[module.name];
                        gatewayServer->StopServer();
                    }
                    log_debug << "Module " << module.name << " stopped";
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

            log_debug << "Entering main routine";

            // Start module and worker. Services needed to StartServer first, as the worker could possibly use the services.
            StartServices();

            // Start HTTP manager
            _restService.setRouter(_router);
            _restService.StartServer();

            // Wait for termination
            this->waitForTerminationRequest();
            log_debug << "Starting termination";

            return Application::EXIT_OK;
        }

    private:

        /**
         * Logger
         */
        Core::LogStream _logger = Core::LogStream("info");

        /**
         * Application configuration
         */
        Core::Configuration &_configuration = Core::Configuration::instance();

        /**
         * Monitoring module
         */
        Core::MetricService &_metricService = Core::MetricService::instance();

        /**
         * Gateway router
         */
        Controller::Router *_router = new Controller::Router(_configuration, _metricService, _serverMap);

        /**
         * S3 module
         */
        std::shared_ptr <Service::S3Server> _s3Server;

        /**
         * SQS module
         */
        std::shared_ptr <Service::SQSServer> _sqsServer;

        /**
         * SNS module
         */
        std::shared_ptr <Service::SNSServer> _snsServer;

        /**
         * Lambda module
         */
        std::shared_ptr <Service::LambdaServer> _lambdaServer;

        /**
         * Transfer module
         */
        std::shared_ptr <Service::TransferServer> _transferServer;

        /**
         * Cognito module
         */
        std::shared_ptr <Service::CognitoServer> _cognitoServer;

        /**
         * DynamoDb module
         */
        std::shared_ptr <Service::DynamoDbServer> _dynamoDbServer;

        /**
         * SecretsManager module
         */
        std::shared_ptr <Service::SecretsManagerServer> _secretsManagerServer;

        /**
         * Request gateway module
         */
        std::shared_ptr <Service::GatewayServer> _gatewayServer{};

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
