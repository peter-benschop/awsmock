//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_SQSDATABASE_H
#define AWSMOCK_DB_SQSDATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include "Poco/Logger.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/RecordSet.h"
#include "Poco/Data/SQLite/Connector.h"

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/db/Database.h>
#include <awsmock/entity/sqs/Queue.h>
#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Database {

    class SQSDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit SQSDatabase(const Core::Configuration &configuration);

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
       * @param queueUrl AWS region
       * @return true if queue already exists
       * @throws DatabaseException
       */
      bool QueueExists(const std::string &queueUrl);

      /**
       * Create a new queue in the SQS queue table
       *
       * @param queue queue entity
       * @return created SQS queue entity
       * @throws DatabaseException
       */
      Entity::SQS::Queue CreateQueue(const Entity::SQS::Queue& queue);

      /**
       * Returns a queue by primary key
       *
       * @param id queue primary key
       * @return queue entity
       * @throws DatabaseException
       */
      Entity::SQS::Queue GetQueueById(long id);

      /**
       * List all available queues
       *
       * @param region AWS region
       * @return List of SQS queues
       * @throws DatabaseException
       */
      Entity::SQS::QueueList ListQueues(const std::string &region);

      /**
       * Purge a given queueUrl.
       *
       * @param region AWS region
       * @param queueUrl queueUrl name
       */
      void PurgeQueue(const std::string &region, const std::string &queueUrl);

      /**
       * Creates a new message in the SQS message table
       *
       * @param message SQS message entity
       * @return saved message entity
       * @throws Core::DatabaseException
       */
      Entity::SQS::Message CreateMessage(const Entity::SQS::Message &message);

      /**
       * Returns a message by ID.
       *
       * @param id message ID
       * @return message entity
       * @throws Core::DatabaseException
       */
      Entity::SQS::Message GetMessageById(long id);

      /**
       * Receive messages from an queue.
       *
       * @param region AWS region
       * @param queueUrl queue URL
       * @param maxMessages maximal number of messages
       * @return MessageList
       */
      Entity::SQS::MessageList ReceiveMessages(const std::string &region, const std::string &queueUrl, int maxMessages);

      /**
       * Reset expired messages
       *
       * @param queueUrl URL of the queue
       * @param visibility visibility period in seconds
       */
      [[maybe_unused]] void ResetMessages(const std::string& queueUrl, long visibility);

      /**
       * Delete a queue.
       *
       * @param queue queue entity
       * @throws DatabaseException
       */
      void DeleteQueue(const Entity::SQS::Queue &queue);

      /**
       * Deletes a message.
       *
       * @param message message to delete
       * @throws Core::DatabaseException
       */
      void DeleteMessage(const Entity::SQS::Message &message);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

    };

} // namespace AwsMock::Database

#endif // AWSMOCK_DB_SQSDATABASE_H
