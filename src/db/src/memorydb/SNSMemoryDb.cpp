//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/SNSMemoryDb.h>

namespace AwsMock::Database {

  SNSMemoryDb::SNSMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

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