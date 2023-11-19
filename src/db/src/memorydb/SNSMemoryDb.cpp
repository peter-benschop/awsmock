//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/SNSMemoryDb.h>

namespace AwsMock::Database {

  SNSMemoryDb::SNSMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

  bool SNSMemoryDb::TopicExists(const std::string &region, const std::string &name) {

    return find_if(_topics.begin(), _topics.end(), [region, name](const std::pair<std::string, Entity::SNS::Topic> &topic) {
      return topic.second.region == region && topic.second.topicName == name;
    }) != _topics.end();

  }

  bool SNSMemoryDb::TopicExists(const std::string &name) {

    return find_if(_topics.begin(), _topics.end(), [name](const std::pair<std::string, Entity::SNS::Topic> &topic) {
      return topic.second.topicName == name;
    }) != _topics.end();

  }

  Entity::SNS::Topic SNSMemoryDb::GetTopicById(const std::string &oid) {

    auto it = find_if(_topics.begin(), _topics.end(), [oid](const std::pair<std::string, Entity::SNS::Topic> &queue) {
      return queue.first == oid;
    });

    if (it != _topics.end()) {
      it->second.oid = oid;
      return it->second;
    }
    return {};
  }

  Entity::SNS::Topic SNSMemoryDb::CreateTopic(const Entity::SNS::Topic &topic) {

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _topics[oid] = topic;
    log_trace_stream(_logger) << "Topic created, oid: " << oid << std::endl;
    return GetTopicById(oid);

  }

  long SNSMemoryDb::CountTopics(const std::string &region) {

    long count = 0;
    if(region.empty()) {

      count = _topics.size();

    } else {

      for (const auto &topic : _topics) {
        if (topic.second.region == region) {
          count++;
        }
      }
    }
    return count;
  }

  long SNSMemoryDb::CountMessages(const std::string &region, const std::string &topicArn) {

    long count = 0;
    for (const auto &message : _messages) {
      if (!region.empty() && message.second.region == region && !topicArn.empty() && message.second.topicArn == topicArn) {
        count++;
      } else if(!region.empty() && message.second.region == region) {
        count++;
      } else if(!topicArn.empty() && message.second.topicArn == topicArn) {
        count++;
      }
    }
    return count;
  }

}