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
#include <awsmock/core/HttpSocket.h>
#include <awsmock/core/HttpSocketResponse.h>
#include <awsmock/dto/module/GatewayConfig.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/dto/transfer/model/Server.h>
#include <awsmock/dto/transfer/model/User.h>
#include <awsmock/repository/ModuleDatabase.h>

#define AWSMOCKCTL_DEFAULT_HOST "localhost"
#define AWSMOCKCTL_DEFAULT_PORT 4566
#define AWSMOCKCTL_DEFAULT_USER "none"
#define AWSMOCKCTL_DEFAULT_CLIENT "00000000"
#define AWSMOCKCTL_DEFAULT_REGION "eu-central-1"

namespace AwsMock::Controller {

    /**
     * @brief AwsMock controller
     *
     * @par
     * AwsMock controller, which sends commands to the awsmock manager. Default port is 4567, but can be changed in the awsmock properties file.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class AwsMockCtl {

      public:

        /**
         * @brief Constructor
         */
        explicit AwsMockCtl();

        /**
         * @brief Initialization
         *
         * @param vm vector of command line options
         * @param commands vector of commands
         */
        void Initialize(boost::program_options::variables_map vm, const std::vector<std::string> &commands);

        /**
         * @brief Main method
         */
        void Run();

        /**
         * @brief List all available services
         */
        void ListServices();

        /**
         * @brief Start a module
         *
         * @param modules list of modules names
         */
        void StartService(std::vector<Dto::Module::Module> &modules);

        /**
         * @brief Restart a module
         *
         * @param modules list of modules names
         */
        void RestartService(std::vector<Dto::Module::Module> &modules);

        /**
         * @brief Stops a module
         *
         * @param modules list of modules names
         */
        void StopService(std::vector<Dto::Module::Module> &modules);

#ifdef HAS_SYSTEMD
        /**
         * @brief Show the logs
         */
        static void ShowServiceLogs();
#endif

        /**
         * @brief Sets the managers log level
         *
         * @param level log level
         */
        void SetLogLevel(const std::string &level);

        /**
         * @brief Returns the current AwsMock configuration
         */
        void GetConfig();

        /**
         * @brief Dumps the current infrastructure as JSON file to stdout.
         *
         * @param modules list of modules
         * @param pretty JSON pretty print (indent=4)
         * @param includeObjects include also objects
         */
        void ExportInfrastructure(Dto::Module::Module::ModuleList &modules, bool pretty = true, bool includeObjects = false);

        /**
         * @brief Imports the current infrastructure from stdin
         */
        void ImportInfrastructure();

        /**
         * @brief Cleans the current infrastructure.
         *
         * @param modules list of modules
         */
        void CleanInfrastructure(Dto::Module::Module::ModuleList &modules);

        /**
         * @brief Cleans the objects of the given modules
         *
         * @param modules list of modules
         */
        void CleanObjects(Dto::Module::Module::ModuleList &modules);

        /**
         * @brief Show FTP users.
         *
         * As the AWS CLI does not allow to see the users password, this is a workaround. It will send a FTP user list
         * request to the server and shows the currently defined FTP users.
         *
         * @param serverId ID of the FTP server.
         */
        void ShowFtpUsers(const std::string &serverId);

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
