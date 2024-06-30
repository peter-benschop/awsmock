//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_DATABASE_H
#define AWSMOCK_REPOSITORY_DATABASE_H

// C++ standard includes
#include <string>

// MongoDB includes
#include <mongocxx/client.hpp>
#include <mongocxx/database.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/exception/query_exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>

// Poco includes
#include <Poco/Util/AbstractConfiguration.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/utils/ConnectionPool.h>

namespace AwsMock::Database {

    /**
     * @brief MongoDB database base class.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DatabaseBase {

      public:

        /**
         * @brief Constructor
         */
        explicit DatabaseBase();

        /**
         * @brief Returns a MongoDB connection from the pool
         *
         * @return MongoDB database client
         */
        mongocxx::database GetConnection();

        /**
         * @brief Check all indexes.
         *
         * <p>Normally done during manager StartServer.</p>
         */
        void CreateIndexes() const;

        /**
         * @brief Check whether we are running without database
         */
        [[nodiscard]] bool HasDatabase() const;

        /**
         * @brief Returns the database name
         *
         * @return database name
         */
        [[nodiscard]] std::string GetDatabaseName() const;

        /**
         * @brief Start the database
         */
        void StartDatabase();

        /**
         * @brief Stops the database
         */
        void StopDatabase();

      private:

        /**
         * Database name
         */
        std::string _name;

        /**
         * Database client
         */
        std::unique_ptr<mongocxx::pool> _pool;

        /**
         * Database flag
         */
        bool _useDatabase;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_DATABASE_H
