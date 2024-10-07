//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_MONITORING_SERVER_H
#define AWSMOCK_SERVICE_MONITORING_SERVER_H

// Boost includes
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/bind/bind.hpp>

// AwsMock includes
#include "MetricService.h"
#include "MetricSystemCollector.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/NotFoundException.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/monitoring/MonitoringService.h>
#include <awsmock/service/monitoring/MonitoringWorker.h>

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
         * Monitoring system collector
         */
        AwsMock::Monitoring::MetricService _metricService;

        /**
         * Monitoring system collector
         */
        AwsMock::Monitoring::MetricSystemCollector _metricSystemCollector;

        /**
         * Monitoring system collector
         */
        Monitoring::MonitoringWorker _monitoringWorker;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_MONITORING_SERVER_H
