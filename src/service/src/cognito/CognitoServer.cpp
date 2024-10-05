//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/cognito/CognitoServer.h>

namespace AwsMock::Service {

    CognitoServer::CognitoServer(boost::asio::thread_pool &pool) : AbstractServer("cognito", 10), _module("cognito"), _pool(pool) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.cognito.http.port", COGNITO_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.cognito.http.host", COGNITO_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.cognito.http.max.queue", COGNITO_DEFAULT_QUEUE_SIZE);
        _maxThreads = configuration.getInt("awsmock.service.cognito.http.max.threads", COGNITO_DEFAULT_MAX_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.cognito.http.timeout", COGNITO_DEFAULT_TIMEOUT);
        _monitoringPeriod = configuration.getInt("awsmock.service.cognito.monitoring.period", COGNITO_DEFAULT_MONITORING_PERIOD);

        // Monitoring
        _cognitoMonitoring = std::make_unique<CognitoMonitoring>(_monitoringPeriod);

        log_debug << "Cognito module initialized, endpoint: " << _host << ":" << _port;
    }

    void CognitoServer::Initialize() {

        // Check module active
        if (!IsActive("cognito")) {
            log_info << "Cognito module inactive";
            return;
        }
        log_info << "Cognito module starting";

        // Start monitoring
        boost::asio::post(_pool, [this] { _cognitoMonitoring->Start(); });

        // Set running
        SetRunning();
    }

    void CognitoServer::Run() {
    }

    void CognitoServer::Shutdown() {
        _cognitoMonitoring->Stop();
    }

}// namespace AwsMock::Service
