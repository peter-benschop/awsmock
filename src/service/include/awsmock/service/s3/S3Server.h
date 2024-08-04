//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_SERVER_H
#define AWSMOCK_SERVICE_S3_SERVER_H

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/NotFoundException.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/s3/S3Monitoring.h>
#include <awsmock/service/s3/S3Service.h>
#include <awsmock/service/s3/S3Worker.h>

#define S3_DEFAULT_PORT 9500
#define S3_DEFAULT_HOST "localhost"
#define S3_DEFAULT_QUEUE_SIZE 250
#define S3_DEFAULT_MAX_THREADS 50
#define S3_DEFAULT_TIMEOUT 900
#define S3_DEFAULT_MONITORING_PERIOD 300
#define S3_DEFAULT_WORKER_PERIOD 3600

namespace AwsMock::Service {

    /**
     * @brief S3 HTTP server
     *
     * The S3 HTTP server gates the requests from the gateway, which acts like a API gateway. The S3 default port is 9500 and can set in the AwsMOck configuration file
     * `/etc/awsmock.properties`
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Server : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit S3Server();

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
         * @brief Create FTP transfer bucket
         */
        void CreateTransferBucket();

        /**
         * @brief Checks whether a bucket exists
         *
         * @param region AWS region
         * @param bucketName name of the bucket
         */
        bool BucketExists(const std::string &region, const std::string &bucketName);

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
         * S3 monitoring
         */
        std::shared_ptr<S3Monitoring> _s3Monitoring;

        /**
         * S3 worker
         */
        std::shared_ptr<S3Worker> _s3Worker;

        /**
         * S3 service
         */
        S3Service _s3Service;

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

#endif// AWSMOCK_SERVICE_S3_SERVER_H
