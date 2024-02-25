//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/repository/S3Database.h"

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::builder::stream::document;

  std::map<std::string, std::vector<std::string>> S3Database::allowedEventTypes = {
    {"Created", {"s3:ObjectCreated:Put", "s3:ObjectCreated:Post", "s3:ObjectCreated:Copy", "s3:ObjectCreated:CompleteMultipartUpload"}},
    {"Deleted", {"s3:ObjectRemoved:Delete", "s3:ObjectRemoved:DeleteMarkerCreated"}}
  };

  S3Database::S3Database(Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("S3Database")), _memoryDb(S3MemoryDb::instance()) {

    if (HasDatabase()) {

      // Get collections
      _bucketCollection = GetConnection()["s3_bucket"];
      _objectCollection = GetConnection()["s3_object"];

    }
  }

  bool S3Database::BucketExists(const std::string &region, const std::string &name) {

    if (HasDatabase()) {

      try {
        int64_t count = _bucketCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
        log_trace_stream(_logger) << "Bucket exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.BucketExists(region, name);

    }
  }

  bool S3Database::BucketExists(const Entity::S3::Bucket &bucket) {
    return BucketExists(bucket.region, bucket.name);
  }

  Entity::S3::Bucket S3Database::CreateBucket(const Entity::S3::Bucket &bucket) {

    if (HasDatabase()) {

      auto insert_one_result = _bucketCollection.insert_one(bucket.ToDocument());
      log_trace_stream(_logger) << "Bucket created, oid: " << insert_one_result->inserted_id().get_oid().value.to_string() << std::endl;
      return GetBucketById(insert_one_result->inserted_id().get_oid().value);

    } else {

      return _memoryDb.CreateBucket(bucket);

    }
  }

  long S3Database::BucketCount() {

    if (HasDatabase()) {

      try {
        long count = _bucketCollection.count_documents(make_document());
        log_trace_stream(_logger) << "Bucket count: " << count << std::endl;
        return count;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Bucket count failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.BucketCount();

    }
    return -1;
  }

  Entity::S3::Bucket S3Database::GetBucketById(bsoncxx::oid oid) {

    mongocxx::stdx::optional<bsoncxx::document::value> mResult = _bucketCollection.find_one(make_document(kvp("_id", oid)));
    Entity::S3::Bucket result;
    result.FromDocument(mResult);

    return result;
  }

  Entity::S3::Bucket S3Database::GetBucketById(const std::string &oid) {

    if (HasDatabase()) {

      return GetBucketById(bsoncxx::oid(oid));

    } else {

      return _memoryDb.GetBucketById(oid);

    }
  }

  Entity::S3::Bucket S3Database::GetBucketByRegionName(const std::string &region, const std::string &name) {

    if (HasDatabase()) {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _bucketCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
      if (mResult->empty()) {
        return {};
      }

      Entity::S3::Bucket result;
      result.FromDocument(mResult);
      log_trace_stream(_logger) << "Got bucket: " << result.ToString() << std::endl;
      return result;

    } else {

      return _memoryDb.GetBucketByRegionName(region, name);

    }
  }

  Entity::S3::BucketList S3Database::ListBuckets() {

    Entity::S3::BucketList bucketList;
    if (HasDatabase()) {

      auto bucketCursor = _bucketCollection.find({});
      for (auto bucket : bucketCursor) {
        Entity::S3::Bucket result;
        result.FromDocument(bucket);
        bucketList.push_back(result);
      }

    } else {

      bucketList = _memoryDb.ListBuckets();

    }
    log_trace_stream(_logger) << "Got bucket list, size:" << bucketList.size() << std::endl;
    return bucketList;
  }

  bool S3Database::HasObjects(const Entity::S3::Bucket &bucket) {

    if (HasDatabase()) {

      int64_t count = _objectCollection.count_documents(make_document(kvp("region", bucket.region), kvp("bucket", bucket.name)));
      log_trace_stream(_logger) << "Objects exists: " << (count > 0 ? "true" : "false") << std::endl;
      return count > 0;

    } else {

      return _memoryDb.HasObjects(bucket);

    }
  }

  Entity::S3::Bucket S3Database::UpdateBucket(const Entity::S3::Bucket &bucket) {

    if (HasDatabase()) {

      auto result = _bucketCollection.replace_one(make_document(kvp("region", bucket.region), kvp("name", bucket.name)), bucket.ToDocument());
      log_trace_stream(_logger) << "Bucket updated: " << bucket.ToString() << std::endl;
      return GetBucketByRegionName(bucket.region, bucket.name);

    } else {

      return _memoryDb.UpdateBucket(bucket);
    }
  }

  Entity::S3::Bucket S3Database::CreateOrUpdateBucket(const Entity::S3::Bucket &bucket) {

    if (BucketExists(bucket)) {
      return UpdateBucket(bucket);
    } else {
      return CreateBucket(bucket);
    }

  }

  // TODO: Combine with Listobject
  Entity::S3::ObjectList S3Database::ListBucket(const std::string &bucket, const std::string &prefix) {

    Entity::S3::ObjectList objectList;
    if (HasDatabase()) {

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

    } else {

      objectList = _memoryDb.ListBucket(bucket, prefix);

    }

    log_trace_stream(_logger) << "Got object list, size:" << objectList.size() << std::endl;

    return objectList;
  }

  Entity::S3::ObjectList S3Database::ListObjects(const std::string &prefix) {

    Entity::S3::ObjectList objectList;
    if (HasDatabase()) {

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

    } else {

      objectList = _memoryDb.ListObjects(prefix);

    }

    log_trace_stream(_logger) << "Got object list in all buckets, size:" << objectList.size() << std::endl;
    return objectList;
  }

  void S3Database::DeleteBucket(const Entity::S3::Bucket &bucket) {

    if (HasDatabase()) {

      auto delete_many_result = _bucketCollection.delete_one(make_document(kvp("name", bucket.name)));
      log_debug_stream(_logger) << "Bucket deleted, count: " << delete_many_result->deleted_count() << std::endl;

    } else {

      _memoryDb.DeleteBucket(bucket);

    }
  }

  void S3Database::DeleteAllBuckets() {

    if (HasDatabase()) {

      auto delete_many_result =
        _bucketCollection.delete_many({});
      log_debug_stream(_logger) << "All buckets deleted, count: " << delete_many_result->deleted_count() << std::endl;

    } else {

      _memoryDb.DeleteAllBuckets();

    }
  }

  bool S3Database::ObjectExists(const Entity::S3::Object &object) {

    if (HasDatabase()) {

      int64_t count = _objectCollection.count_documents(make_document(kvp("region", object.region), kvp("bucket", object.bucket), kvp("key", object.key)));
      log_trace_stream(_logger) << "Object exists: " << (count > 0 ? "true" : "false") << std::endl;
      return count > 0;

    } else {
      return _memoryDb.ObjectExists(object);
    }
  }

  Entity::S3::Object S3Database::CreateObject(const Entity::S3::Object &object) {

    if (HasDatabase()) {

      try {

        auto insert_one_result = _objectCollection.insert_one(object.ToDocument().view());
        log_trace_stream(_logger) << "Object created, oid: " << insert_one_result->inserted_id().get_oid().value.to_string() << std::endl;
        return GetObjectById(insert_one_result->inserted_id().get_oid().value);

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get object by ID failed, error: " << e.what() << std::endl;
      }
      return {};

    } else {

      return _memoryDb.CreateObject(object);

    }
  }

  Entity::S3::Object S3Database::GetObjectById(bsoncxx::oid oid) {

    try {
      bsoncxx::builder::stream::document filter{};
      filter << "_id" << oid << bsoncxx::builder::stream::finalize;

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _objectCollection.find_one(make_document(kvp("_id", oid)));

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

    if (HasDatabase()) {

      return GetObjectById(bsoncxx::oid(oid));

    } else {

      return _memoryDb.GetObjectById(oid);

    }
  }

  Entity::S3::Object S3Database::CreateOrUpdateObject(const Entity::S3::Object &object) {

    if (ObjectExists(object)) {
      return UpdateObject(object);
    } else {
      return CreateObject(object);
    }
  }

  Entity::S3::Object S3Database::UpdateObject(const Entity::S3::Object &object) {

    if (HasDatabase()) {

      try {

        auto update_one_result =
          _objectCollection.replace_one(make_document(kvp("region", object.region), kvp("bucket", object.bucket), kvp("key", object.key)), object.ToDocument());
        log_trace_stream(_logger) << "Object updated: " << object.ToString() << std::endl;
        return GetObject(object.region, object.bucket, object.key);

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Update object failed, error: " << e.what() << std::endl;
      }

      return {};

    } else {

      return _memoryDb.UpdateObject(object);
    }
  }

  Entity::S3::Object S3Database::GetObject(const std::string &region, const std::string &bucket, const std::string &key) {

    if (HasDatabase()) {

      try {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _objectCollection.find_one(make_document(kvp("region", region), kvp("bucket", bucket), kvp("key", key)));
        if (mResult.has_value()) {
          Entity::S3::Object result;
          result.FromDocument(mResult);

          log_trace_stream(_logger) << "Got object: " << result.ToString() << std::endl;
          return result;
        }

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get object failed, error: " << e.what() << std::endl;
      }
      return {};

    } else {

      return _memoryDb.GetObject(region, bucket, key);

    }
  }

  Entity::S3::Object S3Database::GetObjectMd5(const std::string &region, const std::string &bucket, const std::string &key, const std::string &md5sum) {

    try {
      mongocxx::stdx::optional<bsoncxx::document::value>
        mResult = _objectCollection.find_one(make_document(kvp("region", region), kvp("bucket", bucket), kvp("key", key), kvp("md5sum", md5sum)));
      if (mResult.has_value()) {
        Entity::S3::Object result;
        result.FromDocument(mResult);

        log_trace_stream(_logger) << "Got object MD5: " << result.ToString() << std::endl;
        return result;
      }

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Get object MD5 failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  Entity::S3::Object S3Database::GetObjectVersion(const std::string &region, const std::string &bucket, const std::string &key, const std::string &versionId) {

    try {
      auto mResult = _objectCollection.find_one(make_document(kvp("region", region), kvp("bucket", bucket), kvp("key", key), kvp("versionId", versionId)));
      if (mResult) {
        Entity::S3::Object result;
        result.FromDocument(mResult);

        log_trace_stream(_logger) << "Got object version: " << result.ToString() << std::endl;
        return result;
      }

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Get object version failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  long S3Database::ObjectCount(const std::string &region, const std::string &bucket) {

    if (HasDatabase()) {

      bsoncxx::builder::basic::document builder;
      if (!region.empty()) {
        builder.append(bsoncxx::builder::basic::kvp("region", region));
      }
      if (!bucket.empty()) {
        builder.append(bsoncxx::builder::basic::kvp("bucket", bucket));
      }
      bsoncxx::document::value filter = builder.extract();

      try {
        long count = _objectCollection.count_documents({filter});
        log_trace_stream(_logger) << "Object count: " << count << std::endl;
        return count;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Object count failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.ObjectCount(region, bucket);

    }
    return -1;
  }

  void S3Database::DeleteObject(const Entity::S3::Object &object) {

    if (HasDatabase()) {

      try {
        auto result = _objectCollection.delete_many(make_document(kvp("region", object.region), kvp("bucket", object.bucket), kvp("key", object.key)));
        log_debug_stream(_logger) << "Objects deleted, count: " << result->deleted_count() << std::endl;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Delete object failed, error: " << e.what() << std::endl;
      }

    } else {

      _memoryDb.DeleteObject(object);

    }
  }

  void S3Database::DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys) {

    if (HasDatabase()) {

      bsoncxx::builder::basic::array array{};
      for (const auto &key : keys) {
        array.append(key);
      }
      auto result = _objectCollection.delete_many(make_document(kvp("bucket", bucket), kvp("key", make_document(kvp("$in", array)))));
      log_debug_stream(_logger) << "Objects deleted, count: " << result->result().deleted_count() << std::endl;

    } else {

      _memoryDb.DeleteObjects(bucket, keys);

    }
  }

  void S3Database::DeleteAllObjects() {

    if (HasDatabase()) {

      auto result = _objectCollection.delete_many({});
      log_debug_stream(_logger) << "All objects deleted, count: " << result->deleted_count() << std::endl;

    } else {

      _memoryDb.DeleteAllObjects();

    }
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
          .lambdaArn=bucketNotification.lambdaArn
        };
        internBucket.notifications.emplace_back(notification);
      }

    } else {

      internBucket.notifications.emplace_back(bucketNotification);
    }

    log_debug_stream(_logger) << "Bucket notification added, notification: " << bucketNotification.ToString() << std::endl;

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

  void S3Database::DumpObjects(std::string &input) {

    if(!input.empty()) {
      input += ",";
    }
    input += "{\"s3-objects\":[";
    auto objectCursor = _objectCollection.find({});
    for (auto object : objectCursor) {

      input += bsoncxx::to_json(object) + ",";
    }
    if (!input.empty())
      input.pop_back();
    input += "]}";
  }

} // namespace AwsMock::Database
