//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/SQSMemoryDb.h>

namespace AwsMock::Database {

    Poco::Mutex SQSMemoryDb::sqsQueueMutex;
    Poco::Mutex SQSMemoryDb::_sqsMessageMutex;

    bool SQSMemoryDb::QueueExists(const std::string &region, const std::string &name) {

        return find_if(_queues.begin(),
                       _queues.end(),
                       [region, name](const std::pair<std::string, Entity::SQS::Queue> &queue) {
                           return queue.second.region == region && queue.second.name == name;
                       }) != _queues.end();
    }

    bool SQSMemoryDb::QueueUrlExists(const std::string &region, const std::string &queueUrl) {

        return find_if(_queues.begin(),
                       _queues.end(),
                       [region, queueUrl](const std::pair<std::string, Entity::SQS::Queue> &queue) {
                           return queue.second.region == region && queue.second.queueUrl == queueUrl;
                       }) != _queues.end();
    }

    bool SQSMemoryDb::QueueArnExists(const std::string &queueArn) {

        return find_if(_queues.begin(), _queues.end(), [queueArn](const std::pair<std::string, Entity::SQS::Queue> &queue) {
                   return queue.second.queueArn == queueArn;
               }) != _queues.end();
    }

    Entity::SQS::Queue SQSMemoryDb::CreateQueue(const Entity::SQS::Queue &queue) {
        Poco::ScopedLock lock(sqsQueueMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _queues[oid] = queue;
        log_trace << "Queue created, oid: " << oid;
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

        auto it =
                find_if(_queues.begin(), _queues.end(), [queueArn](const std::pair<std::string, Entity::SQS::Queue> &queue) {
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
        auto it =
                find_if(_queues.begin(), _queues.end(), [queueUrl](const std::pair<std::string, Entity::SQS::Queue> &queue) {
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
        auto it = find_if(_queues.begin(),
                          _queues.end(),
                          [region, name](const std::pair<std::string, Entity::SQS::Queue> &queue) {
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
        for (const auto &queue: _queues) {
            queueList.emplace_back(queue.second);
        }

        log_trace << "Got queue list, size: " << queueList.size();
        return queueList;
    }

    void SQSMemoryDb::PurgeQueue(const std::string &queueArn) {
        Poco::ScopedLock lock(sqsQueueMutex);

        const auto count = std::erase_if(_messages, [queueArn](const auto &item) {
            auto const &[key, value] = item;
            return value.queueArn == queueArn;
        });
        log_debug << "Purged queue, queueArn: " << queueArn << " count: " << count;
    }

    Entity::SQS::Queue SQSMemoryDb::UpdateQueue(Entity::SQS::Queue &queue) {
        Poco::ScopedLock lock(sqsQueueMutex);

        std::string region = queue.region;
        std::string name = queue.name;
        auto it = find_if(_queues.begin(),
                          _queues.end(),
                          [region, name](const std::pair<std::string, Entity::SQS::Queue> &queue) {
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
        log_trace << "Count queues, result: " << count;
        return count;
    }

    void SQSMemoryDb::DeleteQueue(const Entity::SQS::Queue &queue) {
        Poco::ScopedLock lock(sqsQueueMutex);

        std::string region = queue.region;
        std::string queueUrl = queue.queueUrl;
        const auto count = std::erase_if(_queues, [region, queueUrl](const auto &item) {
            auto const &[key, value] = item;
            return value.region == region && value.queueUrl == queueUrl;
        });
        log_debug << "Queue deleted, count: " << count;
    }

    void SQSMemoryDb::DeleteAllQueues() {
        Poco::ScopedLock lock(sqsQueueMutex);

        log_debug << "All queues deleted, count: " << _queues.size();
        _queues.clear();
    }

    Entity::SQS::Message SQSMemoryDb::CreateMessage(const Entity::SQS::Message &message) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _messages[oid] = message;
        log_trace << "Message created, oid: " << oid;

        return GetMessageById(oid);
    }

    bool SQSMemoryDb::MessageExists(const std::string &receiptHandle) {

        return find_if(_messages.begin(),
                       _messages.end(),
                       [receiptHandle](const std::pair<std::string, Entity::SQS::Message> &message) {
                           return message.second.receiptHandle == receiptHandle;
                       }) != _messages.end();
    }

    Entity::SQS::Message SQSMemoryDb::GetMessageById(const std::string &oid) {

        auto it =
                find_if(_messages.begin(), _messages.end(), [oid](const std::pair<std::string, Entity::SQS::Message> &message) {
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
        auto it = find_if(_messages.begin(),
                          _messages.end(),
                          [receiptHandle](const std::pair<std::string, Entity::SQS::Message> &message) {
                              return message.second.receiptHandle == receiptHandle;
                          });

        if (it != _messages.end()) {
            it->second.oid = it->first;
            result = it->second;
        }
        return result;
    }

    Entity::SQS::Message SQSMemoryDb::UpdateMessage(Entity::SQS::Message &message) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        std::string oid = message.oid;
        auto it =
                find_if(_messages.begin(), _messages.end(), [oid](const std::pair<std::string, Entity::SQS::Message> &message) {
                    return message.second.oid == oid;
                });
        _messages[it->first] = message;
        return _messages[it->first];
    }

    Entity::SQS::MessageList SQSMemoryDb::ListMessages(const std::string &region) {

        Entity::SQS::MessageList messageList;
        if (region.empty()) {

            for (const auto &message: _messages) {
                messageList.emplace_back(message.second);
            }

        } else {

            for (const auto &message: _messages) {
                if (Core::StringUtils::Contains(message.second.queueArn, region)) {
                    messageList.emplace_back(message.second);
                }
            }
        }

        log_trace << "Got message list, size: " << messageList.size();
        return messageList;
    }

    void SQSMemoryDb::ReceiveMessages(const std::string &queueArn, int visibility, int maxResult, const std::string &dlQueueArn, int maxRetries, Entity::SQS::MessageList &messageList) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        auto reset = std::chrono::high_resolution_clock::now() + std::chrono::seconds{visibility};

        // Get the cursor
        for (auto message: _messages) {

            if (message.second.queueArn == queueArn && message.second.status == Entity::SQS::MessageStatus::INITIAL) {

                message.second.retries++;
                message.second.receiptHandle = Core::AwsUtils::CreateSqsReceiptHandler();
                messageList.push_back(message.second);

                // Update values
                message.second.status = Entity::SQS::MessageStatus::INVISIBLE;
                message.second.reset = reset;

                // Update store
                _messages[message.first] = message.second;

                // Check max resources
                if (messageList.size() >= maxResult) {
                    break;
                }
            }
        }

        log_trace << "Messages received, queueArn: " << queueArn + " count: " << messageList.size();
    }

    void SQSMemoryDb::ResetMessages(const std::string &queueArn, long visibility) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        long count = 0;
        auto now = std::chrono::high_resolution_clock::now();
        for (auto message: _messages) {

            if (message.second.queueArn == queueArn && message.second.status == Entity::SQS::MessageStatus::INVISIBLE && message.second.reset < std::chrono::system_clock::now()) {

                // Reset status
                message.second.status = Entity::SQS::MessageStatus::INITIAL;
                message.second.receiptHandle = "";

                // Update store
                _messages[message.first] = message.second;
                count++;
            }
            log_trace << "Message reset, visibilityTimeout: " << visibility << " updated: " << count << " queueArn: " << queueArn;
        }
    }

    void SQSMemoryDb::RedriveMessages(const std::string &queueArn, const Entity::SQS::RedrivePolicy &redrivePolicy, const Core::Configuration &configuration) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        long count = 0;
        std::string dlqQueueUrl = Core::AwsUtils::ConvertSQSQueueArnToUrl(redrivePolicy.deadLetterTargetArn);
        for (auto message: _messages) {

            if (message.second.queueArn == queueArn && message.second.status == Entity::SQS::MessageStatus::INITIAL && message.second.retries > redrivePolicy.maxReceiveCount) {

                message.second.retries = 0;
                message.second.queueArn = redrivePolicy.deadLetterTargetArn;
                _messages[message.first] = message.second;

                count++;
            }
        }
        log_trace << "Message redrive, arn: " << redrivePolicy.deadLetterTargetArn << " updated: " << count;
    }

    void SQSMemoryDb::ResetDelayedMessages(const std::string &queueArn, long delay) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        long count = 0;
        auto now = std::chrono::high_resolution_clock::now();

        for (auto &message: _messages) {

            if (message.second.queueArn == queueArn && message.second.status == Entity::SQS::MessageStatus::DELAYED && message.second.reset < std::chrono::system_clock::now()) {

                message.second.status = Entity::SQS::MessageStatus::INITIAL;
                _messages[message.first] = message.second;

                count++;
            }
        }
        log_trace << "Delayed message reset, updated: " << count << " queueArn: " << queueArn;
    }

    void SQSMemoryDb::MessageRetention(const std::string &queueArn, long retentionPeriod) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        long count = 0;
        auto reset = std::chrono::high_resolution_clock::now() - std::chrono::seconds{retentionPeriod};

        for (auto &message: _messages) {

            if (message.second.queueArn == queueArn && message.second.status == Entity::SQS::MessageStatus::DELAYED && message.second.reset < std::chrono::system_clock::now()) {

                DeleteMessage(message.second);
                count++;
            }
        }
        log_trace << "Message retention reset, deleted: " << count << " queueArn: " << queueArn;
    }

    long SQSMemoryDb::CountMessages(const std::string &queueArn) {

        long count = 0;
        if (queueArn.empty()) {

            count = _messages.size();

        } else {

            std::map<std::string, Entity::SQS::Message>::iterator it;
            for (it = _messages.begin(); it != _messages.end(); it++) {
                if (it->second.queueArn == queueArn) {
                    count++;
                }
            }
        }
        log_trace << "Count resources, result: " << count;
        return count;
    }

    long SQSMemoryDb::CountMessagesByStatus(const std::string &queueArn, Entity::SQS::MessageStatus status) {

        long count = 0;

        std::map<std::string, Entity::SQS::Message>::iterator it;
        for (it = _messages.begin(); it != _messages.end(); it++) {
            if (it->second.queueArn == queueArn && it->second.status == status) {
                count++;
            }
        }
        log_trace << "Count resources by status, result: " << count;
        return count;
    }

    Entity::SQS::MessageWaitTime SQSMemoryDb::GetAverageMessageWaitingTime() {

        Entity::SQS::MessageWaitTime waitTime{};
        Entity::SQS::QueueList queueList = ListQueues();
        for (const auto &queue: queueList) {

            // Extract map values
            std::vector<Entity::SQS::Message> filtered;
            std::transform(_messages.begin(), _messages.end(),
                           std::back_inserter(filtered),
                           [queue](auto &kv) {
                               if (kv.second.queueArn == queue.queueArn) {
                                   return kv.second;
                               }
                               return (Entity::SQS::Message){};
                           });

            if (!filtered.empty()) {

                // Sort by created timestamp
                std::sort(filtered.begin(), filtered.end(), [](auto x, auto y) { return x.created > y.created; });

                double min = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - filtered.front().created).count();
                double max = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - filtered.back().created).count();

                if (max + min > 5) {
                    waitTime.waitTime[queue.name] = (max + min) / 2.0;
                } else {
                    waitTime.waitTime[queue.name] = 0.0;
                }
            } else {
                waitTime.waitTime[queue.name] = 0.0;
            }
        }
        return waitTime;
    }

    void SQSMemoryDb::DeleteMessages(const std::string &queueArn) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        const auto count = std::erase_if(_messages, [queueArn](const auto &item) {
            auto const &[key, value] = item;
            return value.queueArn == queueArn;
        });

        log_debug << "Messages deleted, queueArn: " << queueArn << " count: " << count;
    }

    void SQSMemoryDb::DeleteMessage(const Entity::SQS::Message &message) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        std::string receiptHandle = message.receiptHandle;
        const auto count = std::erase_if(_messages, [receiptHandle](const auto &item) {
            auto const &[key, value] = item;
            return value.receiptHandle == receiptHandle;
        });
        log_debug << "Messages deleted, receiptHandle: " << message.receiptHandle << " count: " << count;
    }

    void SQSMemoryDb::DeleteMessage(const std::string &receiptHandle) {
        Poco::ScopedLock lock(_sqsMessageMutex);

        const auto count = std::erase_if(_messages, [receiptHandle](const auto &item) {
            auto const &[key, value] = item;
            return value.receiptHandle == receiptHandle;
        });
        log_debug << "Messages deleted, receiptHandle: " << receiptHandle << " count: " << count;
    }

    void SQSMemoryDb::DeleteAllMessages() {
        Poco::ScopedLock lock(_sqsMessageMutex);

        log_debug << "All resources deleted, count: " << _messages.size();
        _messages.clear();
    }
}// namespace AwsMock::Database