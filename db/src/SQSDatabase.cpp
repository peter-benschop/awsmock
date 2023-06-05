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
            session.begin();
            session << "SELECT COUNT(*) FROM sqs_queue WHERE url=?", bind(queueUrl), into(count), now;
            session.close();
            poco_trace(_logger, "Queue exists: " + std::string(count > 0 ? "true" : "false"));

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

        int id = 0;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "INSERT INTO sqs_queue(region,name,owner,queue_url,queue_arn) VALUES(?,?,?,?,?) returning id",
            bind(queue.region), bind(queue.name), bind(queue.owner), bind(queue.queueUrl), bind(queue.queueArn), into(id), now;
            session.commit();

            poco_trace(_logger, "Queue created, region: " + queue.region + " name: " + queue.name + " owner: " + queue.owner);

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return GetQueueById(id);
    }

    Entity::SQS::Queue SQSDatabase::GetQueueById(long id) {

        Entity::SQS::Queue result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,region,name,owner,queue_url,queue_arn,created,modified FROM sqs_queue WHERE id=?", bind(id), into(result.id), into(result.region), into(result.name),
                into(result.owner), into(result.queueUrl), into(result.queueArn), into(result.created), into(result.modified), now;
            session.commit();

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
            stmt << "SELECT id,name,region,queue_url,queue_arn,created,modified FROM sqs_queue WHERE region=?",
                bind(region), into(queue.id), into(queue.name), into(queue.region), into(queue.queueUrl), into(queue.queueArn), into(queue.created),
                into(queue.modified), range(0, 1);

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
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    Entity::SQS::QueueAttribute SQSDatabase::CreateQueueAttributes(const Entity::SQS::QueueAttribute &queueAttribute) {

        int id = 0;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "INSERT INTO sqs_queue_attribute(queue_url,delay_seconds,max_message_size,message_retension_period,policy,receive_message_wait_time,"
                       "visibility_timeout,redrive_policy,redrive_allow_policy) VALUES(?,?,?,?,?,?,?,?,?) returning id",
                bind(queueAttribute.queueUrl), bind(queueAttribute.delaySeconds), bind(queueAttribute.maxMessageSize), bind(queueAttribute.messageRetensionPeriod),
                bind(queueAttribute.policy), bind(queueAttribute.policy), bind(queueAttribute.receiveMessageWaitTime), bind(queueAttribute.receiveMessageWaitTime),
                bind(queueAttribute.visibilityTimeout), bind(queueAttribute.redrivePolicy), bind(queueAttribute.redriveAllowPolicy), into(id), now;
            session.commit();

            poco_trace(_logger, "Queue created, queueAttribute: " + queueAttribute.ToString());

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return GetQueueAttributesById(id);
    }

    Entity::SQS::QueueAttribute SQSDatabase::GetQueueAttributesById(long id) {

        Entity::SQS::QueueAttribute result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,queue_url,delay_seconds,max_message_size,message_retension_period,policy,receive_message_wait_time,visibility_timeout,redrive_policy,"
                       "redrive_allow_policy,created,modified FROM sqs_queue_attribute WHERE id=?", bind(id), into(result.id),
                into(result.queueUrl), into(result.delaySeconds), into(result.maxMessageSize), into(result.messageRetensionPeriod), into(result.policy),
                into(result.receiveMessageWaitTime), into(result.visibilityTimeout), into(result.redrivePolicy), into(result.redriveAllowPolicy), into(result.created),
                into(result.modified), now;
            session.commit();

            poco_trace(_logger, "Got queue attributes, " + result.ToString());

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }

    Entity::SQS::QueueAttribute SQSDatabase::GetQueueAttributesByQueueUrl(const std::string &queueUrl) {

        Entity::SQS::QueueAttribute result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,sqs_queue_attribute(queue_url,delay_seconds,max_message_size,message_retension_period,policy,receive_message_wait_time,"
                       "visibility_timeout,redrive_policy,redrive_allow_policy,created,modified FROM sqs_queue_attribute WHERE queue_url=?", bind(queueUrl), into(result.id),
                into(result.queueUrl), into(result.delaySeconds), into(result.maxMessageSize), into(result.messageRetensionPeriod), into(result.policy),
                into(result.receiveMessageWaitTime), into(result.visibilityTimeout), into(result.redrivePolicy), into(result.redriveAllowPolicy), into(result.created),
                into(result.modified), now;
            session.commit();

            poco_trace(_logger, "Got queue attributes, " + result.ToString());

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }

    void SQSDatabase::DeleteQueue(const Entity::SQS::Queue &queue) {

        try {
            Poco::Data::Session session = GetSession();

            // Select database
            Poco::Data::Statement stmt(session);
            stmt << "DELETE FROM sqs_queue WHERE url=?", bind(queue.queueUrl), now;
            poco_trace(_logger, "Queue deleted, region: " + queue.region + " name: " + queue.name);

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    Entity::SQS::Message SQSDatabase::CreateMessage(const Entity::SQS::Message &message) {

        long id = 0;
        Entity::SQS::Message result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "INSERT INTO sqs_message(queue_url,body,message_id,receipt_handle,status,retries,md5_body,md5_attr) VALUES(?,?,?,?,?,?,?,?) returning id",
                bind(message.queueUrl), bind(message.body), bind(message.messageId), bind(message.receiptHandle), bind(message.status), bind(message.retries),
                bind(message.md5Body), bind(message.md5Attr), into(id), now;
            session.commit();

            poco_trace(_logger, "Message created, queue: " + result.queueUrl + " id: " + std::to_string(result.id));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }

        return GetMessageById(id);
    }

    Entity::SQS::Message SQSDatabase::GetMessageById(long id) {

        Entity::SQS::Message result;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,queue_url,body,message_id,status,retries,md5_body,md5_attr,created,modified FROM sqs_message WHERE id=?", bind(id), into(result.id),
                into(result.queueUrl), into(result.body), into(result.messageId), into(result.status), into(result.retries), into(result.md5Body), into(result.md5Attr),
                into(result.created), into(result.modified), now;
            session.close();

            poco_trace(_logger, "Message selected, queue: " + result.queueUrl + " id: " + std::to_string(result.id));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }
        return result;
    }

    void SQSDatabase::ReceiveMessages(const std::string &region, const std::string &queueUrl, Entity::SQS::MessageList &messageList) {

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
            poco_trace(_logger, "Messages received, region: " + region + " queue: " + queueUrl + " count: " + std::to_string(messageList.size()));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
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
            poco_trace(_logger, "Message reset, visibility: " + std::to_string(visibility));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    void SQSDatabase::DeleteMessage(const Entity::SQS::Message &message) {

        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "DELETE FROM sqs_message WHERE queue_url=? AND receipt_handle=?", bind(message.queueUrl), bind(message.receiptHandle), now;
            session.commit();
            poco_trace(_logger, "Message deleted, queue: " + std::to_string(message.id));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

} // namespace AwsMock::Database
