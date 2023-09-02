//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/SNSDatabase.h"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::builder::stream::document;

    SNSDatabase::SNSDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("SNSDatabase")) {

        // Set default console logger
        Core::Logger::SetDefaultConsoleLogger("SNSDatabase");

        // Get collections
        _topicCollection = GetConnection()["sns_topic"];
        _messageCollection = GetConnection()["sns_message"];
    }

    bool SNSDatabase::TopicExists(const std::string &topicArn) {

        bsoncxx::builder::stream::document filter{};
        filter << "topicArn" << topicArn << bsoncxx::builder::stream::finalize;

        int64_t count = _topicCollection.count_documents({filter});
        log_trace_stream(_logger) << "Topic exists: " << (count > 0 ? "true" : "false") << std::endl;

        return count > 0;
    }

    bool SNSDatabase::TopicExists(const std::string &region, const std::string &topicName) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << region << "topicName" << topicName << bsoncxx::builder::stream::finalize;

        int64_t count = _topicCollection.count_documents({filter});
        log_trace_stream(_logger) << "Topic exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
    }

    Entity::SNS::Topic SNSDatabase::CreateTopic(const Entity::SNS::Topic &topic) {

        auto result = _topicCollection.insert_one(topic.ToDocument());
        log_trace_stream(_logger) << "Topic created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;

        return GetTopicById(result->inserted_id().get_oid().value);
    }

    Entity::SNS::Topic SNSDatabase::GetTopicById(bsoncxx::oid oid) {

        bsoncxx::builder::stream::document filter{};
        filter << "_id" << oid << bsoncxx::builder::stream::finalize;

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _topicCollection.find_one({filter});

        if (mResult->empty()) {
            return {};
        }

        Entity::SNS::Topic result;
        result.FromDocument(mResult);
        return result;
    }

    Entity::SNS::Topic SNSDatabase::GetTopicById(const std::string &oid) {
        return GetTopicById(bsoncxx::oid(oid));
    }

    Entity::SNS::Topic SNSDatabase::GetTopicByArn(const std::string &topicArn) {

        bsoncxx::builder::stream::document filter{};
        filter << "topicArn" << topicArn << bsoncxx::builder::stream::finalize;

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _topicCollection.find_one({filter});
        Entity::SNS::Topic result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::SNS::TopicList SNSDatabase::ListTopics(const std::string &region) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << region << bsoncxx::builder::stream::finalize;

        Entity::SNS::TopicList topicList;
        auto queueCursor = _topicCollection.find({filter});
        for (auto topic : queueCursor) {
            Entity::SNS::Topic result;
            result.FromDocument(topic);
            topicList.push_back(result);
        }

        log_trace_stream(_logger) << "Got topic list, size:" << topicList.size() << std::endl;
        return topicList;
    }

    Entity::SNS::Topic SNSDatabase::UpdateTopic(const Entity::SNS::Topic &topic) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << topic.region << "topicArn" << topic.topicArn << bsoncxx::builder::stream::finalize;

        auto result = _topicCollection.replace_one({filter}, topic.ToDocument());

        log_trace_stream(_logger) << "Topic updated: " << topic.ToString() << std::endl;

        return GetTopicByArn(topic.topicArn);
    }

    long SNSDatabase::CountTopics(const std::string &region) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << region << bsoncxx::builder::stream::finalize;

        long count = _topicCollection.count_documents({filter});
        log_trace_stream(_logger) << "Count topics, result: " << count << std::endl;

        return count;
    }

    void SNSDatabase::DeleteTopic(const Entity::SNS::Topic &topic) {

        bsoncxx::builder::stream::document filter{};
        filter << "topicArn" << topic.topicArn << bsoncxx::builder::stream::finalize;

        auto result = _topicCollection.delete_many({filter});
        log_debug_stream(_logger) << "Topic deleted, count: " << result->deleted_count() << std::endl;
    }

    void SNSDatabase::DeleteAllTopics() {

        auto result = _topicCollection.delete_many({});
        log_debug_stream(_logger) << "All topics deleted, count: " << result->deleted_count() << std::endl;
    }

    Entity::SNS::Message SNSDatabase::CreateMessage(const Entity::SNS::Message &message) {

        try {

            auto result = _messageCollection.insert_one(message.ToDocument());
            log_trace_stream(_logger) << "Message created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;

            return GetMessageById(result->inserted_id().get_oid().value);

        } catch (const mongocxx::exception& exc) {
            std::cerr << exc.what() << std::endl;
            _logger.error() << "Database exception " << exc.what() << std::endl;
            throw Core::DatabaseException(exc.what(), 500);
        }
    }

    Entity::SNS::Message SNSDatabase::GetMessageById(bsoncxx::oid oid) {

        bsoncxx::builder::stream::document filter{};
        filter << "_id" << oid << bsoncxx::builder::stream::finalize;

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _messageCollection.find_one({filter});
        Entity::SNS::Message result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::SNS::Message SNSDatabase::GetMessageById(const std::string &oid) {
        return GetMessageById(bsoncxx::oid(oid));
    }

    long SNSDatabase::CountMessages(const std::string &region, const std::string &topicArn) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << region << "topicArn" << topicArn << bsoncxx::builder::stream::finalize;

        long count = _messageCollection.count_documents({filter});
        log_trace_stream(_logger) << "Count messages, result: " << count << std::endl;

        return count;
    }

    void SNSDatabase::DeleteMessage(const Entity::SNS::Message &message) {

        bsoncxx::builder::stream::document filter{};
        filter << "messageId" << message.messageId << bsoncxx::builder::stream::finalize;

        auto result = _messageCollection.delete_one({filter});
        log_debug_stream(_logger) << "Messages deleted, messageId: " << message.messageId << " count: " << result->deleted_count() << std::endl;
    }

    void SNSDatabase::DeleteMessages(const std::string &topicArn, const std::vector<std::string> &receipts) {

        bsoncxx::builder::basic::array array{};
        for (const auto &receipt : receipts) {
            array.append(receipt);
        }
        bsoncxx::builder::stream::document filter{};
        filter << "$in" << array << bsoncxx::builder::stream::finalize;

        auto result = _messageCollection.delete_many({filter});
        log_debug_stream(_logger) << "Messages deleted, count: " << result->result().deleted_count() << std::endl;
    }

    void SNSDatabase::DeleteAllMessages() {
        auto result = _messageCollection.delete_many({});
        log_debug_stream(_logger) << "All messages deleted, count: " << result->deleted_count() << std::endl;
    }

} // namespace AwsMock::Database
