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

// AwsMock includes
#include <awsmock/controller/Configuration.h>
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CurlUtils.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/dto/common/Services.h>
#include <awsmock/dto/module/GatewayConfig.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/repository/ModuleDatabase.h>

#define AWSMOCKCTL_DEFAULT_HOST "localhost"
#define AWSMOCKCTL_DEFAULT_PORT 4567
#define AWSMOCKCTL_DEFAULT_USER "none"
#define AWSMOCKCTL_DEFAULT_CLIENT "00000000"
#define AWSMOCKCTL_DEFAULT_REGION "eu-central-1"

namespace AwsMock::Controller {

    class Controller {

      public:

        /**
         * Constructor
         */
        explicit Controller(const Configuration &configuration);

        /**
         * List all available services
         */
        void ListServices();

        /**
         * Start a module
         *
         * @param name module name, or 'all'
         */
        void StartService(const std::string &name);

        /**
         * Restart a module
         *
         * @param name module name, or 'all'
         */
        void RestartService(const std::string &name);

        /**
         * Stops a module
         *
         * @param name module name, or 'all'
         */
        void StopService(const std::string &name);

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
        void GetDefaults();

        /**
         * Dumps the current infrastructure as JSON file to stdout.
         *
         * @param services list of services
         * @param pretty JSON pretty print (indent=4)
         * @param includeObjects include also objects
         */
        void ExportInfrastructure(const std::vector<std::string> &services, bool pretty = true, bool includeObjects = false);

        /**
         * Imports the current infrastructure from stdin
         */
        void ImportInfrastructure();

        /**
         * Cleans the current infrastructure.
         *
         * @param services list of services
         */
        void CleanInfrastructure(const std::vector<std::string> &services);

      private:

        /**
         * Add authorization header.
         *
         * @param headers headers
         */
        void AddAuthorization(std::map<std::string, std::string> &headers);

        /**
         * Application configuration
         */
        const Configuration &_configuration;

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
