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

// C++ standard includes
#include <cstdlib>
#include <iostream>

// Boost includes
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

// AwsMock includes
#include <awsmock/controller/Controller.h>

#define DEFAULT_CONFIG_FILE "/etc/awsmock.properties"

/**
 * Main routine.
 *
 * @param argc number of command line arguments.
 * @param argv command line arguments.
 * @return system exit code.
 */
int main(int argc, char *argv[]) {

    // Initialize logging
    AwsMock::Core::LogStream::Initialize();

    // Declare the supported options.
    boost::program_options::options_description desc("Options");
    desc.add_options()("pretty", "produce JSON pretty output")("includeobjects", "include objects in export")("help", "produce help message")("version", "application version")("config", boost::program_options::value<std::string>(), "set configuration file")("loglevel", boost::program_options::value<std::string>(), "set log level")("logfile", boost::program_options::value<std::string>(), "set log file");

    // Get command line options
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    // Get commands
    std::vector<std::string> commands;
    for (int i = vm.size() + 1; i < argc; i++) {
        commands.emplace_back(argv[i]);
    }

    // Show usage
    if (vm.count("help")) {
        int leftIndent = 40;
        std::cout << std::endl
                  << "AwsMock controller v" << AwsMock::Core::Configuration::GetVersion() << std::endl
                  << std::endl
                  << "Usage: " << std::endl
                  << "  awsmockctl [Options] Commands" << std::endl
                  << std::endl
                  << desc << std::endl
                  << "Commands: " << std::endl
                  << std::left << std::setw(leftIndent) << "  list" << ": lists all available services" << std::endl
                  << std::left << std::setw(leftIndent) << "  start [<module>]" << ": starts the given module. If no argument is given, starts all services." << std::endl
                  << std::left << std::setw(leftIndent) << "  stop [<module>]" << ": stops the given module. If no argument is given, stops all services" << std::endl
                  << std::left << std::setw(leftIndent) << "  restart [<module>]" << ": restarts the given module. If no argument is given, restarts all services" << std::endl;
#ifdef HAS_SYSTEMD
        std::cout << std::left << std::setw(leftIndent) << "logs" << ": shows the manager logs" << std::endl;
#endif
        std::cout << std::left << std::setw(leftIndent) << "  loglevel <level>" << ": sets the manager log to level" << std::endl
                  << std::left << std::setw(leftIndent) << "  config" << ": shows the gateway configuration" << std::endl
                  << std::left << std::setw(leftIndent) << "  export [<modules>] [export-options]" << ": dumps the current infrastructure to stdout. Modules is a space separated list of module names." << std::endl
                  << std::left << std::setw(leftIndent) << "  import" << ": imports the infrastructure from stdin." << std::endl
                  << std::left << std::setw(leftIndent) << "  clean [modules]" << ": cleans the current infrastructure. Modules is a space separated list of module names." << std::endl
                  << std::left << std::setw(leftIndent) << "  cleanobjects [modules]" << ": cleans the objects from the module. Modules is a space separated list of module names." << std::endl
                  << "\nModules:\n"
                  << std::endl
                  << "Valid modules are: all, s3, sqs, sns, lambda, transfer, cognito, dynamodb, kms secretsmanager." << std::endl
                  << "\nExport options:\n"
                  << std::left << std::setw(leftIndent) << "  --includeObjects" << ": export objects as well" << std::endl
                  << std::left << std::setw(leftIndent) << "  --pretty" << ": indent output" << std::endl;
        return EXIT_SUCCESS;
    }

    // Show version
    if (vm.count("version")) {
        std::cout << std::endl
                  << "AwsMock controller v" << AwsMock::Core::Configuration::GetVersion() << std::endl
                  << std::endl;
        return EXIT_SUCCESS;
    }

    // Read configuration
    AwsMock::Core::Configuration &configuration = AwsMock::Core::Configuration::instance();
    if (vm.count("config")) {
        configuration.SetFilename(vm["config"].as<std::string>());
    } else {
        configuration.SetFilename(DEFAULT_CONFIG_FILE);
    }

    // Set log level
    if (vm.count("loglevel")) {
        std::string value = vm["loglevel"].as<std::string>();
        AwsMock::Core::Configuration::instance().setString("awsmock.service.logging.level", value);
        AwsMock::Core::LogStream::SetSeverity(value);
    } else {
        AwsMock::Core::LogStream::SetSeverity("info");
    }

    // Set log file
    if (vm.count("logfile")) {
        std::string value = vm["loglevel"].as<std::string>();
        AwsMock::Core::Configuration::instance().setString("awsmock.service.logging.level", value);
        AwsMock::Core::LogStream::SetSeverity(value);
    }

    // Start manager
    AwsMock::Controller::AwsMockCtl awsMockCtl;
    awsMockCtl.Initialize(vm, commands);
    awsMockCtl.Run();

    return EXIT_SUCCESS;
}
