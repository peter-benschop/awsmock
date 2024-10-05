//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/monitoring/MonitoringServer.h>

namespace AwsMock::Service {

    MonitoringServer::MonitoringServer(boost::asio::thread_pool &pool) : AbstractServer("monitoring"), _module("monitoring"), _pool(pool) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();

        _metricService = std::make_shared<Monitoring::MetricService>();
        _metricSystemCollector = std::make_shared<Monitoring::MetricSystemCollector>();

        log_debug << "Monitoring module initialized";
    }

    void MonitoringServer::Initialize() {

        // Start worker thread
        boost::asio::post(_pool, [this] { _metricService->Start(); });
        boost::asio::post(_pool, [this] { _metricSystemCollector->Start(); });

        // Set running
        SetRunning();
    }

    void MonitoringServer::Run() {
    }

    void MonitoringServer::Shutdown() {
        log_info << "Shutdown initiated, monitoring";
        _metricSystemCollector->Stop();
        _metricService->Stop();
    }

}// namespace AwsMock::Service
