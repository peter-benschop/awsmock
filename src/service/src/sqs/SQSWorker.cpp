//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/sqs/SQSWorker.h>

namespace AwsMock::Service {

    void SQSWorker::Initialize() {

        log_debug << "SQSWorker initialized";
    }

    void SQSWorker::Run() {
        ResetMessages();
    }

    void SQSWorker::Shutdown() {}

    [[maybe_unused]] void SQSWorker::ResetMessages() {

        Database::Entity::SQS::QueueList queueList = _sqsDatabase.ListQueues();
        log_trace << "Working on queue list, count" << queueList.size();

        for (auto &queue: queueList) {

            // Check retention period
            if (queue.attributes.messageRetentionPeriod > 0) {
                _sqsDatabase.MessageRetention(queue.queueUrl, queue.attributes.messageRetentionPeriod);
            }

            // Reset resources which have expired
            _sqsDatabase.ResetMessages(queue.queueUrl, queue.attributes.visibilityTimeout);

            // Set counter default userAttributes
            queue.attributes.approximateNumberOfMessages = _sqsDatabase.CountMessages(queue.region, queue.queueUrl);
            queue.attributes.approximateNumberOfMessagesDelayed = _sqsDatabase.CountMessagesByStatus(queue.region, queue.queueUrl, Database::Entity::SQS::MessageStatus::DELAYED);
            queue.attributes.approximateNumberOfMessagesNotVisible = _sqsDatabase.CountMessagesByStatus(queue.region, queue.queueUrl, Database::Entity::SQS::MessageStatus::INVISIBLE);

            // Check retries
            if (!queue.attributes.redrivePolicy.deadLetterTargetArn.empty()) {
                _sqsDatabase.RedriveMessages(queue.queueUrl, queue.attributes.redrivePolicy);
            }

            // Check delays
            if (queue.attributes.delaySeconds > 0) {
                _sqsDatabase.ResetDelayedMessages(queue.queueUrl, queue.attributes.delaySeconds);
            }

            _sqsDatabase.UpdateQueue(queue);
            log_trace << "Queue updated, queueName" << queue.name;
        }
    }
}// namespace AwsMock::Service