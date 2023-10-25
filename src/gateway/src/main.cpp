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
#include <execinfo.h>
#include <csignal>
#include <cstdlib>

// C++ standard includes
#include <iostream>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/FileChannel.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ThreadErrorHandler.h>
#include <awsmock/config/Configuration.h>
#include <awsmock/controller/Router.h>
#include <awsmock/controller/RestService.h>
#include <awsmock/repository/Database.h>
#include <awsmock/service/LambdaServer.h>
#include <awsmock/service/S3Server.h>
#include <awsmock/service/SQSServer.h>
#include <awsmock/service/SNSServer.h>
#include <awsmock/service/TransferServer.h>

namespace AwsMock {

  /**
   * Main application class.
   */
  class AwsMock : public Poco::Util::ServerApplication {

    public:
      AwsMock() : _logger(Core::LogStream(Poco::Logger::get("Gateway"))) {}

    protected:

      /**
       * Initialization callback from Poco Application class.
       *
       * @param self application reference.
       */
      [[maybe_unused]] void initialize(Application &self) override {

        Core::LogStream::setConsoleChannel();
        log_info_stream(_logger) << "Starting " << Configuration::GetAppName() << " " << Configuration::GetVersion() << " pid: " << getpid() << " loglevel: "
                                 << _configuration.GetLogLevel() << std::endl;
        log_info_stream(_logger) << "Configuration file: " << _configuration.GetFilename() << std::endl;
        Poco::Util::ServerApplication::initialize(self);
      }

      /**
       * Shutdown the application. Gets called when the application is about to stop.
       */
      [[maybe_unused]] void uninitialize() override {

        // Shutdown all services
        _restService.StopServer();
        //_transferServer.StopMonitoringServer();

        // Shutdown monitoring
        _metricService.ShutdownServer();
        log_debug_stream(_logger) << "Metric manager stopped" << std::endl;

        //Poco::Util::Application::uninitialize();
        log_debug_stream(_logger) << "Bye, bye and thanks for all the fish" << std::endl;

        //Poco::Util::ServerApplication::terminate();
      }

      /**
       * Define the command line options.
       *
       * @param options Poco options class.
       */
      [[maybe_unused]] void defineOptions(Poco::Util::OptionSet &options) override {

        Poco::Util::ServerApplication::defineOptions(options);
        options.addOption(Poco::Util::Option("config", "", "set the configuration file").required(false).repeatable(false).argument("value").callback(
            Poco::Util::OptionCallback<AwsMock>(this, &AwsMock::handleOption)));
        options.addOption(Poco::Util::Option("loglevel", "", "set the log level").required(false).repeatable(false).argument("value").callback(
            Poco::Util::OptionCallback<AwsMock>(this, &AwsMock::handleOption)));
        options.addOption(Poco::Util::Option("logfile", "", "set the log file").required(false).repeatable(false).argument("value").callback(
            Poco::Util::OptionCallback<AwsMock>(this, &AwsMock::handleOption)));
        options.addOption(Poco::Util::Option("version", "", "display version information").required(false).repeatable(false).callback(
            Poco::Util::OptionCallback<AwsMock>(this, &AwsMock::handleOption)));
        options.addOption(Poco::Util::Option("help", "", "display help information").required(false).repeatable(false).callback(
            Poco::Util::OptionCallback<AwsMock>(this, &AwsMock::handleOption)));
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

          _configuration.SetLogLevel(value);
          Poco::Logger::root().setLevel(value);

        } else if (name == "logfile") {

          Core::LogStream::setFileChannel(value);
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

        // Start HTTP manager
        _restService.setRouter(_router);
        _restService.StartServer();

        // Wait for termination
        this->waitForTerminationRequest();
        return Application::EXIT_OK;
      }

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Application configuration
       */
      Configuration _configuration = Configuration(CONFIGURATION_BASE_PATH);

      /**
       * Monitoring service
       */
      Core::MetricService _metricService = Core::MetricService(_configuration);

      /**
       * Gateway router
       */
      std::shared_ptr<Controller::Router> _router = std::make_shared<Controller::Router>(_configuration, _metricService);

      /**
       * Gateway controller
       */
      RestService _restService = RestService(_configuration);
  };

} // namespace AwsMock

#ifndef TESTING

POCO_SERVER_MAIN (AwsMock::AwsMock)

#endif
