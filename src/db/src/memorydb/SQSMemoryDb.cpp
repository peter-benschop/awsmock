//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/SQSMemoryDb.h>

namespace AwsMock::Database {

  SQSMemoryDb::SQSMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

  bool SQSMemoryDb::QueueExists(const std::string &region, const std::string &name) {

    return find_if(_queues.begin(), _queues.end(), [region, name](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.region == region && queue.second.name == name;
    }) != _queues.end();
  }

  bool SQSMemoryDb::QueueUrlExists(const std::string &region, const std::string &queueUrl) {

    return find_if(_queues.begin(), _queues.end(), [region, queueUrl](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.region == region && queue.second.queueUrl == queueUrl;
    }) != _queues.end();
  }

  bool SQSMemoryDb::QueueArnExists(const std::string &queueArn) {

    return find_if(_queues.begin(), _queues.end(), [queueArn](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.queueArn == queueArn;
    }) != _queues.end();
  }

  Entity::SQS::Queue SQSMemoryDb::CreateQueue(const Entity::SQS::Queue &queue) {
    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _queues[oid] = queue;
    log_trace_stream(_logger) << "Queue created, oid: " << oid << std::endl;
    return GetQueueById(oid);
  }

  Entity::SQS::Queue SQSMemoryDb::GetQueueById(const std::string &oid) {

    auto it = find_if(_queues.begin(), _queues.end(), [oid](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.first == oid;
    });

    if (it != _queues.end()) {
      it->second.oid = oid;
      return it->second;
    }
    return {};
  }

  Entity::SQS::Queue SQSMemoryDb::GetQueueByArn(const std::string &queueArn) {

    Entity::SQS::Queue result;

    auto it = find_if(_queues.begin(), _queues.end(), [queueArn](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.queueArn == queueArn;
    });

    if (it != _queues.end()) {
      it->second.oid = it->first;
      return it->second;
    }
    return {};
  }

  Entity::SQS::Queue SQSMemoryDb::GetQueueByUrl(const std::string &queueUrl) {

    Entity::SQS::Queue result;
    auto it = find_if(_queues.begin(), _queues.end(), [queueUrl](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.queueUrl == queueUrl;
    });

    if (it != _queues.end()) {
      it->second.oid = it->first;
      return it->second;
    }
    return {};
  }

  Entity::SQS::Queue SQSMemoryDb::GetQueueByName(const std::string &region, const std::string &name) {

    Entity::SQS::Queue result;
    auto it = find_if(_queues.begin(), _queues.end(), [region, name](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.region == region && queue.second.name == name;
    });

    if (it != _queues.end()) {
      it->second.oid = it->first;
      return it->second;
    }
    return {};
  }

  Entity::SQS::QueueList SQSMemoryDb::ListQueues(const std::string &region) {

    Entity::SQS::QueueList queueList;
    for (const auto &queue : _queues) {
      queueList.emplace_back(queue.second);
    }

    log_trace_stream(_logger) << "Got queue list, size: " << queueList.size() << std::endl;
    return queueList;
  }

  void SQSMemoryDb::PurgeQueue(const std::string &region, const std::string &queueUrl) {

    const auto count = std::erase_if(_messages, [region, queueUrl](const auto &item) {
      auto const &[key, value] = item;
      return value.region == region && value.queueUrl == queueUrl;
    });
    log_debug_stream(_logger) << "Purged queue, count: " << count << std::endl;
  }

  Entity::SQS::Queue SQSMemoryDb::UpdateQueue(Entity::SQS::Queue &queue) {

    std::string region = queue.region;
    std::string name = queue.name;
    auto it = find_if(_queues.begin(), _queues.end(), [region, name](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.region == region && queue.second.name == name;
    });
    _queues[it->first] = queue;
    return _queues[it->first];

  }

  long SQSMemoryDb::CountQueues(const std::string &region) {

    long count = 0;

    if (region.empty()) {
      count = (long) _queues.size();
    } else {

      std::map<std::string, Entity::SQS::Queue>::iterator it;
      for (it = _queues.begin(); it != _queues.end(); it++) {
        if (it->second.region == region) {
          count++;
        }
      }
    }
    log_trace_stream(_logger) << "Count queues, result: " << count << std::endl;
    return count;
  }

