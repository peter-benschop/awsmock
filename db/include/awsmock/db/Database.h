//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_DATABASE_H
#define AWSMOCK_DB_DATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include "Poco/Data/Session.h"
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/SessionFactory.h>
#include "Poco/Data/SQLite/Connector.h"

// MongoDB includes
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>

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
       * Returns a session
       *
       * @return returns a database session
       */
      //Poco::Data::Session GetSession();

    protected:

      /**
       * MongoDB database
       */
      mongocxx::database _database{};

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
       * Initialize the database
       */
      void Initialize();

      /**
       * Logger
       */
      Poco::LogStream _logger;

      /**
       * Application configuration
       */
      const Core::Configuration &_configuration;

      /**
       * MongoDB client
       */
      mongocxx::client _client{};

    };

} // namespace AwsMock::Database

#endif //AWSMOCK_DB_DATABASE_H
