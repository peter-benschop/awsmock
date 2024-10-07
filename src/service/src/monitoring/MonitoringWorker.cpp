//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/monitoring/MonitoringWorker.h>

namespace AwsMock::Service::Monitoring {

    void MonitoringWorker::DeleteMonitoringData() {

        log_trace << "Monitoring worker starting";

        int retentionPeriod = Core::Configuration::instance().getInt("awsmock.service.monitoring.retention", DEFAULT_RETENTION_PERIOD);
        long deletedCount = _monitoringDatabase.DeleteOldMonitoringData(retentionPeriod);

        log_trace << "Monitoring worker finished, retentionPeriod: " << retentionPeriod << " deletedCount: " << deletedCount;
    }

}// namespace AwsMock::Service::Monitoring