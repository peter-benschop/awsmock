//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SECRETSMANAGER_DATABASE_H
#define AWSMOCK_REPOSITORY_SECRETSMANAGER_DATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/memorydb/SecretsManagerMemoryDb.h>
#include <awsmock/repository/Database.h>
#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Database {

  class SecretsManagerDatabase : public Database {

  public:

    /**
     * Constructor
     *
     * @param configuration configuration properties
     */
    explicit SecretsManagerDatabase();

    /**
     * Singleton instance
     */
    static SecretsManagerDatabase &instance() {
      static Poco::SingletonHolder<SecretsManagerDatabase> sh;
      return *sh.get();
    }

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Use MongoDB
     */
    bool _useDatabase;

    /**
     * Database name
     */
    std::string _databaseName;

    /**
     * Lambda in-memory database
     */
    SecretsManagerMemoryDb &_memoryDb;

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SECRETSMANAGER_DATABASE_H
