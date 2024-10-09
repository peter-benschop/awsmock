//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/s3/S3Server.h>

namespace AwsMock::Service {

    S3Server::S3Server(Core::PeriodicScheduler &scheduler) : AbstractServer("s3") {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _monitoringPeriod = configuration.getInt("awsmock.service.s3.monitoring.period", S3_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = configuration.getInt("awsmock.service.s3.worker.period", S3_DEFAULT_WORKER_PERIOD);

        // Check module active
        if (!IsActive("s3")) {
            log_info << "S3 module inactive";
            return;
        }

        // Start SNS monitoring update counters
        scheduler.AddTask("monitoring-s3-counters", [this] { this->_s3Monitoring.UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        scheduler.AddTask("s3-sync-directories", [this] { this->_s3Worker.SyncObjects(); }, _workerPeriod);
        log_debug << "S3 server initialized";
    }

}// namespace AwsMock::Service
