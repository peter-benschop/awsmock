//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_LAMBDAMEMORYDB_H
#define AWSMOCK_REPOSITORY_LAMBDAMEMORYDB_H

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

  /**
   * Lambda in-memory database.
   *
   * @author jens.vogt@opitz-consulting.com
   */
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
     * Check existence of lambda
     *
     * @param region AWS region name
     * @param function AWS function
     * @param runtime lambda runtime
     * @return true if lambda already exists
     * @throws DatabaseException
     */
    bool LambdaExists(const std::string &region, const std::string &function, const std::string &runtime);

    /**
     * Check existence of lambda
     *
     * @param lambda AWS function
     * @return true if lambda already exists
     * @throws DatabaseException
     */
    bool LambdaExists(const Entity::Lambda::Lambda &lambda);

    /**
     * Check existence of lambda
     *
     * @param function AWS function
     * @return true if lambda already exists
     * @throws DatabaseException
     */
    bool LambdaExists(const std::string &function);

    /**
     * Check existence of lambda
     *
     * @param arn AWS ARN
     * @return true if lambda exists
     * @throws DatabaseException
     */
    bool LambdaExistsByArn(const std::string &arn);

    /**
     * Create a new lambda function
     *
     * @param lambda lambda entity
     * @return created lambda entity.
     */
    Entity::Lambda::Lambda CreateLambda(const Entity::Lambda::Lambda &lambda);

    /**
     * Returns a lambda entity by primary key
     *
     * @param oid lambda primary key
     * @return lambda entity
     * @throws DatabaseException
     */
    Entity::Lambda::Lambda GetLambdaById(const std::string &oid);

    /**
      * Returns a lambda entity by ARN
      *
      * @param arn lambda ARN
      * @return lambda entity
      * @throws DatabaseException
      */
    Entity::Lambda::Lambda GetLambdaByArn(const std::string &arn);

    /**
     * Returns a lambda entity by name
     *
     * @param region AWS region
     * @param name function name
     * @return lambda entity
     * @throws DatabaseException
     */
    Entity::Lambda::Lambda GetLambdaByName(const std::string &region, const std::string &name);

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

    /**
     * Updates an existing lambda lambda function
     *
     * @param lambda lambda entity
     * @return updated lambda entity.
     */
    Entity::Lambda::Lambda UpdateLambda(const Entity::Lambda::Lambda &lambda);

    /**
     * Deletes an existing lambda function
     *
     * @param functionName lambda function name
     * @throws DatabaseException
     */
    void DeleteLambda(const std::string &functionName);

    /**
     * Deletes all existing lambda functions
     *
     * @throws DatabaseException
     */
    void DeleteAllLambdas();

  private:

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

#endif // AWSMOCK_REPOSITORY_LAMBDAMEMORYDB_H
