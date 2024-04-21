//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_SQS_SERVER_H
#define AWSMOCK_SERVICE_SQS_SERVER_H

// C++ standard includes
#include <string>
#include <chrono>
#include <condition_variable>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Runnable.h>
#include <Poco/SignalHandler.h>
#include <Poco/Condition.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ThreadPool.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/repository/SQSDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/sqs/SQSHandlerFactory.h>
#include <awsmock/service/sqs/SQSMonitoring.h>

#define SQS_DEFAULT_PORT 9501
#define SQS_DEFAULT_HOST "localhost"
#define SQS_DEFAULT_QUEUE_LENGTH  250
#define SQS_DEFAULT_THREADS 50
#define SQS_DEFAULT_TIMEOUT 120
#define SQS_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    class SQSServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit SQSServer(Core::Configuration &configuration);

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
         * Reset messages
         *
         * <p>Loops over all SQS queues and sets the state to INITIAL in case the visibilityTimeout timeout has been reached. Also the retry count in increased by one.</p>
         * <p>Checks also the expiration date and removed the messages, which are older than the max retention period.</>
         */
        void ResetMessages();

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * SQS database
         */
        Database::SQSDatabase &_sqsDatabase;

        /**
         * SQS monitoring
         */
        std::shared_ptr<SQSMonitoring> _sqsMonitoring;

        /**
         * AWS region
         */
        std::string _region;

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
         * SQS monitoring period
         */
        int _monitoringPeriod;
    };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SQS_SERVER_H
