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
#include <cstdlib>

// C++ standard includes
#include <iostream>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/OptionProcessor.h>
#include <Poco/Util/ServerApplication.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/controller/Configuration.h>
#include <awsmock/controller/Controller.h>

namespace AwsMock::Controller {

  /**
   * Main application class.
   */
  class AwsMockCtl : public Poco::Util::Application {

    protected:

      /**
       * Initialization callback from Poco Application class.
       *
       * @param self application reference.
       */
      [[maybe_unused]] void initialize(Application &self) override {
        Poco::Util::Application::initialize(self);
      }

      /**
       * Shutdown the application. Gets called when the application is about to stop.
       */
      [[maybe_unused]] void uninitialize() override {

        Poco::Util::Application::uninitialize();
        log_debug << "Bye, bye, and thanks for all the fish";
      }

      /**
       * Define the command line options.
       *
       * @param options Poco options class.
       */
      [[maybe_unused]] void defineOptions(Poco::Util::OptionSet &options) override {

        Poco::Util::Application::defineOptions(options);
        options.addOption(Poco::Util::Option("config", "", "set the configuration file").required(false).repeatable(false).argument("file").callback(
          Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("pretty", "", "set the export pretty print flag").required(false).repeatable(false).argument("pretty").callback(
          Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("version", "", "display version information").required(false).repeatable(false).callback(
          Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("help", "", "display help information").required(false).repeatable(false).callback(
          Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
      }

      /**
       * Handles the command line options. Uses Poco command line optios handling.
       *
       * @param name command line option name.
       * @param value command line option value.
       */
      void handleOption(const std::string &name, const std::string &value) override {

        if (name == "help") {

          usage();

        } else if (name == "file") {

          _configuration.SetFilename(value);

        } else if (name == "version") {

          std::cout << "awsmockctl" << " " << Configuration::GetVersion();
          exit(0);

        } else if (name == "level") {

          _configuration.setString("awsmock.log.level", value);
          Poco::Logger::get("").setLevel(value);

        } else if (name == "pretty") {

          _configuration.setBool("awsmock.pretty", value == "true");

        }
      }

      void usage() {
        std::cout << std::endl;
        Poco::Util::HelpFormatter helpFormatter(options());
        helpFormatter.setHeader("\nAwsMock - AWS simulation written in C++ " + Configuration::GetVersion() + "\n\nOptions:");
        helpFormatter.setCommand(commandName());
        helpFormatter.setUsage("<options> <command>");
        helpFormatter.format(std::cout);
        std::cout << "\nCommands:\n" << std::endl;
        std::cout << "list\t\t\t: lists all available services" << std::endl;
        std::cout << "start [<module>]\t: starts the given module. If no argument is given, starts all services." << std::endl;
        std::cout << "stop [<module>]\t\t: stops the given module. If no argument is given, stops all services" << std::endl;
        std::cout << "restart [<module>]\t: restarts the given module. If no argument is given, restarts all services" << std::endl;
#ifdef HAS_SYSTEMD
        std::cout << "logs\t\t\t: shows the manager logs" << std::endl;
#endif
        std::cout << "loglevel <level>\t: sets the manager log to level" << std::endl;
        std::cout << "config\t\t\t: shows the gateway configuration" << std::endl;
        std::cout << "export [modules]\t: dumps the current infrastructure to stdout. Modules is a space separated list of module names." << std::endl;
        std::cout << "import\t\t\t: imports the infrastructure from stdin." << std::endl;
        std::cout << "clean [modules]\t\t: cleans the current infrastructure. Modules is a space separated list of module names." << std::endl;
        std::cout << "\nModules:\n" << std::endl;
        std::cout << "Valid modules are: all, s3, sqs, sns, lambda, transfer, cognito, dynamodb." << std::endl;
        stopOptionsProcessing();
        exit(0);
      }

      int ProcessCommand(const ArgVec &args) {

        const std::string &name = args[0];
        if(name == "awsmockctl") {

          usage();

        } else if (name == "list") {

          _controller.ListServices();

        } else if (name == "start") {

          _controller.StartService(args[1]);

        } else if (name == "restart") {

          _controller.RestartService(args[1]);

        } else if (name == "stop") {

          _controller.StopService(args[1]);

#ifdef HAS_SYSTEMD
        } else if (name == "logs") {

          AwsMock::Controller::Controller::ShowServiceLogs();
#endif
        } else if (name == "loglevel") {

          _controller.SetLogLevel(args[1]);

        } else if (name == "config") {

          _controller.GetDefaults();

        } else if (name == "export") {

          bool pretty = _configuration.getBool("awsmock.pretty");
          std::vector<std::string> services = {args.begin() + 1, args.end()};
          if (services.empty()) {
            services.emplace_back("all");
          }
          _controller.ExportInfrastructure(services, pretty);

        } else if (name == "import") {

          _controller.ImportInfrastructure();

        } else if (name == "clean") {

          std::vector<std::string> services = {args.begin() + 1, args.end()};
          if (services.empty()) {
            services.emplace_back("all");
          }
          _controller.CleanInfrastructure(services);

        } else {

          std::cerr << "Unknown command: " << name << std::endl;
          usage();

        }
        return 0;
      }

      /**
       * Main routine.
       *
       * @param args command line arguments.
       * @return system exit code.
       */
      int main([[maybe_unused]]const ArgVec &args) override {

        return ProcessCommand(args);
      }

    private:

      /**
       * Application configuration
       */
      Configuration _configuration = Configuration(CONFIGURATION_BASE_PATH);

      /**
       * Controller
       */
      Controller _controller = Controller(_configuration);

  };

} // namespace AwsMock

#ifndef TESTING

POCO_APP_MAIN(AwsMock::Controller::AwsMockCtl)

#endif
