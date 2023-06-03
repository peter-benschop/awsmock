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
#include "Poco/AutoPtr.h"
#include "Poco/Logger.h"
#include "Poco/Data/Session.h"
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/SessionFactory.h>
#include "Poco/Data/SQLite/Connector.h"

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
       * Destructor
       */
      ~Database();

      /**
       * Returns a session
       *
       * @return returns a database session
       */
      Poco::Data::Session GetSession();

    private:

      /**
       * Initialize the database
       */
      void Initialize();

      /**
       * Create database tables
       *
       * @param dataDir database directory
       * @param dbFile database file
       */
      void CreateDatabase(const std::string &dataDir, const std::string &dbFile);

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Logger
       */
      const Core::Configuration &_configuration;

      /**
       * SQLite database file
       */
      std::string _dbFile;

      /**
       * Session pool
       */
      Poco::AutoPtr<Poco::Data::SessionPool> _sessionPool;

    };

} // namespace AwsMock::Database

#endif //AWSMOCK_DB_DATABASE_H
