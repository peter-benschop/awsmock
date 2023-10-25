//
// Created by vogje01 on 22/08/2022.
//

#ifndef AWS_MOCK_CONFIGURATION_H
#define AWS_MOCK_CONFIGURATION_H

// Standard C++ includes
#include <string>

// Poco includes
#include "Poco/Logger.h"

// AwsMock includes
#include "awsmock/core/Configuration.h"

#define CONFIGURATION_BASE_PATH std::string("/etc/aws-mock.properties")

namespace AwsMock {

    /**
     * Onix splitting service configuration handler. Configurations are read from the /etc/ directory. By default the class will read a configuration file called
     * /etc/onix-splitting-service-&lt;profile&gt;.properties. The configuration files can be chosen using the profile, running with profile 'dev' will read
     * /etc/onix-splitting-service-dev.properties.
     * <p>
     * Supported profile are:
     * <pre>
     * dev: development environment
     * int: integration environment
     * prod: production environment
     * localstack: localstack environment
     * </pre>
     * </p>
     * <p>
     * AWS properties:
     * <pre>
     * awsmock.region=eu-central-1
     * awsmock.endpoint=http://localhost:4566
     * awsmock.request.timeout=300000
     * awsmock.connect.timeout=10000
     * </pre>
     * </p>
     * <p>
     * Thread pool configuration:
     * <pre>
     * awsmock.threadpool.initial=1
     * awsmock.threadpool.max=32
     * awsmock.threadpool.timeout=60
     * awsmock.processor.timeout=300000
     * </pre>
     * </p>
     * Prometheus monitoring:
     * <p>
     * <pre>
     * awsmock.monitoring.port=8081
     * awsmock.monitoring.timeout=60000
     * </pre>
     * </p>
     * <p>
     * Logging properties:
     * <pre>
     * monitoring.log.level=debug
     * </pre>
     * </p>
     */
    class Configuration : public Core::Configuration {
    public:

      /**
       * Constructor
       */
      Configuration();

      /**
       * Constructor.
       *
       * @param basename base name of the configuration file.
       */
      explicit Configuration(const std::string &basename);

      /**
       * Initialize the configuration and add the default configuration options.
       */
      void InitializeConfig();

    private:
      /**
       * Logger
       */
      Poco::Logger &_logger = Poco::Logger::get("Configuration");
    };
}
#endif //AWS_MOCK_CONFIGURATION_H
