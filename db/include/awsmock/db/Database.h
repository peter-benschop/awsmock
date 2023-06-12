//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_DATABASE_H
#define AWSMOCK_DB_DATABASE_H

// C++ standard includes
#include <string>

// Poco includes
#include "Poco/Logger.h"
#include "Poco/LogStream.h"

// MongoDB includes
#include <mongocxx/client.hpp>
#include <mongocxx/pool.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/exception/exception.hpp>

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/Configuration.h>

namespace AwsMock::Database {

    class Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit Database(const Core::Configuration &configuration);

      /**
       * Returns a MongoDB connection from the pool
       *
       * @return MongoDB database client
       */
      mongocxx::database GetConnection();

      /**
       * Returns a MongoDB collection connection, without pool
       *
       * @return MongoDB database collection client
       */
      mongocxx::database GetCollection();

    protected:

      /**
       * Create a collection.
       *
       * <p>The collection is only created, in case the collection does not exist already.</p>
       *
       * @param name collection name
       */
      void CreateCollection(const std::string &name);

      /**
       * Create a collection.
       *
       * <p>The collection is only dropped, in case the collection exists.</p>
       *
       * @param name collection name
       */
      void DropCollection(const std::string &name);

    private:

      /**
       * Logger
       */
      Poco::LogStream _logger;

      /**
       * Application configuration
       */
      const Core::Configuration &_configuration;

      mongocxx::uri uri;

      /**
       * MongoDB connection pool
       */
      std::shared_ptr<mongocxx::pool> _connectionPool;

    };

} // namespace AwsMock::Database

#endif //AWSMOCK_DB_DATABASE_H
