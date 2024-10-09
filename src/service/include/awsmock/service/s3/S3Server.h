//
// Created by vogje01 on 04/01/2023.
//

#ifndef AWSMOCK_SERVICE_S3_SERVER_H
#define AWSMOCK_SERVICE_S3_SERVER_H

// Boost includes
#include <boost/asio/thread_pool.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/scheduler/PeriodicScheduler.h>
#include <awsmock/core/scheduler/PeriodicTask.h>
#include <awsmock/service/common/AbstractServer.h>
#include <awsmock/service/s3/S3Monitoring.h>
#include <awsmock/service/s3/S3Service.h>
#include <awsmock/service/s3/S3Worker.h>

#define S3_DEFAULT_MONITORING_PERIOD 300
#define S3_DEFAULT_WORKER_PERIOD 3600

namespace AwsMock::Service {

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
         * S3 monitoring
         */
        S3Monitoring _s3Monitoring;

        /**
         * S3 worker
         */
        S3Worker _s3Worker;

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
