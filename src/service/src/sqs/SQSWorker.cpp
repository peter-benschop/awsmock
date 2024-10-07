//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/sqs/SQSWorker.h>

namespace AwsMock::Service {

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