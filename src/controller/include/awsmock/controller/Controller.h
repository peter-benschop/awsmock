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
#include <awsmock/controller/Configuration.h>
#include <awsmock/repository/ServiceDatabase.h>

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

    private:

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
      std::shared_ptr<Database::ServiceDatabase> _serviceDatabase;
  };

} // namespace AwsMock::Controller

#endif // AWSMOCK_CONTROLLER_CONTROLLER_H
