//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/SQSDatabase.h"

namespace AwsMock::Database {

    //using namespace Poco::Data::Keywords;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    SQSDatabase::SQSDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("SQSDatabase")) {

        Core::Logger::SetDefaultConsoleLogger("SQSDatabase");

        CreateCollection("sqs_queue");
        CreateCollection("sqs_message");

        _queueCollection = GetConnection()["sqs_queue"];
        _messageCollection = GetConnection()["sqs_message"];
    }

    bool SQSDatabase::QueueExists(const std::string &queueUrl) {

        int64_t count = _queueCollection.count_documents(make_document(kvp("queueUrl", queueUrl)));
        _logger.trace() << "Queue exists: " << (count > 0 ? "true" : "false");
        return count > 0;
    }

    bool SQSDatabase::QueueExists(const std::string &region, const std::string &name) {

        int64_t count = _queueCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
        _logger.trace() << "Queue exists: " << (count > 0 ? "true" : "false");
        return count > 0;
    }

    Entity::SQS::Queue SQSDatabase::CreateQueue(const Entity::SQS::Queue &queue) {

        auto result = _queueCollection.insert_one(queue.ToDocument());
        _logger.trace() << "Bucket created, oid: " << result->inserted_id().get_oid().value.to_string();

        return GetQueueById(result->inserted_id().get_oid().value);
    }

    Entity::SQS::Queue SQSDatabase::GetQueueById(bsoncxx::oid oid) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _queueCollection.find_one(make_document(kvp("_id", oid)));
        Entity::SQS::Queue result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::SQS::Queue SQSDatabase::GetQueueById(const std::string &oid) {
        return GetQueueById(bsoncxx::oid(oid));
    }

    Entity::SQS::QueueList SQSDatabase::ListQueues(const std::string &region) {

        Entity::SQS::QueueList queueList;
        auto queueCursor = _queueCollection.find(make_document(kvp("region", region)));
        for (auto queue : queueCursor) {
            Entity::SQS::Queue result;
            result.FromDocument(queue);
            queueList.push_back(result);
        }

        _logger.trace() << "Got queue list, size:" << queueList.size();
        return queueList;
    }

    void SQSDatabase::PurgeQueue(const std::string &region, const std::string &queueUrl) {

        auto result = _messageCollection.delete_many(make_document(kvp("region", region), kvp("queueUrl", queueUrl)));

        _logger.debug() << "Purged queue, count: " << result->deleted_count();
    }

    void SQSDatabase::DeleteQueue(const Entity::SQS::Queue &queue) {
       auto result = _queueCollection.delete_many(make_document(kvp("queueUrl", queue.queueUrl)));
       _logger.debug() << "Queues deleted, count: " << result->deleted_count();
   }

    void SQSDatabase::DeleteAllQueues() {
        auto result = _queueCollection.delete_many({});
        _logger.debug() << "All queues deleted, count: " << result->deleted_count();
    }

    Entity::SQS::Message SQSDatabase::CreateMessage(const Entity::SQS::Message &message) {

        auto result = _messageCollection.insert_one(message.ToDocument());
        _logger.trace() << "Message created, oid: " << result->inserted_id().get_oid().value.to_string();

        return GetMessageById(result->inserted_id().get_oid().value);
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(bsoncxx::oid oid) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _messageCollection.find_one(make_document(kvp("_id", oid)));
        Entity::SQS::Message result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::SQS::Message SQSDatabase::GetMessageByReceiptHandle(const std::string &receiptHandle) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _messageCollection.find_one(make_document(kvp("receiptHandle", receiptHandle)));
        Entity::SQS::Message result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(const std::string &oid) {
        return GetMessageById(bsoncxx::oid(oid));
    }

    void SQSDatabase::ReceiveMessages(const std::string &region, const std::string &queueUrl, Entity::SQS::MessageList &messageList) {
        auto now = std::chrono::high_resolution_clock::now();

        auto messageCursor = _messageCollection.find(make_document(kvp("queueUrl", queueUrl), kvp("status", Entity::SQS::INITIAL)));
        for (auto message : messageCursor) {
            Entity::SQS::Message result;
            result.FromDocument(message);
            result.receiptHandle = Core::StringUtils::GenerateRandomString(120);
            messageList.push_back(result);
            _messageCollection.update_one(make_document(kvp("_id", message["_id"].get_oid())),
                                          make_document(kvp("$set", make_document(kvp("status", Entity::SQS::SEND),
                                                                                  kvp("lastSend", bsoncxx::types::b_date(now)),
                                                                                  kvp("receiptHandle", result.receiptHandle)))));
        }
        _logger.trace() << "Messages received, region: " << region << " queue: " << queueUrl + " count: " << messageList.size();
    }

    void SQSDatabase::ResetMessages(const std::string &queueUrl, long visibility) {

        long updated = 0;
        auto messageCursor = _messageCollection.find(make_document(kvp("queueUrl", queueUrl), kvp("status", Entity::SQS::SEND)));
        for (auto message : messageCursor) {
            _messageCollection.update_one(make_document(kvp("_id", message["_id"].get_oid())),
                                          make_document(kvp("$set",
                                                            make_document(kvp("status", Entity::SQS::INITIAL), kvp("receiptHandle", "")))));
            updated++;
        }
        _logger.trace() << "Message reset, visibility: " << visibility << " updated: " << updated;
    }

    long SQSDatabase::CountMessages(const std::string &region, const std::string &queueUrl) {

        long count = _messageCollection.count_documents(make_document(kvp("region", region), kvp("queueUrl", queueUrl)));
        _logger.trace() << "Count messages, result: " << count;
        return count;
    }

    long SQSDatabase::CountMessagesByStatus(const std::string &region, const std::string &queueUrl, int status) {

        long count = _messageCollection.count_documents(make_document(kvp("region", region), kvp("queueUrl", queueUrl), kvp("status", status)));
        _logger.trace() << "Count messages by status, status: " << status << " result: " << count;
        return count;
    }

    void SQSDatabase::DeleteMessage(const Entity::SQS::Message &message) {
        auto result = _messageCollection.delete_one(make_document(kvp("receiptHandle", message.receiptHandle)));
        _logger.debug() << "Messages deleted, receiptHandle: " << message.receiptHandle << " count: " << result->deleted_count();
    }

    void SQSDatabase::DeleteAllMessages() {
        auto result = _messageCollection.delete_many({});
        _logger.debug() << "All messages deleted, count: " << result->deleted_count();
    }

} // namespace AwsMock::Database
