//
// Created by vogje01 on 20/12/2023.
//

#ifndef AWSMOCK_SERVER_DYNAMODB_SERVER_H
#define AWSMOCK_SERVER_DYNAMODB_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/repository/DynamoDbDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/docker/DockerService.h>
#include <awsmock/service/dynamodb/DynamoDbMonitoring.h>
#include <awsmock/service/dynamodb/DynamoDbWorker.h>

#define DYNAMODB_DEFAULT_MONITORING_PERIOD 300
#define DYNAMODB_DEFAULT_WORKER_PERIOD 300
#define DYNAMODB_DOCKER_IMAGE std::string("dynamodb-local")
#define DYNAMODB_DOCKER_TAG std::string("latest")
#define DYNAMODB_DOCKER_PORT 8000
#define DYNAMODB_DOCKER_HOST "localhost"
#define DYNAMODB_DOCKER_FILE "FROM amazon/dynamodb-local:latest\n"                           \
                             "VOLUME /home/awsmock/data/dynamodb /home/dynamodblocal/data\n" \
                             "WORKDIR /home/dynamodblocal\n"                                 \
                             "EXPOSE 8000 8000\n"                                            \
                             "ENTRYPOINT [\"java\", \"-Djava.library.path=./DynamoDBLocal_lib\", \"-jar\", \"DynamoDBLocal.jar\", \"-sharedDb\"]\n"

namespace AwsMock::Service {

    /**
     * @brief AwsMock DynamoDB server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DynamoDbServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit DynamoDbServer(Core::PeriodicScheduler &scheduler);

        /**
         * @brief Initialization
         */
        void Initialize();

      protected:

        /**
         * @brief Main method
         */
        void Run();

        /**
         * @brief Shutdown
         */
        void Shutdown();

      private:

        /**
         * @brief Delete dangling, stopped containers
         */
        void CleanupContainers();

        /**
         * @brief Start the local DynamoDB container.
         *
         * <p>
         * If the AWS DynamoDb docker image does not already exists, it will be downloaded. Otherwise the local docker
         * image will be started as container.
         * </p>
         */
        void StartLocalDynamoDb();

        /**
         * @brief Stop the local DynamoDB container.
         *
         * <p>
         * The AWS DynamoDb docker container will be stopped.
         * </p>
         */
        void StopLocalDynamoDb();

        /**
         * Docker module
         */
        Service::DockerService &_dockerService;

        /**
         * Monitoring
         */
        DynamoDbMonitoring _dynamoDbMonitoring;

        /**
         * Monitoring
         */
        DynamoDbWorker _dynamoDbWorker;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;

        /**
         * Worker period
         */
        int _workerPeriod;

        /**
         * Dynamo DB docker host
         */
        std::string _dockerHost;

        /**
         * Dynamo DB docker host
         */
        int _dockerPort;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVER_DYNAMODB_SERVER_H
