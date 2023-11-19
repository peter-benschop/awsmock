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
     * Counts the number of topics
     *
     * @param region AWS region
     * @return number of topics
     */
    long CountTopics(const std::string &region = {});

    /**
     * Count the number of message by state
     *
     * @param region AWS region
     * @param topicArn ARN of the topic
     */
    long CountMessages(const std::string &region = {}, const std::string &topicArn = {});

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
