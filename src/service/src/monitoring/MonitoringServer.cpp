//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/monitoring/MonitoringServer.h>

namespace AwsMock::Service {

    MonitoringServer::MonitoringServer() : AbstractServer("monitoring") {
        log_debug << "Monitoring module initialized";
    }

    void MonitoringServer::Initialize() {

        // Initialize metric server
        _metricService.Initialize();

        // Start monitoring system collector
        _metricSystemCollector.Initialize();
        Core::PeriodicScheduler::instance().AddTask("monitoring-system-collector", [this] { this->_metricSystemCollector.Run(); }, 60);

        // Start the database cleanup worker thread every day
        Core::PeriodicScheduler::instance().AddTask("monitoring-cleanup-database", [this] { this->_monitoringWorker.DeleteMonitoringData(); }, 24 * 3600, Core::DateTimeUtils::GetSecondsUntilMidnight());

        // TODO: Get the delay running
        //std::this_thread::sleep_for(std::chrono::seconds(_delay));

        // Set running
        SetRunning();
    }

    void MonitoringServer::Run() {
    }

    void MonitoringServer::Shutdown() {
        log_info << "Shutdown initiated, monitoring";
        Core::PeriodicScheduler::instance().Shutdown();
    }

}// namespace AwsMock::Service
