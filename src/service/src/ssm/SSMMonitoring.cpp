//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/ssm/SSMMonitoring.h>

namespace AwsMock::Service {

    void SSMMonitoring::Initialize() {
    }

    void SSMMonitoring::Run() {
        UpdateCounter();
    }

    void SSMMonitoring::Shutdown() {}

    void SSMMonitoring::UpdateCounter() {
        log_trace << "SSM monitoring starting";

        // Get total counts
        long keys = _ssmDatabase.CountParameters();
        _metricService.SetGauge(KMS_KEY_COUNT, keys);

        log_trace << "SSM monitoring finished";
    }
}// namespace AwsMock::Service