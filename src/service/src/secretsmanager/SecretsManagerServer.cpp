//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/secretsmanager/SecretsManagerServer.h>

namespace AwsMock::Service {

    SecretsManagerServer::SecretsManagerServer(Core::Configuration &configuration) : AbstractServer(configuration, "secretsmanager", 10), _configuration(configuration),
                                                                                     _moduleDatabase(Database::ModuleDatabase::instance()) {
        // HTTP manager configuration
        _port = _configuration.getInt("awsmock.service.secretsmanager.port", SECRETSMANAGER_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.secretsmanager.host", SECRETSMANAGER_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.secretsmanager.max.queue", SECRETSMANAGER_DEFAULT_QUEUE_LENGTH);
        _maxThreads = _configuration.getInt("awsmock.service.secretsmanager.max.threads", SECRETSMANAGER_DEFAULT_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.secretsmanager.timeout", SECRETSMANAGER_DEFAULT_TIMEOUT);
        _monitoringPeriod = _configuration.getInt("awsmock.service.secretsmanager.monitoring.period", SECRETSMANAGER_DEFAULT_MONITORING_PERIOD);
        log_debug << "SecretsManager rest module initialized, endpoint: " << _host << ":" << _port;

        // Create environment
        _region = _configuration.getString("awsmock.region");

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
        _secretsManagerMonitoring->Start();

        // Start REST module
        StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new SecretsManagerRequestHandlerFactory(_configuration));
    }

    void SecretsManagerServer::Run() {
    }

    void SecretsManagerServer::Shutdown() {
        StopHttpServer();
        _secretsManagerMonitoring->Stop();
    }

}// namespace AwsMock::Service
