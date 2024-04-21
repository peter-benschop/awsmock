//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/sns/SNSServer.h"

namespace AwsMock::Service {

    SNSServer::SNSServer(Core::Configuration &configuration) : AbstractServer(configuration, "sns", 10), _configuration(configuration), _snsDatabase(Database::SNSDatabase::instance()) {

        // HTTP manager configuration
        _port = _configuration.getInt("awsmock.service.sns.port", SNS_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.sns.host", SNS_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.sns.max.queue", SNS_DEFAULT_QUEUE_LENGTH);
        _maxThreads = _configuration.getInt("awsmock.service.sns.max.threads", SNS_DEFAULT_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.sns.timeout", SNS_DEFAULT_TIMEOUT);
        _messageTimeout = _configuration.getInt("awsmock.service.sns.message.timeout", SNS_DEFAULT_MESSAGE_TIMEOUT);
        _monitoringPeriod = _configuration.getInt("awsmock.service.sns.monitoring.period", SNS_DEFAULT_MONITORING_PERIOD);
        log_debug << "SNS rest module initialized, endpoint: " << _host << ":" << _port;

        // Create environment
        _region = _configuration.getString("awsmock.region");

        // Message timeout in seconds
        _messageTimeout *= 60 * 24;

        // Monitoring
        _snsMonitoring = std::make_unique<SNSMonitoring>(_monitoringPeriod);

        log_debug << "SNSServer initialized, timeout: " << _messageTimeout;
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

        // Start REST module
        StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new SNSRequestHandlerFactory(_configuration));
    }

    void SNSServer::Run() {
        log_trace << "S3 processing started";
        DeleteOldMessages();
    }

    void SNSServer::Shutdown() {
        StopHttpServer();
    }

    void SNSServer::DeleteOldMessages() {
        _snsDatabase.DeleteOldMessages(_messageTimeout);
    }

} // namespace AwsMock::Worker
