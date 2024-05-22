//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SNS_DATABASE_H
#define AWSMOCK_REPOSITORY_SNS_DATABASE_H

// C++ standard includes
#include <iostream>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>

// AwsMock includes
#include "awsmock/core/exception/DatabaseException.h"
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/sns/Message.h>
#include <awsmock/entity/sns/Topic.h>
#include <awsmock/memorydb/SNSMemoryDb.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * SNS MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSDatabase : public DatabaseBase {

      public:

        /**
         * Constructor
         *
         * @param configuration configuration properties
         */
        explicit SNSDatabase();

        /**
         * Singleton instance
         */
        static SNSDatabase &instance() {
            static Poco::SingletonHolder<SNSDatabase> sh;
            return *sh.get();
        }

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
        Entity::SNS::Topic CreateTopic(const Entity::SNS::Topic &topic);

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
         * Returns a topic by its region and name
         *
         * @param region AWS region
         * @param topicName topic name
         * @return topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic GetTopicByName(const std::string &region, const std::string &topicName);

        /**
         * Return a list of topics with the given subscription ARN
         *
         * @param subscriptionArn subscription ARN
         * @return topic with given topic ARN
         */
        Entity::SNS::TopicList GetTopicsBySubscriptionArn(const std::string &subscriptionArn);

        /**
         * Updates an existing topic in the SNS topic table
         *
         * @param topic topic entity
         * @return updated SNS topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic UpdateTopic(const Entity::SNS::Topic &topic);

        /**
         * Create a new topic or updates an existing topic
         *
         * @param topic topic entity
         * @return created or updated SNS topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic CreateOrUpdateTopic(Entity::SNS::Topic &topic);

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
         * Check existence of message
         *
         * @param id message ID
         * @return true if message already exists
         * @throws DatabaseException
         */
        bool MessageExists(const std::string &id);

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
        [[maybe_unused]] Entity::SNS::Message GetMessageById(const std::string &oid);

        /**
         * Count the number of message by state
         *
         * @param region AWS region
         * @param topicUrl URL of the topic
         */
        long CountMessages(const std::string &region = {}, const std::string &topicUrl = {});

        /**
         * Count the number of message by state
         *
         * @param region AWS region
         * @param topicArn ARN of the topic
         * @param status message status
         */
        long CountMessagesByStatus(const std::string &region, const std::string &topicArn, Entity::SNS::MessageStatus status);

        /**
         * List all available resources
         *
         * @param region AWS region
         * @return list of SNS resources
         * @throws DatabaseException
         */
        Entity::SNS::MessageList ListMessages(const std::string &region = {});

        /**
         * Updates an existing message
         *
         * @param message message entity
         * @return created or updated SNS message entity
         * @throws DatabaseException
         */
        Entity::SNS::Message UpdateMessage(Entity::SNS::Message &message);

        /**
         * Create a new queue or updates an existing message
         *
         * @param message message entity
         * @return created or updated SNS message entity
         * @throws DatabaseException
         */
        Entity::SNS::Message CreateOrUpdateMessage(Entity::SNS::Message &message);

        /**
         * Deletes a message.
         *
         * @param message message to delete
         * @throws Core::DatabaseException
         */
        void DeleteMessage(const Entity::SNS::Message &message);

        /**
         * Bulk delete of resources.
         *
         * @param region AWS region
         * @param topicArn topic ARN
         * @param receipts vector of receipts
         * @throws Core::DatabaseException
         */
        void DeleteMessages(const std::string &region, const std::string &topicArn, const std::vector<std::string> &receipts);

        /**
         * Deletes old resources message.
         *
         * @param timeout timeout in seconds
         * @throws Core::DatabaseException
         */
        void DeleteOldMessages(long timeout);

        /**
         * Deletes a resources.
         *
         * @throws Core::DatabaseException
         */
        void DeleteAllMessages();

      private:

        /**
         * Use MongoDB
         */
        bool _useDatabase;

        /**
         * Database name
         */
        std::string _databaseName;

        /**
         * Topic collection name
         */
        std::string _topicCollectionName;

        /**
         * Message collection name
         */
        std::string _messageCollectionName;

        /**
         * SNS in-memory database
         */
        SNSMemoryDb &_memoryDb;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_SNS_DATABASE_H
