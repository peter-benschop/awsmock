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
     */
    explicit CognitoDatabase();

    /**
     * Singleton instance
     */
    static CognitoDatabase &instance() {
      static Poco::SingletonHolder<CognitoDatabase> sh;
      return *sh.get();
    }

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
     * Create a new cognito user pool
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
    long CountUserPools(const std::string &region = {});

    /**
     * Updates an existing cognito user pool
     *
     * @param userPool user pool entity
     * @return updated cognito user pool entity.
     */
    Entity::Cognito::UserPool UpdateUserPool(const Entity::Cognito::UserPool &userPool);

    /**
     * Creates a new user pool or updates an existing user pool
     *
     * @param userPool user pool entity
     * @return created or updated Cognito user pool entity
     * @throws DatabaseException
     */
    Entity::Cognito::UserPool CreateOrUpdateUserPool(Entity::Cognito::UserPool &userPool);

    /**
     * Created or updates an existing cognito user pool
     *
     * @param cognito cognito entity
     * @return created or updated cognito entity.
     */
    //Entity::Cognito::Cognito CreateOrUpdateCognito(const Entity::Cognito::Cognito &cognito);

    /**
     * Returns a cognito user pool entity by primary key
     *
     * @param oid cognito user pool primary key
     * @return cognito user pool entity
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
    std::vector<Entity::Cognito::UserPool> ListUserPools(const std::string &region = {});

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

    /**
     * Check existence of cognito user
     *
     * @param region AWS region name
     * @param userPoolId user pool ID
     * @param userName name of the user
     * @return true if cognito user exists
     * @throws DatabaseException
     */
    bool UserExists(const std::string &region, const std::string &userPoolId, const std::string &userName);

    /**
     * Create a new cognito user
     *
     * @param user cognito user entity to create
     * @return created cognito user entity.
     */
    Entity::Cognito::User CreateUser(const Entity::Cognito::User &user);

    /**
     * Returns a cognito user entity by primary key
     *
     * @param oid cognito user primary key
     * @return cognito user entity
     * @throws DatabaseException
     */
    Entity::Cognito::User GetUserById(bsoncxx::oid oid);

    /**
     * Returns a cognito user entity by primary key
     *
     * @param oid cognito user primary key
     * @return cognito user entity
     * @throws DatabaseException
     */
    Entity::Cognito::User GetUserById(const std::string &oid);

    /**
     * Returns a cognito user entity by region, userId and name.
     *
     * @param region aws-mock region.
     * @param userPoolId user pool ID
     * @param userName user name
     * @return cognito user entity
     * @throws DatabaseException
     */
    Entity::Cognito::User GetUserByUserName(const std::string &region, const std::string &userPoolId, const std::string &userName);

    /**
     * Count all user pools
     *
     * @param region aws-mock region.
     * @param userPoolId user pool ID
     * @return total number of users.
     */
    long CountUsers(const std::string &region = {}, const std::string &userPoolId = {});

    /**
     * Returns a list of cognito users.
     *
     * @param region AWS region name
     * @param userPoolId user pool ID
     * @return list of cognito users
     */
    std::vector<Entity::Cognito::User> ListUsers(const std::string &region = {}, const std::string &userPoolId = {});

    /**
     * Updates an existing cognito user
     *
     * @param user user entity
     * @return updated cognito user entity.
     */
    Entity::Cognito::User UpdateUser(const Entity::Cognito::User &user);

    /**
     * Creates a new user or updates an existing user
     *
     * @param user user entity
     * @return created or updated Cognito user entity
     * @throws DatabaseException
     */
    Entity::Cognito::User CreateOrUpdateUser(Entity::Cognito::User &user);

    /**
     * Deletes an existing cognito users
     *
     * @param user cognito user to delete
     * @throws DatabaseException
     */
    void DeleteUser(const Entity::Cognito::User &user);

    /**
     * Deletes all existing cognito users
     *
     * @throws DatabaseException
     */
    void DeleteAllUsers();

    private:

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Use MongoDB
     */
    bool _hasDatabase;

    /**
     * Database name
     */
    std::string _databaseName;

    /**
     * S3 in-memory database
     */
    CognitoMemoryDb &_memoryDb;

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_COGNITODATABASE_H
