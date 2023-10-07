//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SNSDATABASE_H
#define AWSMOCK_REPOSITORY_SNSDATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/Database.h>
#include <awsmock/entity/sns/Message.h>
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
       * Returns a topic by is ARN
       *
       * @param topicArn topic ARN
       * @return topic entity
       * @throws DatabaseException
       */
      Entity::SNS::Topic GetTopicByArn(const std::string &topicArn);

      /**
       * Updates an existing topic in the SNS topic table
       *
       * @param topic topic entity
       * @return updated SNS topic entity
       * @throws DatabaseException
       */
      Entity::SNS::Topic UpdateTopic(const Entity::SNS::Topic& topic);

      /**
       * List all available topics
       *
       * @param region AWS region
       * @return list of SNS topics
       * @throws DatabaseException
       */
      Entity::SNS::TopicList ListTopics(const std::string &region = {});

      /**
       * Counts the number of topics
       *
       * @param region AWS region
       * @return number of topics
       */
      long CountTopics(const std::string &region = {});

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
      Entity::SNS::Message CreateMessage(const Entity::SNS::Message &message);

      /**
       * Returns a message by ID.
       *
       * @param oid message objectId
       * @return message entity
       * @throws Core::DatabaseException
       */
      Entity::SNS::Message GetMessageById(bsoncxx::oid oid);

      /**
       * Returns a message by ID.
       *
       * @param oid message objectId
       * @return message entity
       * @throws Core::DatabaseException
       */
      [[maybe_unused]] Entity::SNS::Message GetMessageById(const std::string & oid);

      /**
       * Count the number of message by status
       *
       * @param topicUrl URL of the topic
       * @param visibility visibility period in seconds
       */
      long CountMessages(const std::string &region = {}, const std::string& topicUrl = {});

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
      void DeleteMessage(const Entity::SNS::Message &message);

      /**
       * Bulk delete of messages.
       *
       * @param region AWS region
       * @param topicArn topic ARN
       * @param receipts vector of receipts
       * @throws Core::DatabaseException
       */
      void DeleteMessages(const std::string &region, const std::string &topicArn, const std::vector<std::string> &receipts);

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
       * SNS topic collection
       */
      mongocxx::collection _topicCollection{};

      /**
       * SNS message collection
       */
      mongocxx::collection _messageCollection{};
    };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SNSDatabase_H
