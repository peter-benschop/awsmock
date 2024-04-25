//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/sqs/SQSMonitoring.h>

namespace AwsMock::Service {

    void SQSMonitoring::Initialize() {
        UpdateCounter();
    }

    void SQSMonitoring::Run() {
        UpdateCounter();
    }

    void SQSMonitoring::Shutdown() {}

    void SQSMonitoring::UpdateCounter() {

        // Get total counts
        long queues = _sqsDatabase.CountQueues();
        long messages = _sqsDatabase.CountMessages();
        _metricService.SetGauge(SQS_QUEUE_COUNT, queues);
        _metricService.SetGauge(SQS_MESSAGE_COUNT, messages);

        // Count messages per queue
        for (const auto &queue: _sqsDatabase.ListQueues()) {
            std::string labelValue = Poco::replace(queue.name, "-", "_");
            long messagesPerQueue = _sqsDatabase.CountMessages(queue.region, queue.queueUrl);
            _metricService.SetGauge(SQS_MESSAGE_BY_QUEUE_COUNT, "queue", labelValue, messagesPerQueue);
        }
        log_trace << "SQS update counter finished";
    }
}// namespace AwsMock::Service