//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_DYNAMODB_DATABASE_H
#define AWSMOCK_REPOSITORY_DYNAMODB_DATABASE_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/memorydb/DynamoDbMemoryDb.h>
#include <awsmock/repository/Database.h>
#include <awsmock/entity/dynamodb/DynamoDb.h>

namespace AwsMock::Database {

  class DynamoDbDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit DynamoDbDatabase(Core::Configuration &configuration);

      /**
       * Checks the existence of a DynamoDb instance.
       *
       * @param region AWS region.
       * @param name name of the database instance.
       * @return true if database exists, otherwise false
       */
      bool DatabaseExists(const std::string &region, const std::string &name);

      /**
       * Returns the database entity by name.
       *
       * @param region AWS region.
       * @param name name of the database instance.
       */
      Entity::DynamoDb::DynamoDb GetDatabaseByName(const std::string &region, const std::string &name);

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * DynamoDb collection
       */
      mongocxx::collection _dynamodbCollection{};

      /**
       * DynamoDB in-memory database
       */
      DynamoDbMemoryDb &_memoryDb;

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_DYNAMODB_DATABASE_H
