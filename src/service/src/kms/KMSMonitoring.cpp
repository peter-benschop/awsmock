//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/kms/KMSMonitoring.h>

namespace AwsMock::Service {

    KMSMonitoring::KMSMonitoring(int timeout) : Core::Timer("kms-monitoring", timeout) {
        Start();
    }

    void KMSMonitoring::Initialize() {
        UpdateCounter();
    }

    void KMSMonitoring::Run() {
        UpdateCounter();
    }

    void KMSMonitoring::Shutdown() {}

    void KMSMonitoring::UpdateCounter() {

        // Get total counts
        long keys = _kmsDatabase.CountKeys();
        _metricService.SetGauge(KMS_KEY_COUNT, keys);

        log_trace << "KMS update counter finished";
    }
}// namespace AwsMock::Service