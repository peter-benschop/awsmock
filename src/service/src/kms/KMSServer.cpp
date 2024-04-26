//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/kms/KMSServer.h>

namespace AwsMock::Service {

    KMSServer::KMSServer(Core::Configuration &configuration) : AbstractServer(configuration, "sns", 10), _configuration(configuration), _kmsDatabase(Database::KMSDatabase::instance()) {

        // HTTP manager configuration
        _port = _configuration.getInt("awsmock.service.sns.http.port", KMS_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.sns.http.host", KMS_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.sns.http.max.queue", KMS_DEFAULT_QUEUE_LENGTH);
        _maxThreads = _configuration.getInt("awsmock.service.sns.http.max.threads", KMS_DEFAULT_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.sns.http.timeout", KMS_DEFAULT_TIMEOUT);
        _workerPeriod = _configuration.getInt("awsmock.service.sns.worker.period", KMS_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = _configuration.getInt("awsmock.service.sns.monitoring.period", KMS_DEFAULT_MONITORING_PERIOD);
        log_debug << "KMS rest module initialized, endpoint: " << _host << ":" << _port;

        // Monitoring
        _kmsMonitoring = std::make_unique<KMSMonitoring>(_monitoringPeriod);

        // Worker
        _kmsWorker = std::make_unique<KMSWorker>(_workerPeriod);

        log_debug << "KMSServer initialized, workerPeriod: " << _workerPeriod << " monitoringPeriod: " << _monitoringPeriod;
    }

    void KMSServer::Initialize() {

        // Check module active
        if (!IsActive("sns")) {
            log_info << "SNS module inactive";
            return;
        }
        log_info << "SNS module starting";

        // Start monitoring
        _kmsMonitoring->Start();

        // Start monitoring
        _kmsWorker->Start();

        // Start REST module
        StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new KMSRequestHandlerFactory(_configuration));
    }

    void KMSServer::Run() {}

    void KMSServer::Shutdown() {
        _kmsWorker->Stop();
        _kmsMonitoring->Stop();
        StopHttpServer();
    }

}// namespace AwsMock::Service
