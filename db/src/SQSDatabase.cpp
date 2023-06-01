//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/SQSDatabase.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    SQSDatabase::SQSDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("SQSDatabase")) {
        Core::Logger::SetDefaultConsoleLogger("SQSDatabase");
    }

    bool SQSDatabase::QueueExists(const std::string &url) {

        int count = 0;
        try {

            Poco::Data::Session session = GetSession();

            Poco::Data::Statement stmt(session);
            stmt << "SELECT count(*) FROM sqs_queue WHERE url=?", bind(url), into(count), now;

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
            Poco::Data::Statement insert(session);
            insert << "INSERT INTO sqs_queue(region,name,owner,url) VALUES(?,?,?,?)", bind(queue.region), bind(queue.name), bind(queue.owner), bind(queue.url),
                now;

            Poco::Data::Statement select(session);
            select << "SELECT id,region,name,owner,created,modified FROM sqs_queue WHERE region=? AND name=?", bind(queue.region), bind(queue.name),
                into(result.id), into(result.region), into(result.name), into(result.owner), into(result.created), into(result.modified), now;

            session.close();
            poco_trace(_logger, "Queue created, region: " + result.region + " name: " + result.name + " owner: " + result.owner);

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }

        return result;
    }

    Entity::SQS::QueueList SQSDatabase::ListQueues(const std::string &region) {

        Poco::Data::Session session = GetSession();

        // Select database
        Entity::SQS::Queue queue;
        Entity::SQS::QueueList queueList;

        Poco::Data::Statement stmt(session);
        stmt << "SELECT id,name,region,url,created,modified FROM sqs_queue WHERE region=?", bind(region), into(queue.id), into(queue.name), into(queue.region), into(queue.url),
            into(queue.created), into(queue.modified), range(0, 1);

        while (!stmt.done()) {
            stmt.execute();
            if(queue.id > 0) {
                queueList.push_back(queue);
            }
        }
        poco_trace(_logger, "Queue list created, size:" + std::to_string(queueList.size()));
        return queueList;
    }

    void SQSDatabase::DeleteQueue(const Entity::SQS::Queue &queue) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "DELETE FROM sqs_queue WHERE url=?", bind(queue.url);
        stmt.execute();
    }

} // namespace AwsMock::Database
