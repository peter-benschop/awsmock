//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/S3Database.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    S3Database::S3Database(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("S3Database")) {
        Core::Logger::SetDefaultConsoleLogger("S3Database");
    }

    bool S3Database::BucketExists(const std::string &region, const std::string &name) {

        Poco::Data::Session session = GetSession();

        int count = 0;
        Poco::Data::Statement stmt(session);
        stmt << "SELECT count(*) FROM s3_bucket WHERE region='" + region + "' AND name='" + name + "'", into(count), now;;
        stmt.execute();

        session.close();
        poco_trace(_logger, "Bucket exists: " + std::to_string(count));

        return count > 0;
    }

    void S3Database::CreateBucket(std::string &region, std::string &name) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "INSERT INTO s3_bucket(region, name) VALUES(?,?)", use(region), use(name);

        poco_trace(_logger, "Bucket created, region: " + region + " name: " + name);

        stmt.execute();
    }

    void S3Database::DeleteBucket(const std::string &region, const std::string &name) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "DELETE FROM s3_bucket WHERE region='" + region + "' AND name='" + name + "'";
        stmt.execute();
    }

} // namespace AwsMock::Database
