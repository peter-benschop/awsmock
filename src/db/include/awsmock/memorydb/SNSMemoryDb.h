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
