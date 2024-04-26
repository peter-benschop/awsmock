//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/kms/KMSMonitoring.h>

namespace AwsMock::Service {

    void KMSMonitoring::Initialize() {
        UpdateCounter();
    }

    void KMSMonitoring::Run() {
        UpdateCounter();
    }

    void KMSMonitoring::Shutdown() {}

    void KMSMonitoring::UpdateCounter() {

        // Get total counts
        long topics = _snsDatabase.CountTopics();
        long messages = _snsDatabase.CountMessages();
        _metricService.SetGauge(SNS_TOPIC_COUNT, topics);
        _metricService.SetGauge(SNS_MESSAGE_COUNT, messages);

        // Count messages per topic
        for (const auto &topic: _snsDatabase.ListTopics()) {
            std::string labelValue = Poco::replace(topic.topicName, "-", "_");
            long messagesPerTopic = _snsDatabase.CountMessages(topic.region, topic.topicArn);
            _metricService.SetGauge(SNS_MESSAGE_BY_TOPIC_COUNT, "topic", labelValue, messagesPerTopic);
        }
        log_trace << "SNS update counter finished";
    }
}// namespace AwsMock::Service