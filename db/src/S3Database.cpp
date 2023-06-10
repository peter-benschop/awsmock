//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/S3Database.h"

namespace AwsMock::Database {

    //using namespace Poco::Data::Keywords;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    S3Database::S3Database(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("S3Database")) {
        Core::Logger::SetDefaultConsoleLogger("S3Database");

        CreateCollection("s3_bucket");
        CreateCollection("s3_object");

        _bucketCollection = _database["s3_bucket"];
        _objectCollection = _database["s3_object"];
    }

    bool S3Database::BucketExists(const std::string &region, const std::string &name) {

        int64_t count = _bucketCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
        _logger.trace() << "Bucket exists: " << (count > 0 ? "true" : "false");
        return count > 0;
    }

    bool S3Database::BucketExists(const Entity::S3::Bucket &bucket) {
        return BucketExists(bucket.region, bucket.name);
    }

    Entity::S3::Bucket S3Database::CreateBucket(const Entity::S3::Bucket &bucket) {

        auto insert_one_result = _bucketCollection.insert_one(bucket.ToDocument());
        _logger.trace() << "Bucket created, oid: " << insert_one_result->inserted_id().get_oid().value.to_string();

        return GetBucketById(insert_one_result->inserted_id().get_oid().value);
    }

    Entity::S3::Bucket S3Database::GetBucketById(bsoncxx::oid oid) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _bucketCollection.find_one(make_document(kvp("_id", oid)));
        Entity::S3::Bucket result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::S3::Bucket S3Database::GetBucketById(const std::string &oid) {
        return GetBucketById(bsoncxx::oid(oid));
    }

    Entity::S3::Bucket S3Database::GetBucketByRegionName(const std::string &region, const std::string &name) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _bucketCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
        Entity::S3::Bucket result;
        result.FromDocument(mResult);

        _logger.trace() << "Got bucket: " << result.ToString();

        return result;
    }

    Entity::S3::BucketList S3Database::ListBuckets() {

        Entity::S3::BucketList bucketList;
        auto bucketCursor = _bucketCollection.find({});
        for (auto bucket : bucketCursor) {
            Entity::S3::Bucket result;
            result.FromDocument(bucket);
            bucketList.push_back(result);
        }

        _logger.trace() << "Got bucket list, size:" << bucketList.size();
        return bucketList;
    }


    /*bool S3Database::HasObjects(const Entity::S3::Bucket &bucket) {

        int count = 0;
        try {
            Poco::Data::Session session = GetSession();
            session << "SELECT count(*) FROM s3_object WHERE bucket=?", bind(bucket.name), into(count), now;

            session.close();
            _logger.trace() << "Bucket has objects: " << (count > 0 ? std::string("true") : std::string("false"));

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message());
        }
        return count > 0;
    }

    Entity::S3::ObjectList S3Database::ListBucket(const std::string &bucket, const std::string &prefix) {

        // Select database
        Entity::S3::Object object;
        Entity::S3::ObjectList objectList;
        try {

            Poco::Data::Session session = GetSession();
            Poco::Data::Statement stmt(session);
            session.begin();
            stmt << "SELECT id,bucket,key,size,md5sum,content_type,created,modified FROM s3_object WHERE bucket=? AND key like '" + prefix + "%'",
                into(object.id), into(object.bucket), into(object.key), into(object.size), into(object.md5sum), into(object.contentType),
                into(object.created), into(object.modified), bind(bucket), range(0, 1);

            while (!stmt.done() && objectList.size() < MAX_FILES) {
                stmt.execute();
                if (object.id > 0) {
                    objectList.push_back(object);
                }
            }
            session.close();
            _logger.trace() << "Object list created, size:" << objectList.size();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();

            throw Core::DatabaseException(exc.message(), 500);
        }
        return objectList;
    }*/

    bool S3Database::ObjectExists(const Entity::S3::Object &object) {

        int64_t count = _objectCollection.count_documents(make_document(kvp("bucket", object.bucket), kvp("key", object.key)));
        _logger.trace() << "Object exists: " << (count > 0 ? "true" : "false");
        return count > 0;
    }

    /*Entity::S3::Object S3Database::CreateObject(const Entity::S3::Object &object) {

        int id = 0;
        try {

            Poco::Data::Session session = GetSession();
            session.begin();
            session << "INSERT INTO s3_object(bucket,key,owner,size,md5sum,content_type) VALUES(?,?,?,?,?,?) returning id",
                bind(object.bucket), bind(object.key), bind(object.owner), bind(object.size), bind(object.md5sum), bind(object.contentType), into(id), now;
            session.commit();

            _logger.trace() << "Object created, id: " << id << " object: " << object.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return GetObjectById(id);
    }

    Entity::S3::Object S3Database::CreateOrUpdateObject(const Entity::S3::Object &object) {

        if (ObjectExists(object)) {
            return UpdateObject(object);
        } else {
            return CreateObject(object);
        }
    }

    Entity::S3::Object S3Database::UpdateObject(const Entity::S3::Object &object) {

        int id = 0;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "UPDATE s3_object SET owner=?,size=?,md5sum=?,content_type=?,modified=CURRENT_TIMESTAMP WHERE bucket=? AND key=? returning id",
                bind(object.owner), bind(object.size), bind(object.md5sum), bind(object.contentType), bind(object.bucket), bind(object.key), into(id), now;
            session.commit();

            _logger.trace() << "Object updated, bucket: " << object.bucket << " key: " << object.key;

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
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

            _logger.trace() << "S3 object, bucket: " << object.bucket + " key: " << object.key;

            session.close();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return object;
    }

    Entity::S3::Object S3Database::GetObjectById(long id) {

        Entity::S3::Object object;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT id,bucket,key,owner,size,md5sum,content_type,modified FROM s3_object WHERE id=?",
                bind(id), into(object.id), into(object.bucket), into(object.key), into(object.owner), into(object.size), into(object.md5sum), into(object.contentType),
                into(object.modified), now;

            _logger.trace() << "Get S3 object by id, object: " + object.ToString();

            session.close();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return object;
    }

    bool S3Database::BucketNotificationExists(const Entity::S3::BucketNotification &bucketNotification) {

        int count = 0;
        try {
            std::string event = Poco::replace(bucketNotification.event, "*", "%");

            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT COUNT(*) FROM s3_notification WHERE region=? AND bucket=? AND event=?",
                bind(bucketNotification.region), bind(bucketNotification.bucket), bind(event), into(count), now;
            session.close();

            _logger.trace() << "Bucket notification exists: " << (count > 0 ? "true" : "false");

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return count > 0;
    }

    Entity::S3::BucketNotification S3Database::CreateBucketNotification(const Entity::S3::BucketNotification &bucketNotification) {

        long id = 0;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            std::string event = Poco::replace(bucketNotification.event, "*", "%");
            session << "INSERT INTO s3_notification(region,bucket,notification_id,lambda_arn,queue_arn,event) VALUES(?,?,?,?,?,?) returning id",
                bind(bucketNotification.region), bind(bucketNotification.bucket), bind(bucketNotification.notificationId), bind(bucketNotification.lambdaArn),
                bind(bucketNotification.queueArn), bind(event), into(id), now;
            session.commit();

            _logger.trace() << "Bucket notification added, bucketNotification: " << bucketNotification.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return GetBucketNotificationById(id);
    }

    Entity::S3::BucketNotification S3Database::GetBucketNotificationById(long id) {

        Entity::S3::BucketNotification result;
        try {
            Poco::Data::Session session = GetSession();

            session << "SELECT id,region,bucket,event,notification_id,lambda_arn,queue_arn,created,modified FROM s3_notification WHERE id=?",
                into(result.id), into(result.region), into(result.bucket), into(result.event), into(result.notificationId), into(result.lambdaArn),
                into(result.queueArn), into(result.created), into(result.modified), bind(id), now;
            session.close();

            _logger.trace() << "Got bucket notification: " << result.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return result;
    }

    Entity::S3::BucketNotification S3Database::GetBucketNotificationByNotificationId(const std::string &region,
                                                                                     const std::string &bucket,
                                                                                     const std::string &notificationId) {
        Entity::S3::BucketNotification result;
        try {
            Poco::Data::Session session = GetSession();
            session << "SELECT id,region,bucket,event,notification_id,lambda_arn,queue_arn,created,modified FROM s3_notification "
                       "WHERE region=? AND bucket=? AND notification_id=?",
                into(result.id), into(result.region), into(result.bucket), into(result.event), into(result.notificationId), into(result.lambdaArn),
                into(result.queueArn), into(result.created), into(result.modified), bind(region), bind(bucket), bind(notificationId), now;
            session.close();

            _logger.trace() << "Got bucket notification: " + result.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return result;
    }

    bool S3Database::HasBucketNotification(const Entity::S3::BucketNotification &bucketNotification) {

        int count = 0;
        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT COUNT(*) FROM s3_notification WHERE region=? AND bucket=?",
                bind(bucketNotification.region), bind(bucketNotification.bucket), into(count), now;
            session.close();

            _logger.trace() << "Check bucket notification added, count: " << count;

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return count > 0;
    }

    Entity::S3::BucketNotification S3Database::GetBucketNotification(const Entity::S3::BucketNotification &bucketNotification) {

        Entity::S3::BucketNotification result;
        try {
            Poco::Data::Session session = GetSession();

            session << "SELECT id,region,bucket,notification_id,event,lambda_arn,queue_arn,created,modified FROM s3_notification "
                       "WHERE region=? AND bucket=? AND '" + bucketNotification.event + "' like event",
                into(result.id), into(result.region), into(result.bucket), into(result.notificationId), into(result.event), into(result.lambdaArn),
                into(result.queueArn), into(result.created), into(result.modified), bind(bucketNotification.region), bind(bucketNotification.bucket),
                bind(bucketNotification.event), now;

            _logger.trace() << "Got bucket notification: " << result.ToString();

            session.close();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
        return result;
    }

    void S3Database::DeleteBucketNotifications(const Entity::S3::BucketNotification &notification) {

        try {
            Poco::Data::Session session = GetSession();

            session.begin();
            session << "DELETE FROM s3_notification WHERE region=? AND bucket=?",
                bind(notification.region), bind(notification.bucket), now;
            session.commit();

            _logger.trace() << "Bucket notification deleted, region: " << notification.region << " bucket: " << notification.bucket;

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    void S3Database::DeleteBucket(const Entity::S3::Bucket &bucket) {

        try {
            Poco::Data::Session session = GetSession();

            session << "DELETE FROM s3_bucket WHERE region=? AND name=?", bind(bucket.region), bind(bucket.name), now;
            _logger.trace() << "Bucket deleted, bucket: " << bucket.name << " region: " << bucket.region;

            session.close();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    void S3Database::DeleteObject(const Entity::S3::Object &object) {

        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            session << "DELETE FROM s3_object WHERE bucket=? AND key=?", bind(object.bucket), bind(object.key), now;
            session.commit();

            _logger.trace() << "Object deleted: " << object.ToString();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }

    void S3Database::DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys) {

        try {
            Poco::Data::Session session = GetSession();
            session.begin();
            for(const auto &it : keys) {
                session << "DELETE FROM s3_object WHERE bucket=? AND key=?", bind(bucket), bind(it), now;
            }
            session.commit();

            _logger.trace() << "Objects deleted, bucket: " << bucket << " count: " << keys.size();

        } catch (Poco::Exception &exc) {
            _logger.error() << "Database exception: " << exc.message();
            throw Core::DatabaseException(exc.message(), 500);
        }
    }
    */

    void S3Database::DeleteAllBuckets() {
        auto  delete_many_result =
            _bucketCollection.delete_many({});
        _logger.debug() << "All buckets deleted, count: " << delete_many_result->deleted_count();
    }

} // namespace AwsMock::Database
