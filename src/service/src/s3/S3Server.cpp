//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/s3/S3Server.h>

namespace AwsMock::Service {

    S3Server::S3Server() : AbstractServer(Core::Configuration::instance(), "s3"), _module("s3") {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.s3.http.port", S3_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.s3.http.host", S3_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.s3.http.max.queue", S3_DEFAULT_QUEUE_SIZE);
        _maxThreads = configuration.getInt("awsmock.service.s3.http.max.threads", S3_DEFAULT_MAX_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.s3.http.timeout", S3_DEFAULT_TIMEOUT);
        _monitoringPeriod = configuration.getInt("awsmock.service.s3.monitoring.period", S3_DEFAULT_MONITORING_PERIOD);

        // Monitoring
        _s3Monitoring = std::make_shared<S3Monitoring>(_monitoringPeriod);
        log_debug << "S3 module initialized, endpoint: " << _host << ":" << _port;
    }

    void S3Server::Initialize() {

        // Check module active
        if (!IsActive("s3")) {
            log_info << "S3 module inactive";
            return;
        }
        log_info << "S3 module starting";

        // Start REST module
        //StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new S3RequestHandlerFactory(_configuration));
    }

    void S3Server::Run() {
    }

    void S3Server::Shutdown() {
        log_debug << "Shutdown initiated, s3";
        _s3Monitoring->Stop();
        StopHttpServer();
    }
}// namespace AwsMock::Service
