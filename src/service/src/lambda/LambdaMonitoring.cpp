//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/lambda/LambdaMonitoring.h>

namespace AwsMock::Service {

    void LambdaMonitoring::Initialize() {}

    void LambdaMonitoring::Run() {
        UpdateCounter();
    }

    void LambdaMonitoring::Shutdown() {}

    void LambdaMonitoring::UpdateCounter() {
        long lambdas = _lambdaDatabase.LambdaCount();
        _metricService.SetGauge(LAMBDA_FUNCTION_COUNT, lambdas);
    }
}