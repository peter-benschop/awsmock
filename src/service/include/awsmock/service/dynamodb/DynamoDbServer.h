//
// Created by vogje01 on 20/12/2023.
//

#ifndef AWSMOCK_SERVER_DYNAMODB_SERVER_H
#define AWSMOCK_SERVER_DYNAMODB_SERVER_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Condition.h>
#include <Poco/Logger.h>
#include <Poco/NotificationQueue.h>
#include <Poco/Runnable.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/repository/DynamoDbDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/dynamodb/DynamoDbHandlerFactory.h>
#include <awsmock/service/dynamodb/DynamoDbMonitoring.h>

#define DYNAMODB_DEFAULT_PORT 9507
#define DYNAMODB_DEFAULT_HOST "localhost"
#define DYNAMODB_DEFAULT_QUEUE 150
#define DYNAMODB_DEFAULT_THREADS 50
#define DYNAMODB_DEFAULT_TIMEOUT 120
#define DYNAMODB_DEFAULT_MONITORING_PERIOD 300
#define DYNAMODB_DOCKER_IMAGE std::string("dynamodb-local")
#define DYNAMODB_DOCKER_TAG std::string("latest")
#define DYNAMODB_INTERNAL_PORT 8000
#define DYNAMODB_EXTERNAL_PORT 8000
#define DYNAMODB_DOCKER_FILE "FROM amazon/dynamodb-local:latest\n"                           \
                             "VOLUME /home/awsmock/data/dynamodb /home/dynamodblocal/data\n" \
                             "WORKDIR /home/dynamodblocal\n"                                 \
                             "EXPOSE 8000 8000\n"                                            \
                             "ENTRYPOINT [\"java\", \"-Djava.library.path=./DynamoDBLocal_lib\", \"-jar\", \"DynamoDBLocal.jar\", \"-sharedDb\"]\n"

namespace AwsMock::Service {

    /**
     * AwsMock DynamoDB server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DynamoDbServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param configuration aws-mock configuration
         */
        explicit DynamoDbServer(Core::Configuration &configuration);

        /**
         * Destructor
         */
        ~DynamoDbServer() override;

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
         * Delete dangling, stopped containers
         */
        void CleanupContainers();

        /**
         * Start the local DynamoDB container.
         *
         * <p>
         * If the AWS DynamoDb docker image does not already exists, it will be downloaded. Otherwise the local docker
         * image will be started as container.
         * </p>
         */
        void StartLocalDynamoDb();

        /**
         * Stop the local DynamoDB container.
         *
         * <p>
         * The AWS DynamoDb docker container will be stopped.
         * </p>
         */
        void StopLocalDynamoDb();

        /**
         * Configuration
         */
        Core::Configuration &_configuration;

        /**
         * Docker module
         */
        std::unique_ptr<Service::DockerService> _dockerService;

        /**
         * Monitoring
         */
        std::shared_ptr<DynamoDbMonitoring> _dynamoDbMonitoring;

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
         * HTTP max concurrent connection
         */
        int _maxThreads;

        /**
         * HTTP request timeout in seconds
         */
        int _requestTimeout;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;

        /**
         * Module name
         */
        std::string _module;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVER_DYNAMODB_SERVER_H
