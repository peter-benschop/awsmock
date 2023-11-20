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

    auto it = find_if(_topics.begin(), _topics.end(), [oid](const std::pair<std::string, Entity::SNS::Topic> &topic) {
      return topic.first == oid;
    });

    if (it != _topics.end()) {
      it->second.oid = oid;
      return it->second;
    }
    return {};
  }

  Entity::SNS::Topic SNSMemoryDb::GetTopicByArn(const std::string &topicArn) {

    auto it = find_if(_topics.begin(), _topics.end(), [topicArn](const std::pair<std::string, Entity::SNS::Topic> &topic) {
      return topic.second.topicArn == topicArn;
    });

    if (it != _topics.end()) {
      it->second.oid = it->first;
      return it->second;
    }
    return {};
  }

  Entity::SNS::TopicList SNSMemoryDb::GetTopicsBySubscriptionArn(const std::string &subscriptionArn) {

    Entity::SNS::TopicList topics;
    for(const auto &topic:_topics){
      if(topic.second.subscriptions.size()>0) {
        auto it = find_if(topic.second.subscriptions.begin(), topic.second.subscriptions.end(), [subscriptionArn](const Entity::SNS::Subscription &subcription) {
          return subcription.subscriptionArn == subscriptionArn;
        });
        if (it != topic.second.subscriptions.end()) {
          topics.emplace_back(topic.second);
        }
      }
    }
    return topics;
  }

  Entity::SNS::Topic SNSMemoryDb::CreateTopic(const Entity::SNS::Topic &topic) {

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _topics[oid] = topic;
    log_trace_stream(_logger) << "Topic created, oid: " << oid << std::endl;
    return GetTopicById(oid);

  }

  Entity::SNS::Topic SNSMemoryDb::UpdateTopic(const Entity::SNS::Topic &topic) {

    std::string region = topic.region;
    std::string name = topic.topicName;
    auto it = find_if(_topics.begin(), _topics.end(), [region, name](const std::pair<std::string, Entity::SNS::Topic> &topic) {
      return topic.second.region == region && topic.second.topicName == name;
    });
    _topics[it->first] = topic;
    return _topics[it->first];

  }

  Entity::SNS::TopicList SNSMemoryDb::ListTopics(const std::string &region) {

    Entity::SNS::TopicList topicList;
    for (const auto &topic : _topics) {
      if(topic.second.region == region) {
        topicList.emplace_back(topic.second);
      }
    }

    log_trace_stream(_logger) << "Got topic list, size: " << topicList.size() << std::endl;
    return topicList;
  }

  long SNSMemoryDb::CountTopics(const std::string &region) {

    long count = 0;
    if (region.empty()) {

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
      } else if (!region.empty() && message.second.region == region) {
        count++;
      } else if (!topicArn.empty() && message.second.topicArn == topicArn) {
        count++;
      }
    }
    return count;
  }

  long SNSMemoryDb::CountMessagesByStatus(const std::string &region, const std::string &topicArn, Entity::SNS::MessageStatus status) {

    long count = 0;
    for (const auto &message : _messages) {
      if (!region.empty() && message.second.region == region && !topicArn.empty() && message.second.topicArn == topicArn && message.second.status == status) {
        count++;
      }
    }
    return count;
  }

  void SNSMemoryDb::DeleteMessage(const Entity::SNS::Message &message) {

    std::string messageId = message.messageId;
    const auto count = std::erase_if(_messages, [messageId](const auto &item) {
      auto const &[key, value] = item;
      return value.messageId == messageId;
    });
    log_debug_stream(_logger) << "Message deleted, messageId: " << message.messageId << " count: " << count << std::endl;
  }

  void SNSMemoryDb::DeleteMessages(const std::string &region, const std::string &topicArn, const std::vector<std::string> &messageIds) {

    auto count = 0;
    for (auto &messageId : messageIds) {
      count += std::erase_if(_messages, [region, topicArn, messageId](const auto &item) {
        auto const &[key, value] = item;
        return value.region == region && value.topicArn == topicArn && value.messageId == messageId;
      });
    }
    log_debug_stream(_logger) << "Messages deleted, count: " << count << " count: " << count << std::endl;
  }

  void SNSMemoryDb::DeleteAllMessages() {

    log_debug_stream(_logger) << "All messages deleted, count: " << _messages.size() << std::endl;
    _messages.clear();
  }
}