//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/sns/SNSServer.h"

namespace AwsMock::Service {

    SNSServer::SNSServer(Core::PeriodicScheduler &scheduler) : AbstractServer("sns", 10) {

        // HTTP manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _workerPeriod = configuration.getInt("awsmock.service.sns.worker.period", SNS_DEFAULT_WORKER_PERIOD);
        _monitoringPeriod = configuration.getInt("awsmock.service.sns.monitoring.period", SNS_DEFAULT_MONITORING_PERIOD);

        // Check module active
        if (!IsActive("sns")) {
            log_info << "SNS module inactive";
            return;
        }
        log_info << "SNS server starting";

        // Start SNS monitoring update counters
        scheduler.AddTask("monitoring-sns-counters", [this] { UpdateCounter(); }, _monitoringPeriod);

        // Start delete old message task
        scheduler.AddTask("sns-delete-messages", [this] { DeleteOldMessages(); }, _workerPeriod);

        // Set running
        SetRunning();

        log_debug << "SNS server initialized, workerPeriod: " << _workerPeriod << " monitoringPeriod: " << _monitoringPeriod;
    }

    void SNSServer::DeleteOldMessages() {
        Core::Configuration &configuration = Core::Configuration::instance();
        int messageTimeout = configuration.getInt("awsmock.service.sns.message.timeout", SNS_DEFAULT_MESSAGE_TIMEOUT);
        _snsDatabase.DeleteOldMessages(messageTimeout);
    }

    void SNSServer::UpdateCounter() {
        log_trace << "SNS Monitoring starting";

        // Get total counts
        long topics = _snsDatabase.CountTopics();
        long messages = _snsDatabase.CountMessages();
        _metricService.SetGauge(SNS_TOPIC_COUNT, topics);
        _metricService.SetGauge(SNS_MESSAGE_COUNT, messages);

        // Count resources per topic
        for (const auto &topic: _snsDatabase.ListTopics()) {
            std::string labelValue = Poco::replace(topic.topicName, "-", "_");
            long messagesPerTopic = _snsDatabase.CountMessages(topic.region, topic.topicArn);
            _metricService.SetGauge(SNS_MESSAGE_BY_TOPIC_COUNT, "topic", labelValue, messagesPerTopic);
        }
        log_trace << "SNS monitoring finished";
    }

}// namespace AwsMock::Service
