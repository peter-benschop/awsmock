//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/transfer/TransferMonitoring.h>

namespace AwsMock::Service {

    void TransferMonitoring::UpdateCounter() {
        log_trace << "Transfer monitoring starting";

        long servers = _transferDatabase.CountServers();
        _metricService.SetGauge(TRANSFER_SERVER_COUNT, static_cast<double>(servers));

        log_trace << "Transfer monitoring finished";
    }
}// namespace AwsMock::Service