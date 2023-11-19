//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_LAMBDAMEMORYDB_H
#define AWSMOCK_REPOSITORY_LAMBDAMEMORYDB_H

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
#include <awsmock/repository/Database.h>
#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Database {

  class LambdaMemoryDb {

  public:

    /**
     * Constructor
     */
    LambdaMemoryDb();

    /**
     * Singleton instance
     */
    static LambdaMemoryDb &instance() {
      static Poco::SingletonHolder<LambdaMemoryDb> sh;
      return *sh.get();
    }

    /**
     * Count all lambdas
     *
     * @param region aws-mock region.
     * @return total number of lambdas.
     */
    long LambdaCount(const std::string &region = {});

    /**
     * Returns a list of lambda functions.
     *
     * @param region AWS region name
     * @return list of lambda functions
     */
    std::vector<Entity::Lambda::Lambda> ListLambdas(const std::string &region);

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Lambda map
     */
    std::map<std::string, Entity::Lambda::Lambda> _lambdas{};

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_LAMBDAMEMORYDB_H
