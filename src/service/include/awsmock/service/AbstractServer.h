//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_ABSTRACTSERVER_H
#define AWSMOCK_SERVICE_ABSTRACTSERVER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/repository/ServiceDatabase.h>

namespace AwsMock::Service {

  class AbstractServer : public Poco::Runnable {

    public:

      /**
       * Constructor
       *
       * @param configuration AwsMock configuration
       * @param condition stop condition
       */
      explicit AbstractServer(const Core::Configuration &configuration, Poco::Condition &condition);

      /**
       * Checks whether the service is active
       *
       * @param url HTTP URL
       * @param body HTTP message body
       * @param contentType HTTP content type
       */
      bool IsActive(const std::string &name);

      /**
       * Main thread methods
       */
      void run() override;

    protected:

      /**
       * Main loop
       */
      virtual void MainLoop() = 0;

      /**
       * Interruptable sleep
       */
      bool InterruptableSleep(int period);

      /**
       * Shutdown condition
       */
      Poco::Condition &_condition;

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Service database
       */
      std::unique_ptr<Database::ServiceDatabase> _serviceDatabase;

      /**
       * Shutdown mutex
       */
      Poco::Mutex _mutex;

      /**
       * Running flag
       */
      bool _running;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_ABSTRACTSERVER_H
