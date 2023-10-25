//
// Created by vogje01 on 10/23/23.
//

#ifndef AWSMOCK_CONTROLLER_CONTROLLER_H
#define AWSMOCK_CONTROLLER_CONTROLLER_H

// C includes
#include <stdlib.h>

// C++ includes
#include <string>
#include <iostream>
#include <iomanip>

// Poco includes
#include <Poco/Logger.h>

// AwsMock includes
#include <awsmock/core/CurlUtils.h>
#include <awsmock/dto/module/Module.h>
#include <awsmock/controller/Configuration.h>
#include <awsmock/repository/ModuleDatabase.h>

#define AWSMOCKCTL_DEFAULT_HOST "localhost"
#define AWSMOCKCTL_DEFAULT_PORT 4567

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
       * @param name service name
       */
      void StartService(const std::string &name);

      /**
       * Stops a service
       *
       * @param name service name
       */
      void StopService(const std::string &name);

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
       * Service database
       */
      std::shared_ptr<Database::ModuleDatabase> _serviceDatabase;

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
  };

} // namespace AwsMock::Controller

#endif // AWSMOCK_CONTROLLER_CONTROLLER_H
