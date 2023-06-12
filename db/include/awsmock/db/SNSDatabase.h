//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_SNSDATABASE_H
#define AWSMOCK_DB_SNSDATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
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
#include <awsmock/db/SNSDatabase.h>
//#include <awsmock/entity/sqs/Message.h>
#include <awsmock/entity/sns/Topic.h>

namespace AwsMock::Database {

    class SNSDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit SNSDatabase(const Core::Configuration &configuration);

      /**
       * Check existence of topic
       *
       * @param region AWS region
       * @param name topic name
       * @return true if topic already exists
       * @throws DatabaseException
       */
      bool TopicExists(const std::string &region, const std::string &name);

      /**
       * Check existence of topic
       *
       * @param topicName topic ARN
       * @return true if topic already exists
       * @throws DatabaseException
       */
      bool TopicExists(const std::string &topicName);

      /**
       * Create a new topic in the SNS topic table
       *
       * @param topic topic entity
       * @return created SNS topic entity
       * @throws DatabaseException
       */
      Entity::SNS::Topic CreateTopic(const Entity::SNS::Topic& topic);

      /**
       * Returns a topic by primary key
       *
       * @param oid topic primary key
       * @return topic entity
       * @throws DatabaseException
       */
      Entity::SNS::Topic GetTopicById(bsoncxx::oid oid);

      /**
       * Returns a topic by primary key
       *
       * @param oid topic primary key
       * @return topic entity
       * @throws DatabaseException
       */
      Entity::SNS::Topic GetTopicById(const std::string &oid);

      /**
       * List all available topics
       *
       * @param region AWS region
       * @return list of SNS topics
       * @throws DatabaseException
       */
      Entity::SNS::TopicList ListTopics(const std::string &region);

      /**
       * Purge a given topicUrl.
       *
       * @param region AWS region
       * @param topicUrl topicUrl name
       */
      //void Purgetopic(const std::string &region, const std::string &topicUrl);

      /**
       * Deletes a topic.
       *
       * @param topic topic entity
       * @throws DatabaseException
       */
      void DeleteTopic(const Entity::SNS::Topic &topic);

      /**
       * Deletes all topics
       */
      void DeleteAllTopics();

      /**
       * Creates a new message in the SQS message table
       *
       * @param message SQS message entity
       * @return saved message entity
       * @throws Core::DatabaseException
       */
      //Entity::SQS::Message CreateMessage(const Entity::SQS::Message &message);

      /**
       * Returns a message by ID.
       *
       * @param oid message objectId
       * @return message entity
       * @throws Core::DatabaseException
       */
      //Entity::SQS::Message GetMessageById(bsoncxx::oid oid);

      /**
       * Returns a message by ID.
       *
       * @param oid message objectId
       * @return message entity
       * @throws Core::DatabaseException
       */
      //Entity::SQS::Message GetMessageById(const std::string & oid);

      /**
       * Returns a message by receipt handle.
       *
       * @param receiptHandle message receipt handle
       * @return message entity
       * @throws Core::DatabaseException
       */
      //Entity::SQS::Message GetMessageByReceiptHandle(const std::string &receiptHandle);

      /**
       * Receive messages from an topic.
       *
       * @param region AWS region
       * @param topicUrl topic URL
       * @param messageList message list
       * @return MessageList
       */
      //void ReceiveMessages(const std::string &region, const std::string &topicUrl, Entity::SQS::MessageList &messageList);

      /**
       * Reset expired messages
       *
       * @param topicUrl URL of the topic
       * @param visibility visibility period in seconds
       */
      //[[maybe_unused]] void ResetMessages(const std::string& topicUrl, long visibility);

      /**
       * Count the number of message by status
       *
       * @param topicUrl URL of the topic
       * @param visibility visibility period in seconds
       */
      //[[maybe_unused]] long CountMessages(const std::string &region, const std::string& topicUrl);

      /**
       * Count the number of message by status
       *
       * @param topicUrl URL of the topic
       * @param visibility visibility period in seconds
       */
      //[[maybe_unused]] long CountMessagesByStatus(const std::string &region, const std::string& topicUrl, int status);

      /**
       * Deletes a message.
       *
       * @param message message to delete
       * @throws Core::DatabaseException
       */
      //void DeleteMessage(const Entity::SQS::Message &message);

      /**
       * Deletes a messages.
       *
       * @throws Core::DatabaseException
       */
      //void DeleteAllMessages();

    private:

      /**
       * Logger
       */
      Poco::LogStream _logger;

      /**
       * SNS topic collection
       */
      mongocxx::collection _topicCollection{};

      /**
       * SNS message collection
       */
      mongocxx::collection _messageCollection{};
    };

} // namespace AwsMock::Database

#endif // AWSMOCK_DB_SNSDatabase_H
