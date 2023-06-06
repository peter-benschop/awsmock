//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_DB_SERVICEDATABASE_H
#define AWSMOCK_DB_SERVICEDATABASE_H

// C++ standard includes
#include <string>


// Poco includes
#include "Poco/Logger.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/db/Database.h>

namespace AwsMock::Database {

    class ServiceDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit ServiceDatabase(const Core::Configuration &configuration);

      /**
       * Checks the active flag.
       *
       * @param name service name
       * @return true if active
       */
      bool IsActive(const std::string &name);

    private:

      /**
       * Logger
       */
      Poco::Logger &_logger;

    };

} // namespace AwsMock::Database

#endif //AWSMOCK_DB_SERVICEDATABASE_H
