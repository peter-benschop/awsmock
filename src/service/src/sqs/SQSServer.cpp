//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/sqs/SQSServer.h>

namespace AwsMock::Service {

    SQSServer::SQSServer() : AbstractServer("sqs") {
        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _monitoringPeriod = configuration.getInt("awsmock.service.sqs.monitoring.period", SQS_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = configuration.getInt("awsmock.service.sqs.worker.period", SQS_DEFAULT_WORKER_PERIOD);

        // Check module active
        if (!IsActive("sqs")) {
            log_info << "SQS module inactive";
            return;
        }
        log_info << "SQS server starting";

        // Start SQS monitoring update counters
        Core::PeriodicScheduler::instance().AddTask("monitoring-sqs-counters", [this] { this->_sqsMonitoring.UpdateCounter(); }, _monitoringPeriod);
        Core::PeriodicScheduler::instance().AddTask("monitoring-sqs-wait-time", [this] { this->_sqsMonitoring.CollectWaitingTimeStatistics(); }, _monitoringPeriod);

        // Start reset messages task
        Core::PeriodicScheduler::instance().AddTask("sqs-reset-messages", [this] { this->_sqsWorker.ResetMessages(); }, _workerPeriod);

        // Set running
        SetRunning();

        log_debug << "SQS server initialized";
    }

    void SQSServer::Initialize() {
    }

    void SQSServer::Run() {}

    void SQSServer::Shutdown() {
    }

}// namespace AwsMock::Service
