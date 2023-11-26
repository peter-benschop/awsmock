//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_COGNITOMEMORYDB_H
#define AWSMOCK_REPOSITORY_COGNITOMEMORYDB_H

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
#include <awsmock/repository/Database.h>
#include <awsmock/entity/cognito/UserPool.h>

namespace AwsMock::Database {

  class CognitoMemoryDb {

  public:

    /**
     * Constructor
     */
    CognitoMemoryDb();

    /**
     * Singleton instance
     */
    static CognitoMemoryDb &instance() {
      static Poco::SingletonHolder<CognitoMemoryDb> sh;
      return *sh.get();
    }

    /**
     * Check existence of cognito user pool
     *
     * @param region AWS region name
     * @param name cognito user pool name
     * @return true if cognito already exists
     * @throws DatabaseException
     */
    bool UserPoolExists(const std::string &region, const std::string &name);

    /**
     * Check existence of cognito user pool
     *
     * @param id user pool id
     * @return true if cognito user pool exists
     * @throws DatabaseException
     */
    bool UserPoolExists(const std::string &id);

    /**
     * Create a new cognito user pool
     *
     * @param userPool cognito user pool entity to create
     * @return created cognito user pool entity.
     */
    Entity::Cognito::UserPool CreateUserPool(const Entity::Cognito::UserPool &userPool);

    /**
     * Returns a cognito user pool entity by primary key
     *
     * @param oid cognito user pool primary key
     * @return cognito user pool entity
     * @throws DatabaseException
     */
    Entity::Cognito::UserPool GetUserPoolByOid(const std::string &oid);

    /**
      * Returns a cognito entity by ARN
      *
      * @param arn cognito ARN
      * @return cognito entity
      * @throws DatabaseException
      */
    //Entity::Cognito::Cognito GetCognitoByArn(const std::string &arn);

    /**
     * Count all user pools
     *
     * @param region aws-mock region.
     * @return total number of user pools.
     */
    //long CognitoCount(const std::string &region = {});

    /**
     * Returns a list of cognito user pools.
     *
     * @param region AWS region name
     * @return list of cognito user pools
     */
    std::vector<Entity::Cognito::UserPool> ListUserPools(const std::string &region);

    /**
     * Updates an existing cognito cognito function
     *
     * @param cognito cognito entity
     * @return updated cognito entity.
     */
    //Entity::Cognito::Cognito UpdateCognito(const Entity::Cognito::Cognito &cognito);

    /**
     * Deletes an existing cognito user pool
     *
     * @param id cognito user pool ID
     * @throws DatabaseException
     */
    void DeleteUserPool(const std::string &id);

    /**
     * Deletes all existing cognito user pools
     *
     * @throws DatabaseException
     */
     void DeleteAllUserPools();

  private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Cognito user pool map
     */
    std::map<std::string, Entity::Cognito::UserPool> _userPools{};

    /**
     * Cognito user pool mutex
     */
    Poco::Mutex _userPoolMutex;
  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_COGNITOMEMORYDB_H
