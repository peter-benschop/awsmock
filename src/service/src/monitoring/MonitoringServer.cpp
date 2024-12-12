//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/monitoring/MonitoringServer.h>

namespace AwsMock::Service {

    MonitoringServer::MonitoringServer(Core::PeriodicScheduler &scheduler) : AbstractServer("monitoring") {

        // Initialize metric server
        AwsMock::Monitoring::MetricService::instance().Initialize();

        // Start monitoring system collector
        AwsMock::Monitoring::MetricSystemCollector::instance().Initialize();
        scheduler.AddTask("monitoring-system-collector", [this] { this->_metricSystemCollector.Run(); }, 60);

        // Start the database cleanup worker thread every day
        scheduler.AddTask("monitoring-cleanup-database", [this] { this->_monitoringWorker.DeleteMonitoringData(); }, 24 * 3600, Core::DateTimeUtils::GetSecondsUntilMidnight());

        // Set running
        SetRunning();
        log_debug << "Monitoring module initialized";
    }

}// namespace AwsMock::Service
