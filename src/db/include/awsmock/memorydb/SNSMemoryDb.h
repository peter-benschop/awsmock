//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_SNSMEMORYDB_H
#define AWSMOCK_REPOSITORY_SNSMEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/sns/Topic.h>
#include <awsmock/entity/sns/Message.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

  class SNSMemoryDb {

  public:

    /**
     * Constructor
     */
    SNSMemoryDb();

    /**
     * Singleton instance
     */
    static SNSMemoryDb &instance() {
      static Poco::SingletonHolder<SNSMemoryDb> sh;
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
     * Count the number of message by state
     *
     * @param region AWS region
     * @param topicArn ARN of the topic
     */
    long CountMessages(const std::string &region = {}, const std::string &topicArn = {});

    /**
     * Count the number of message by state
     *
     * @param region AWS region
     * @param topicArn ARN of the topic
     * @param status message status
     */
    long CountMessagesByStatus(const std::string &region, const std::string &topicArn, Entity::SNS::MessageStatus status);

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
     * SNS topic vector, when running without database
     */
    std::map<std::string, Entity::SNS::Topic> _topics;

    /**
     * SNS message vector, when running without database
     */
    std::map<std::string, Entity::SNS::Message> _messages;

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SNSMEMORYDB_H
