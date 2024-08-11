//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/S3MemoryDb.h>

namespace AwsMock::Database {

    Poco::Mutex S3MemoryDb::_bucketMutex;
    Poco::Mutex S3MemoryDb::_objectMutex;

    bool S3MemoryDb::BucketExists(const std::string &region, const std::string &name) {

        return find_if(_buckets.begin(),
                       _buckets.end(),
                       [region, name](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
                           return bucket.second.region == region && bucket.second.name == name;
                       }) != _buckets.end();
    }

    bool S3MemoryDb::BucketExists(const Entity::S3::Bucket &bucket) {
        return BucketExists(bucket.region, bucket.name);
    }

    Entity::S3::Bucket S3MemoryDb::GetBucketById(const std::string &oid) {

        auto
                it = find_if(_buckets.begin(), _buckets.end(), [oid](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
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

        auto it = find_if(_buckets.begin(),
                          _buckets.end(),
                          [region, name](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
                              return bucket.second.region == region && bucket.second.name == name;
                          });

        if (it != _buckets.end()) {
            it->second.oid = it->first;
            return it->second;
        }
        return {};
    }

    Entity::S3::Bucket S3MemoryDb::CreateBucket(const Entity::S3::Bucket &bucket) {
        Poco::ScopedLock lock(_bucketMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _buckets[oid] = bucket;
        log_trace << "Bucket created, oid: " << oid;
        return GetBucketById(oid);
    }

    Entity::S3::BucketList S3MemoryDb::ListBuckets() {

        Entity::S3::BucketList bucketList;
        for (const auto &bucket: _buckets) {
            bucketList.emplace_back(bucket.second);
        }

        log_trace << "Got bucket list, size: " << bucketList.size();
        return bucketList;
    }

    bool S3MemoryDb::HasObjects(const Entity::S3::Bucket &bucket) {

        long count = 0;
        for (const auto &object: _objects) {
            if (object.second.region == bucket.region && object.second.bucket == bucket.name) {
                count++;
            }
        }
        return count > 0;
    }

    std::vector<Entity::S3::Object> S3MemoryDb::GetBucketObjectList(const std::string &region, const std::string &bucket, long maxKeys) {

        std::vector<Entity::S3::Object> objectList;
        for (const auto &object: _objects) {
            if (object.second.region == region && object.second.bucket == bucket && objectList.size() < maxKeys) {
                objectList.emplace_back(object.second);
            } else {
                break;
            }
        }
        return objectList;
    }

    long S3MemoryDb::BucketCount() {

        return static_cast<long>(_buckets.size());
    }

    Entity::S3::ObjectList S3MemoryDb::ListBucket(const std::string &bucket, const std::string &prefix) {

        Entity::S3::ObjectList objectList;

        if (prefix.empty()) {

            for (const auto &object: _objects) {
                if (object.second.bucket == bucket) {
                    objectList.emplace_back(object.second);
                }
            }

        } else {

            for (const auto &object: _objects) {
                if (object.second.bucket == bucket && Core::StringUtils::StartsWith(object.second.key, prefix)) {
                    objectList.emplace_back(object.second);
                }
            }
        }

        log_trace << "Got object list, size: " << objectList.size();
        return objectList;
    }

    Entity::S3::Bucket S3MemoryDb::UpdateBucket(const Entity::S3::Bucket &bucket) {

        Poco::ScopedLock lock(_bucketMutex);

        std::string region = bucket.region;
        std::string name = bucket.name;
        auto it = find_if(_buckets.begin(),
                          _buckets.end(),
                          [region, name](const std::pair<std::string, Entity::S3::Bucket> &bucket) {
                              return bucket.second.region == region && bucket.second.name == name;
                          });
        _buckets[it->first] = bucket;
        return _buckets[it->first];
    }

    void S3MemoryDb::DeleteBucket(const Entity::S3::Bucket &bucket) {
        Poco::ScopedLock lock(_bucketMutex);

        std::string region = bucket.region;
        std::string name = bucket.name;
        const auto count = std::erase_if(_buckets, [region, name](const auto &item) {
            auto const &[key, value] = item;
            return value.region == region && value.name == name;
        });
        log_debug << "Bucket deleted, count: " << count;
    }

    void S3MemoryDb::DeleteAllBuckets() {
        Poco::ScopedLock lock(_bucketMutex);

        log_debug << "All buckets deleted, count: " << _buckets.size();
        _buckets.clear();
    }

    bool S3MemoryDb::ObjectExists(const Entity::S3::Object &object) {

        std::string region = object.region;
        std::string bucket = object.bucket;
        std::string key = object.key;
        return find_if(_objects.begin(),
                       _objects.end(),
                       [region, bucket, key](const std::pair<std::string, Entity::S3::Object> &object) {
                           return object.second.region == region && object.second.bucket == bucket && object.second.key == key;
                       }) != _objects.end();
    }

    bool S3MemoryDb::ObjectExists(const std::string &filename) {

        return find_if(_objects.begin(),
                       _objects.end(),
                       [filename](const std::pair<std::string, Entity::S3::Object> &object) {
                           return object.second.internalName == filename;
                       }) != _objects.end();
    }

    Entity::S3::Object S3MemoryDb::CreateObject(const Entity::S3::Object &object) {
        Poco::ScopedLock lock(_objectMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _objects[oid] = object;
        log_trace << "Object created, oid: " << oid;
        return GetObjectById(oid);
    }

    Entity::S3::Object S3MemoryDb::UpdateObject(const Entity::S3::Object &object) {
        Poco::ScopedLock lock(_objectMutex);

        std::string bucket = object.bucket;
        std::string key = object.key;
        auto it = find_if(_objects.begin(),
                          _objects.end(),
                          [bucket, key](const std::pair<std::string, Entity::S3::Object> &object) {
                              return object.second.bucket == bucket && object.second.key == key;
                          });
        _objects[it->first] = object;
        return _objects[it->first];
    }

    Entity::S3::Object S3MemoryDb::GetObjectById(const std::string &oid) {

        auto
                it = find_if(_objects.begin(), _objects.end(), [oid](const std::pair<std::string, Entity::S3::Object> &object) {
                    return object.first == oid;
                });

        if (it != _objects.end()) {
            it->second.oid = oid;
            return it->second;
        }
        return {};
    }

    Entity::S3::Object S3MemoryDb::GetObject(const std::string &region, const std::string &bucket, const std::string &key) {

        auto it = find_if(_objects.begin(),
                          _objects.end(),
                          [region, bucket, key](const std::pair<std::string, Entity::S3::Object> &object) {
                              return object.second.region == region && object.second.bucket == bucket && object.second.key == key;
                          });

        if (it != _objects.end()) {
            it->second.oid = it->first;
            return it->second;
        }
        return {};
    }

    Entity::S3::Object S3MemoryDb::GetObjectMd5(const std::string &region, const std::string &bucket, const std::string &key, const std::string &md5sum) {

        auto it = find_if(_objects.begin(),
                          _objects.end(),
                          [region, bucket, key, md5sum](const std::pair<std::string, Entity::S3::Object> &object) {
                              return object.second.region == region && object.second.bucket == bucket && object.second.key == key && object.second.md5sum == md5sum;
                          });

        if (it != _objects.end()) {
            it->second.oid = it->first;
            return it->second;
        }
        return {};
    }

    long S3MemoryDb::ObjectCount(const std::string &region, const std::string &bucket) {

        if (region.empty() && bucket.empty()) {
            return static_cast<long>(_objects.size());
        }

        long count = 0;
        if (!region.empty() && bucket.empty()) {
            for (const auto &object: _objects) {
                if (object.second.region == region) {
                    count++;
                }
            }
        } else if (region.empty() && !bucket.empty()) {
            for (const auto &object: _objects) {
                if (object.second.bucket == bucket) {
                    count++;
                }
            }
        } else if (!region.empty() && !bucket.empty()) {
            for (const auto &object: _objects) {
                if (object.second.bucket == bucket && object.second.region == region) {
                    count++;
                }
            }
        }
        return count;
    }

    Entity::S3::ObjectList S3MemoryDb::ListObjects(const std::string &prefix) {

        Entity::S3::ObjectList objectList;
        if (prefix.empty()) {
            for (const auto &object: _objects) {
                objectList.emplace_back(object.second);
            }
        } else {
            for (const auto &object: _objects) {
                if (!prefix.empty() && Core::StringUtils::StartsWith(object.second.key, prefix)) {
                    objectList.emplace_back(object.second);
                }
            }
        }

        log_trace << "Got object list, size: " << objectList.size();
        return objectList;
    }

    Entity::S3::ObjectList S3MemoryDb::ListObjectVersions(const std::string &region, const std::string &bucket, const std::string &prefix) {

        Entity::S3::ObjectList objectList;
        if (prefix.empty()) {
            for (const auto &object: _objects) {
                if (object.second.region == region && object.second.bucket == bucket) {
                    objectList.emplace_back(object.second);
                }
            }
        } else {
            for (const auto &object: _objects) {
                if (object.second.region == region && object.second.bucket == bucket) {
                    if (!prefix.empty() && Core::StringUtils::StartsWith(object.second.key, prefix)) {
                        objectList.emplace_back(object.second);
                    }
                }
            }
        }

        log_trace << "Got versioned object list, size: " << objectList.size();
        return objectList;
    }

    void S3MemoryDb::DeleteObject(const Entity::S3::Object &object) {
        Poco::ScopedLock lock(_objectMutex);

        std::string bucket = object.bucket;
        std::string key = object.key;
        const auto count = std::erase_if(_objects, [bucket, key](const auto &item) {
            auto const &[k, v] = item;
            return v.bucket == bucket && v.key == key;
        });
        log_debug << "Object deleted, count: " << count;
    }

    void S3MemoryDb::DeleteObjects(const std::string &bucket, const std::vector<std::string> &keys) {
        Poco::ScopedLock lock(_objectMutex);

        auto count = 0;
        for (const auto &key: keys) {
            count += std::erase_if(_objects, [bucket, key](const auto &item) {
                auto const &[k, v] = item;
                return v.bucket == bucket && v.key == key;
            });
        }
        log_debug << "Objects deleted, count: " << count;
    }

    void S3MemoryDb::DeleteAllObjects() {
        Poco::ScopedLock lock(_objectMutex);

        _objects.clear();
    }
}// namespace AwsMock::Database