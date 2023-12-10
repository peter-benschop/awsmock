//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SQSDATABASE_H
#define AWSMOCK_REPOSITORY_SQSDATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/options/find_one_and_update.hpp>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/memorydb/SQSMemoryDb.h>
#include <awsmock/repository/Database.h>
#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Database {

  class SQSDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit SQSDatabase(Core::Configuration &configuration);

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
      Entity::SQS::Queue GetQueueById(bsoncxx::oid oid);

      /**
       * Returns a queue by primary key
       *
       * @param oid queue primary key
       * @return queue entity
       * @throws DatabaseException
       */
      Entity::SQS::Queue GetQueueById(const std::string &oid);

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
      Entity::SQS::Queue GetQueueByUrl(const std::string &region, const std::string &queueUrl);

      /**
       * List all available queues
       *
       * @param region AWS region
       * @return List of SQS queues
       * @throws DatabaseException
       */
      Entity::SQS::QueueList ListQueues(const std::string &region = {});

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
       * Converts a queue object to a JSON string
       *
       * @param queue queue entity
       * @return queue converted to JSON string
       * @throws Core::DatabaseException
       */
      //static std::string ConvertQueueToJson(const Entity::SQS::Queue &queue);

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
       * @param messageId message ID
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
      Entity::SQS::Message GetMessageById(bsoncxx::oid oid);

      /**
       * Returns a message by ID.
       *
       * @param oid message objectId
       * @return message entity
       * @throws Core::DatabaseException
       */
      Entity::SQS::Message GetMessageById(const std::string &oid);

      /**
       * Returns a message by receipt handle.
       *
       * @param receiptHandle message receipt handle
       * @return message entity
       * @throws Core::DatabaseException
       */
      Entity::SQS::Message GetMessageByReceiptHandle(const std::string &receiptHandle);

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
       * Receive messages from an queue.
       *
       * @param region AWS region
       * @param queueUrl queue URL
       * @param visibility in seconds
       * @param count message count to receive
       * @param messageList message list
       */
      void ReceiveMessages(const std::string &region, const std::string &queueUrl, int visibility, int count, Entity::SQS::MessageList &messageList);

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
       */
      void RedriveMessages(const std::string &queueUrl, const Entity::SQS::RedrivePolicy &redrivePolicy);

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
       * Converts a message object to a JSON string
       *
       * @param document message document
       * @return message converted to JSON string
       * @throws Core::DatabaseException
       */
      static std::string ConvertMessageToJson(mongocxx::stdx::optional<bsoncxx::document::value> document);

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
       * Deletes a messages.
       *
       * @throws Core::DatabaseException
       */
      void DeleteAllMessages();

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * AwsMock configuration
       */
      Core::Configuration &_configuration;

      /**
       * SQS queue collection
       */
      mongocxx::collection _queueCollection{};

      /**
       * SQS message collection
       */
      mongocxx::collection _messageCollection{};

      /**
       * SQS queue vector, when running without database
       */
      std::map<std::string, Entity::SQS::Queue> _queues;

      /**
       * SQS message vector, when running without database
       */
      std::map<std::string, Entity::SQS::Message> _messages;

      /**
       * SQS in-memory database
       */
      SQSMemoryDb &_memoryDb;
  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SQSDATABASE_H