  void SQSMemoryDb::DeleteQueue(const Entity::SQS::Queue &queue) {

    std::string region = queue.region;
    std::string queueUrl = queue.queueUrl;
    const auto count = std::erase_if(_queues, [region, queueUrl](const auto &item) {
      auto const &[key, value] = item;
      return value.region == region && value.queueUrl == queueUrl;
    });
    log_debug_stream(_logger) << "Queue deleted, count: " << count << std::endl;
  }

  void SQSMemoryDb::DeleteAllQueues() {

    log_debug_stream(_logger) << "All queues deleted, count: " << _queues.size() << std::endl;
    _queues.clear();
  }

  Entity::SQS::Message SQSMemoryDb::CreateMessage(const Entity::SQS::Message &message) {

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _messages[oid] = message;
    log_trace_stream(_logger) << "Message created, oid: " << oid << std::endl;

    return GetMessageById(oid);
  }

  bool SQSMemoryDb::MessageExists(const std::string &receiptHandle) {

    return find_if(_messages.begin(), _messages.end(), [receiptHandle](const std::pair<std::string, Entity::SQS::Message> &message) {
      return message.second.receiptHandle == receiptHandle;
    }) != _messages.end();

  }

  Entity::SQS::Message SQSMemoryDb::GetMessageById(const std::string &oid) {

    auto it = find_if(_messages.begin(), _messages.end(), [oid](const std::pair<std::string, Entity::SQS::Message> &message) {
      return message.first == oid;
    });

    if (it != _messages.end()) {
      it->second.oid = it->first;
      return it->second;
    }
    return {};
  }

  Entity::SQS::Message SQSMemoryDb::GetMessageByReceiptHandle(const std::string &receiptHandle) {

    Entity::SQS::Message result;
    auto it = find_if(_messages.begin(), _messages.end(), [receiptHandle](const std::pair<std::string, Entity::SQS::Message> &message) {
      return message.second.receiptHandle == receiptHandle;
    });

    if (it != _messages.end()) {
      it->second.oid = it->first;
      result = it->second;
    }
    return result;
  }

  Entity::SQS::Message SQSMemoryDb::UpdateMessage(Entity::SQS::Message &message) {

    std::string oid = message.oid;
    auto it = find_if(_messages.begin(), _messages.end(), [oid](const std::pair<std::string, Entity::SQS::Message> &message) {
      return message.second.oid == oid;
    });
    _messages[it->first] = message;
    return _messages[it->first];
  }

  void SQSMemoryDb::ReceiveMessages(const std::string &region, const std::string &queueUrl, int visibility, Entity::SQS::MessageList &messageList) {

    auto reset = std::chrono::high_resolution_clock::now() + std::chrono::seconds{visibility};

    // Get the cursor
    for (auto message : _messages) {

      if (message.second.region == region && message.second.queueUrl == queueUrl && message.second.status == Entity::SQS::MessageStatus::INITIAL) {

        message.second.retries++;
        message.second.receiptHandle = Core::AwsUtils::CreateSqsReceiptHandler();
        messageList.push_back(message.second);

        // Update values
        message.second.status = Entity::SQS::MessageStatus::INVISIBLE;
        message.second.reset = Poco::Timestamp(reset.time_since_epoch().count() / 1000);

        // Update store
        _messages[message.first] = message.second;
      }
    }

    log_trace_stream(_logger) << "Messages received, region: " << region << " queue: " << queueUrl + " count: " << messageList.size() << std::endl;
  }

  void SQSMemoryDb::ResetMessages(const std::string &queueUrl, long visibility) {

    long count = 0;
    auto now = std::chrono::high_resolution_clock::now();
    for (auto message : _messages) {

      if (message.second.queueUrl == queueUrl && message.second.status == Entity::SQS::MessageStatus::INVISIBLE && message.second.reset < Poco::Timestamp(now.time_since_epoch().count() / 1000)) {

        // Reset status
        message.second.status = Entity::SQS::MessageStatus::INITIAL;
        message.second.receiptHandle = "";

        // Update store
        _messages[message.first] = message.second;
        count++;
      }
      log_trace_stream(_logger) << "Message reset, visibility: " << visibility << " updated: " << count << " queue: " << queueUrl << std::endl;
    }
  }

