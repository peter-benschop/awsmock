//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/KMSMemoryDb.h>

namespace AwsMock::Database {

    Poco::Mutex KMSMemoryDb::_keyMutex;

    bool KMSMemoryDb::KeyExists(const std::string &region, const std::string &name) {

        return find_if(_keys.begin(),
                       _keys.end(),
                       [region, name](const std::pair<std::string, Entity::KMS::Key> &key) {
                           return key.second.region == region && key.second.description == name;
                       }) != _keys.end();
    }

    bool KMSMemoryDb::KeyExists(const std::string &arn) {

        return find_if(_keys.begin(), _keys.end(), [arn](const std::pair<std::string, Entity::KMS::Key> &topic) {
                   return topic.second.arn == arn;
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

    Entity::KMS::Key KMSMemoryDb::CreateKey(const Entity::KMS::Key &topic) {
        Poco::ScopedLock loc(_keyMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _keys[oid] = topic;
        log_trace << "Key created, oid: " << oid;
        return GetKeyById(oid);
    }

}// namespace AwsMock::Database