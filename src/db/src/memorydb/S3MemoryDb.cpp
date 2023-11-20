//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/S3MemoryDb.h>

namespace AwsMock::Database {

  S3MemoryDb::S3MemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

  bool S3MemoryDb::BucketExists(const std::string &region, const std::string &name) {

    return find_if(_buckets.begin(), _buckets.end(), [region, name](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
      return bucket.second.region == region && bucket.second.name == name;
    }) != _buckets.end();
  }

  bool S3MemoryDb::BucketExists(const Entity::S3::Bucket &bucket) {

    return BucketExists(bucket.region, bucket.name);
  }

  Entity::S3::Bucket S3MemoryDb::GetBucketById(const std::string &oid) {

    auto it = find_if(_buckets.begin(), _buckets.end(), [oid](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
      return bucket.first == oid;
    });

    if (it != _buckets.end()) {
      it->second.oid = oid;
      return it->second;
    }
    return {};
  }

  Entity::S3::Bucket S3MemoryDb::GetBucketByRegionName(const std::string &region, const std::string &name) {

    Entity::S3::Bucket result;

    auto it = find_if(_buckets.begin(), _buckets.end(), [region, name](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
      return bucket.second.region == region && bucket.second.name == name;
    });

    if (it != _buckets.end()) {
      it->second.oid = it->first;
      return it->second;
    }
    return {};
  }

  Entity::S3::Bucket S3MemoryDb::CreateBucket(const Entity::S3::Bucket &bucket) {

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _buckets[oid] = bucket;
    log_trace_stream(_logger) << "Bucket created, oid: " << oid << std::endl;
    return GetBucketById(oid);

  }

  Entity::S3::BucketList S3MemoryDb::ListBuckets() {

    Entity::S3::BucketList bucketList;
    for (const auto &bucket : _buckets) {
      bucketList.emplace_back(bucket.second);
    }

    log_trace_stream(_logger) << "Got bucket list, size: " << bucketList.size() << std::endl;
    return bucketList;
  }

  bool S3MemoryDb::HasObjects(const Entity::S3::Bucket &bucket) {

    long count = 0;
    for (const auto &object : _objects) {
      if (object.second.region == bucket.region && object.second.bucket == bucket.name) {
        count++;
      }
    }
    return count > 0;
  }

  long S3MemoryDb::BucketCount() {

    return _buckets.size();

  }

  Entity::S3::ObjectList S3MemoryDb::ListBucket(const std::string &bucket, const std::string &prefix) {

    Entity::S3::ObjectList objectList;
    if (prefix.empty()) {
      for (const auto &object : _objects) {
        if (object.second.bucket == bucket) {
          objectList.emplace_back(object.second);
        }
      }
    } else {
      for (const auto &object : _objects) {
        if (object.second.bucket == bucket && Core::StringUtils::StartsWith(object.second.key, prefix)) {
          objectList.emplace_back(object.second);
        }
      }
    }

    log_trace_stream(_logger) << "Got object list, size: " << objectList.size() << std::endl;
    return objectList;
  }

  Entity::S3::Bucket S3MemoryDb::UpdateBucket(const Entity::S3::Bucket &bucket) {

    std::string region = bucket.region;
    std::string name = bucket.name;
    auto it = find_if(_buckets.begin(), _buckets.end(), [region, name](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
      return bucket.second.region == region && bucket.second.name == name;
    });
    _buckets[it->first] = bucket;
    return _buckets[it->first];
  }

  void S3MemoryDb::DeleteBucket(const Entity::S3::Bucket &bucket) {

    std::string region = bucket.region;
    std::string name = bucket.name;
    const auto count = std::erase_if(_buckets, [region, name](const auto &item) {
      auto const &[key, value] = item;
      return value.region == region && value.name == name;
    });
    log_debug_stream(_logger) << "Bucket deleted, count: " << count << std::endl;
  }

  void S3MemoryDb::DeleteAllBuckets() {

    log_debug_stream(_logger) << "All buckets deleted, count: " << _buckets.size() << std::endl;
    _buckets.clear();
  }

  long S3MemoryDb::ObjectCount(const std::string &region, const std::string &bucket) {

    long count = 0;
    for (const auto &object : _objects) {
      if (!region.empty() && object.second.region == region && !bucket.empty() && object.second.bucket == bucket) {
        count++;
      } else if (!region.empty() && object.second.region == region) {
        count++;
      } else if (!bucket.empty() && object.second.bucket == bucket) {
        count++;
      }
    }
    return count;
  }

  Entity::S3::ObjectList S3MemoryDb::ListObjects(const std::string &prefix) {

    Entity::S3::ObjectList objectList;
    if (prefix.empty()) {
      for (const auto &object : _objects) {
        objectList.emplace_back(object.second);
      }
    } else {
      for (const auto &object : _objects) {
        if (!prefix.empty() && Core::StringUtils::StartsWith(object.second.key, prefix)) {
          objectList.emplace_back(object.second);
        }
      }
    }

    log_trace_stream(_logger) << "Got object list, size: " << objectList.size() << std::endl;
    return objectList;
  }

  void S3MemoryDb::DeleteObject(const Entity::S3::Object &object) {

    std::string bucket = object.bucket;
    std::string key = object.key;
    const auto count = std::erase_if(_objects, [bucket, key](const auto &item) {
      auto const &[k, v] = item;
      return v.bucket == bucket && v.key == key;
    });
    log_debug_stream(_logger) << "Object deleted, count: " << count << std::endl;
  }

  void S3MemoryDb::DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys) {

    auto count = 0;
    for (const auto &key : keys) {
      count += std::erase_if(_objects, [bucket, key](const auto &item) {
        auto const &[k, v] = item;
        return v.bucket == bucket && v.key == key;
      });
    }
    log_debug_stream(_logger) << "Objects deleted, count: " << count << std::endl;
  }

  void S3MemoryDb::DeleteAllObjects() {
    _objects.clear();
  }
}