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
#include <awsmock/service/sns/SNSMonitoring.h>

#define SNS_DEFAULT_PORT 9502
#define SNS_DEFAULT_HOST "localhost"
#define SNS_DEFAULT_QUEUE_LENGTH  250
#define SNS_DEFAULT_THREADS 50
#define SNS_DEFAULT_TIMEOUT 120
#define SNS_DEFAULT_MESSAGE_TIMEOUT 14
#define SNS_DEFAULT_MONITORING_PERIOD 300

namespace AwsMock::Service {

    class SNSServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit SNSServer(Core::Configuration &configuration);

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
         * Delete old messages
         */
        void DeleteOldMessages();

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * SNS database
         */
        Database::SNSDatabase &_snsDatabase;

        /**
         * SNS monitoring
         */
        std::shared_ptr<SNSMonitoring> _snsMonitoring;

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

        /**
         * SNS monitoring period
         */
        int _monitoringPeriod;

    };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_SNSSERVER_H
