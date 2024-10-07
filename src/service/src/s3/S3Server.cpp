//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/s3/S3Server.h>

namespace AwsMock::Service {

    S3Server::S3Server() : AbstractServer("s3") {

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
        Core::PeriodicScheduler::instance().AddTask("monitoring-s3-counters", [this] { this->_s3Monitoring.UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        Core::PeriodicScheduler::instance().AddTask("s3-sync-directories", [this] { this->_s3Worker.SyncObjects(); }, _workerPeriod);
        log_debug << "S3 server initialized";
    }

    void S3Server::Initialize() {

        // Check module active
        if (!IsActive("s3")) {
            log_info << "S3 module inactive";
            return;
        }
        log_info << "S3 server starting";

        // Start SNS monitoring update counters
        Core::PeriodicScheduler::instance().AddTask("monitoring-s3-counters", [this] { this->_s3Monitoring.UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        Core::PeriodicScheduler::instance().AddTask("s3-sync-directories", [this] { this->_s3Worker.SyncObjects(); }, _workerPeriod);
    }

    void S3Server::Run() {
    }

    void S3Server::Shutdown() {
    }
}// namespace AwsMock::Service
