//
// Created by vogje01 on 29/11/2023.
//

#ifndef AWSMOCK_REPOSITORY_COGNITODATABASE_H
#define AWSMOCK_REPOSITORY_COGNITODATABASE_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/memorydb/CognitoMemoryDb.h>
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

  class CognitoDatabase : public Database {

  public:

    /**
     * Constructor
     *
     * @param configuration configuration properties
     */
    explicit CognitoDatabase(Core::Configuration &configuration);

    /**
     * Check existence of cognito user pool
     *
     * @param region AWS region name
     * @param name AWS function
     * @return true if cognito user pool exists
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
     * Create a new cognito function
     *
     * @param userPool cognito user pool entity to create
     * @return created cognito entity.
     */
    Entity::Cognito::UserPool CreateUserPool(const Entity::Cognito::UserPool &userPool);

    /**
     * Count all user pools
     *
     * @param region aws-mock region.
     * @return total number of user pools.
     */
    long CognitoCount(const std::string &region = {});

    /**
     * Updates an existing cognito user pool
     *
     * @param userPool user pool entity
     * @return updated cognito user pool entity.
     */
    Entity::Cognito::UserPool UpdateUserPool(const Entity::Cognito::UserPool &userPool);

    /**
     * Created or updates an existing cognito function
     *
     * @param cognito cognito entity
     * @return created or updated cognito entity.
     */
    //Entity::Cognito::Cognito CreateOrUpdateCognito(const Entity::Cognito::Cognito &cognito);

    /**
     * Returns a cognito user pool entity by primary key
     *
     * @param oid cognito user pool primary key
     * @return cognito entity
     * @throws DatabaseException
     */
    Entity::Cognito::UserPool GetUserPoolById(bsoncxx::oid oid);

    /**
     * Returns a cognito user pool entity by region and name
     *
     * @param region AWS region
     * @param name cognito user pool name
     * @return cognito entity
     * @throws DatabaseException
     */
    Entity::Cognito::UserPool GetUserPoolByRegionName(const std::string &region, const std::string &name);

    /**
     * Returns a list of cognito user pools.
     *
     * @param region AWS region name
     * @return list of cognito user pools
     */
    std::vector<Entity::Cognito::UserPool> ListUserPools(const std::string &region);

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
     * Cognito user pool collection
     */
    mongocxx::collection _userPoolCollection{};

    /**
     * S3 in-memory database
     */
    CognitoMemoryDb &_memoryDb;

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_COGNITODATABASE_H
