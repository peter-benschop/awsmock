//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SECRETSMANAGER_MEMORYDB_H
#define AWSMOCK_REPOSITORY_SECRETSMANAGER_MEMORYDB_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/repository/Database.h>
#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Database {

  class SecretsManagerMemoryDb {

  public:

    /**
     * Constructor
     */
    SecretsManagerMemoryDb();

    /**
     * Singleton instance
     */
    static SecretsManagerMemoryDb &instance() {
      static Poco::SingletonHolder<SecretsManagerMemoryDb> sh;
      return *sh.get();
    }

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Lambda map
     */
    std::map<std::string, Entity::Lambda::Lambda> _lambdas{};

    /**
     * Lambda mutex
     */
    Poco::Mutex _lambdaMutex;
  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SECRETSMANAGER_MEMORYDB_H
