//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/ssm/SSMServer.h>

namespace AwsMock::Service {

    SSMServer::SSMServer(boost::asio::thread_pool &pool) : AbstractServer("kms", 10), _ssmDatabase(Database::SSMDatabase::instance()), _pool(pool) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.kms.http.port", SSM_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.kms.http.host", SSM_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.kms.http.max.queue", SSM_DEFAULT_QUEUE_LENGTH);
        _maxThreads = configuration.getInt("awsmock.service.kms.http.max.threads", SSM_DEFAULT_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.kms.http.timeout", SSM_DEFAULT_TIMEOUT);
        _workerPeriod = configuration.getInt("awsmock.service.kms.worker.period", SSM_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = configuration.getInt("awsmock.service.kms.monitoring.period", SSM_DEFAULT_MONITORING_PERIOD);
        log_debug << "KMS rest module initialized, endpoint: " << _host << ":" << _port;

        // Monitoring
        _ssmMonitoring = std::make_unique<SSMMonitoring>(_monitoringPeriod);

        // Worker
        _ssmWorker = std::make_unique<SSMWorker>(_workerPeriod);

        log_debug << "KMSServer initialized, workerPeriod: " << _workerPeriod << " monitoringPeriod: " << _monitoringPeriod;
    }

    void SSMServer::Initialize() {

        // Check module active
        if (!IsActive("sns")) {
            log_info << "KMS module inactive";
            return;
        }
        log_info << "KMS module starting";

        // Start worker threads
        boost::asio::post(_pool, [this] { _ssmWorker->Start(); });
        boost::asio::post(_pool, [this] { _ssmMonitoring->Start(); });

        // Set running
        SetRunning();
    }

    void SSMServer::Run() {
        // Intentionally left empty
    }

    void SSMServer::Shutdown() {
        _ssmWorker->Stop();
        _ssmMonitoring->Stop();
    }

}// namespace AwsMock::Service
