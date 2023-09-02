//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/S3Database.h"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::builder::stream::document;

    std::map<std::string, std::vector<std::string>> S3Database::allowedEventTypes = {
        {"Created", {"s3:ObjectCreated:Put", "s3:ObjectCreated:Post", "s3:ObjectCreated:Copy", "s3:ObjectCreated:CompleteMultipartUpload"}},
        {"Deleted", {"s3:ObjectRemoved:Delete", "s3:ObjectRemoved:DeleteMarkerCreated"}}
    };

    S3Database::S3Database(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("S3Database")) {

        // Get collections
        _bucketCollection = GetConnection()["s3_bucket"];
        _objectCollection = GetConnection()["s3_object"];
    }

    bool S3Database::BucketExists(const std::string &region, const std::string &name) {

        int64_t count = _bucketCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
        log_trace_stream(_logger) << "Bucket exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
    }

    bool S3Database::BucketExists(const Entity::S3::Bucket &bucket) {
        return BucketExists(bucket.region, bucket.name);
    }

    Entity::S3::Bucket S3Database::CreateBucket(const Entity::S3::Bucket &bucket) {

        auto insert_one_result = _bucketCollection.insert_one(bucket.ToDocument());
        log_trace_stream(_logger) << "Bucket created, oid: " << insert_one_result->inserted_id().get_oid().value.to_string() << std::endl;

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

        bsoncxx::builder::stream::document filter{};
        filter << "region" << region << "name" << name << bsoncxx::builder::stream::finalize;

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _bucketCollection.find_one({filter});

        if (mResult->empty()) {
            return {};
        }

        Entity::S3::Bucket result;
        result.FromDocument(mResult);
        log_trace_stream(_logger) << "Got bucket: " << result.ToString() << std::endl;
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

        log_trace_stream(_logger) << "Got bucket list, size:" << bucketList.size() << std::endl;
        return bucketList;
    }

    bool S3Database::HasObjects(const Entity::S3::Bucket &bucket) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << bucket.region << "name" << bucket.name << bsoncxx::builder::stream::finalize;

        int64_t count = _objectCollection.count_documents({filter});
        log_trace_stream(_logger) << "Objects exists: " << (count > 0 ? "true" : "false") << std::endl;

        return count > 0;
    }

    Entity::S3::Bucket S3Database::UpdateBucket(const Entity::S3::Bucket &bucket) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << bucket.region << "name" << bucket.name << bsoncxx::builder::stream::finalize;

        auto result = _bucketCollection.replace_one({filter}, bucket.ToDocument());
        log_trace_stream(_logger) << "Bucket updated: " << bucket.ToString() << std::endl;

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

        log_trace_stream(_logger) << "Got object list, size:" << objectList.size() << std::endl;

        return objectList;
    }

    Entity::S3::ObjectList S3Database::ListObjects(const std::string &prefix) {

        Entity::S3::ObjectList objectList;
        if (prefix.empty()) {
            auto objectCursor = _objectCollection.find({});
            for (auto object : objectCursor) {
                Entity::S3::Object result;
                result.FromDocument(object);
                objectList.push_back(result);
            }
        } else {
            auto objectCursor = _objectCollection.find(make_document(kvp("key", bsoncxx::types::b_regex{"^" + prefix + ".*"})));
            for (auto object : objectCursor) {
                Entity::S3::Object result;
                result.FromDocument(object);
                objectList.push_back(result);
            }
        }

        log_trace_stream(_logger) << "Got object list in all buckets, size:" << objectList.size() << std::endl;

        return objectList;
    }


    void S3Database::DeleteBucket(const Entity::S3::Bucket &bucket) {

        auto delete_many_result =
            _bucketCollection.delete_one(make_document(kvp("name", bucket.name)));
        log_debug_stream(_logger) << "Bucket deleted, count: " << delete_many_result->deleted_count() << std::endl;
    }

    void S3Database::DeleteAllBuckets() {
        auto delete_many_result =
            _bucketCollection.delete_many({});
        log_debug_stream(_logger) << "All buckets deleted, count: " << delete_many_result->deleted_count() << std::endl;
    }

    bool S3Database::ObjectExists(const Entity::S3::Object &object) {

        bsoncxx::builder::stream::document filter{};
        filter << "region" << object.region << "key" << object.key << bsoncxx::builder::stream::finalize;

        int64_t count = _objectCollection.count_documents({filter});
        log_trace_stream(_logger) << "Object exists: " << (count > 0 ? "true" : "false") << std::endl;

        return count > 0;
    }

    Entity::S3::Object S3Database::CreateObject(const Entity::S3::Object &object) {

        try {

            auto insert_one_result = _objectCollection.insert_one(object.ToDocument().view());
            log_trace_stream(_logger) << "Object created, oid: " << insert_one_result->inserted_id().get_oid().value.to_string() << std::endl;
            return GetObjectById(insert_one_result->inserted_id().get_oid().value);

        } catch (mongocxx::exception::system_error &e) {
            log_error_stream(_logger) << "Get object by ID failed, error: " << e.what() << std::endl;
        }
        return {};
    }

    Entity::S3::Object S3Database::GetObjectById(bsoncxx::oid oid) {

        try {
            bsoncxx::builder::stream::document filter{};
            filter << "_id" << oid << bsoncxx::builder::stream::finalize;

            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _objectCollection.find_one({filter});

            if (mResult->empty()) {
                return {};
            }

            Entity::S3::Object result;
            result.FromDocument(mResult);
            return result;
        } catch (mongocxx::exception::system_error &e) {
            log_error_stream(_logger) << "Get object by ID failed, error: " << e.what() << std::endl;
        }
        return {};
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

        try {
            bsoncxx::builder::stream::document filter{};
            filter << "region" << object.region << "bucket" << object.bucket << "key" << object.key << bsoncxx::builder::stream::finalize;

            auto update_one_result = _objectCollection.replace_one({filter}, object.ToDocument());
            log_trace_stream(_logger) << "Object updated: " << object.ToString() << std::endl;

        } catch (mongocxx::exception::system_error &e) {
            log_error_stream(_logger) << "Update object failed, error: " << e.what() << std::endl;
        }
        return GetObject(object.region, object.bucket, object.key);
    }

    Entity::S3::Object S3Database::GetObject(const std::string &region, const std::string &bucket, const std::string &key) {

        try {
            bsoncxx::builder::stream::document filter{};
            filter << "region" << region << "bucket" << bucket << "key" << key << bsoncxx::builder::stream::finalize;

            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _objectCollection.find_one({filter});
            if (!mResult->empty()) {
                Entity::S3::Object result;
                result.FromDocument(mResult);

                log_trace_stream(_logger) << "Got object: " << result.ToString() << std::endl;
                return result;
            }

        } catch (mongocxx::exception::system_error &e) {
            log_error_stream(_logger) << "Get object failed, error: " << e.what() << std::endl;
        }
        return {};
    }

    long S3Database::ObjectCount(const Entity::S3::Bucket &bucket) {

        try {
            bsoncxx::builder::stream::document filter{};
            filter << "region" << bucket.region << "bucket" << bucket.name << bsoncxx::builder::stream::finalize;

            long count = _objectCollection.count_documents({filter});
            log_trace_stream(_logger) << "Object count: " << count << std::endl;
            return count;

        } catch (mongocxx::exception::system_error &e) {
            log_error_stream(_logger) << "Object count failed, error: " << e.what() << std::endl;
        }
        return {};
    }

    void S3Database::DeleteObject(const Entity::S3::Object &object) {

        try {
            bsoncxx::builder::stream::document filter{};
            filter << "region" << object.region << "bucket" << object.bucket << "key" << object.key << bsoncxx::builder::stream::finalize;

            auto result = _objectCollection.delete_many({filter});
            log_debug_stream(_logger) << "Objects deleted, count: " << result->deleted_count() << std::endl;

        } catch (mongocxx::exception::system_error &e) {
            log_error_stream(_logger) << "Delete object failed, error: " << e.what() << std::endl;
        }
    }

    void S3Database::DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys) {

        bsoncxx::builder::basic::array array{};
        for (const auto &key : keys) {
            array.append(key);
        }
        bsoncxx::builder::stream::document filter{};
        filter << "$in" << array << bsoncxx::builder::stream::finalize;

        auto result = _objectCollection.delete_many({filter});
        log_debug_stream(_logger) << "Objects deleted, count: " << result->result().deleted_count() << std::endl;
    }

    void S3Database::DeleteAllObjects() {
        auto result = _objectCollection.delete_many({});
        log_debug_stream(_logger) << "All objects deleted, count: " << result->deleted_count() << std::endl;
    }

    Entity::S3::Bucket S3Database::CreateBucketNotification(const Entity::S3::Bucket &bucket, const Entity::S3::BucketNotification &bucketNotification) {

        Entity::S3::Bucket internBucket = GetBucketByRegionName(bucket.region, bucket.name);
        internBucket.notifications.clear();
        if (Core::StringUtils::Contains(bucketNotification.event, "*")) {

            std::vector<std::string> allowedEvents;
            if (Core::StringUtils::StartsWith(bucketNotification.event, "s3:ObjectCreated:")) {
                allowedEvents = allowedEventTypes["Created"];
            } else if (Core::StringUtils::StartsWith(bucketNotification.event, "s3:ObjectRemoved:")) {
                allowedEvents = allowedEventTypes["Deleted"];
            }

            for (const auto &it : allowedEvents) {

                Entity::S3::BucketNotification notification = {
                    .event=it,
                    .notificationId=bucketNotification.notificationId,
                    .queueArn=bucketNotification.queueArn,
                    .lambdaArn=bucketNotification.lambdaArn};
                internBucket.notifications.emplace_back(notification);
            }

        } else {

            internBucket.notifications.emplace_back(bucketNotification);
        }

        log_info_stream(_logger) << "Bucket notification added, notification: " << bucketNotification.ToString() << std::endl;

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

        log_trace_stream(_logger) << "Bucket notification deleted, notification: " << bucketNotification.ToString() << std::endl;

        return UpdateBucket(internBucket);
    }

} // namespace AwsMock::Database
