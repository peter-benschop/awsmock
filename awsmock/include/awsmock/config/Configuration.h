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
     * aws.region=eu-central-1
     * aws.endpoint=http://localhost:4566
     * aws.request.timeout=300000
     * aws.connect.timeout=10000
     * </pre>
     * </p>
     * <p>
     * AWS Queues und S3 buckets
     * <pre>
     * libri.sqs.input.queue.name=ftp-file-distribution-onix-queue
     * libri.sqs.input.messages.max=10
     * libri.sqs.input.messages.waittime=5
     * libri.sqs.input.messages.request.timeout=30000
     * libri.sqs.input.messages.connect.timeout=30000
     * libri.sns.topic.name=file-logging-topic
     * libri.s3.input.bucket=pim-dev-file-delivery
     * libri.s3.full.parsing.output.bucket=pim-dev-splitter-test
     * </pre>
     * </p>
     * <p>
     * XSLT configuration
     * <pre>
     * libri.xslt.ref.to.short.v2=/etc/Onix2RefToShort.xsl
     * libri.xslt.ref.to.short.v3=etc/Onix3RefToShort.xsl
     * libri.xslt.onix2.onix3=/etc/Onix2ToOnix3.xsl
     * </pre>
     * </p>
     * <p>
     * Thread pool configuration:
     * <pre>
     * libri.threadpool.initial=1
     * libri.threadpool.max=32
     * libri.threadpool.timeout=60
     * libri.processor.timeout=300000
     * </pre>
     * </p>
     * Prometheus monitoring:
     * <p>
     * <pre>
     * libri.prometheus.port=8081
     * libri.prometheus.system.collector.timeout=60000
     * </pre>
     * </p>
     * <p>
     * Logging properties:
     * <pre>
     * libri.logging.level=debug
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
