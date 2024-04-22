//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/secretsmanager/SecretsManagerMonitoring.h>

namespace AwsMock::Service {

    void SecretsManagerMonitoring::Initialize() {
        UpdateCounter();
    }

    void SecretsManagerMonitoring::Run() {
        UpdateCounter();
    }

    void SecretsManagerMonitoring::Shutdown() {}

    void SecretsManagerMonitoring::UpdateCounter() {
        long secrets = _secretsManagerDatabase.CountSecrets();
        _metricService.SetGauge(SECRETSMANAGER_SECRETS_COUNT, secrets);
        log_trace << "Secrets manager update counter finished";
    }
}