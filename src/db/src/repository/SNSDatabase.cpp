//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/repository/SNSDatabase.h"

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::builder::stream::document;

  SNSDatabase::SNSDatabase(Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("SNSDatabase")) {

    // Get collections
    _topicCollection = GetConnection()["sns_topic"];
    _messageCollection = GetConnection()["sns_message"];
  }

  bool SNSDatabase::TopicExists(const std::string &topicArn) {
    try {
      int64_t count = _topicCollection.count_documents(make_document(kvp("topicArn", topicArn)));
      log_trace_stream(_logger) << "Topic exists: " << (count > 0 ? "true" : "false") << std::endl;

      return count > 0;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  bool SNSDatabase::TopicExists(const std::string &region, const std::string &topicName) {
    try {
      int64_t count = _topicCollection.count_documents(make_document(kvp("region", region), kvp("topicName", topicName)));
      log_trace_stream(_logger) << "Topic exists: " << (count > 0 ? "true" : "false") << std::endl;
      return count > 0;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }

  }

  Entity::SNS::Topic SNSDatabase::CreateTopic(const Entity::SNS::Topic &topic) {

    try {
      auto result = _topicCollection.insert_one(topic.ToDocument());
      log_trace_stream(_logger) << "Topic created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;
      return GetTopicById(result->inserted_id().get_oid().value);
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
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
    return GetTopicById(bsoncxx::oid(oid));
  }

  Entity::SNS::Topic SNSDatabase::GetTopicByArn(const std::string &topicArn) {
    try {
      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _topicCollection.find_one(make_document(kvp("topicArn", topicArn)));
      Entity::SNS::Topic result;
      result.FromDocument(mResult);
      return result;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  Entity::SNS::TopicList SNSDatabase::GetTopicsBySubscriptionArn(const std::string &subscriptionArn) {

    Entity::SNS::TopicList topicList;
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
    return topicList;
  }

  Entity::SNS::TopicList SNSDatabase::ListTopics(const std::string &region) {

    Entity::SNS::TopicList topicList;
    try {
      auto queueCursor = _topicCollection.find(make_document(kvp("region", region)));
      for (auto topic : queueCursor) {
        Entity::SNS::Topic result;
        result.FromDocument(topic);
        topicList.push_back(result);
      }
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
    log_trace_stream(_logger) << "Got topic list, size:" << topicList.size() << std::endl;
    return topicList;
  }

  Entity::SNS::Topic SNSDatabase::UpdateTopic(const Entity::SNS::Topic &topic) {

    try {
      auto result = _topicCollection.replace_one(make_document(kvp("region", topic.region), kvp("topicArn", topic.topicArn)), topic.ToDocument());
      log_trace_stream(_logger) << "Topic updated: " << topic.ToString() << std::endl;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
    return GetTopicByArn(topic.topicArn);
  }

  long SNSDatabase::CountTopics(const std::string &region) {

    try {
      long count = _topicCollection.count_documents(make_document(kvp("region", region)));
      log_trace_stream(_logger) << "Count topics, result: " << count << std::endl;

      return count;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  void SNSDatabase::DeleteTopic(const Entity::SNS::Topic &topic) {
    try {
      auto result = _topicCollection.delete_many(make_document(kvp("topicArn", topic.topicArn)));
      log_debug_stream(_logger) << "Topic deleted, count: " << result->deleted_count() << std::endl;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  void SNSDatabase::DeleteAllTopics() {
    try {
      auto result = _topicCollection.delete_many({});
      log_debug_stream(_logger) << "All topics deleted, count: " << result->deleted_count() << std::endl;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  Entity::SNS::Message SNSDatabase::CreateMessage(const Entity::SNS::Message &message) {

    try {

      auto result = _messageCollection.insert_one(message.ToDocument());
      log_trace_stream(_logger) << "Message created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;

      return GetMessageById(result->inserted_id().get_oid().value);

    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
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

    try {
      long count = _messageCollection.count_documents(make_document(kvp("region", region), kvp("topicArn", topicArn)));
      log_trace_stream(_logger) << "Count messages, region: " << region << " arn: " << topicArn << " result: " << count << std::endl;
      return count;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  long SNSDatabase::CountMessagesByStatus(const std::string &region, const std::string &topicArn, int status) {

    try {
      long count = _messageCollection.count_documents(make_document(kvp("region", region), kvp("topicArn", topicArn), kvp("state", status)));
      log_trace_stream(_logger) << "Count messages by state, region: " << region << " arn: " << topicArn << " result: " << count << std::endl;
      return count;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  void SNSDatabase::DeleteMessage(const Entity::SNS::Message &message) {
    try {
      auto result = _messageCollection.delete_one(make_document(kvp("messageId", message.messageId)));
      log_debug_stream(_logger) << "Messages deleted, messageId: " << message.messageId << " count: " << result->deleted_count() << std::endl;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  void SNSDatabase::DeleteMessages(const std::string &region, const std::string &topicArn, const std::vector<std::string> &receipts) {

    bsoncxx::builder::basic::array array{};
    for (const auto &receipt : receipts) {
      array.append(receipt);
    }
    try {
      auto result = _messageCollection.delete_many(make_document(kvp("region", region), kvp("topicArn", topicArn), kvp("messageId", make_document(kvp("$in", array)))));
      log_debug_stream(_logger) << "Messages deleted, count: " << result->result().deleted_count() << std::endl;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

  void SNSDatabase::DeleteAllMessages() {
    try {
      auto result = _messageCollection.delete_many({});
      log_debug_stream(_logger) << "All messages deleted, count: " << result->deleted_count() << std::endl;
    } catch (const mongocxx::exception &exc) {
      _logger.error() << "SNS Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException(exc.what(), 500);
    }
  }

} // namespace AwsMock::Database
