//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_MONITORING_SERVER_H
#define AWSMOCK_SERVICE_MONITORING_SERVER_H

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/NotFoundException.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/monitoring/MonitoringService.h>
//#include <awsmock/service/monitoring/MonitoringWorker.h>

#define S3_DEFAULT_PORT 9500
#define S3_DEFAULT_HOST "localhost"
#define S3_DEFAULT_QUEUE_SIZE 250
#define S3_DEFAULT_MAX_THREADS 50
#define S3_DEFAULT_TIMEOUT 900
#define S3_DEFAULT_MONITORING_PERIOD 300
#define S3_DEFAULT_WORKER_PERIOD 3600

namespace AwsMock::Service {

    /**
     * @brief Monitoring HTTP server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class MonitoringServer : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit MonitoringServer();

        /**
         * @brief Timer initialization
         */
        void Initialize() override;

        /**
         * @brief Timer main method
         */
        void Run() override;

        /**
         * @brief Shutdown
         */
        void Shutdown() override;

      private:

        /**
         * Rest port
         */
        int _port;

        /**
         * Rest host
         */
        std::string _host;

        /**
         * HTTP manager instance
         */
        std::shared_ptr<Poco::Net::HTTPServer> _httpServer;

        /**
         * Monitoring worker
         */
        //        std::shared_ptr<S3Worker> _s3Worker;

        /**
         * Monitoring service
         */
        MonitoringService _monitoringService;

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
         * Data directory
         */
        std::string _dataDir;

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

#endif// AWSMOCK_SERVICE_MONITORING_SERVER_H
