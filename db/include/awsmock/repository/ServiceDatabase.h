//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SERVICEDATABASE_H
#define AWSMOCK_REPOSITORY_SERVICEDATABASE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/Logger.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/repository/Database.h>

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
      Core::LogStream _logger;

      /**
       * Service collection
       */
      mongocxx::collection _serviceCollection{};

    };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SERVICEDATABASE_H
