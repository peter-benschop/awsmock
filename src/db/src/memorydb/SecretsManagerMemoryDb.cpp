//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/SecretsManagerMemoryDb.h>

namespace AwsMock::Database {

    bool SecretsManagerMemoryDb::SecretExists(const std::string &region, const std::string &name) {

        return find_if(_secrets.begin(),
                       _secrets.end(),
                       [region, name](const std::pair <std::string, Entity::SecretsManager::Secret> &secret) {
                           return secret.second.region == region && secret.second.name == name;
                       }) != _secrets.end();
    }

    bool SecretsManagerMemoryDb::SecretExists(const Entity::SecretsManager::Secret &secret) {
        return SecretExists(secret.region, secret.name);
    }

    bool SecretsManagerMemoryDb::SecretExists(const std::string &secretId) {

        return find_if(_secrets.begin(),
                       _secrets.end(),
                       [secretId](const std::pair <std::string, Entity::SecretsManager::Secret> &secret) {
                           return secret.second.secretId == secretId;
                       }) != _secrets.end();
    }

    Entity::SecretsManager::Secret SecretsManagerMemoryDb::GetSecretById(const std::string &oid) {

        auto it = find_if(_secrets.begin(),
                          _secrets.end(),
                          [oid](const std::pair <std::string, Entity::SecretsManager::Secret> &secret) {
                              return secret.first == oid;
                          });

        if (it != _secrets.end()) {
            it->second.oid = oid;
            return it->second;
        }
        return {};
    }

    Entity::SecretsManager::Secret SecretsManagerMemoryDb::GetSecretByRegionName(const std::string &region,
                                                                                 const std::string &name) {

        Entity::SecretsManager::Secret result;

        auto it = find_if(_secrets.begin(),
                          _secrets.end(),
                          [region, name](const std::pair <std::string, Entity::SecretsManager::Secret> &secret) {
                              return secret.second.region == region && secret.second.name == name;
                          });

        if (it != _secrets.end()) {
            it->second.oid = it->first;
            return it->second;
        }
        return {};
    }

    Entity::SecretsManager::Secret SecretsManagerMemoryDb::GetSecretBySecretId(const std::string &secretId) {

        Entity::SecretsManager::Secret result;

        auto it = find_if(_secrets.begin(),
                          _secrets.end(),
                          [secretId](const std::pair <std::string, Entity::SecretsManager::Secret> &secret) {
                              return secret.second.secretId == secretId;
                          });

        if (it != _secrets.end()) {
            it->second.oid = it->first;
            return it->second;
        }
        return {};
    }

    Entity::SecretsManager::Secret SecretsManagerMemoryDb::CreateSecret(const Entity::SecretsManager::Secret &secret) {
        Poco::ScopedLock lock(_secretMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _secrets[oid] = secret;
        log_trace << "Secret created, oid: " << oid;
        return GetSecretById(oid);

    }

    Entity::SecretsManager::Secret SecretsManagerMemoryDb::UpdateSecret(const Entity::SecretsManager::Secret &secret) {

        Poco::ScopedLock lock(_secretMutex);

        std::string secretId = secret.secretId;
        auto it = find_if(_secrets.begin(),
                          _secrets.end(),
                          [secretId](const std::pair <std::string, Entity::SecretsManager::Secret> &secret) {
                              return secret.second.secretId == secretId;
                          });
        _secrets[it->first] = secret;
        return _secrets[it->first];
    }

    Entity::SecretsManager::SecretList SecretsManagerMemoryDb::ListSecrets() {

        Entity::SecretsManager::SecretList secretList;

        for (const auto &secret: _secrets) {
            secretList.emplace_back(secret.second);
        }

        log_trace << "Got secret list, size: " << secretList.size();
        return secretList;
    }

    long SecretsManagerMemoryDb::CountSecrets(const std::string &region) {

        long count = 0;
        if (region.empty()) {

            return (long) _secrets.size();

        } else {

            for (const auto &secret: _secrets) {
                if (secret.second.region == region) {
                    count++;
                }
            }
        }
        return count;
    }

    void SecretsManagerMemoryDb::DeleteSecret(const Entity::SecretsManager::Secret &secret) {
        Poco::ScopedLock lock(_secretMutex);

        std::string region = secret.region;
        std::string name = secret.name;
        const auto count = std::erase_if(_secrets, [region, name](const auto &item) {
            auto const &[key, value] = item;
            return value.region == region && value.name == name;
        });
        log_debug << "Secret deleted, count: " << count;
    }

    void SecretsManagerMemoryDb::DeleteAllSecrets() {
        Poco::ScopedLock lock(_secretMutex);

        log_debug << "Secrets deleted, count: " << _secrets.size();
        _secrets.clear();
    }

}