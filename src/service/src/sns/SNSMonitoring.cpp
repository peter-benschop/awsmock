//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/sns/SNSMonitoring.h>

namespace AwsMock::Service {

    SNSMonitoring::SNSMonitoring(int timeout) : Core::Timer("sns-monitoring", timeout) {
    }

    void SNSMonitoring::Initialize() {
        UpdateCounter();
    }

    void SNSMonitoring::Run() {
        UpdateCounter();
    }

    void SNSMonitoring::Shutdown() {}

    void SNSMonitoring::UpdateCounter() {
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