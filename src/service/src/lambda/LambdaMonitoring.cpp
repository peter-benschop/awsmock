//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/lambda/LambdaMonitoring.h>

namespace AwsMock::Service {

    void LambdaMonitoring::UpdateCounter() {
        log_trace << "Lambda monitoring starting";

        long lambdas = _lambdaDatabase.LambdaCount();
        _metricService.SetGauge(LAMBDA_FUNCTION_COUNT, lambdas);

        log_trace << "Lambda monitoring finished";
    }
}// namespace AwsMock::Service