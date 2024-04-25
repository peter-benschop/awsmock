//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/cognito/CognitoMonitoring.h>

namespace AwsMock::Service {

    void CognitoMonitoring::Initialize() {
        UpdateCounter();
    }

    void CognitoMonitoring::Run() {
        UpdateCounter();
    }

    void CognitoMonitoring::Shutdown() {}

    void CognitoMonitoring::UpdateCounter() {
        long users = _cognitoDatabase.CountUsers();
        long userPools = _cognitoDatabase.CountUserPools();
        _metricService.SetGauge(COGNITO_USER_COUNT, users);
        _metricService.SetGauge(COGNITO_USERPOOL_COUNT, userPools);

        // Count users per userpool
        for (const auto &userpool: _cognitoDatabase.ListUserPools()) {
            std::string labelValue = Poco::replace(userpool.name, "-", "_");
            long usersPerUserPool = _cognitoDatabase.CountUsers(userpool.region, userpool.userPoolId);
            _metricService.SetGauge(COGNITO_USER_BY_USERPOOL_COUNT, "userpool", labelValue, usersPerUserPool);
        }
        log_trace << "Cognito update counter finished";
    }
}// namespace AwsMock::Service