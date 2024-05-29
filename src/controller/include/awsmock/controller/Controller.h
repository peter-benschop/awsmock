//
// Created by vogje01 on 10/23/23.
//

#ifndef AWSMOCK_CONTROLLER_CONTROLLER_H
#define AWSMOCK_CONTROLLER_CONTROLLER_H

// C includes
#ifdef HAS_SYSTEMD
#include <systemd/sd-daemon.h>
#include <systemd/sd-journal.h>
#endif

// C++ includes
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Boost includes
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CurlUtils.h>
#include <awsmock/core/HttpSocket.h>
#include <awsmock/core/HttpSocketResponse.h>
#include <awsmock/dto/module/GatewayConfig.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/repository/ModuleDatabase.h>

#define AWSMOCKCTL_DEFAULT_HOST "localhost"
#define AWSMOCKCTL_DEFAULT_PORT 4567
#define AWSMOCKCTL_DEFAULT_USER "none"
#define AWSMOCKCTL_DEFAULT_CLIENT "00000000"
#define AWSMOCKCTL_DEFAULT_REGION "eu-central-1"

namespace AwsMock::Controller {

    class AwsMockCtl {

      public:

        /**
         * Constructor
         */
        explicit AwsMockCtl();

        /**
         * Initialization
         *
         * @param vm vector of command line options
         * @param command vector of commands
         */
        void Initialize(boost::program_options::variables_map vm, const std::vector<std::string> &commands);

        /**
         * Initialization
         */
        void Run();

        /**
         * List all available services
         */
        void ListServices();

        /**
         * Start a module
         *
         * @param services list of service names
         */
        void StartService(std::vector<Dto::Module::Module> &nmodules);

        /**
         * Restart a module
         *
         * @param services list of service names
         */
        void RestartService(std::vector<Dto::Module::Module> &nmodules);

        /**
         * Stops a module
         *
         * @param services list of service names
         */
        void StopService(std::vector<Dto::Module::Module> &nmodules);

#ifdef HAS_SYSTEMD
        /**
         * Show the logs
         */
        static void ShowServiceLogs();
#endif

        /**
         * Sets the managers log level
         *
         * @param level log level
         */
        void SetLogLevel(const std::string &level);

        /**
         * Returns the current AwsMock configuration
         */
        void GetConfig();

        /**
         * Dumps the current infrastructure as JSON file to stdout.
         *
         * @param modules list of modules
         * @param pretty JSON pretty print (indent=4)
         * @param includeObjects include also objects
         */
        void ExportInfrastructure(Dto::Module::Module::ModuleList &modules, bool pretty = true, bool includeObjects = false);

        /**
         * Imports the current infrastructure from stdin
         */
        void ImportInfrastructure();

        /**
         * @brief Cleans the current infrastructure.
         *
         * @param services list of services
         */
        void CleanInfrastructure(const std::vector<std::string> &services);

        /**
         * @brief Cleans the objects of the given modules
         *
         * @param modules list of modules
         */
        void CleanObjects(Dto::Module::Module::ModuleList &modules);

      private:

        /**
         * @brief Add authorization header.
         *
         * @param headers headers
         * @param action action to perform
         */
        void AddStandardHeaders(std::map<std::string, std::string> &headers, const std::string &action);

        /**
         * @brief Get a list of all modules.
         *
         * @return list of all modules.
         */
        Dto::Module::Module::ModuleList GetAllModules();

        /**
         * Commands
         */
        std::vector<std::string> _commands;

        /**
         * Command line options
         */
        boost::program_options::variables_map _vm;

        /**
         * Curl utils
         */
        Core::CurlUtils _curlUtils;

        /**
         * Host
         */
        std::string _host;

        /**
         * Port
         */
        int _port;

        /**
         * Base URL
         */
        std::string _baseUrl;

        /**
         * User
         */
        std::string _user;

        /**
         * Client ID
         */
        std::string _clientId;

        /**
         * AWS region
         */
        std::string _region;
    };

}// namespace AwsMock::Controller

#endif// AWSMOCK_CONTROLLER_CONTROLLER_H
