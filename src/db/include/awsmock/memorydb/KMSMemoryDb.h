//
// Created by vogje01 on 11/19/23.
//

#ifndef AWSMOCK_REPOSITORY_KMS_MEMORYDB_H
#define AWSMOCK_REPOSITORY_KMS_MEMORYDB_H

// C++ includes
#include <string>

// Poco includes
#include <Poco/Mutex.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/entity/kms/Key.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * KMS in-memory database.
     *
     * @author jens.vogt\@opitz-consulting.com
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
            static KMSMemoryDb kmsMemoryDb;
            return kmsMemoryDb;
        }

        /**
         * Check existence of key by keyId
         *
         * @param keyId key ID
         * @return true if key already exists
         * @throws DatabaseException
         */
        bool KeyExists(const std::string &keyId);

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
         * List all keys
         *
         * @param region AWS region
         * @return KeyList
         * @see Database::Entity::KMS::Key
         */
        Entity::KMS::KeyList ListKeys(const std::string &region = {});

        /**
         * Returns the total number of keys
         *
         * @return total number of keys
         * @throws DatabaseException
         */
        long CountKeys() const;

        /**
         * Create a new key in the KMS key table
         *
         * @param key key entity
         * @return created KMS key entity
         * @throws DatabaseException
         */
        Entity::KMS::Key CreateKey(const Entity::KMS::Key &key);

        /**
         * Updates a key
         *
         * @param key key entity
         * @return created key entity
         * @throws DatabaseException
         */
        Entity::KMS::Key UpdateKey(const Entity::KMS::Key &key);

        /**
         * Delete a key
         *
         * @param key key entity
         * @throws DatabaseException
         */
        void DeleteKey(const Entity::KMS::Key &key);

        /**
         * Delete a all keys
         *
         * @throws DatabaseException
         */
        void DeleteAllKeys();

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
