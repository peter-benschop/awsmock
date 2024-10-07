//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/secretsmanager/SecretsManagerServer.h>

namespace AwsMock::Service {

    SecretsManagerServer::SecretsManagerServer() : AbstractServer("secretsmanager", 10) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _monitoringPeriod = configuration.getInt("awsmock.service.secretsmanager.monitoring.period", SECRETSMANAGER_DEFAULT_MONITORING_PERIOD);
        log_debug << "SecretsManager rest module initialized";

        // Check module active
        if (!IsActive("secretsmanager")) {
            log_info << "SecretsManager module inactive";
            return;
        }
        log_info << "SecretsManager server starting";

        // Start secrets manager monitoring update counters
        Core::PeriodicScheduler::instance().AddTask("monitoring-sns-counters", [this] { this->_secretsManagerMonitoring.UpdateCounter(); }, _monitoringPeriod);

        // Set running
        SetRunning();
    }

    void SecretsManagerServer::Initialize() {
    }

    void SecretsManagerServer::Run() {
    }

    void SecretsManagerServer::Shutdown() {
    }

}// namespace AwsMock::Service
