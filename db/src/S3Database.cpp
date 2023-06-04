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

        int count = 0;
        Poco::Data::Session session = GetSession();

        session << "SELECT COUNT(*) FROM s3_bucket WHERE region=? AND name=?", bind(region), bind(name), into(count), now;

        session.close();
        poco_trace(_logger, "Bucket exists: " + std::to_string(count));

        return count > 0;
    }

    bool S3Database::BucketExists(const Entity::S3::Bucket &bucket) {

        int count = 0;
        try {
            Poco::Data::Session session = GetSession();
            session << "SELECT count(*) FROM s3_bucket WHERE region=? AND name=?", bind(bucket.region), bind(bucket.name), into(count), now;

            session.close();
            poco_trace(_logger, "Bucket exists: " + (count > 0 ? std::string("true") : std::string("false")));

        } catch(Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message());
        }
        return count > 0;
    }

    Entity::S3::Bucket S3Database::CreateBucket(const Entity::S3::Bucket &bucket) {

        Entity::S3::Bucket result;
        try {
            Poco::Data::Session session = GetSession();

            // Select database
            long id = 0;
            Poco::Data::Statement insert(session);
            insert << "INSERT INTO s3_bucket(region, name, owner) VALUES(?,?,?) returning id", bind(bucket.region), bind(bucket.name), bind(bucket.owner),
                into(id), now;

            Poco::Data::Statement select(session);
            select << "SELECT id,region,name,owner,created,modified FROM s3_bucket WHERE id=?", bind(id), into(result.id), into(result.region), into(result.name),
                into(result.owner), into(result.created), into(result.modified), now;
            poco_trace(_logger, "Bucket created, id: " + std::to_string(result.id) + " region: " + result.region + " name: " + result.name + " owner: " + result.owner);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message());
        }
        return result;
    }

    bool S3Database::HasObjects(const Entity::S3::Bucket &bucket) {

        int count = 0;
        try {
            Poco::Data::Session session = GetSession();
            session << "SELECT count(*) FROM s3_object WHERE bucket=?", bind(bucket.name), into(count), now;

            session.close();
            poco_trace(_logger, "Bucket has objects: " + (count > 0 ? std::string("true") : std::string("false")));

        } catch(Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message());
        }
        return count > 0;
    }

    Entity::S3::Bucket S3Database::GetBucketById(long id) {

        Entity::S3::Bucket result;
        try {
            Poco::Data::Session session = GetSession();

            // Select database
            Poco::Data::Statement select(session);
            select << "SELECT id,region,name,owner,created,modified FROM s3_bucket WHERE id=?", bind(id), into(result.id), into(result.region), into(result.name),
                into(result.owner), into(result.created), into(result.modified), now;
            poco_trace(_logger, "Bucket created, id: " + std::to_string(result.id) + " region: " + result.region + " name: " + result.name + " owner: " + result.owner);

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }

    Entity::S3::BucketList S3Database::ListBuckets() {

        Poco::Data::Session session = GetSession();

        // Select database
        Entity::S3::Bucket bucket;
        Entity::S3::BucketList bucketList;

        Poco::Data::Statement stmt(session);
        stmt << "SELECT id,name,created,modified FROM s3_bucket", into(bucket.id), into(bucket.name), into(bucket.created), into(bucket.modified), range(0, 1);

        while (!stmt.done()) {
            stmt.execute();
            if(bucket.id > 0)
            bucketList.push_back(bucket);
        }
        poco_trace(_logger, "Bucket list created, size:" + std::to_string(bucketList.size()));
        return bucketList;
    }

    Entity::S3::ObjectList S3Database::ListBucket(const std::string &bucket) {

        Poco::Data::Session session = GetSession();

        // Select database
        Entity::S3::Object object;
        Entity::S3::ObjectList objectList;

        Poco::Data::Statement stmt(session);
        stmt << "SELECT id,bucket,key,size,md5sum,content_type,created,modified FROM s3_object WHERE bucket=?", bind(bucket), into(object.id), into(object.bucket), into(object.key),
            into(object.size), into(object.md5sum), into(object.contentType), into(object.created), into(object.modified), range(0, 1);

        while (!stmt.done() && objectList.size() < MAX_FILES) {
            stmt.execute();
            if (object.id > 0) {
                objectList.push_back(object);
            }
        }
        poco_trace(_logger, "Bucket list created, size:" + std::to_string(objectList.size()));
        return objectList;
    }

    bool S3Database::ObjectExists(const Entity::S3::Object &object) {

        int count = 0;
        Poco::Data::Session session = GetSession();
        try {
            session << "SELECT count(*) FROM s3_object WHERE bucket=? AND key=?", bind(object.bucket), bind(object.key), into(count), now;
            session.close();
            poco_trace(_logger, "Object exists: " + std::to_string(count));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return count > 0;
    }

    Entity::S3::Object S3Database::CreateObject(const Entity::S3::Object &object) {

        int id = 0;
        try {
            Poco::Data::Session session = GetSession();

            session << "INSERT INTO s3_object(bucket,key,owner,size,md5sum,content_type) VALUES(?,?,?,?,?,?) returning id",
                bind(object.bucket), bind(object.key), bind(object.owner), bind(object.size), bind(object.md5sum), bind(object.contentType), into(id), now;
            poco_trace(_logger, "Object created, bucket: " + object.bucket + " key: " + object.key);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return GetObjectById(id);
    }

    Entity::S3::Object S3Database::UpdateObject(const Entity::S3::Object &object) {

        int id = 0;
        try {
            Poco::Data::Session session = GetSession();

            Poco::Data::Statement update(session);
            update << "UPDATE s3_object SET owner=?,size=?,md5sum=?,content_type=?,modified=CURRENT_TIMESTAMP WHERE bucket=? AND key=? returning id",
                bind(object.owner), bind(object.size), bind(object.md5sum), bind(object.contentType), bind(object.bucket), bind(object.key), into(id), now;
            poco_trace(_logger, "Object updated, bucket: " + object.bucket + " key: " + object.key);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return GetObjectById(id);
    }

    Entity::S3::Object S3Database::GetObject(const std::string &bucket, const std::string &key) {

        Entity::S3::Object object;
        try {
            Poco::Data::Session session = GetSession();

            session << "SELECT id,bucket,key,owner,size,md5sum,content_type,modified FROM s3_object WHERE bucket=? AND key=?",
                bind(bucket), bind(key), into(object.id), into(object.bucket), into(object.key), into(object.owner), into(object.size), into(object.md5sum),
                into(object.contentType), into(object.modified), now;

            poco_trace(_logger, "S3 object, bucket: " + object.bucket + " key: " + object.key);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return object;
    }

    Entity::S3::Object S3Database::GetObjectById(long id) {

        Entity::S3::Object object;
        try {
            Poco::Data::Session session = GetSession();

            session << "SELECT id,bucket,key,owner,size,md5sum,content_type,modified FROM s3_object WHERE id=?",
                bind(id), into(object.id), into(object.bucket), into(object.key), into(object.owner), into(object.size), into(object.md5sum), into(object.contentType),
                into(object.modified), now;

            poco_trace(_logger, "S3 object, bucket: " + object.bucket + " key: " + object.key);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return object;
    }

    bool S3Database::BucketNotificationExists(const Entity::S3::BucketNotification &bucketNotification) {

        int count = 0;
        Poco::Data::Session session = GetSession();

        std::string event = Poco::replace(bucketNotification.event, "*", "%");
        session << "SELECT COUNT(*) FROM s3_notification WHERE region=? AND bucket=? AND event=?",
            bind(bucketNotification.region), bind(bucketNotification.bucket), bind(event), into(count), now;

        session.close();
        poco_trace(_logger, "Bucket notification exists: " + std::string(count > 0 ? "true" : "false"));

        return count > 0;
    }

    Entity::S3::BucketNotification S3Database::CreateBucketNotification(const Entity::S3::BucketNotification &bucketNotification) {

        long id = 0;
        try {
            Poco::Data::Session session = GetSession();

            std::string event = Poco::replace(bucketNotification.event, "*", "%");
            session << "INSERT INTO s3_notification(bucket,region,notification_id,function,event) VALUES(?,?,?,?,?) returning id",
                bind(bucketNotification.bucket), bind(bucketNotification.region), bind(bucketNotification.notificationId), bind(bucketNotification.function),
                bind(event), into(id), now;

            poco_trace(_logger,
                       "Bucket notification added, bucket: " + bucketNotification.bucket + " function: " + bucketNotification.function + " event: "
                           + bucketNotification.event);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
            throw Core::DatabaseException(exc.message(), 500);
        }
        return GetBucketNotificationById(id);
    }

    Entity::S3::BucketNotification S3Database::GetBucketNotificationById(long id) {

        Entity::S3::BucketNotification result;
        try {
            Poco::Data::Session session = GetSession();

            session << "SELECT id,bucket,region,notification_id,function,event,created,modified FROM s3_notification WHERE id=?", bind(id), into(result.id),
                into(result.bucket), into(result.region), into(result.notificationId), into(result.function), into(result.event), into(result.created),
                into(result.modified), now;

            poco_trace(_logger, "Bucket notification added, bucket: " + result.bucket + " function: " + result.function + " event: " + result.event);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }

    bool S3Database::HasBucketNotification(const Entity::S3::BucketNotification &bucketNotification) {

        int count = 0;
        try {
            Poco::Data::Session session = GetSession();

            session << "SELECT COUNT(*) FROM s3_notification WHERE region=? AND bucket=?",
                bind(bucketNotification.region), bind(bucketNotification.bucket), into(count), now;

            poco_trace(_logger, "Check bucket notification added, count: " + std::to_string(count));

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return count > 0;
    }

    Entity::S3::BucketNotification S3Database::GetBucketNotification(const Entity::S3::BucketNotification &bucketNotification) {

        Entity::S3::BucketNotification result;
        try {
            Poco::Data::Session session = GetSession();

            session << "SELECT id,bucket,region,notification_id,function,event,created,modified FROM s3_notification WHERE region=? AND bucket=? AND '" +
                bucketNotification.event + "' like event",
                bind(bucketNotification.region), bind(bucketNotification.bucket), bind(bucketNotification.event), into(result.id), into(result.bucket), into(result.region),
                into(result.notificationId), into(result.function), into(result.event), into(result.created), into(result.modified), now;

            poco_trace(_logger, "Bucket notification added, bucket: " + result.bucket + " function: " + result.function + " event: " + result.event);

            session.close();

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message() << std::endl;
            poco_error(_logger, "Database exception: " + exc.message());
        }
        return result;
    }

    void S3Database::DeleteBucket(const Entity::S3::Bucket &bucket) {

        try {
            Poco::Data::Session session = GetSession();

            session << "DELETE FROM s3_bucket WHERE region=? AND name=?", bind(bucket.region), bind(bucket.name), now;
            poco_trace(_logger, "Bucket deleted, bucket: " + bucket.name + " region: " + bucket.region);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
    }

    void S3Database::DeleteObject(const Entity::S3::Object &object) {

        try {
            Poco::Data::Session session = GetSession();

            session << "DELETE FROM s3_object WHERE bucket=? AND key=?", bind(object.bucket), bind(object.key), now;
            poco_trace(_logger, "Object deleted, bucket: " + object.bucket + " key: " + object.key);

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
    }

    void S3Database::DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys) {

        try {
            Poco::Data::Session session = GetSession();

            for(auto it : keys) {
                session << "DELETE FROM s3_object WHERE bucket=? AND key=?", bind(bucket), bind(it), now;
            }
            poco_trace(_logger, "Objects deleted, bucket: " + bucket + " count: " + std::to_string(keys.size()));

            session.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }
    }

} // namespace AwsMock::Database
