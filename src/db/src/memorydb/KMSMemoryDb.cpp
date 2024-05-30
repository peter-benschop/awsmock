//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/KMSMemoryDb.h>

namespace AwsMock::Database {

    Poco::Mutex KMSMemoryDb::_keyMutex;

    bool KMSMemoryDb::KeyExists(const std::string &keyId) {

        return find_if(_keys.begin(), _keys.end(), [keyId](const std::pair<std::string, Entity::KMS::Key> &topic) {
                   return topic.second.keyId == keyId;
               }) != _keys.end();
    }

    Entity::KMS::Key KMSMemoryDb::GetKeyById(const std::string &oid) {

        auto it = find_if(_keys.begin(), _keys.end(), [oid](const std::pair<std::string, Entity::KMS::Key> &topic) {
            return topic.first == oid;
        });

        if (it != _keys.end()) {
            it->second.oid = oid;
            return it->second;
        }

        log_warning << "Key not found, oid: " << oid;
        return {};
    }

    Entity::KMS::Key KMSMemoryDb::GetKeyByKeyId(const std::string &keyId) {

        auto it = find_if(_keys.begin(), _keys.end(), [keyId](const std::pair<std::string, Entity::KMS::Key> &topic) {
            return topic.second.keyId == keyId;
        });

        if (it != _keys.end()) {
            it->second.oid = it->first;
            return it->second;
        }

        log_warning << "Key not found, keyId: " << keyId;
        return {};
    }

    Entity::KMS::KeyList KMSMemoryDb::ListKeys(const std::string &region) {

        Entity::KMS::KeyList keyList;

        if (region.empty()) {

            for (const auto &key: _keys) {
                keyList.emplace_back(key.second);
            }

        } else {

            for (const auto &key: _keys) {
                if (key.second.region == region) {
                    keyList.emplace_back(key.second);
                }
            }
        }

        log_trace << "Got key list, size: " << keyList.size();
        return keyList;
    }

    long KMSMemoryDb::CountKeys() {

        return (long) _keys.size();
    }

    Entity::KMS::Key KMSMemoryDb::CreateKey(const Entity::KMS::Key &topic) {
        Poco::ScopedLock loc(_keyMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _keys[oid] = topic;
        log_trace << "Key created, oid: " << oid;
        return GetKeyById(oid);
    }

    Entity::KMS::Key KMSMemoryDb::UpdateKey(const Entity::KMS::Key &key) {
        Poco::ScopedLock lock(_keyMutex);

        std::string keyId = key.keyId;
        auto it = find_if(_keys.begin(),
                          _keys.end(),
                          [keyId](const std::pair<std::string, Entity::KMS::Key> &key) {
                              return key.second.keyId == keyId;
                          });
        if (it != _keys.end()) {
            _keys[it->first] = key;
            return _keys[it->first];
        }
        log_warning << "Key not found, keyId: " << keyId;
        return key;
    }

    void KMSMemoryDb::DeleteKey(const Entity::KMS::Key &key) {
        Poco::ScopedLock lock(_keyMutex);

        std::string keyId = key.keyId;
        const auto count = std::erase_if(_keys, [keyId](const auto &item) {
            auto const &[k, v] = item;
            return v.keyId == keyId;
        });
        log_debug << "Key deleted, count: " << count;
    }

    void KMSMemoryDb::DeleteAllKeys() {
        Poco::ScopedLock lock(_keyMutex);
        _keys.clear();
        log_debug << "All KMS keys deleted";
    }

}// namespace AwsMock::Database