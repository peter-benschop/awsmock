//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_SERVER_H
#define AWSMOCK_SERVICE_LAMBDA_SERVER_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/dto/lambda/mapper/Mapper.h>
#include <awsmock/dto/lambda/model/InvocationNotification.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/ModuleDatabase.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/lambda/LambdaCreator.h>
#include <awsmock/service/lambda/LambdaExecutor.h>
#include <awsmock/service/lambda/LambdaMonitoring.h>
#include <awsmock/service/lambda/LambdaWorker.h>
#include <awsmock/service/s3/S3Service.h>

#define LAMBDA_DEFAULT_PORT 9503
#define LAMBDA_DEFAULT_HOST "localhost"
#define LAMBDA_DEFAULT_QUEUE 150
#define LAMBDA_DEFAULT_THREADS 50
#define LAMBDA_DEFAULT_TIMEOUT 120
#define LAMBDA_DEFAULT_MONITORING_PERIOD 300
#define LAMBDA_DEFAULT_WORKER_PERIOD 300

namespace AwsMock::Service {

    /**
     * @brief Lambda server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class LambdaServer : public AbstractServer {

      public:

        /**
         * Constructor
         *
         * @param pool global thread pool
         */
        explicit LambdaServer(boost::asio::thread_pool &pool);

        /**
         * Initialization
         */
        void Initialize() override;

      protected:

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
         * Start all lambdas if they are not existing
         */
        void StartLambdaFunctions();

        /**
         * Returns the code from a local file.
         *
         * <p>The code will provided as a Base64 encoded zip file.</p>
         *
         * @param lambda lambda to get the code from.
         * @return Dto::lambda::Code
         */
        Dto::Lambda::Code GetCode(const Database::Entity::Lambda::Lambda &lambda);

        /**
         * lambda database
         */
        Database::LambdaDatabase &_lambdaDatabase;

        /**
         * lambda module
         */
        std::unique_ptr<Service::LambdaService> _lambdaService;

        /**
         * Docker module
         */
        std::unique_ptr<Service::DockerService> _dockerService;

        /**
         * Monitoring
         */
        std::shared_ptr<LambdaMonitoring> _lambdaMonitoring;

        /**
         * Lambda worker
         */
        std::shared_ptr<LambdaWorker> _lambdaWorker;

        /**
         * Global thread pool
         */
        boost::asio::thread_pool &_pool;

        /**
         * Data dir
         */
        std::string _lambdaDir;

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
         * Lambda module host
         */
        std::string _lambdaServiceHost;

        /**
         * Lambda module port
         */
        int _lambdaServicePort;

        /**
         * Module name
         */
        std::string _module;

        /**
         * Monitoring period
         */
        int _monitoringPeriod;

        /**
         * Worker period
         */
        int _workerPeriod;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_LAMBDA_SERVER_H
