//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SQS_DATABASE_H
#define AWSMOCK_REPOSITORY_SQS_DATABASE_H

// C++ standard includes
#include <chrono>
#include <iostream>
#include <iterator>
#include <string>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/options/find_one_and_update.hpp>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/SortColumn.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/sqs/MessageWaitTime.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/memorydb/SQSMemoryDb.h>
#include <awsmock/repository/Database.h>
#include <awsmock/utils/MongoUtils.h>

namespace AwsMock::Database {

    using std::chrono::system_clock;

    /**
     * @brief SQS MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SQSDatabase : public DatabaseBase {

      public:

        /**
         * @brief Constructor
         */
        explicit SQSDatabase();

        /**
         * @brief Singleton instance
         */
        static SQSDatabase &instance() {
            static SQSDatabase sqsDatabase;
            return sqsDatabase;
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
        Entity::SQS::Queue CreateQueue(Entity::SQS::Queue &queue);

        /**
         * @brief Returns a queue by primary key
         *
         * @param oid queue primary key
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueById(bsoncxx::oid oid);

        /**
         * @brief Returns a queue by primary key
         *
         * @param oid queue primary key
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueById(const std::string &oid);

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
         * @param region AWS region
         * @param queueUrl queue URL
         * @return queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue GetQueueByUrl(const std::string &region, const std::string &queueUrl);

        /**
         * @brief List available queues, using paging
         *
         * @param prefix queue name prefix
         * @param pageSize maximal number of results
         * @param pageIndex pge index
         * @param sortColumns vector of sort columns
         * @param region AWS region
         * @return List of SQS queues
         * @throws DatabaseException
         */
        Entity::SQS::QueueList ListQueues(const std::string &prefix, int pageSize, int pageIndex, const std::vector<Core::SortColumn> &sortColumns, const std::string &region = {});

        /**
         * @brief List all available queues
         *
         * @param region AWS region
         * @return List of SQS queues
         * @throws DatabaseException
         */
        Entity::SQS::QueueList ListQueues(const std::string &region = {});

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
         * @brief Create a new queue or updates an existing queue
         *
         * @param queue queue entity
         * @return created SQS queue entity
         * @throws DatabaseException
         */
        Entity::SQS::Queue CreateOrUpdateQueue(Entity::SQS::Queue &queue);

        /**
         * @brief Count the number of queues for a given region.
         *
         * @param prefix queue name prefix
         * @param region AWS region
         * @return number of queues in the given region.
         */
        long CountQueues(const std::string &prefix = {}, const std::string &region = {});

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
        Entity::SQS::Message CreateMessage(Entity::SQS::Message &message);

        /**
         * @brief Checks whether the message exists by receipt handle.
         *
         * @param receiptHandle SQS message receipt handle
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
        Entity::SQS::Message GetMessageById(bsoncxx::oid oid);

        /**
         * @brief Returns a message by ID.
         *
         * @param oid message objectId
         * @return message entity
         * @throws Core::DatabaseException
         */
        Entity::SQS::Message GetMessageById(const std::string &oid);

        /**
         * @brief Returns a message by receipt handle.
         *
         * @param receiptHandle message receipt handle
         * @return message entity
         * @throws Core::DatabaseException
         */
        Entity::SQS::Message GetMessageByReceiptHandle(const std::string &receiptHandle);

        /**
         * @brief Updates a given message.
         *
         * @param message SQS message
         * @return updated message
         */
        Entity::SQS::Message UpdateMessage(Entity::SQS::Message &message);

        /**
         * @brief Create a new queue or updates an existing message
         *
         * @param message message entity
         * @return created or updated SQS message entity
         * @throws DatabaseException
         */
        Entity::SQS::Message CreateOrUpdateMessage(Entity::SQS::Message &message);

        /**
         * @brief List all available resources
         *
         * @param region AWS region
         * @return list of SQS resources
         * @throws DatabaseException
         */
        Entity::SQS::MessageList ListMessages(const std::string &region = {});

        /**
         * @brief Paged list of messages
         *
         * @param queueArn queue ARN
         * @param pageSize page size
         * @param pageIndex page index
         * @param sortColumns sorting columns array
         * @return list of SQS messages
         * @throws DatabaseException
         */
        Entity::SQS::MessageList ListMessages(const std::string &queueArn, int pageSize, int pageIndex, const std::vector<Core::SortColumn> &sortColumns);

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
         * @param queueUrl URL of the queue
         * @param visibility visibilityTimeout period in seconds
         * @return number of message resets
         */
        long ResetMessages(const std::string &queueUrl, long visibility);

        /**
         * @brief Redrive expired resources.
         *
         * @param queueArn ARN of the queue
         * @param redrivePolicy redrive policy
         */
        void RedriveMessages(const std::string &queueArn, const Entity::SQS::RedrivePolicy &redrivePolicy);

        /**
         * @brief Any message, which has a message state is DELAYED is reset when the delay period is over.
         *
         * @param queueArn queue ARN.
         * @param delay delay in seconds.
         * @return number of updated queues
         */
        long ResetDelayedMessages(const std::string &queueArn, long delay);

        /**
         * @brief Any message, which has is older than the retention period is deleted.
         *
         * @param queueArn queue ARN.
         * @param retentionPeriod retention period in seconds.
         * @return number of messages deleted.
         */
        long MessageRetention(const std::string &queueArn, long retentionPeriod);

        /**
         * @brief  Count the number of message by state
         *
         * @param queueArn ARN of the queue
         * @return total number of messages
         */
        long CountMessages(const std::string &queueArn = {});

        /**
         * @brief  Count the number of message by state
         *
         * @param queueArn ARN of the queue
         * @return total message size
         */
        long CountMessageSize(const std::string &queueArn = {});

        /**
         * @brief Count the number of message by state
         *
         * @param queueArn ARN of the queue
         * @param status message state
         */
        long CountMessagesByStatus(const std::string &queueArn, Entity::SQS::MessageStatus status);

        /**
         * @brief Converts a message object to a JSON string
         *
         * @param document message document
         * @return message converted to JSON string
         * @throws Core::DatabaseException
         */
        static std::string ConvertMessageToJson(mongocxx::stdx::optional<bsoncxx::document::value> document);

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
         * @brief Deletes all messages of a queue
         *
         * @param queueArn message queue ARN to delete messages from
         * @return number of messages deleted
         * @throws Core::DatabaseException
         */
        long DeleteMessages(const std::string &queueArn);

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
        std::map<std::string, Entity::SQS::Queue> _queues;

        /**
         * SQS message vector, when running without database
         */
        std::map<std::string, Entity::SQS::Message> _messages;

        /**
         * Database name
         */
        std::string _databaseName;

        /**
         * Queue collection name
         */
        std::string _collectionNameQueue;

        /**
         * Message collection name
         */
        std::string _collectionNameMessage;

        /**
         * SQS in-memory database
         */
        SQSMemoryDb &_memoryDb;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_SQS_DATABASE_H
