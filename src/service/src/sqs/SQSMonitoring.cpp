//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/sqs/SQSMonitoring.h>

namespace AwsMock::Service {

    SQSMonitoring::SQSMonitoring(int timeout) : Core::Timer("sqs-monitoring", timeout) {}

    void SQSMonitoring::Initialize() {
        UpdateCounter();
        CollectWaitingTimeStatistics();
    }

    void SQSMonitoring::Run() {
        UpdateCounter();
        CollectWaitingTimeStatistics();
    }

    void SQSMonitoring::Shutdown() {}

    void SQSMonitoring::UpdateCounter() {
        log_trace << "SQS counter update starting";

        // Get total counts
        long queues = _sqsDatabase.CountQueues();
        long messages = _sqsDatabase.CountMessages();
        _metricService.SetGauge(SQS_QUEUE_COUNT, static_cast<double>(queues));
        _metricService.SetGauge(SQS_MESSAGE_COUNT, static_cast<double>(messages));

        // Count resources per queue
        for (const auto &queue: _sqsDatabase.ListQueues()) {
            std::string labelValue = Poco::replace(queue.name, "-", "_");
            long messagesPerQueue = _sqsDatabase.CountMessages(queue.queueArn);
            _metricService.SetGauge(SQS_MESSAGE_BY_QUEUE_COUNT, "queue", labelValue, static_cast<double>(messagesPerQueue));
        }
        log_trace << "SQS counter update finished";
    }

    void SQSMonitoring::CollectWaitingTimeStatistics() {
        log_trace << "SQS message wait time starting";

        Database::Entity::SQS::MessageWaitTime waitingTime = _sqsDatabase.GetAverageMessageWaitingTime();
        log_trace << "SQS worker starting, count: " << waitingTime.waitTime.size();

        if (!waitingTime.waitTime.empty()) {
            for (auto &w: waitingTime.waitTime) {
                _metricService.SetGauge(SQS_MESSAGE_WAIT_TIME, "queue", w.first, w.second);
            }
        }
        log_trace << "SQS wait time update finished";
    }

}// namespace AwsMock::Service