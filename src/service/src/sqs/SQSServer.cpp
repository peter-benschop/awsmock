//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/sqs/SQSServer.h>

namespace AwsMock::Service {
    SQSServer::SQSServer(Core::PeriodicScheduler &scheduler) : AbstractServer("sqs") {
        // HTTP manager configuration
        _monitoringPeriod = Core::YamlConfiguration::instance().GetValueInt("awsmock.modules.sqs.monitoring.period");
        _resetPeriod = Core::YamlConfiguration::instance().GetValueInt("awsmock.modules.sqs.reset.period");
        _counterPeriod = Core::YamlConfiguration::instance().GetValueInt("awsmock.modules.sqs.counter.period");

        // Check module active
        if (!IsActive("sqs")) {
            log_info << "SQS module inactive";
            return;
        }
        log_info << "SQS server starting";

        // Start SQS monitoring update counters
        scheduler.AddTask("monitoring-sqs-counters", [this] { this->UpdateCounter(); }, _monitoringPeriod);
        scheduler.AddTask("monitoring-sqs-wait-time",
                          [this] { this->CollectWaitingTimeStatistics(); },
                          _monitoringPeriod);

        // Start reset messages task
        scheduler.AddTask("sqs-reset-messages", [this] { this->ResetMessages(); }, _resetPeriod);
        scheduler.AddTask("sqs-count-messages", [this] { this->AdjustCounters(); }, _resetPeriod);

        // Set running
        SetRunning();

        log_debug << "SQS server initialized";
    }

    void SQSServer::AdjustCounters() const {
        Database::Entity::SQS::QueueList queueList = _sqsDatabase.ListQueues();
        log_trace << "SQS adjust counter starting, count: " << queueList.size();

        // Loop over queues and synchronize queue counters
        for (auto &queue : queueList) {
            queue.attributes.approximateNumberOfMessages = _sqsDatabase.CountMessagesByStatus(
                queue.queueArn,
                Database::Entity::SQS::MessageStatus::INITIAL);
            queue.attributes.approximateNumberOfMessagesNotVisible = _sqsDatabase.CountMessagesByStatus(
                queue.queueArn,
                Database::Entity::SQS::MessageStatus::INVISIBLE);
            queue.attributes.approximateNumberOfMessagesDelayed = _sqsDatabase.CountMessagesByStatus(
                queue.queueArn,
                Database::Entity::SQS::MessageStatus::DELAYED);
            queue = _sqsDatabase.UpdateQueue(queue);
        }
        log_trace << "SQS adjust counter finished, count: " << queueList.size();
    }

    void SQSServer::ResetMessages() const {
        Database::Entity::SQS::QueueList queueList = _sqsDatabase.ListQueues();
        log_trace << "SQS reset messages starting, count: " << queueList.size();

        if (queueList.empty()) {
            return;
        }

        // Loop over queues and do some maintenance work
        for (auto &queue : queueList) {
            long messageCount = _sqsDatabase.CountMessages(queue.queueArn);
            if (messageCount > 0) {
                // Check retention period
                if (queue.attributes.messageRetentionPeriod > 0) {
                    queue.attributes.approximateNumberOfMessages -= _sqsDatabase.MessageRetention(
                        queue.queueUrl,
                        queue.attributes.messageRetentionPeriod);
                }

                // Check visibility timeout
                if (queue.attributes.visibilityTimeout > 0) {
                    queue.attributes.approximateNumberOfMessagesNotVisible -= _sqsDatabase.ResetMessages(
                        queue.queueArn,
                        queue.attributes.visibilityTimeout);
                }

                // Check delays
                if (queue.attributes.delaySeconds > 0) {
                    queue.attributes.approximateNumberOfMessagesDelayed -= _sqsDatabase.ResetDelayedMessages(
                        queue.queueUrl,
                        queue.attributes.delaySeconds);
                }

                // Save results
                queue = _sqsDatabase.UpdateQueue(queue);
                log_trace << "Queue updated, queueName" << queue.name;
            }
        }
        log_trace << "SQS reset messages finished, count: " << queueList.size();
    }

    void SQSServer::UpdateCounter() const {
        log_trace << "SQS counter update starting";

        // Get total counts
        long queues = _sqsDatabase.CountQueues();
        long messages = _sqsDatabase.CountMessages();
        _metricService.SetGauge(SQS_QUEUE_COUNT, static_cast<double>(queues));
        _metricService.SetGauge(SQS_MESSAGE_COUNT, static_cast<double>(messages));

        // Count resources per queue
        for (const auto &queue : _sqsDatabase.ListQueues()) {
            std::string labelValue = Poco::replace(queue.name, "-", "_");
            const long messagesPerQueue = _sqsDatabase.CountMessages(queue.queueArn);
            _metricService.SetGauge(SQS_MESSAGE_BY_QUEUE_COUNT,
                                    "queue",
                                    labelValue,
                                    static_cast<double>(messagesPerQueue));
        }
        log_trace << "SQS counter update finished";
    }

    void SQSServer::CollectWaitingTimeStatistics() const {
        log_trace << "SQS message wait time starting";

        Database::Entity::SQS::MessageWaitTime waitingTime = _sqsDatabase.GetAverageMessageWaitingTime();
        log_trace << "SQS worker starting, count: " << waitingTime.waitTime.size();

        if (!waitingTime.waitTime.empty()) {
            for (auto &w : waitingTime.waitTime) {
                _metricService.SetGauge(SQS_MESSAGE_WAIT_TIME, "queue", w.first, w.second);
            }
        }
        log_trace << "SQS wait time update finished";
    }
} // namespace AwsMock::Service
