//
// Created by vogje01 on 06/10/2023.
//

#ifndef AWSMOCK_SERVICE_SNSSERVER_H
#define AWSMOCK_SERVICE_SNSSERVER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sns/SNSHandlerFactory.h>

#define SNS_DEFAULT_PORT 9502
#define SNS_DEFAULT_HOST "localhost"
#define SNS_DEFAULT_QUEUE_LENGTH  250
#define SNS_DEFAULT_THREADS 50
#define SNS_DEFAULT_TIMEOUT 120
#define SNS_DEFAULT_MESSAGE_TIMEOUT 14

namespace AwsMock::Service {

    class SNSServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         * @param metricService aws-mock monitoring module
         */
        explicit SNSServer(Core::Configuration &configuration, Core::MetricService &metricService);

        /**
         * Initialization
         */
        void Initialize() override;

        /**
         * Main method
         */
        void Run() override;

        /**
         * Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * Update metric counters
         */
        void UpdateCounters();

        /**
         * Delete old messages
         */
        void DeleteOldMessages();

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * Metric module
         */
        Core::MetricService &_metricService;

        /**
         * S3 module
         */
        Database::SNSDatabase &_snsDatabase;

        /**
         * AWS region
         */
        std::string _region;

        /**
         * Sleeping period in ms
         */
        int _period;

        /**
         * Rest port
         */
        int _port;

        /**
         * Rest host
         */
        std::string _host;

        /**
         * HTTP max message queue length
         */
        int _maxQueueLength;

        /**
         * HTTP max concurrent connections
         */
        int _maxThreads;

        /**
         * HTTP request timeout in seconds
         */
        int _requestTimeout;

        /**
         * Message timeout in seconds
         */
        int _messageTimeout;
    };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SNSSERVER_H
