//
// Created by vogje01 on 4/21/24.
//

#ifndef AWSMOCK_SERVICE_MONITORING_WORKER_H
#define AWSMOCK_SERVICE_MONITORING_WORKER_H

// AwsMock includes
#include <awsmock/core/Timer.h>
#include <awsmock/repository/MonitoringDatabase.h>

#define DEFAULT_RETENTION_PERIOD 3

namespace AwsMock::Service::Monitoring {

    /**
     * @brief Monitoring worker thread
     *
     * @par
     * Used as background thread to do maintenance work, like resetting deleting monitoring data after the retention period. The different methods are
     * called periodical by the scheduler. Each method can have a different periodic period.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class MonitoringWorker {

      public:

        /**
         * @brief Constructor
         */
        explicit MonitoringWorker() = default;

        /**
         * @brief Delete monitoring data older than the retention period.
         *
         * @par
         * Delete al monitoring data oder than the retention period. Default is 3 days, which means monitoring data older than 3 days will be deleted.
         */
        [[maybe_unused]] void DeleteMonitoringData();

      private:

        /**
         * Database connection
         */
        Database::MonitoringDatabase &_monitoringDatabase = Database::MonitoringDatabase::instance();
    };

}// namespace AwsMock::Service::Monitoring

#endif// AWSMOCK_SERVICE_MONITORING_WORKER_H
