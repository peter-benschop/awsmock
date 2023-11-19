//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/S3MemoryDb.h>

namespace AwsMock::Database {

  S3MemoryDb::S3MemoryDb() : _logger(Poco::Logger::get("SQSMemoryDb")) {}

  Entity::S3::BucketList S3MemoryDb::ListBuckets() {

    Entity::S3::BucketList bucketList;
    for (const auto &bucket : _buckets) {
      bucketList.emplace_back(bucket.second);
    }

    log_trace_stream(_logger) << "Got bucket list, size: " << bucketList.size() << std::endl;
    return bucketList;
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

  long S3MemoryDb::ObjectCount(const std::string &region, const std::string &bucket) {

    long count = 0;
    for (const auto &object : _objects) {
      if (!region.empty() && object.second.region == region && !bucket.empty() && object.second.bucket == bucket) {
        count++;
      } else if(!region.empty() && object.second.region == region) {
        count++;
      } else if(!bucket.empty() && object.second.bucket == bucket) {
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
}