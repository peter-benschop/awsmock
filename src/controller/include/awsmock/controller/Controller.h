//
// Created by vogje01 on 10/23/23.
//

#ifndef AWSMOCK_CONTROLLER_CONTROLLER_H
#define AWSMOCK_CONTROLLER_CONTROLLER_H

// C includes
#include <systemd/sd-journal.h>
#include <systemd/sd-daemon.h>

// C++ includes
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>

// Poco includes
#include <Poco/Logger.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CurlUtils.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/controller/Configuration.h>
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
       * Start a service
       *
       * @param name service name, or 'all'
       */
      void StartService(const std::string &name);

      /**
       * Restart a service
       *
       * @param name service name, or 'all'
       */
      void RestartService(const std::string &name);

      /**
       * Stops a service
       *
       * @param name service name, or 'all'
       */
      void StopService(const std::string &name);

      /**
       * Show the logs
       */
      void ShowServiceLogs();

      /**
       * Sets the managers log level
       *
       * @param level log level
       */
      void SetLogLevel(const std::string &level);

    private:
      /**
       * Add authorization header.
       *
       * @param headers headers
       */
      void AddAuthorization(std::map<std::string, std::string> &headers);

      /**
       * Logger
       */
      Core::LogStream _logger;

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

} // namespace AwsMock::Controller

#endif // AWSMOCK_CONTROLLER_CONTROLLER_H
