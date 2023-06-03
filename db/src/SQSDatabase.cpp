//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/SQSDatabase.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    SQSDatabase::SQSDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("SQSDatabase")) {
        Core::Logger::SetDefaultConsoleLogger("SQSDatabase");
    }

    bool SQSDatabase::QueueExists(const std::string &queueUrl) {

        int count = 0;
        try {

            Poco::Data::Session session = GetSession();

            Poco::Data::Statement stmt(session);
            stmt << "SELECT count(*) FROM sqs_queue WHERE url=?", bind(queueUrl), into(count), now;

            session.close();
            poco_trace(_logger, "Queue exists: " + std::to_string(count));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return count > 0;
    }

    bool SQSDatabase::QueueExists(const std::string &region, const std::string &name) {

        int count = 0;
        try {

            Poco::Data::Session session = GetSession();

            Poco::Data::Statement stmt(session);
            stmt << "SELECT count(*) FROM sqs_queue WHERE region=? AND name=?", bind(region), bind(name), into(count), now;

            session.close();
            poco_trace(_logger, "Queue exists: " + std::to_string(count));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return count > 0;
    }

    Entity::SQS::Queue SQSDatabase::CreateQueue(const Entity::SQS::Queue &queue) {

        Entity::SQS::Queue result;
        try {
            Poco::Data::Session session = GetSession();

            // Select database
            int id = 0;
            Poco::Data::Statement insert(session);
            insert << "INSERT INTO sqs_queue(region,name,owner,url) VALUES(?,?,?,?) returning id", bind(queue.region), bind(queue.name), bind(queue.owner),
                bind(queue.url), into(id), now;

            Poco::Data::Statement select(session);
            select << "SELECT id,region,name,owner,created,modified FROM sqs_queue WHERE id=?", bind(id), into(result.id), into(result.region), into(result.name),
                into(result.owner), into(result.created), into(result.modified), now;

            session.close();
            poco_trace(_logger, "Queue created, region: " + result.region + " name: " + result.name + " owner: " + result.owner);

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }

        return result;
    }

    Entity::SQS::QueueList SQSDatabase::ListQueues(const std::string &region) {

        try {
            Poco::Data::Session session = GetSession();

            // Select database
            Entity::SQS::Queue queue;
            Entity::SQS::QueueList queueList;

            Poco::Data::Statement stmt(session);
            stmt << "SELECT id,name,region,url,created,modified FROM sqs_queue WHERE region=?", bind(region), into(queue.id), into(queue.name), into(queue.region),
                into(queue.url), into(queue.created), into(queue.modified), range(0, 1);

            while (!stmt.done()) {
                stmt.execute();
                if (queue.id > 0) {
                    queueList.push_back(queue);
                }
            }
            poco_trace(_logger, "Queue list created, size:" + std::to_string(queueList.size()));
            return queueList;

        } catch (Poco::Exception &exc) {
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    void SQSDatabase::PurgeQueue(const std::string &region, const std::string &queueUrl) {

        try {
            Poco::Data::Session session = GetSession();

            // Delete messages
            Poco::Data::Statement stmt(session);
            stmt << "DELETE from sqs_message WHERE queue_url=?", bind(queueUrl), now;
            poco_trace(_logger, "Queue purged, url: " + queueUrl);

        } catch (Poco::Exception &exc) {
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    Entity::SQS::Message SQSDatabase::CreateMessage(const Entity::SQS::Message &message) {

        Entity::SQS::Message result;
        try {
            Poco::Data::Session session = GetSession();

            // Select database
            int id = 0;
            Poco::Data::Statement insert(session);
            insert << "INSERT INTO sqs_message(queue_url,body,message_id,receipt_handle,status,retries,md5_body,md5_attr) VALUES(?,?,?,?,?,?,?,?) returning id",
                bind(message.queue), bind(message.body), bind(message.messageId), bind(message.receiptHandle), bind(message.status), bind(message.retries),
                bind(message.md5Body), bind(message.md5Attr), into(id), now;

            Poco::Data::Statement select(session);
            select
                << "SELECT id,queue_url,body,message_id,receipt_handle,status,retries,md5_body,md5_attr,created,modified FROM sqs_message WHERE id=?",
                bind(id), into(result.id), into(result.queue), into(result.body), into(result.messageId), into(result.receiptHandle), into(result.status),
                into(result.retries), into(result.md5Body), into(result.md5Attr), into(result.created), into(result.modified), now;

            session.close();
            poco_trace(_logger, "Message created, queue: " + result.queue + " id: " + std::to_string(result.id));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }

        return result;
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(long id) {

        Entity::SQS::Message result;
        try {
            Poco::Data::Session session = GetSession();

            // Select database
            Poco::Data::Statement select(session);
            select << "SELECT id,queue_url,body,message_id,status,retries,md5_body,md5_attr,created,modified FROM sqs_message WHERE id=?", bind(id), into(result.id),
                into(result.queue), into(result.body), into(result.messageId), into(result.status), into(result.retries), into(result.md5Body), into(result.md5Attr),
                into(result.created), into(result.modified), now;

            session.close();
            poco_trace(_logger, "Message selected, queue: " + result.queue + " id: " + std::to_string(result.id));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }

    void SQSDatabase::DeleteMessage(const Entity::SQS::Message &message) {

        try {
            Poco::Data::Session session = GetSession();

            Poco::Data::Statement stmt(session);
            stmt << "DELETE FROM sqs_message WHERE id=?", bind(message.id), now;

            session.close();
            poco_trace(_logger, "Message deleted, queue: " + std::to_string(message.id));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
    }

    void SQSDatabase::DeleteQueue(const Entity::SQS::Queue &queue) {

        try {
            Poco::Data::Session session = GetSession();

            // Select database
            Poco::Data::Statement stmt(session);
            stmt << "DELETE FROM sqs_queue WHERE url=?", bind(queue.url), now;
            poco_trace(_logger, "Queue deleted, region: " + queue.region + " name: " + queue.name);

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
    }

} // namespace AwsMock::Database
