//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_KMS_DATABASE_H
#define AWSMOCK_REPOSITORY_KMS_DATABASE_H

// C++ standard includes
#include <iostream>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/s3/Object.h>
#include <awsmock/memorydb/KMSMemoryDb.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::builder::stream::document;

    /**
     * KMS MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class KMSDatabase : public DatabaseBase {

      public:

        /**
         * Constructor
         */
        explicit KMSDatabase() : _memoryDb(KMSMemoryDb::instance()), _useDatabase(HasDatabase()), _databaseName(GetDatabaseName()), _keyCollectionName("kms_key") {}

        /**
         * Singleton instance
         */
        static KMSDatabase &instance() {
            static Poco::SingletonHolder<KMSDatabase> sh;
            return *sh.get();
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
         * Returns a KMS key by primary key
         *
         * @param oid key primary key
         * @return key entity
         * @throws DatabaseException
         */
        Entity::KMS::Key GetKeyById(bsoncxx::oid oid);

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
         */
        Entity::KMS::KeyList ListKeys(const std::string &region = {});

        /**
         * Returns the total number of keys
         *
         * @return total number of keys
         * @throws DatabaseException
         */
        long CountKeys();

        /**
         * Create a new topic in the KMS topic table
         *
         * @param topic topic entity
         * @return created KMS topic entity
         * @throws DatabaseException
         */
        Entity::KMS::Key CreateKey(const Entity::KMS::Key &topic);

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

      private:

        /**
         * Use MongoDB
         */
        bool _useDatabase;

        /**
         * Database name
         */
        std::string _databaseName;

        /**
         * Key collection name
         */
        std::string _keyCollectionName;

        /**
         * KMS in-memory database
         */
        KMSMemoryDb &_memoryDb;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_KMS_DATABASE_H
