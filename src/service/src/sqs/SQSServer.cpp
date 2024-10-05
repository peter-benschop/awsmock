//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/sqs/SQSServer.h>

namespace AwsMock::Service {

    SQSServer::SQSServer(boost::asio::thread_pool &pool) : AbstractServer("sqs"), _sqsDatabase(Database::SQSDatabase::instance()), _pool(pool) {
        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.sqs.http.port", SQS_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.sqs.http.host", SQS_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.sqs.http.max.queue", SQS_DEFAULT_QUEUE_LENGTH);
        _maxThreads = configuration.getInt("awsmock.service.sqs.max.http.threads", SQS_DEFAULT_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.sqs.http.timeout", SQS_DEFAULT_TIMEOUT);
        _monitoringPeriod = configuration.getInt("awsmock.service.sqs.monitoring.period", SQS_DEFAULT_MONITORING_PERIOD);
        _workerPeriod = configuration.getInt("awsmock.service.sqs.worker.period", SQS_DEFAULT_WORKER_PERIOD);
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

        // Start worker thread
        boost::asio::post(_pool, [this] { _sqsWorker->Start(); });
        boost::asio::post(_pool, [this] { _sqsMonitoring->Start(); });

        // Set running
        SetRunning();
    }

    void SQSServer::Run() {}

    void SQSServer::Shutdown() {
        _sqsMonitoring->Stop();
        _sqsWorker->Stop();
        StopHttpServer();
    }

}// namespace AwsMock::Service
