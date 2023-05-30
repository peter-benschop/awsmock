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
        stmt << "SELECT count(*) FROM s3_bucket WHERE region=? AND name=?", bind(region), bind(name), into(count), now;;
        stmt.execute();

        session.close();
        poco_trace(_logger, "Bucket exists: " + std::to_string(count));

        return count > 0;
    }

    void S3Database::CreateBucket(const std::string &region, const std::string &name, const std::string &owner) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "INSERT INTO s3_bucket(region, name, owner) VALUES(?,?,?)", bind(region), bind(name), bind(owner);

        poco_trace(_logger, "Bucket created, region: " + region + " name: " + name);

        stmt.execute();
    }

    Dto::S3::BucketList S3Database::ListBuckets() {

        Poco::Data::Session session = GetSession();

        // Select database
        Dto::S3::BucketRecord bucketRecord;
        Dto::S3::BucketList bucketList;

        Poco::Data::Statement stmt(session);
        stmt << "SELECT name,creation_date FROM s3_bucket", into(bucketRecord.name), into(bucketRecord.creationDatetime), range(0, 1);
        while (!stmt.done())
        {
            stmt.execute();
            bucketList.push_back(bucketRecord);
        }
        poco_trace(_logger, "Bucket list created, size:" + std::to_string(bucketList.size()));
        return bucketList;
    }

    void S3Database::CreateObject(const std::string &bucket, const std::string &key, const std::string &owner) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "INSERT INTO s3_object(bucket, key, owner) VALUES(?,?,?)", bind(bucket), bind(key), bind(owner);

        poco_trace(_logger, "Object created, bucket: " + bucket + " key: " + key + " owner: " + owner);

        stmt.execute();
    }

    void S3Database::DeleteBucket(const std::string &region, const std::string &name) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "DELETE FROM s3_bucket WHERE region=? AND name=?", bind(region), bind(name);
        stmt.execute();
    }

} // namespace AwsMock::Database
