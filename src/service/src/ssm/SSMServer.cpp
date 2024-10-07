//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/ssm/SSMServer.h>

namespace AwsMock::Service {

    SSMServer::SSMServer() : AbstractServer("kms", 10) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _workerPeriod = configuration.getInt("awsmock.service.ssm.worker.period", SSM_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = configuration.getInt("awsmock.service.ssm.monitoring.period", SSM_DEFAULT_MONITORING_PERIOD);
        log_debug << "SSM server initialized";

        // Check module active
        if (!IsActive("ssm")) {
            log_info << "SSM module inactive";
            return;
        }
        log_info << "SSM server starting";

        // Monitoring
        // Start SNS monitoring update counters
        Core::PeriodicScheduler::instance().AddTask("monitoring-ssm-counters", [this] { this->_ssmMonitoring.UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        //Core::PeriodicScheduler::instance().AddTask("s3-sync-directories", [this] { this->_ssmWorker.SyncObjects(); }, _workerPeriod);

        // Set running
        SetRunning();

        log_debug << "SSM server started, workerPeriod: " << _workerPeriod << " monitoringPeriod: " << _monitoringPeriod;
    }

    void SSMServer::Initialize() {
        // Intentionally left empty
    }

    void SSMServer::Run() {
        // Intentionally left empty
    }

    void SSMServer::Shutdown() {
        // Intentionally left empty
    }

}// namespace AwsMock::Service
