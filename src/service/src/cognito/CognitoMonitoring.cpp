//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/cognito/CognitoMonitoring.h>

namespace AwsMock::Service {

    void CognitoMonitoring::UpdateCounter() {
        log_trace << "Cognito monitoring starting";

        long users = _cognitoDatabase.CountUsers();
        long userPools = _cognitoDatabase.CountUserPools();
        _metricService.SetGauge(COGNITO_USER_COUNT, users);
        _metricService.SetGauge(COGNITO_USERPOOL_COUNT, userPools);

        // Count users per user pool
        for (const auto &userPool: _cognitoDatabase.ListUserPools()) {
            std::string labelValue = Poco::replace(userPool.name, "-", "_");
            long usersPerUserPool = _cognitoDatabase.CountUsers(userPool.region, userPool.userPoolId);
            _metricService.SetGauge(COGNITO_USER_BY_USERPOOL_COUNT, "userPool", labelValue, usersPerUserPool);
        }
        log_trace << "Cognito monitoring finished";
    }
}// namespace AwsMock::Service