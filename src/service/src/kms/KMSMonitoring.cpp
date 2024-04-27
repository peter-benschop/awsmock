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
        long keys = _kmsDatabase.CountKeys();
        _metricService.SetGauge(KMS_KEY_COUNT, keys);

        // Count messages per topic
        /*for (const auto &topic: _kmsDatabase.ListTopics()) {
            std::string labelValue = Poco::replace(topic.topicName, "-", "_");
            long messagesPerTopic = _kmsDatabase.CountMessages(topic.region, topic.topicArn);
            _metricService.SetGauge(SNS_MESSAGE_BY_TOPIC_COUNT, "topic", labelValue, messagesPerTopic);
        }*/
        log_trace << "KMS update counter finished";
    }
}// namespace AwsMock::Service