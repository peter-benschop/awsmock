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

    void SQSWorker::ResetMessages() {

        Database::Entity::SQS::QueueList queueList = _sqsDatabase.ListQueues();
        log_trace << "SQS worker starting, count: " << queueList.size();

        if (queueList.empty()) {
            return;
        }

        // Loop over queues and do some maintenance work
        for (auto &queue: queueList) {

            // Check retention period
            if (queue.attributes.messageRetentionPeriod > 0) {
                _sqsDatabase.MessageRetention(queue.queueUrl, queue.attributes.messageRetentionPeriod);
            }

            // Set counter default userAttributes
            queue.attributes.approximateNumberOfMessages = _sqsDatabase.CountMessages(queue.queueArn);
            queue.attributes.approximateNumberOfMessagesDelayed = _sqsDatabase.CountMessagesByStatus(queue.queueArn, Database::Entity::SQS::MessageStatus::DELAYED);
            queue.attributes.approximateNumberOfMessagesNotVisible = _sqsDatabase.CountMessagesByStatus(queue.queueArn, Database::Entity::SQS::MessageStatus::INVISIBLE);

            // Reset resources which have expired
            //_sqsDatabase.ResetMessages(queue.queueUrl, queue.attributes.visibilityTimeout);

            // Check retries
            /*if (!queue.attributes.redrivePolicy.deadLetterTargetArn.empty()) {
                _sqsDatabase.RedriveMessages(queue.queueUrl, queue.attributes.redrivePolicy);
            }*/

            // Check delays
            if (queue.attributes.delaySeconds > 0) {
                _sqsDatabase.ResetDelayedMessages(queue.queueUrl, queue.attributes.delaySeconds);
            }

            _sqsDatabase.UpdateQueue(queue);
            log_trace << "Queue updated, queueName" << queue.name;
        }
        log_trace << "SQS worker finished, count: " << queueList.size();
    }

}// namespace AwsMock::Service