//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/SQSMemoryDb.h>

namespace AwsMock::Database {

  SQSMemoryDb::SQSMemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {

  }

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
      result = it->second;
    }
    return result;
  }

  Entity::SQS::Queue SQSMemoryDb::GetQueueByUrl(const std::string &queueUrl) {

    Entity::SQS::Queue result;

    auto it = find_if(_queues.begin(), _queues.end(), [queueUrl](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.queueUrl == queueUrl;
    });

    if (it != _queues.end()) {
      it->second.oid = it->first;
      result = it->second;
    }
    return result;
  }

  Entity::SQS::Queue SQSMemoryDb::GetQueueByName(const std::string &region, const std::string &name) {

    Entity::SQS::Queue result;
    auto it = find_if(_queues.begin(), _queues.end(), [region, name](const std::pair<std::string, Entity::SQS::Queue> &queue) {
      return queue.second.region == region && queue.second.name == name;
    });

    if (it != _queues.end()) {
      it->second.oid = it->first;
      result = it->second;
    }
    return result;
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
    std::string name = queue.name;
    const auto count = std::erase_if(_queues, [region, name](const auto &item) {
      auto const &[key, value] = item;
      return value.region == region && value.name == name;
    });
    log_debug_stream(_logger) << "Queue deleted, count: " << count << std::endl;
  }

  void SQSMemoryDb::DeleteAllQueues() {

    log_debug_stream(_logger) << "All queues deleted, count: " << _queues.size() << std::endl;
    _queues.clear();
  }
}