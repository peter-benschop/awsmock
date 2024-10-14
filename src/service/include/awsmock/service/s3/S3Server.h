//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_SERVER_H
#define AWSMOCK_SERVICE_S3_SERVER_H

// Boost includes
#include <boost/asio/thread_pool.hpp>
#include <boost/filesystem.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/s3/S3Service.h>

#define S3_DEFAULT_MONITORING_PERIOD 300
#define S3_DEFAULT_WORKER_PERIOD 3600

namespace AwsMock::Service {

    using namespace boost::filesystem;

    /**
     * @brief S3 module server
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Server : public AbstractServer {

      public:

        /**
         * @brief Constructor
         */
        explicit S3Server(Core::PeriodicScheduler &scheduler);

      private:

        /**
         * @brief Synchronize S3 object between filesystem and database.
         */
        [[maybe_unused]] void SyncObjects();

        /**
         * Update counters
         */
        void UpdateCounter();

        /**
         * Metric service
         */
        Monitoring::MetricService &_metricService = Monitoring::MetricService::instance();

        /**
         * Database connection
         */
        Database::S3Database &_s3Database = Database::S3Database::instance();

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
