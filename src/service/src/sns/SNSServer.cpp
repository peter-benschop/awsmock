//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/sns/SNSServer.h"

namespace AwsMock::Service {

    SNSServer::SNSServer() : AbstractServer("sns", 10) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _workerPeriod = configuration.getInt("awsmock.service.sns.worker.period", SNS_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = configuration.getInt("awsmock.service.sns.monitoring.period", SNS_DEFAULT_MONITORING_PERIOD);

        // Check module active
        if (!IsActive("sns")) {
            log_info << "SNS module inactive";
            return;
        }
        log_info << "SNS server starting";

        // Start SNS monitoring update counters
        Core::PeriodicScheduler::instance().AddTask("monitoring-sns-counters", [this] { this->_snsMonitoring.UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        Core::PeriodicScheduler::instance().AddTask("sns-delete-messages", [this] { this->_snsWorker.DeleteOldMessages(); }, _workerPeriod);

        // Set running
        SetRunning();

        log_debug << "SNS server initialized, workerPeriod: " << _workerPeriod << " monitoringPeriod: " << _monitoringPeriod;
    }

    void SNSServer::Initialize() {
    }

    void SNSServer::Run() {}

    void SNSServer::Shutdown() {
    }

}// namespace AwsMock::Service
