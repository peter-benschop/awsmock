//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_SQS_MEMORYDB_H
#define AWSMOCK_REPOSITORY_SQS_MEMORYDB_H

// C++ includes
#include <chrono>
#include <string>

// Poco includes
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/sqs/MessageWaitTime.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    using std::chrono::system_clock;

    /**
     * @brief SQS in-memory database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSMemoryDb {

      public:

        /**
         * @brief Constructor
         */
        SQSMemoryDb() = default;

        /**
         * @brief Singleton instance
         */
        static SQSMemoryDb &instance() {
            static SQSMemoryDb sqsMemoryDb;
            return sqsMemoryDb;
        }

        /**
         * @brief Check existence of queue
         *
         * @param region AWS region
         * @param name queue name
         * @return true if queue already exists
         * @throws DatabaseException
         */
        bool QueueExists(const std::string &region, const std::string &name);

        /**
         * @brief Check existence of queue
         *
         * @param region AWS region
         * @param queueUrl AWS region
         * @return true if queue already exists
         * @throws DatabaseException
         */
        bool QueueUrlExists(const std::string &region, const std::string &queueUrl);

        /**
         * @brief Check existence of queue by ARN
         *
         * @param queueArn queue ARN
         * @return true in case queue exists
         * @throws DatabaseException
         */
        bool QueueArnExists(const std::string &queueArn);

        /**
         * @brief Create a new queue in the SQS queue table
         *
         * @param queue queue entity
         * @return created SQS queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue CreateQueue(const Entity::SQS::Queue &queue);

        /**
         * @brief Returns a queue by primary key
         *
         * @param oid queue primary key
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueById(const std::string &oid);

        /**
         * @brief List all available queues
         *
         * @param region AWS region
         * @return List of SQS queues
         * @throws DatabaseException
         */
        Entity::SQS::QueueList ListQueues(const std::string &region = {});

        /**
         * @brief Returns a queue by ARN
         *
         * @param queueArn queue ARN
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueByArn(const std::string &queueArn);

        /**
         * @brief Returns a queue by name and region
         *
         * @param region AWS region
         * @param queueName queue name
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueByName(const std::string &region, const std::string &queueName);

        /**
         * @brief Returns a queue by URL
         *
         * @param queueUrl queue URL
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueByUrl(const std::string &queueUrl);

        /**
         * @brief Purge a given queueUrl.
         *
         * @param queueArn queue ARN
         */
        void PurgeQueue(const std::string &queueArn);

        /**
         * @brief Updates a given queue.
         *
         * @param queue AWS region
         * @return updated queue
         */
        Entity::SQS::Queue UpdateQueue(Entity::SQS::Queue &queue);

        /**
         * @brief Count the number of queues for a given region.
         *
         * @param prefix queue name prefix
         * @param region AWS region
         * @return number of queues in the given region.
         */
        long CountQueues(const std::string &prefix = {}, const std::string &region = {}) const;

        /**
         * @brief Deletes a queue.
         *
         * @param queue queue entity
         * @throws DatabaseException
         */
        void DeleteQueue(const Entity::SQS::Queue &queue);

        /**
         * @brief Deletes all queues
         */
        void DeleteAllQueues();

        /**
         * @brief Creates a new message in the SQS message table
         *
         * @param message SQS message entity
         * @return saved message entity
         * @throws Core::DatabaseException
         */
        Entity::SQS::Message CreateMessage(const Entity::SQS::Message &message);

        /**
         * @brief Checks whether the message exists by receipt handle.
         *
         * @param receiptHandle receipt handle
         * @return true if message exists, otherwise false
         * @throws Core::DatabaseException
         */
        bool MessageExists(const std::string &receiptHandle);

        /**
         * @brief Returns a message by ID.
         *
         * @param oid message objectId
         * @return message entity
         * @throws Core::DatabaseException
         */
        Entity::SQS::Message GetMessageById(const std::string &oid);

        /**
         * @brief Updates a given message.
         *
         * @param message SQS message
         * @return updated message
         */
        Entity::SQS::Message UpdateMessage(Entity::SQS::Message &message);

        /**
         * @brief List all available resources
         *
         * @param region AWS region
         * @return list of SQS resources
         * @throws DatabaseException
         */
        Entity::SQS::MessageList ListMessages(const std::string &region = {});

        /**
         * @brief Receive messages from an queue.
         *
         * @param queueArn queue ARN
         * @param visibility in seconds
         * @param maxResult maximal message count to receive
         * @param dlQueueArn dead letter queue ARN
         * @param maxRetries maximal number of retries
         * @param messageList message list
         */
        void ReceiveMessages(const std::string &queueArn, int visibility, int maxResult, const std::string &dlQueueArn, int maxRetries, Entity::SQS::MessageList &messageList);

        /**
         * @brief Reset expired resources
         *
         * @param queueArn ARN of the queue
         * @param visibility visibilityTimeout period in seconds
         * @return number of message resets
         */
        long ResetMessages(const std::string &queueArn, long visibility);

        /**
         * @brief Redrive expired resources.
         *
         * @param queueArn ARN of the queue
         * @param redrivePolicy redrive policy
         * @param configuration AwsMock configuration
         */
        void RedriveMessages(const std::string &queueArn, const Entity::SQS::RedrivePolicy &redrivePolicy, const Core::Configuration &configuration);

        /**
         * @brief Any message, which has a message state is DELAYED is reset when the delay period is over.
         *
         * @param queueArn queue URL.
         * @param delay delay in seconds.
         * @reset number of delayed messages
         */
        long ResetDelayedMessages(const std::string &queueArn, long delay);

        /**
         * @brief Any message, which has is older than the retention period is deleted.
         *
         * @param queueUrl queue URL.
         * @param retentionPeriod retention period in seconds.
         * @return number of deleted messages
         */
        long MessageRetention(const std::string &queueUrl, long retentionPeriod);

        /**
          * @brief Returns a message by receipt handle.
          *
          * @param receiptHandle message receipt handle
          * @return message entity
          * @throws Core::DatabaseException
          */
        Entity::SQS::Message GetMessageByReceiptHandle(const std::string &receiptHandle);

        /**
         * @brief Count the number of message by state
         *
         * @param region AWS region
         * @param queueUrl URL of the queue
         */
        long CountMessages(const std::string &queueArn = {});

        /**
         * @brief Count the number of message by state
         *
         * @param queueArn ARN of the queue
         * @param status message state
         */
        long CountMessagesByStatus(const std::string &queueArn, Entity::SQS::MessageStatus status);

        /**
         * @brief Returns the average waiting time for messages in the given queue
         *
         * @par
         * Uses a simple min, max query to get the first and the last entry in the sqs_message collection. The average is then calculated as
         * (max-min)/2. This is done on a per queue arn basis.
         *
         * @return map of average message waiting time per queue
         * @throws Core::DatabaseException
         */
        Entity::SQS::MessageWaitTime GetAverageMessageWaitingTime();

        /**
         * @brief Deletes all resources of a queue
         *
         * @param queue message queue to delete resources from
         * @return number of messages deleted
         * @throws Core::DatabaseException
         */
        long DeleteMessages(const std::string &queue);

        /**
         * @brief Deletes a message.
         *
         * @param message message to delete
         * @return number of messages deleted
         * @throws Core::DatabaseException
         */
        long DeleteMessage(const Entity::SQS::Message &message);

        /**
         * @brief Deletes a message by receipt handle.
         *
         * @param receiptHandle message receipt handle
         * @return number of messages deleted
         * @throws Core::DatabaseException
         */
        long DeleteMessage(const std::string &receiptHandle);

        /**
         * @brief Deletes a resources.
         *
         * @throws Core::DatabaseException
         */
        void DeleteAllMessages();

      private:

        /**
         * SQS queue vector, when running without database
         */
        std::map<std::string, Entity::SQS::Queue> _queues{};

        /**
         * SQS message vector, when running without database
         */
        std::map<std::string, Entity::SQS::Message> _messages{};

        /**
         * Queue mutex
         */
        static Poco::Mutex sqsQueueMutex;

        /**
         * Message mutex
         */
        static Poco::Mutex _sqsMessageMutex;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_SQS_MEMORYDB_H
