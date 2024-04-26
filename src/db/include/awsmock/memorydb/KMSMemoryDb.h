//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_KMS_MEMORYDB_H
#define AWSMOCK_REPOSITORY_KMS_MEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/kms/Key.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * KMS in-memory database.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class KMSMemoryDb {

      public:

        /**
         * Constructor
         */
        KMSMemoryDb() = default;

        /**
         * Singleton instance
         */
        static KMSMemoryDb &instance() {
            static Poco::SingletonHolder<KMSMemoryDb> sh;
            return *sh.get();
        }

        /**
         * Check existence of key
         *
         * @param region AWS region
         * @param name key name
         * @return true if key already exists
         * @throws DatabaseException
         */
        bool KeyExists(const std::string &region, const std::string &name);

        /**
         * Check existence of key
         *
         * @param keyName key ARN
         * @return true if key already exists
         * @throws DatabaseException
         */
        bool KeyExists(const std::string &keyName);

        /**
         * Returns a KMS key by primary key
         *
         * @param oid key primary key
         * @return key entity
         * @throws DatabaseException
         */
        Entity::KMS::Key GetKeyById(const std::string &oid);

        /**
         * Returns a KMS key by key ID
         *
         * @param keyId key ID
         * @return key entity
         * @throws DatabaseException
         */
        Entity::KMS::Key GetKeyByKeyId(const std::string &keyId);

        /**
         * Create a new key in the KMS key table
         *
         * @param key key entity
         * @return created KMS key entity
         * @throws DatabaseException
         */
        Entity::KMS::Key CreateKey(const Entity::KMS::Key &key);

      private:

        /**
         * KMS topic vector, when running without database
         */
        std::map<std::string, Entity::KMS::Key> _keys;

        /**
         * Key mutex
         */
        static Poco::Mutex _keyMutex;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_KMS_MEMORYDB_H
