//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/S3Database.h"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    std::map<std::string, std::vector<std::string>> S3Database::allowedEventTypes = {
        {"Created", {"s3:ObjectCreated:Put", "s3:ObjectCreated:Post", "s3:ObjectCreated:Copy", "s3:ObjectCreated:CompleteMultipartUpload"}},
        {"Deleted", {"s3:ObjectRemoved:Delete", "s3:ObjectRemoved:DeleteMarkerCreated"}}
    };

    S3Database::S3Database(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("S3Database")) {
        Core::Logger::SetDefaultConsoleLogger("S3Database");

        CreateCollection("s3_bucket");
        CreateCollection("s3_object");

        _bucketCollection = GetConnection()["s3_bucket"];
        _objectCollection = GetConnection()["s3_object"];
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

    bool S3Database::HasObjects(const Entity::S3::Bucket &bucket) {

        int64_t count = _objectCollection.count_documents(make_document(kvp("region", bucket.region), kvp("bucket", bucket.name)));
        _logger.trace() << "Objects exists: " << (count > 0 ? "true" : "false");
        return count > 0;
    }

    Entity::S3::Bucket S3Database::UpdateBucket(const Entity::S3::Bucket &bucket) {

        auto result = _bucketCollection.replace_one(make_document(kvp("region", bucket.region), kvp("name", bucket.name)), bucket.ToDocument());

        _logger.trace() << "Bucket updated: " << bucket.ToString();

        return GetBucketByRegionName(bucket.region, bucket.name);
    }

    Entity::S3::ObjectList S3Database::ListBucket(const std::string &bucket, const std::string &prefix) {

        Entity::S3::ObjectList objectList;
        if (prefix.empty()) {
            auto objectCursor = _objectCollection.find(make_document(kvp("bucket", bucket)));
            for (auto object : objectCursor) {
                Entity::S3::Object result;
                result.FromDocument(object);
                objectList.push_back(result);
            }
        } else {
            auto objectCursor = _objectCollection.find(make_document(kvp("bucket", bucket), kvp("key", bsoncxx::types::b_regex{"^" + prefix + ".*"})));
            for (auto object : objectCursor) {
                Entity::S3::Object result;
                result.FromDocument(object);
                objectList.push_back(result);
            }
        }

        _logger.trace() << "Got object list, size:" << objectList.size();

        return objectList;
    }

    void S3Database::DeleteBucket(const Entity::S3::Bucket &bucket) {

        auto delete_many_result =
            _bucketCollection.delete_one(make_document(kvp("name", bucket.name)));
        _logger.debug() << "Bucket deleted, count: " << delete_many_result->deleted_count();
    }

    void S3Database::DeleteAllBuckets() {
        auto delete_many_result =
            _bucketCollection.delete_many({});
        _logger.debug() << "All buckets deleted, count: " << delete_many_result->deleted_count();
    }

    bool S3Database::ObjectExists(const Entity::S3::Object &object) {

        int64_t count = _objectCollection.count_documents(make_document(kvp("bucket", object.bucket), kvp("key", object.key)));
        _logger.trace() << "Object exists: " << (count > 0 ? "true" : "false");
        return count > 0;
    }

    Entity::S3::Object S3Database::CreateObject(const Entity::S3::Object &object) {

        auto insert_one_result = _objectCollection.insert_one(object.ToDocument());
        _logger.trace() << "Object created, oid: " << insert_one_result->inserted_id().get_oid().value.to_string();

        return GetObjectById(insert_one_result->inserted_id().get_oid().value);
    }

    Entity::S3::Object S3Database::GetObjectById(bsoncxx::oid oid) {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _objectCollection.find_one(make_document(kvp("_id", oid)));
        Entity::S3::Object result;
        result.FromDocument(mResult);

        return result;
    }

    Entity::S3::Object S3Database::GetObjectById(const std::string &oid) {
        return GetObjectById(bsoncxx::oid(oid));
    }

    Entity::S3::Object S3Database::CreateOrUpdateObject(const Entity::S3::Object &object) {

        if (ObjectExists(object)) {
            return UpdateObject(object);
        } else {
            return CreateObject(object);
        }
    }

    Entity::S3::Object S3Database::UpdateObject(const Entity::S3::Object &object) {

        auto update_one_result =
            _objectCollection.replace_one(make_document(kvp("region", object.region), kvp("bucket", object.bucket), kvp("key", object.key)), object.ToDocument());

        _logger.trace() << "Object updated: " << object.ToString();

        return GetObject(object.region, object.bucket, object.key);
    }

    Entity::S3::Object S3Database::GetObject(const std::string &region, const std::string &bucket, const std::string &key) {

        mongocxx::stdx::optional<bsoncxx::document::value>
            mResult = _objectCollection.find_one(make_document(kvp("region", region), kvp("bucket", bucket), kvp("key", key)));
        Entity::S3::Object result;
        result.FromDocument(mResult);

        _logger.trace() << "Got object: " << result.ToString();
        return result;
    }

    void S3Database::DeleteObject(const Entity::S3::Object &object) {
        auto result = _objectCollection.delete_many(make_document(kvp("region", object.region), kvp("bucket", object.bucket), kvp("key", object.key)));
        _logger.debug() << "Objects deleted, count: " << result->deleted_count();
    }

    // TODO: do it!
    /*void S3Database::DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys) {
        auto result = _objectCollection.delete_many(make_document(kvp("bucket", bucket), make_document(kvp("$in", make_array(keys))));
        _logger.debug() << "Objects deleted, count: " << result->deleted_count();
    }*/

    void S3Database::DeleteAllObjects() {
        auto result = _objectCollection.delete_many({});
        _logger.debug() << "All objects deleted, count: " << result->deleted_count();
    }

    Entity::S3::Bucket S3Database::CreateBucketNotification(const Entity::S3::Bucket &bucket, const Entity::S3::BucketNotification &bucketNotification) {

        Entity::S3::Bucket internBucket = GetBucketByRegionName(bucket.region, bucket.name);

        if (Core::StringUtils::Contains(bucketNotification.event, "*")) {

            std::vector<std::string> allowedEvents;
            if (Core::StringUtils::StartsWith(bucketNotification.event, "s3:ObjectCreated:")) {
                allowedEvents = allowedEventTypes["Created"];
            } else if (Core::StringUtils::StartsWith(bucketNotification.event, "s3:ObjectRemoved:")) {
                allowedEvents = allowedEventTypes["Deleted"];
            }

            for (const auto &it : allowedEvents) {

                if (!internBucket.HasNotification(bucketNotification.event)) {

                    Entity::S3::BucketNotification notification = {
                        .event=it,
                        .notificationId=bucketNotification.notificationId,
                        .queueArn=bucketNotification.queueArn,
                        .lambdaArn=bucketNotification.lambdaArn};
                    internBucket.notifications.emplace_back(notification);
                }
            }

        } else if (!internBucket.HasNotification(bucketNotification.event)) {

            internBucket.notifications.emplace_back(bucketNotification);
        }

        _logger.trace() << "Bucket notification added, notification: " << bucketNotification.ToString();

        return UpdateBucket(internBucket);
    }

    Entity::S3::Bucket S3Database::DeleteBucketNotifications(const Entity::S3::Bucket &bucket, const Entity::S3::BucketNotification &bucketNotification) {

        Entity::S3::Bucket internBucket = GetBucketByRegionName(bucket.region, bucket.name);

        if (Core::StringUtils::Contains(bucketNotification.event, "*")) {

            std::vector<std::string> allowedEvents;
            if (Core::StringUtils::StartsWith(bucketNotification.event, "s3:ObjectCreated:")) {
                allowedEvents = allowedEventTypes["Created"];
            } else if (Core::StringUtils::StartsWith(bucketNotification.event, "s3:ObjectRemoved:")) {
                allowedEvents = allowedEventTypes["Deleted"];
            }

            for (const auto &it : allowedEvents) {
                internBucket.notifications.erase(std::remove_if(internBucket.notifications.begin(),
                                                                internBucket.notifications.end(),
                                                                [it](const Entity::S3::BucketNotification &notification) {
                                                                  return it == notification.event;
                                                                }), internBucket.notifications.end());
            }
        } else {
            internBucket.notifications.erase(std::remove_if(internBucket.notifications.begin(),
                                                            internBucket.notifications.end(),
                                                            [bucketNotification](const Entity::S3::BucketNotification &notification) {
                                                              return bucketNotification.event == notification.event;
                                                            }), internBucket.notifications.end());
        }

        _logger.trace() << "Bucket notification deleted, notification: " << bucketNotification.ToString();

        return UpdateBucket(internBucket);
    }

    /*
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

} // namespace AwsMock::Database
