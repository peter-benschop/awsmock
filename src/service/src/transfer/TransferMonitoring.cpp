//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/transfer/TransferMonitoring.h>

namespace AwsMock::Service {

    void TransferMonitoring::Initialize() {
        UpdateCounter();
    }

    void TransferMonitoring::Run() {
        UpdateCounter();
    }

    void TransferMonitoring::Shutdown() {}

    void TransferMonitoring::UpdateCounter() {
        long servers = _transferDatabase.CountServers();
        _metricService.SetGauge(TRANSFER_SERVER_COUNT, servers);
        log_trace << "Transfer update counter finished";
    }
}