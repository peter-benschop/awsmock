//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SNS_DATABASE_H
#define AWSMOCK_REPOSITORY_SNS_DATABASE_H

// C++ standard includes
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/entity/sns/Message.h>
#include <awsmock/entity/sns/Topic.h>
#include <awsmock/memorydb/SNSMemoryDb.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    using std::chrono::system_clock;

    /**
     * @brief SNS MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SNSDatabase : public DatabaseBase {

      public:

        /**
         * @brief Constructor
         */
        explicit SNSDatabase();

        /**
         * Singleton instance
         */
        static SNSDatabase &instance() {
            static SNSDatabase snsDatabase;
            return snsDatabase;
        }

        /**
         * @brief Check existence of topic
         *
         * @param region AWS region
         * @param name topic name
         * @return true if topic already exists
         * @throws DatabaseException
         */
        bool TopicExists(const std::string &region, const std::string &name);

        /**
         * @brief Check existence of topic
         *
         * @param topicName topic ARN
         * @return true if topic already exists
         * @throws DatabaseException
         */
        bool TopicExists(const std::string &topicName);

        /**
         * @brief Create a new topic in the SNS topic table
         *
         * @param topic topic entity
         * @return created SNS topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic CreateTopic(Entity::SNS::Topic &topic);

        /**
         * @brief Returns a topic by primary key
         *
         * @param oid topic primary key
         * @return topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic GetTopicById(bsoncxx::oid oid);

        /**
         * @brief Returns a topic by primary key
         *
         * @param oid topic primary key
         * @return topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic GetTopicById(const std::string &oid);

        /**
         * @brief Returns a topic by is ARN
         *
         * @param topicArn topic ARN
         * @return topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic GetTopicByArn(const std::string &topicArn);

        /**
         * @brief Returns a topic by its region and name
         *
         * @param region AWS region
         * @param topicName topic name
         * @return topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic GetTopicByName(const std::string &region, const std::string &topicName);

        /**
         * @brief Return a list of topics with the given subscription ARN
         *
         * @param subscriptionArn subscription ARN
         * @return topic with given topic ARN
         */
        Entity::SNS::TopicList GetTopicsBySubscriptionArn(const std::string &subscriptionArn);

        /**
         * @brief Updates an existing topic in the SNS topic table
         *
         * @param topic topic entity
         * @return updated SNS topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic UpdateTopic(Entity::SNS::Topic &topic);

        /**
         * @brief Create a new topic or updates an existing topic
         *
         * @param topic topic entity
         * @return created or updated SNS topic entity
         * @throws DatabaseException
         */
        Entity::SNS::Topic CreateOrUpdateTopic(Entity::SNS::Topic &topic);

        /**
         * @brief List all available topics
         *
         * @param region AWS region
         * @return list of SNS topics
         * @throws DatabaseException
         */
        Entity::SNS::TopicList ListTopics(const std::string &region = {});

        /**
         * @brief Counts the number of topics
         *
         * @param region AWS region
         * @return number of topics
         */
        long CountTopics(const std::string &region = {});

        /**
         * @brief Deletes a topic.
         *
         * @param topic topic entity
         * @throws DatabaseException
         */
        void DeleteTopic(const Entity::SNS::Topic &topic);

        /**
         * @brief Deletes all topics
         */
        void DeleteAllTopics();

        /**
         * @brief Check existence of message
         *
         * @param id message ID
         * @return true if message already exists
         * @throws DatabaseException
         */
        bool MessageExists(const std::string &id);

        /**
         * @brief Creates a new message in the SQS message table
         *
         * @param message SQS message entity
         * @return saved message entity
         * @throws Core::DatabaseException
         */
        Entity::SNS::Message CreateMessage(Entity::SNS::Message &message);

        /**
         * @brief Returns a message by ID.
         *
         * @param oid message objectId
         * @return message entity
         * @throws Core::DatabaseException
         */
        Entity::SNS::Message GetMessageById(bsoncxx::oid oid);

        /**
         * @brief Returns a message by ID.
         *
         * @param oid message objectId
         * @return message entity
         * @throws Core::DatabaseException
         */
        [[maybe_unused]] Entity::SNS::Message GetMessageById(const std::string &oid);

        /**
         * @brief Count the number of message by state
         *
         * @param region AWS region
         * @param topicUrl URL of the topic
         */
        long CountMessages(const std::string &region = {}, const std::string &topicUrl = {});

        /**
         * @brief Count the number of message by state
         *
         * @param region AWS region
         * @param topicArn ARN of the topic
         * @param status message status
         */
        long CountMessagesByStatus(const std::string &region, const std::string &topicArn, Entity::SNS::MessageStatus status);

        /**
         * @brief List all available resources
         *
         * @param region AWS region
         * @param topicArn AWS topic ARN
         * @return list of SNS messages
         * @throws DatabaseException
         */
        Entity::SNS::MessageList ListMessages(const std::string &region = {}, const std::string &topicArn = {});

        /**
         * @brief Paged list all available messages
         *
         * @param region AWS region
         * @param topicArn AWS topic ARN
         * @param pageSize page size
         * @param pageIndex page index
         * @return list of SNS messages
         * @throws DatabaseException
         */
        Entity::SNS::MessageList ListMessages(const std::string &region, const std::string &topicArn, int pageSize, int pageIndex);

        /**
         * @brief Updates an existing message
         *
         * @param message message entity
         * @return created or updated SNS message entity
         * @throws DatabaseException
         */
        Entity::SNS::Message UpdateMessage(Entity::SNS::Message &message);

        /**
         * @brief Create a new queue or updates an existing message
         *
         * @param message message entity
         * @return created or updated SNS message entity
         * @throws DatabaseException
         */
        Entity::SNS::Message CreateOrUpdateMessage(Entity::SNS::Message &message);

        /**
         * @brief Deletes a message.
         *
         * @param message message to delete
         * @throws Core::DatabaseException
         */
        void DeleteMessage(const Entity::SNS::Message &message);

        /**
         * @brief Bulk delete of resources.
         *
         * @param region AWS region
         * @param topicArn topic ARN
         * @param receipts vector of receipts
         * @throws Core::DatabaseException
         */
        void DeleteMessages(const std::string &region, const std::string &topicArn, const std::vector<std::string> &receipts);

        /**
         * @brief Deletes old resources message.
         *
         * @param timeout timeout in seconds
         * @throws Core::DatabaseException
         */
        void DeleteOldMessages(long timeout);

        /**
         * @brief Deletes a resources.
         *
         * @throws Core::DatabaseException
         */
        void DeleteAllMessages();

      private:

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
