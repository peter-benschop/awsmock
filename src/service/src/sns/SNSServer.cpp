//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/sns/SNSServer.h"

namespace AwsMock::Service {

    SNSServer::SNSServer(boost::asio::thread_pool &pool) : AbstractServer("sns", 10), _snsDatabase(Database::SNSDatabase::instance()), _pool(pool) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.sns.http.port", SNS_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.sns.http.host", SNS_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.sns.http.max.queue", SNS_DEFAULT_QUEUE_LENGTH);
        _maxThreads = configuration.getInt("awsmock.service.sns.http.max.threads", SNS_DEFAULT_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.sns.http.timeout", SNS_DEFAULT_TIMEOUT);
        _workerPeriod = configuration.getInt("awsmock.service.sns.worker.period", SNS_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = configuration.getInt("awsmock.service.sns.monitoring.period", SNS_DEFAULT_MONITORING_PERIOD);
        log_debug << "SNS rest module initialized, endpoint: " << _host << ":" << _port;

        // Monitoring
        _snsMonitoring = std::make_unique<SNSMonitoring>(_monitoringPeriod);

        // Worker
        _snsWorker = std::make_unique<SNSWorker>(_workerPeriod);

        log_debug << "SNSServer initialized, workerPeriod: " << _workerPeriod << " monitoringPeriod: " << _monitoringPeriod;
    }

    void SNSServer::Initialize() {

        // Check module active
        if (!IsActive("sns")) {
            log_info << "SNS module inactive";
            return;
        }
        log_info << "SNS module starting";

        // Start monitoring
        boost::asio::post(_pool, [this] { _snsWorker->Start(); });
        boost::asio::post(_pool, [this] { _snsMonitoring->Start(); });

        // Set running
        SetRunning();
    }

    void SNSServer::Run() {}

    void SNSServer::Shutdown() {
        _snsWorker->Stop();
        _snsMonitoring->Stop();
        StopHttpServer();
    }

}// namespace AwsMock::Service
