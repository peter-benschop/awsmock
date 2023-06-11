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

   /* void SQSDatabase::PurgeQueue(const std::string &region, const std::string &queueUrl) {

        try {
            Poco::Data::Session session = GetSession();

            // Delete messages
            Poco::Data::Statement stmt(session);
            stmt << "DELETE from sqs_message WHERE queue_url=?", bind(queueUrl), now;
            _logger.trace() << "Queue purged, url: " << queueUrl;

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    Entity::SQS::QueueAttribute SQSDatabase::CreateQueueAttributes(const Entity::SQS::QueueAttribute &queueAttribute) {

        int id = 0;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "INSERT INTO sqs_queue_attribute(queue_url,delay_seconds,max_message_size,message_retention_period,policy,redrive_policy,redrive_allow_policy,"
                       "receive_message_wait_time,visibility_timeout) VALUES(?,?,?,?,?,?,?,?,?) returning id",
                bind(queueAttribute.queueUrl), bind(queueAttribute.delaySeconds), bind(queueAttribute.maxMessageSize), bind(queueAttribute.messageRetentionPeriod),
                bind(queueAttribute.policy), bind(queueAttribute.redrivePolicy), bind(queueAttribute.redriveAllowPolicy), bind(queueAttribute.receiveMessageWaitTime),
                bind(queueAttribute.visibilityTimeout), into(id), now;
            session.commit();

            _logger.trace() << "Queue created, queueAttribute: " << queueAttribute.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
        }
        return GetQueueAttributesById(id);
    }

    Entity::SQS::QueueAttribute SQSDatabase::GetQueueAttributesById(long id) {

        Entity::SQS::QueueAttribute result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session
                << "SELECT id,queue_url,delay_seconds,max_message_size,message_retention_period,policy,redrive_policy,redrive_allow_policy,receive_message_wait_time,"
                   "visibility_timeout,created,modified FROM sqs_queue_attribute WHERE id=?",
                bind(id), into(result.id), into(result.queueUrl), into(result.delaySeconds), into(result.maxMessageSize), into(result.messageRetentionPeriod),
                into(result.policy), into(result.redrivePolicy), into(result.redriveAllowPolicy), into(result.receiveMessageWaitTime), into(result.visibilityTimeout),
                into(result.created), into(result.modified), now;
            session.commit();

            _logger.trace() << "Got queue: " << result.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
        }
        return result;
    }

    Entity::SQS::QueueAttribute SQSDatabase::GetQueueAttributesByQueueUrl(const std::string &queueUrl) {

        Entity::SQS::QueueAttribute result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,queue_url,delay_seconds,max_message_size,message_retention_period,policy,redrive_policy,redrive_allow_policy,receive_message_wait_time,"
                       "visibility_timeout,created,modified FROM sqs_queue_attribute WHERE queue_url=?",
                into(result.id), into(result.queueUrl), into(result.delaySeconds), into(result.maxMessageSize), into(result.messageRetentionPeriod),
                into(result.policy), into(result.redrivePolicy), into(result.redriveAllowPolicy), into(result.receiveMessageWaitTime), into(result.visibilityTimeout),
                into(result.created), into(result.modified),bind(queueUrl), now;
            session.commit();

            _logger.trace() << "Got queue sqs, " + result.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
        }
        return result;
    }

    void SQSDatabase::DeleteQueue(const Entity::SQS::Queue &queue) {

        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "DELETE FROM sqs_queue WHERE queue_url=?", bind(queue.queueUrl), now;
            session.commit();

            _logger.trace() << "Queue deleted: " << queue.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }*/

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

    Entity::SQS::Message SQSDatabase::GetMessageById(const std::string &oid) {
        return GetMessageById(bsoncxx::oid(oid));
    }

/*    void SQSDatabase::ReceiveMessages(const std::string &region, const std::string &queueUrl, Entity::SQS::MessageList &messageList) {

        try {
            Entity::SQS::Message result;

            Poco::Data::Session session = GetSession();

            // TODO: Add region to messages
            session.begin();
            Poco::Data::Statement select(session);
            select << "SELECT id,queue_url,body,message_id,receipt_handle,status,retries,md5_body,md5_attr,created,modified FROM sqs_message "
                      "WHERE queue_url=? AND status=?",
                bind(queueUrl), bind(Entity::SQS::INITIAL), into(result.id), into(result.queueUrl), into(result.body), into(result.messageId), into(result.receiptHandle),
                into(result.status), into(result.retries), into(result.md5Body), into(result.md5Attr), into(result.created), into(result.modified), range(0, 1);

            while (!select.done() && messageList.size() < 10) {
                select.execute();
                if (result.id > 0) {
                    messageList.push_back(result);
                }
            }

            for (const auto &m : messageList) {
                Poco::DateTime now;
                Poco::Data::Statement update(session);
                update << "UPDATE sqs_message SET status=?,retries=?,last_send=? WHERE id=?",
                    bind(Entity::SQS::SEND), bind(m.retries + 1), bind(now), bind(m.id);
                update.execute();
            }

            session.commit();
            _logger.trace() << "Messages received, region: " << region << " queue: " << queueUrl + " count: " << messageList.size();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    [[maybe_unused]] void SQSDatabase::ResetMessages(const std::string &queueUrl, long visibility) {

        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session
                << "UPDATE sqs_message SET status=?, modified=CURRENT_TIMESTAMP WHERE queue_url=? AND status=? AND "
                   "(strftime('%s', CURRENT_TIMESTAMP) - strftime('%s', last_send)) > ?",
                bind(Entity::SQS::INITIAL), bind(queueUrl), bind(Entity::SQS::SEND), bind(visibility), now;

            session.commit();
            _logger.trace() << "Message reset, visibility: " << visibility;

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    void SQSDatabase::DeleteMessage(const Entity::SQS::Message &message) {

        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "DELETE FROM sqs_message WHERE queue_url=? AND receipt_handle=?", bind(message.queueUrl), bind(message.receiptHandle), now;
            session.commit();
            _logger.trace() << "Message deleted, queue: " << message.id;

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }*/

    void SQSDatabase::DeleteAllMessages() {
        auto result = _messageCollection.delete_many({});
        _logger.debug() << "All messages deleted, count: " << result->deleted_count();
    }

} // namespace AwsMock::Database
