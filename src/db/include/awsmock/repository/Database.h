//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_DATABASE_H
#define AWSMOCK_REPOSITORY_DATABASE_H

// C++ standard includes
#include <string>

// MongoDB includes
#include <mongocxx/client.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/exception/query_exception.hpp>

// Poco includes
#include <Poco/Util/AbstractConfiguration.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>

namespace AwsMock::Database {

  /**
   * MongoDB database base class.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit Database();

      /**
       * Singleton instance
       */
      /*static Database &instance() {
        static Poco::SingletonHolder<Database> sh;
        return *sh.get();
      }*/

      /**
       * Returns a MongoDB connection from the pool
       *
       * @return MongoDB database client
       */
      mongocxx::database GetConnection();

      /**
       * Returns a MongoDB client from the pool
       *
       * @return MongoDB database client
       */
      mongocxx::pool::entry GetClient();

      /**
       * Check all indexes.
       *
       * <p>Normally done during manager StartServer.</p>
       */
      void CreateIndexes();

      /**
       * Check whether we are running without database
       */
      bool HasDatabase() const;

      /**
       * Returns the database name
       *
       * @return database name
       */
      std::string GetDatabaseName() const;

      /**
       * Start the database
       */
      void StartDatabase();

      /**
       * Stops the database
       */
      void StopDatabase();

    private:

      /**
       * Update module status
       */
      void UpdateModuleStatus();

      /**
       * Application configuration
       */
      Core::Configuration &_configuration;

      /**
       * Database name
       */
      std::string _name;

      /**
       * Database host
       */
      std::string _host;

      /**
       * Database port
       */
      int _port;

      /**
       * Database user
       */
      std::string _user;

      /**
       * Database password
       */
      std::string _password;

      /**
       * MongoDB URI
       */
      mongocxx::uri _uri;

      /**
       * Database client
       */
      std::shared_ptr<mongocxx::pool> _pool;

      /**
       * Database connection pool size
       */
      int _poolSize;

      /**
       * Database flag
       */
      bool _useDatabase;

      /**
       * Initialization flag
       */
      bool _initialized;
  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_DATABASE_H
