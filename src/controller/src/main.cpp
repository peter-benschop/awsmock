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
#include <Poco/Util/HelpFormatter.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/ServerApplication.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/controller/Configuration.h>
#include <awsmock/repository/Database.h>
#include "awsmock/controller/Controller.h"

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

        //log_info_stream(_logger) << "Starting " << Configuration::GetAppName() << " " << Configuration::GetVersion() << " pid: " << getpid() << " loglevel: "
//                                 << _configuration.GetLogLevel() << std::endl;
        //      log_info_stream(_logger) << "Configuration file: " << _configuration.GetFilename() << std::endl;
        Poco::Util::Application::initialize(self);
      }

      /**
       * Shutdown the application. Gets called when the application is about to stop.
       */
      [[maybe_unused]] void uninitialize() override {

        Poco::Util::Application::uninitialize();
        log_debug_stream(_logger) << "Bye, bye, and thanks for all the fish" << std::endl;
      }

      /**
       * Define the command line options.
       *
       * @param options Poco options class.
       */
      [[maybe_unused]] void defineOptions(Poco::Util::OptionSet &options) override {

        Poco::Util::Application::defineOptions(options);
        options.addOption(Poco::Util::Option("config", "", "set the configuration file").required(false).repeatable(false).argument("value").callback(
            Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("level", "", "set the log level").required(false).repeatable(false).argument("value").callback(
            Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("version", "", "display version information").required(false).repeatable(false).callback(
            Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("list", "", "list all services").required(false).repeatable(false).callback(
            Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("start", "", "starts a service").required(false).repeatable(false).argument("value").callback(
            Poco::Util::OptionCallback<AwsMockCtl>(this, &AwsMockCtl::handleOption)));
        options.addOption(Poco::Util::Option("stop", "", "stops a service").required(false).repeatable(false).argument("value").callback(
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

          std::cout << "awsmockctl" << " " << Configuration::GetVersion() << std::endl;
          exit(0);

        } else if (name == "level") {

          _configuration.SetLogLevel(value);
          Poco::Logger::get("").setLevel(value);

        } else if (name == "list") {

          _controller.ListServices();

        } else if (name == "start") {

          _controller.StartService(value);

        } else if (name == "stop") {

          _controller.StopService(value);
        }

      }

      /**
       * Main routine.
       *
       * @param args command line arguments.
       * @return system exit code.
       */
      int main([[maybe_unused]]const ArgVec &args) override {
        return 0;
      }

    private:

      /**
       * Logger
       */
      Core::LogStream _logger = Core::LogStream(Poco::Logger::get("Gateway"));

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
