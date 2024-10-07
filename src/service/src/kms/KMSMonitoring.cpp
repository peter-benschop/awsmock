//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/kms/KMSMonitoring.h>

namespace AwsMock::Service {

    void KMSMonitoring::UpdateCounter() {
        log_trace << "KMS monitoring starting";

        // Get total counts
        long keys = _kmsDatabase.CountKeys();
        _metricService.SetGauge(KMS_KEY_COUNT, keys);

        log_trace << "KMS monitoring finished";
    }
}// namespace AwsMock::Service