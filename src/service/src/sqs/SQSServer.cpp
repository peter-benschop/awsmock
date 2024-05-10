//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/sqs/SQSServer.h>

namespace AwsMock::Service {

    SQSServer::SQSServer(Core::Configuration &configuration) : AbstractServer(configuration, "sqs"), _configuration(configuration), _sqsDatabase(Database::SQSDatabase::instance()) {

        // HTTP manager configuration
        _port = _configuration.getInt("awsmock.service.sqs.http.port", SQS_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.sqs.http.host", SQS_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.sqs.http.max.queue", SQS_DEFAULT_QUEUE_LENGTH);
        _maxThreads = _configuration.getInt("awsmock.service.sqs.max.http.threads", SQS_DEFAULT_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.sqs.http.timeout", SQS_DEFAULT_TIMEOUT);
        _monitoringPeriod = _configuration.getInt("awsmock.service.sqs.monitoring.period", SQS_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = _configuration.getInt("awsmock.service.sqs.worker.period", SQS_DEFAULT_WORKER_PERIOD);
        log_debug << "SQS rest module initialized, endpoint: " << _host << ":" << _port;

        // Monitoring
        _sqsMonitoring = std::make_unique<SQSMonitoring>(_monitoringPeriod);

        // Worker thread
        _sqsWorker = std::make_unique<SQSWorker>(_workerPeriod);
        log_debug << "SQSServer initialized";
    }

    void SQSServer::Initialize() {

        // Check module active
        if (!IsActive("sqs")) {
            log_info << "SQS module inactive";
            return;
        }
        log_info << "SQS server starting, port: " << _port;

        // Start monitoring
        _sqsMonitoring->Start();

        // Start worker thread
        _sqsWorker->Start();

        // Start REST module
        StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new SQSRequestHandlerFactory(_configuration));
    }

    void SQSServer::Run() {}

    void SQSServer::Shutdown() {
        _sqsMonitoring->Stop();
        _sqsWorker->Stop();
        StopHttpServer();
    }

}// namespace AwsMock::Service
