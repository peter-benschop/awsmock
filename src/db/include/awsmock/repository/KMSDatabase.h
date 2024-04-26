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
#include <awsmock/memorydb/KMSMemoryDb.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    /**
     * KMS MongoDB database.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class KMSDatabase : public Database {

      public:

        /**
         * Constructor
         *
         * @param configuration configuration properties
         */
        explicit KMSDatabase();

        /**
         * Singleton instance
         */
        static KMSDatabase &instance() {
            static Poco::SingletonHolder<KMSDatabase> sh;
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
         * @param arn key ARN
         * @return true if key already exists
         * @throws DatabaseException
         */
        bool KeyExists(const std::string &arn);

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
         * Create a new topic in the KMS topic table
         *
         * @param topic topic entity
         * @return created KMS topic entity
         * @throws DatabaseException
         */
        Entity::KMS::Key CreateKey(const Entity::KMS::Key &topic);

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
