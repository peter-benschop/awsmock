//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_SQS_MEMORYDB_H
#define AWSMOCK_REPOSITORY_SQS_MEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * SQS in-memory database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSMemoryDb {

      public:

        /**
         * Constructor
         */
        SQSMemoryDb() = default;

        /**
         * Singleton instance
         */
        static SQSMemoryDb &instance() {
            static Poco::SingletonHolder<SQSMemoryDb> sh;
            return *sh.get();
        }

        /**
         * Check existence of queue
         *
         * @param region AWS region
         * @param name queue name
         * @return true if queue already exists
         * @throws DatabaseException
         */
        bool QueueExists(const std::string &region, const std::string &name);

        /**
         * Check existence of queue
         *
         * @param region AWS region
         * @param queueUrl AWS region
         * @return true if queue already exists
         * @throws DatabaseException
         */
        bool QueueUrlExists(const std::string &region, const std::string &queueUrl);

        /**
         * Check existence of queue by ARN
         *
         * @param queueArn queue ARN
         * @return true in case queue exists
         * @throws DatabaseException
         */
        bool QueueArnExists(const std::string &queueArn);

        /**
         * Create a new queue in the SQS queue table
         *
         * @param queue queue entity
         * @return created SQS queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue CreateQueue(const Entity::SQS::Queue &queue);

        /**
         * Returns a queue by primary key
         *
         * @param oid queue primary key
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueById(const std::string &oid);

        /**
         * List all available queues
         *
         * @param region AWS region
         * @return List of SQS queues
         * @throws DatabaseException
         */
        Entity::SQS::QueueList ListQueues(const std::string &region = {});

        /**
         * Returns a queue by ARN
         *
         * @param queueArn queue ARN
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueByArn(const std::string &queueArn);

        /**
         * Returns a queue by name and region
         *
         * @param region AWS region
         * @param queueName queue name
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueByName(const std::string &region, const std::string &queueName);

        /**
         * Returns a queue by URL
         *
         * @param queueUrl queue URL
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueByUrl(const std::string &queueUrl);

        /**
         * Purge a given queueUrl.
         *
         * @param region AWS region
         * @param queueUrl queueUrl name
         */
        void PurgeQueue(const std::string &region, const std::string &queueUrl);

        /**
         * Updates a given queue.
         *
         * @param queue AWS region
         * @return updated queue
         */
        Entity::SQS::Queue UpdateQueue(Entity::SQS::Queue &queue);

        /**
         * Count the number of queues for a given region.
         *
         * @param region AWS region
         * @return number of queues in the given region.
         */
        long CountQueues(const std::string &region = {});

        /**
         * Deletes a queue.
         *
         * @param queue queue entity
         * @throws DatabaseException
         */
        void DeleteQueue(const Entity::SQS::Queue &queue);

        /**
         * Deletes all queues
         */
        void DeleteAllQueues();

        /**
         * Creates a new message in the SQS message table
         *
         * @param message SQS message entity
         * @return saved message entity
         * @throws Core::DatabaseException
         */
        Entity::SQS::Message CreateMessage(const Entity::SQS::Message &message);

        /**
         * Checks whether the message exists by receipt handle.
         *
         * @param receiptHandle receipt handle
         * @return true if message exists, otherwise false
         * @throws Core::DatabaseException
         */
        bool MessageExists(const std::string &receiptHandle);

        /**
         * Returns a message by ID.
         *
         * @param oid message objectId
         * @return message entity
         * @throws Core::DatabaseException
         */
        Entity::SQS::Message GetMessageById(const std::string &oid);

        /**
         * Updates a given message.
         *
         * @param message SQS message
         * @return updated message
         */
        Entity::SQS::Message UpdateMessage(Entity::SQS::Message &message);

        /**
         * List all available messages
         *
         * @param region AWS region
         * @return list of SQS messages
         * @throws DatabaseException
         */
        Entity::SQS::MessageList ListMessages(const std::string &region = {});

        /**
         * Receive messages from a queue.
         *
         * @param region AWS region
         * @param queueUrl queue URL
         * @param visibility in seconds
         * @param maxMessages maximal number of messages
         * @param messageList message list
         */
        void ReceiveMessages(const std::string &region, const std::string &queueUrl, int visibility, int maxMessages, Entity::SQS::MessageList &messageList);

        /**
         * Reset expired messages
         *
         * @param queueUrl URL of the queue
         * @param visibility visibilityTimeout period in seconds
         */
        [[maybe_unused]] void ResetMessages(const std::string &queueUrl, long visibility);

        /**
         * Redrive expired messages.
         *
         * @param queueUrl URL of the queue
         * @param redrivePolicy redrive policy
         * @param configuration AwsMock configuration
         */
        void RedriveMessages(const std::string &queueUrl, const Entity::SQS::RedrivePolicy &redrivePolicy, const Core::Configuration &configuration);

        /**
         * Any message, which has a message state is DELAYED is reset when the delay period is over.
         *
         * @param queueUrl queue URL.
         * @param delay delay in seconds.
         */
        void ResetDelayedMessages(const std::string &queueUrl, long delay);

        /**
         * Any message, which has is older than the retention period is deleted.
         *
         * @param queueUrl queue URL.
         * @param retentionPeriod retention period in seconds.
         */
        void MessageRetention(const std::string &queueUrl, long retentionPeriod);

        /**
          * Returns a message by receipt handle.
          *
          * @param receiptHandle message receipt handle
          * @return message entity
          * @throws Core::DatabaseException
          */
        Entity::SQS::Message GetMessageByReceiptHandle(const std::string &receiptHandle);

        /**
         * Count the number of message by state
         *
         * @param region AWS region
         * @param queueUrl URL of the queue
         */
        long CountMessages(const std::string &region = {}, const std::string &queueUrl = {});

        /**
         * Count the number of message by state
         *
         * @param region AWS region
         * @param queueUrl URL of the queue
         * @param status message state
         */
        long CountMessagesByStatus(const std::string &region, const std::string &queueUrl, Entity::SQS::MessageStatus status);

        /**
         * Deletes all messages of a queue
         *
         * @param queue message queue to delete messages from
         * @throws Core::DatabaseException
         */
        void DeleteMessages(const std::string &queue);

        /**
         * Deletes a message.
         *
         * @param message message to delete
         * @throws Core::DatabaseException
         */
        void DeleteMessage(const Entity::SQS::Message &message);

        /**
         * Deletes a message by receipt handle.
         *
         * @param receiptHandle message receipt handle
         * @throws Core::DatabaseException
         */
        void DeleteMessage(const std::string &receiptHandle);

        /**
         * Deletes a messages.
         *
         * @throws Core::DatabaseException
         */
        void DeleteAllMessages();

      private:

        /**
         * SQS queue vector, when running without database
         */
        std::map<std::string, Entity::SQS::Queue> _queues;

        /**
         * SQS message vector, when running without database
         */
        std::map<std::string, Entity::SQS::Message> _messages;

        /**
         * Queue mutex
         */
        Poco::Mutex _queueMutex;

        /**
         * Message mutex
         */
        Poco::Mutex _messageMutex;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_SQS_MEMORYDB_H
