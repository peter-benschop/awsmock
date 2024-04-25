//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/sns/SNSServer.h"

namespace AwsMock::Service {

    SNSServer::SNSServer(Core::Configuration &configuration) : AbstractServer(configuration, "sns", 10), _configuration(configuration), _snsDatabase(Database::SNSDatabase::instance()) {

        // HTTP manager configuration
        _port = _configuration.getInt("awsmock.service.sns.http.port", SNS_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.sns.http.host", SNS_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.sns.http.max.queue", SNS_DEFAULT_QUEUE_LENGTH);
        _maxThreads = _configuration.getInt("awsmock.service.sns.http.max.threads", SNS_DEFAULT_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.sns.http.timeout", SNS_DEFAULT_TIMEOUT);
        _workerPeriod = _configuration.getInt("awsmock.service.sns.worker.period", SNS_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = _configuration.getInt("awsmock.service.sns.monitoring.period", SNS_DEFAULT_MONITORING_PERIOD);
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
        _snsMonitoring->Start();

        // Start monitoring
        _snsWorker->Start();

        // Start REST module
        StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new SNSRequestHandlerFactory(_configuration));
    }

    void SNSServer::Run() {}

    void SNSServer::Shutdown() {
        _snsWorker->Stop();
        _snsMonitoring->Stop();
        StopHttpServer();
    }

}// namespace AwsMock::Service