  void SQSMemoryDb::RedriveMessages(const std::string &queueUrl, const Entity::SQS::RedrivePolicy &redrivePolicy, const Core::Configuration &configuration) {

    long count = 0;
    std::string dlqQueueUrl = Core::AwsUtils::ConvertSQSQueueArnToUrl(configuration, redrivePolicy.deadLetterTargetArn);
    for (auto message : _messages) {

      if (message.second.queueUrl == queueUrl && message.second.status == Entity::SQS::MessageStatus::INITIAL && message.second.retries > redrivePolicy.maxReceiveCount) {

        message.second.retries = 0;
        message.second.queueUrl = dlqQueueUrl;
        _messages[message.first] = message.second;

        count++;
      }
    }
    log_trace_stream(_logger) << "Message redrive, arn: " << redrivePolicy.deadLetterTargetArn << " updated: " << count << " queue: " << queueUrl << std::endl;
  }

  void SQSMemoryDb::ResetDelayedMessages(const std::string &queueUrl, long delay) {

    long count = 0;
    auto now = std::chrono::high_resolution_clock::now();

    for (auto &message : _messages) {

      if (message.second.queueUrl == queueUrl && message.second.status == Entity::SQS::MessageStatus::DELAYED && message.second.reset < Poco::Timestamp(now.time_since_epoch().count() / 1000)) {

        message.second.status = Entity::SQS::MessageStatus::INITIAL;
        _messages[message.first] = message.second;

        count++;
      }
    }
    log_trace_stream(_logger) << "Delayed message reset, updated: " << count << " queue: " << queueUrl << std::endl;
  }

  long SQSMemoryDb::CountMessages(const std::string &region, const std::string &queueUrl) {

    long count = 0;

    if (region.empty() && queueUrl.empty()) {

      count = (long) _messages.size();

    } else if (!region.empty() && !queueUrl.empty()) {

      std::map<std::string, Entity::SQS::Message>::iterator it;
      for (it = _messages.begin(); it != _messages.end(); it++) {
        if (it->second.region == region && it->second.queueUrl == queueUrl) {
          count++;
        }
      }
    } else if (region.empty() && !queueUrl.empty()) {

      std::map<std::string, Entity::SQS::Message>::iterator it;
      for (it = _messages.begin(); it != _messages.end(); it++) {
        if (it->second.queueUrl == queueUrl) {
          count++;
        }
      }
    } else if (!region.empty() && queueUrl.empty()) {

      std::map<std::string, Entity::SQS::Message>::iterator it;
      for (it = _messages.begin(); it != _messages.end(); it++) {
        if (it->second.region == region) {
          count++;
        }
      }
    }
    log_trace_stream(_logger) << "Count messages, result: " << count << std::endl;
    return count;
  }

  long SQSMemoryDb::CountMessagesByStatus(const std::string &region, const std::string &queueUrl, Entity::SQS::MessageStatus status) {

    long count = 0;

    std::map<std::string, Entity::SQS::Message>::iterator it;
    for (it = _messages.begin(); it != _messages.end(); it++) {
      if (it->second.region == region && it->second.queueUrl == queueUrl && it->second.status == status) {
        count++;
      }
    }
    log_trace_stream(_logger) << "Count messages by status, result: " << count << std::endl;
    return count;
  }

  void SQSMemoryDb::DeleteMessages(const std::string &queueUrl) {

    const auto count = std::erase_if(_messages, [queueUrl](const auto &item) {
      auto const &[key, value] = item;
      return value.queueUrl == queueUrl;
    });

    log_debug_stream(_logger) << "Messages deleted, queue: " << queueUrl << " count: " << count << std::endl;
  }

  void SQSMemoryDb::DeleteMessage(const Entity::SQS::Message &message) {

    std::string receiptHandle = message.receiptHandle;
    const auto count = std::erase_if(_messages, [receiptHandle](const auto &item) {
      auto const &[key, value] = item;
      return value.receiptHandle == receiptHandle;
    });
    log_debug_stream(_logger) << "Messages deleted, receiptHandle: " << message.receiptHandle << " count: " << count << std::endl;
  }

  void SQSMemoryDb::DeleteAllMessages() {

    log_debug_stream(_logger) << "All messages deleted, count: " << _messages.size() << std::endl;
    _messages.clear();
  }
}