//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/monitoring/MonitoringServer.h>

namespace AwsMock::Service {

    MonitoringServer::MonitoringServer() : AbstractServer("monitoring"), _module("monitoring") {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.s3.http.port", S3_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.s3.http.host", S3_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.s3.http.max.queue", S3_DEFAULT_QUEUE_SIZE);
        _maxThreads = configuration.getInt("awsmock.service.s3.http.max.threads", S3_DEFAULT_MAX_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.s3.http.timeout", S3_DEFAULT_TIMEOUT);

        log_debug << "S3 module initialized, endpoint: " << _host << ":" << _port;
    }

    void MonitoringServer::Initialize() {

        // Start worker thread
        //        _s3Worker->Start();

        // Set running
        SetRunning();
    }

    void MonitoringServer::Run() {
    }

    void MonitoringServer::Shutdown() {
        log_debug << "Shutdown initiated, monitoring";
        StopHttpServer();
    }

}// namespace AwsMock::Service
