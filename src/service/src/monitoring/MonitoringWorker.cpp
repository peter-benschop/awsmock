//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/monitoring/MonitoringWorker.h>

namespace AwsMock::Service::Monitoring {

    void MonitoringWorker::DeleteMonitoringData() const {

        log_trace << "Monitoring worker starting";

        const int retentionPeriod = Core::Configuration::instance().GetValueInt("awsmock.monitoring.retention");
        const long deletedCount = _monitoringDatabase.DeleteOldMonitoringData(retentionPeriod);

        log_trace << "Monitoring worker finished, retentionPeriod: " << retentionPeriod << " deletedCount: " << deletedCount;
    }

}// namespace AwsMock::Service::Monitoring