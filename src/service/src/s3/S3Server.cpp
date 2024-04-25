//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/s3/S3Server.h>

namespace AwsMock::Service {

    S3Server::S3Server(Core::Configuration &configuration) : AbstractWorker(configuration), AbstractServer(configuration, "s3", 10), _configuration(configuration), _module("s3") {

        // Get HTTP configuration values
        _port = _configuration.getInt("awsmock.service.s3.port", S3_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.s3.host", S3_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.s3.max.queue", S3_DEFAULT_QUEUE_SIZE);
        _maxThreads = _configuration.getInt("awsmock.service.s3.max.threads", S3_DEFAULT_MAX_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.s3.timeout", S3_DEFAULT_TIMEOUT);
        _monitoringPeriod = _configuration.getInt("awsmock.service.s3.monitoring.period", S3_DEFAULT_MONITORING_PERIOD);

        // Monitoring
        _s3Monitoring = std::make_unique<S3Monitoring>(_monitoringPeriod);

        // Sleeping period
        log_debug << "S3 module initialized, endpoint: " << _host << ":" << _port;
    }

    void S3Server::Initialize() {

        // Check module active
        if (!IsActive("s3")) {
            log_info << "S3 module inactive";
            return;
        }
        log_info << "S3 module starting";

        // Start monitoring
        _s3Monitoring->Start();

        // Start REST module
        StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new S3RequestHandlerFactory(_configuration));
    }

    void S3Server::Run() {
        log_trace << "S3 processing started";
    }

    void S3Server::Shutdown() {
        StopHttpServer();
        _s3Monitoring->Stop();
    }
}// namespace AwsMock::Service
