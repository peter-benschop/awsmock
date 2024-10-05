//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_MONITORING_SERVER_H
#define AWSMOCK_SERVICE_MONITORING_SERVER_H

// Boost includes
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/NotFoundException.h>
#include <awsmock/monitoring/MetricService.h>
#include <awsmock/monitoring/MetricSystemCollector.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/monitoring/MonitoringService.h>

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
        explicit MonitoringServer(boost::asio::thread_pool &pool);

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
         * Module name
         */
        std::string _module;

        /**
         * Metric service
         */
        std::shared_ptr<Monitoring::MetricService> _metricService;

        /**
         * Monitoring system collector
         */
        std::shared_ptr<Monitoring::MetricSystemCollector> _metricSystemCollector;

        /**
         * Global thread pool
         */
        boost::asio::thread_pool &_pool;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_MONITORING_SERVER_H
