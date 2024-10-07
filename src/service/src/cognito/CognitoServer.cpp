//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/cognito/CognitoServer.h>

namespace AwsMock::Service {

    CognitoServer::CognitoServer() : AbstractServer("cognito", 10) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _monitoringPeriod = configuration.getInt("awsmock.service.cognito.monitoring.period", COGNITO_DEFAULT_MONITORING_PERIOD);

        // Check module active
        if (!IsActive("cognito")) {
            log_info << "Cognito module inactive";
            return;
        }
        log_info << "Cognito module starting";

        // Start DynamoDB monitoring update counters
        Core::PeriodicScheduler::instance().AddTask("monitoring-dynamodb-counters", [this] { this->_cognitoMonitoring.UpdateCounter(); }, _monitoringPeriod);

        // Set running
        SetRunning();

        log_debug << "Cognito server started";
    }
    void CognitoServer::Initialize() {
    }
    void CognitoServer::Run() {
    }
    void CognitoServer::Shutdown() {
    }

}// namespace AwsMock::Service
