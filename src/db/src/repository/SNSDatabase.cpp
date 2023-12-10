//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/repository/SNSDatabase.h"

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::builder::stream::document;

  SNSDatabase::SNSDatabase(Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("SNSDatabase")), _memoryDb(SNSMemoryDb::instance()) {

    if (HasDatabase()) {

      // Get collections
      _topicCollection = GetConnection()["sns_topic"];
      _messageCollection = GetConnection()["sns_message"];

    }
  }

  bool SNSDatabase::TopicExists(const std::string &topicArn) {

    if (HasDatabase()) {

      try {
        int64_t count = _topicCollection.count_documents(make_document(kvp("topicArn", topicArn)));
        log_trace_stream(_logger) << "Topic exists: " << (count > 0 ? "true" : "false") << std::endl;

        return count > 0;
      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.TopicExists(topicArn);

    }
  }

  bool SNSDatabase::TopicExists(const std::string &region, const std::string &topicName) {

    if (HasDatabase()) {

      try {
        int64_t count = _topicCollection.count_documents(make_document(kvp("region", region), kvp("topicName", topicName)));
        log_trace_stream(_logger) << "Topic exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.TopicExists(region, topicName);

    }
  }

  Entity::SNS::Topic SNSDatabase::CreateTopic(const Entity::SNS::Topic &topic) {

    if (HasDatabase()) {

      auto session = GetSession();
      session.start_transaction();

      try {

        auto result = _topicCollection.insert_one(topic.ToDocument());
        log_trace_stream(_logger) << "Topic created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;

        // Commit
        session.commit_transaction();

        return GetTopicById(result->inserted_id().get_oid().value);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.CreateTopic(topic);

    }
  }

  Entity::SNS::Topic SNSDatabase::GetTopicById(bsoncxx::oid oid) {

    try {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _topicCollection.find_one(make_document(kvp("_id", oid)));
      if (!mResult) {
        return {};
      }

      Entity::SNS::Topic result;
      result.FromDocument(mResult);
      return result;

    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  Entity::SNS::Topic SNSDatabase::GetTopicById(const std::string &oid) {

    if (HasDatabase()) {

      return GetTopicById(bsoncxx::oid(oid));

    } else {

      return _memoryDb.GetTopicById(oid);

    }
  }

  Entity::SNS::Topic SNSDatabase::GetTopicByArn(const std::string &topicArn) {

    if (HasDatabase()) {

      try {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _topicCollection.find_one(make_document(kvp("topicArn", topicArn)));
        Entity::SNS::Topic result;
        result.FromDocument(mResult);
        return result;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.GetTopicByArn(topicArn);

    }
  }

  Entity::SNS::TopicList SNSDatabase::GetTopicsBySubscriptionArn(const std::string &subscriptionArn) {

    Entity::SNS::TopicList topicList;
    if (HasDatabase()) {

      try {

        auto queueCursor = _topicCollection.find(make_document(kvp("subscriptions.subscriptionArn", subscriptionArn)));
        for (auto topic : queueCursor) {
          Entity::SNS::Topic result;
          result.FromDocument(topic);
          topicList.push_back(result);
        }

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      topicList = _memoryDb.GetTopicsBySubscriptionArn(subscriptionArn);

    }
    return topicList;
  }

  Entity::SNS::TopicList SNSDatabase::ListTopics(const std::string &region) {

    Entity::SNS::TopicList topicList;
    if (HasDatabase()) {

      try {

        if(region.empty()) {

          auto queueCursor = _topicCollection.find({});
          for (auto topic : queueCursor) {
            Entity::SNS::Topic result;
            result.FromDocument(topic);
            topicList.push_back(result);
          }

        } else {

          auto queueCursor = _topicCollection.find(make_document(kvp("region", region)));
          for (auto topic : queueCursor) {
            Entity::SNS::Topic result;
            result.FromDocument(topic);
            topicList.push_back(result);
          }
        }

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      topicList = _memoryDb.ListTopics(region);

    }
    log_trace_stream(_logger) << "Got topic list, size:" << topicList.size() << std::endl;
    return topicList;
  }

  Entity::SNS::Topic SNSDatabase::UpdateTopic(const Entity::SNS::Topic &topic) {

    if (HasDatabase()) {

      auto session = GetSession();
      session.start_transaction();

      try {

        auto result = _topicCollection.replace_one(make_document(kvp("region", topic.region), kvp("topicArn", topic.topicArn)), topic.ToDocument());
        log_trace_stream(_logger) << "Topic updated: " << topic.ToString() << std::endl;

        // Commit
        session.commit_transaction();

        return GetTopicByArn(topic.topicArn);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.UpdateTopic(topic);

    }
  }

  long SNSDatabase::CountTopics(const std::string &region) {

    if (HasDatabase()) {

      try {
        long count = _topicCollection.count_documents(make_document(kvp("region", region)));
        log_trace_stream(_logger) << "Count topics, result: " << count << std::endl;

        return count;
      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.CountTopics();

    }
  }

  void SNSDatabase::DeleteTopic(const Entity::SNS::Topic &topic) {

    if (HasDatabase()) {

      auto session = GetSession();
      session.start_transaction();

      try {

        auto result = _topicCollection.delete_many(make_document(kvp("topicArn", topic.topicArn)));
        log_debug_stream(_logger) << "Topic deleted, count: " << result->deleted_count() << std::endl;

        // Commit
        session.commit_transaction();

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      _memoryDb.DeleteTopic(topic);

    }
  }

  void SNSDatabase::DeleteAllTopics() {

    if (HasDatabase()) {

      auto session = GetSession();
      session.start_transaction();

      try {

        auto result = _topicCollection.delete_many({});
        log_debug_stream(_logger) << "All topics deleted, count: " << result->deleted_count() << std::endl;

        // Commit
        session.commit_transaction();

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      _memoryDb.DeleteAllTopics();

    }
  }

  Entity::SNS::Message SNSDatabase::CreateMessage(const Entity::SNS::Message &message) {

    if (HasDatabase()) {

      auto session = GetSession();
      session.start_transaction();

      try {

        auto result = _messageCollection.insert_one(message.ToDocument());
        log_trace_stream(_logger) << "Message created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;

        // Commit
        session.commit_transaction();

        return GetMessageById(result->inserted_id().get_oid().value);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.CreateMessage(message);

    }
  }

  Entity::SNS::Message SNSDatabase::GetMessageById(bsoncxx::oid oid) {
    try {
      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _messageCollection.find_one(make_document(kvp("_id", oid)));
      Entity::SNS::Message result;
      result.FromDocument(mResult);

      return result;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  Entity::SNS::Message SNSDatabase::GetMessageById(const std::string &oid) {
    return GetMessageById(bsoncxx::oid(oid));
  }

  long SNSDatabase::CountMessages(const std::string &region, const std::string &topicArn) {

    if (HasDatabase()) {

      try {

        long count = 0;
        if(!region.empty() && !topicArn.empty()) {
          count = _messageCollection.count_documents(make_document(kvp("region", region), kvp("topicArn", topicArn)));
        } else if(!region.empty()) {
          count = _messageCollection.count_documents(make_document(kvp("region", region)));
        } else {
          count = _messageCollection.count_documents({});
        }
        log_trace_stream(_logger) << "Count messages, region: " << region << " arn: " << topicArn << " result: " << count << std::endl;
        return count;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.CountMessages(region, topicArn);

    }
  }

  long SNSDatabase::CountMessagesByStatus(const std::string &region, const std::string &topicArn, Entity::SNS::MessageStatus status) {

    if (HasDatabase()) {

      try {
        long count = _messageCollection.count_documents(make_document(kvp("region", region), kvp("topicArn", topicArn), kvp("status", Entity::SNS::MessageStatusToString(status))));
        log_trace_stream(_logger) << "Count messages by state, region: " << region << " arn: " << topicArn << " result: " << count << std::endl;
        return count;
      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {
      return _memoryDb.CountMessagesByStatus(region, topicArn, status);
    }
  }

  Entity::SNS::MessageList SNSDatabase::ListMessages(const std::string &region) {

    Entity::SNS::MessageList messageList;
    if (HasDatabase()) {

      if (region.empty()) {

        auto messageCursor = _messageCollection.find(make_document());
        for (auto message : messageCursor) {
          Entity::SNS::Message result;
          result.FromDocument(message);
          messageList.push_back(result);
        }

      } else {

        auto messageCursor = _messageCollection.find(make_document(kvp("region", region)));
        for (auto message : messageCursor) {
          Entity::SNS::Message result;
          result.FromDocument(message);
          messageList.push_back(result);
        }
      }

    } else {

      messageList = _memoryDb.ListMessages(region);

    }
    log_trace_stream(_logger) << "Got message list, size: " << messageList.size() << std::endl;
    return messageList;
  }

  void SNSDatabase::DeleteMessage(const Entity::SNS::Message &message) {

    if (HasDatabase()) {

      auto session = GetSession();
      session.start_transaction();

      try {

        auto result = _messageCollection.delete_one(make_document(kvp("messageId", message.messageId)));
        log_debug_stream(_logger) << "Messages deleted, messageId: " << message.messageId << " count: " << result->deleted_count() << std::endl;

        // Commit
        session.commit_transaction();

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      _memoryDb.DeleteMessage(message);

    }
  }

  void SNSDatabase::DeleteMessages(const std::string &region, const std::string &topicArn, const std::vector<std::string> &receipts) {

    if (HasDatabase()) {

      auto session = GetSession();
      session.start_transaction();

      bsoncxx::builder::basic::array array{};
      for (const auto &receipt : receipts) {
        array.append(receipt);
      }

      try {

        auto result = _messageCollection.delete_many(make_document(kvp("region", region), kvp("topicArn", topicArn), kvp("messageId", make_document(kvp("$in", array)))));
        log_debug_stream(_logger) << "Messages deleted, count: " << result->result().deleted_count() << std::endl;

        // Commit
        session.commit_transaction();

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      _memoryDb.DeleteMessages(region, topicArn, receipts);

    }
  }

  void SNSDatabase::DeleteAllMessages() {

    if (HasDatabase()) {

      try {

        auto result = _messageCollection.delete_many({});
        log_debug_stream(_logger) << "All messages deleted, count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "SNS Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      _memoryDb.DeleteAllMessages();

    }
  }

} // namespace AwsMock::Database
