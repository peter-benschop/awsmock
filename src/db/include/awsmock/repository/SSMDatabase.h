//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SSM_DATABASE_H
#define AWSMOCK_REPOSITORY_SSM_DATABASE_H

// C++ standard includes
#include <iostream>
#include <string>
#include <vector>

// MongoDB includes
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>

// AwsMock includes
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/DatabaseException.h>
#include <awsmock/entity/ssm/Parameter.h>
#include <awsmock/memorydb/SSMMemoryDb.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::builder::stream::document;

    /**
     * @brief ssm MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class SSMDatabase : public DatabaseBase {

      public:

        /**
         * @brief Constructor
         */
        explicit SSMDatabase() : _memoryDb(SSMMemoryDb::instance()), _databaseName(GetDatabaseName()), _parameterCollectionName("ssm_parameter") {}

        /**
         * @brief Singleton instance
         */
        static SSMDatabase &instance() {
            static SSMDatabase ssmDatabase;
            return ssmDatabase;
        }

        /**
         * @brief Check existence of a parameter by name
         *
         * @param keyId key ID
         * @return true if key already exists
         * @throws DatabaseException
         */
        bool ParameterExists(const std::string &name);

        /**
         * @brief Returns a SMS parameter by primary key
         *
         * @param oid key primary key
         * @return key entity
         * @throws DatabaseException
         */
        Entity::SSM::Parameter GetParameterById(const std::string &oid);

        /**
         * @brief Returns a parameter by primary key
         *
         * @param oid key primary key
         * @return key entity
         * @throws DatabaseException
         */
        Entity::SSM::Parameter GetParameterById(bsoncxx::oid oid);

        /**
         * @brief Returns a parameter by name
         *
         * @param name parameter name
         * @return key entity
         * @throws DatabaseException
         */
        Entity::SSM::Parameter GetParameterByName(const std::string &name);

        /**
         * @brief List all parameters
         *
         * @param region AWS region
         * @return ParameterList
         */
        Entity::SSM::ParameterList ListParameters(const std::string &region = {});

        /**
         * @brief Returns the total number of parameters
         *
         * @return total number of parameters
         * @throws DatabaseException
         */
        long CountParameters();

        /**
         * @brief Create a new parameter in the ssm parameter table
         *
         * @param parameter parameter entity
         * @return created parameter entity
         * @throws DatabaseException
         */
        Entity::SSM::Parameter CreateParameter(Entity::SSM::Parameter &parameter);

        /**
         * @brief Updates a parameter
         *
         * @param parameter parameter entity
         * @return created parameter entity
         * @throws DatabaseException
         */
        Entity::SSM::Parameter UpdateParameter(Entity::SSM::Parameter &parameter);

        /**
         * @brief Deletes a parameter
         *
         * @param parameter parameter entity
         * @throws DatabaseException
         */
        void DeleteParameter(const Entity::SSM::Parameter &parameter);

        /**
         * @brief Delete a all parameters
         *
         * @throws DatabaseException
         */
        void DeleteAllParameters();

      private:

        /**
         * Database name
         */
        std::string _databaseName;

        /**
         * Parameter collection name
         */
        std::string _parameterCollectionName;

        /**
         * ssm in-memory database
         */
        SSMMemoryDb &_memoryDb;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_KMS_DATABASE_H
