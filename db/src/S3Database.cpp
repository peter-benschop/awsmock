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

    void S3Database::CreateBucket(const Entity::S3::Bucket &bucket) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "INSERT INTO s3_bucket(region, name, owner) VALUES(?,?,?)", bind(bucket.region), bind(bucket.name), bind(bucket.owner);

        poco_trace(_logger, "Bucket created, region: " + bucket.region + " name: " + bucket.name + " owner: " + bucket.owner);

        stmt.execute();
    }

    Entity::S3::BucketList S3Database::ListBuckets() {

        Poco::Data::Session session = GetSession();

        // Select database
        Entity::S3::Bucket bucket;
        Entity::S3::BucketList bucketList;

        Poco::Data::Statement stmt(session);
        stmt << "SELECT name,created,modified FROM s3_bucket", into(bucket.name), into(bucket.created), into(bucket.modified), range(0, 1);

        while (!stmt.done()) {
            stmt.execute();
            bucketList.push_back(bucket);
        }
        poco_trace(_logger, "Bucket list created, size:" + std::to_string(bucketList.size()));
        return bucketList;
    }

    Entity::S3::ObjectList S3Database::ListBucket(const std::string &bucket) {

        int count;
        Poco::Data::Session session = GetSession();

        // Select database
        Entity::S3::Object object;
        Entity::S3::ObjectList objectList;

        Poco::Data::Statement stmt(session);
        stmt << "SELECT id,key,created,modified FROM s3_object WHERE bucket=?", bind(bucket), into(object.id), into(object.key), into(object.created),
            into(object.modified), range(0, 1);

        while (!stmt.done() && count < MAX_FILES) {
            stmt.execute();
            objectList.push_back(object);
        }
        poco_trace(_logger, "Bucket list created, size:" + std::to_string(objectList.size()));
        return objectList;
    }

    void S3Database::CreateObject(const Entity::S3::Object &object) {

        try {
            Poco::Data::Session session = GetSession();

            // Select database
            Poco::Data::Statement stmt(session);
            stmt << "INSERT INTO s3_object(bucket, key, owner, size, md5sum, content_type) VALUES(?,?,?,?,?,?)",
                bind(object.bucket), bind(object.key), bind(object.owner), bind(object.size), bind(object.md5sum), bind(object.contentType);

            poco_trace(_logger, "Object created, bucket: " + object.bucket + " key: " + object.key);

            stmt.execute();
        } catch(Poco::Exception &exc){
            poco_error(_logger, "DB exception: " + exc.message());
        }
    }

    void S3Database::DeleteBucket(const Entity::S3::Bucket &bucket) {

        Poco::Data::Session session = GetSession();

        // Select database
        Poco::Data::Statement stmt(session);
        stmt << "DELETE FROM s3_bucket WHERE region=? AND name=?", bind(bucket.region), bind(bucket.name);
        stmt.execute();
    }

} // namespace AwsMock::Database
