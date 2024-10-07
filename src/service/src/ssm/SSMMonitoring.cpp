//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/ssm/SSMMonitoring.h>

namespace AwsMock::Service {

    void SSMMonitoring::UpdateCounter() {
        log_trace << "SSM monitoring starting";

        // Get total counts
        long parameters = _ssmDatabase.CountParameters();
        _metricService.SetGauge(SSM_PARAMETER_COUNT, parameters);

        log_trace << "SSM monitoring finished";
    }
}// namespace AwsMock::Service