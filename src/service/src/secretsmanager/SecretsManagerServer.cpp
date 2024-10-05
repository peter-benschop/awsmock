//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/secretsmanager/SecretsManagerServer.h>

namespace AwsMock::Service {

    SecretsManagerServer::SecretsManagerServer(boost::asio::thread_pool &pool) : AbstractServer("secretsmanager", 10), _moduleDatabase(Database::ModuleDatabase::instance()), _pool(pool) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.secretsmanager.port", SECRETSMANAGER_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.secretsmanager.host", SECRETSMANAGER_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.secretsmanager.max.queue", SECRETSMANAGER_DEFAULT_QUEUE_LENGTH);
        _maxThreads = configuration.getInt("awsmock.service.secretsmanager.max.threads", SECRETSMANAGER_DEFAULT_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.secretsmanager.timeout", SECRETSMANAGER_DEFAULT_TIMEOUT);
        _monitoringPeriod = configuration.getInt("awsmock.service.secretsmanager.monitoring.period", SECRETSMANAGER_DEFAULT_MONITORING_PERIOD);
        log_debug << "SecretsManager rest module initialized, endpoint: " << _host << ":" << _port;

        // Create environment
        _region = configuration.getString("awsmock.region");

        // Monitoring
        _secretsManagerMonitoring = std::make_unique<SecretsManagerMonitoring>(_monitoringPeriod);

        log_debug << "SecretsManager server initialized";
    }

    void SecretsManagerServer::Initialize() {

        // Check module active
        if (!IsActive("secretsmanager")) {
            log_info << "SecretsManager module inactive";
            return;
        }
        log_info << "SecretsManager server starting, port: " << _port;

        // Start monitoring
        boost::asio::post(_pool, [this] { _secretsManagerMonitoring->Start(); });

        // Set running
        SetRunning();
    }

    void SecretsManagerServer::Run() {
    }

    void SecretsManagerServer::Shutdown() {
        _secretsManagerMonitoring->Stop();
    }

}// namespace AwsMock::Service
