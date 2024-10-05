//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/kms/KMSServer.h>

namespace AwsMock::Service {

    KMSServer::KMSServer(boost::asio::thread_pool &pool) : AbstractServer("kms", 10), _kmsDatabase(Database::KMSDatabase::instance()), _pool(pool) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.kms.http.port", KMS_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.kms.http.host", KMS_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.kms.http.max.queue", KMS_DEFAULT_QUEUE_LENGTH);
        _maxThreads = configuration.getInt("awsmock.service.kms.http.max.threads", KMS_DEFAULT_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.kms.http.timeout", KMS_DEFAULT_TIMEOUT);
        _workerPeriod = configuration.getInt("awsmock.service.kms.worker.period", KMS_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = configuration.getInt("awsmock.service.kms.monitoring.period", KMS_DEFAULT_MONITORING_PERIOD);
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
            log_info << "KMS module inactive";
            return;
        }
        log_info << "KMS module starting";

        boost::asio::post(_pool, [this] { _kmsWorker->Start(); });
        boost::asio::post(_pool, [this] { _kmsMonitoring->Start(); });

        // Set running
        SetRunning();
    }

    void KMSServer::Run() {
        // Intentionally left empty
    }

    void KMSServer::Shutdown() {
        _kmsWorker->Stop();
        _kmsMonitoring->Stop();
    }

}// namespace AwsMock::Service
