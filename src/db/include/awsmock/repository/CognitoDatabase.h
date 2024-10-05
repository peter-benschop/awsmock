//
// Created by vogje01 on 29/11/2023.
//

#ifndef AWSMOCK_REPOSITORY_COGNITO_DATABASE_H
#define AWSMOCK_REPOSITORY_COGNITO_DATABASE_H

// C++ standard includes
#include <iostream>
#include <string>
#include <vector>

// AwsMock includes
#include "awsmock/core/config/Configuration.h"
#include "awsmock/core/exception/DatabaseException.h"
#include <awsmock/core/LogStream.h>
#include <awsmock/memorydb/CognitoMemoryDb.h>
#include <awsmock/repository/Database.h>
#include <awsmock/utils/ConnectionPool.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    /**
     * @brief Cognito MongoDB database.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoDatabase : public DatabaseBase {

      public:

        /**
         * @brief Constructor
         */
        explicit CognitoDatabase() : _databaseName(GetDatabaseName()), _memoryDb(CognitoMemoryDb::instance()), _userpoolCollectionName("cognito_userpool"), _userCollectionName("cognito_user"), _groupCollectionName("cognito_group") {};

        /**
         * @brief Singleton instance
         */
        static CognitoDatabase &instance() {
            static CognitoDatabase cognitoDatabase;
            return cognitoDatabase;
        }

        /**
         * @brief Check existence of cognito user pool
         *
         * @param region AWS region name
         * @param name AWS function
         * @return true if cognito user pool exists
         * @throws DatabaseException
         */
        bool UserPoolExists(const std::string &region, const std::string &name);

        /**
         * @brief Check existence of cognito user pool
         *
         * @param userPoolId user pool userPoolId
         * @return true if cognito user pool exists
         * @throws DatabaseException
         */
        bool UserPoolExists(const std::string &userPoolId);

        /**
         * @brief Create a new cognito user pool
         *
         * @param userPool cognito user pool entity to create
         * @return created cognito entity.
         */
        Entity::Cognito::UserPool CreateUserPool(Entity::Cognito::UserPool &userPool);

        /**
         * @brief Count all user pools
         *
         * @param region aws-mock region.
         * @return total number of user pools.
         */
        long CountUserPools(const std::string &region = {});

        /**
         * @brief Updates an existing cognito user pool
         *
         * @param userPool user pool entity
         * @return updated cognito user pool entity.
         */
        Entity::Cognito::UserPool UpdateUserPool(Entity::Cognito::UserPool &userPool);

        /**
         * @brief Creates a new user pool or updates an existing user pool
         *
         * @param userPool user pool entity
         * @return created or updated Cognito user pool entity
         * @throws DatabaseException
         */
        Entity::Cognito::UserPool CreateOrUpdateUserPool(Entity::Cognito::UserPool &userPool);

        /**
         * @brief Returns a cognito user pool entity by primary key
         *
         * @param oid cognito user pool primary key
         * @return cognito user pool entity
         * @throws DatabaseException
         */
        Entity::Cognito::UserPool GetUserPoolById(bsoncxx::oid oid);

        /**
         * @brief Returns a cognito user pool entity by primary key
         *
         * @param userPoolId cognito user pool ID
         * @return cognito user pool entity
         * @throws DatabaseException
         */
        Entity::Cognito::UserPool GetUserPoolByUserPoolId(const std::string &userPoolId);

        /**
         * @brief Returns a cognito user pool entity by client Id
         *
         * @param clientId cognito client ID
         * @return cognito user pool entity
         * @throws DatabaseException
         */
        Entity::Cognito::UserPool GetUserPoolByClientId(const std::string &clientId);

        /**
         * @brief Returns a cognito user pool entity by region and name
         *
         * @param region AWS region
         * @param name cognito user pool name
         * @return cognito entity
         * @throws DatabaseException
         */
        Entity::Cognito::UserPool GetUserPoolByRegionName(const std::string &region, const std::string &name);

        /**
         * @brief Returns a list of cognito user pools.
         *
         * @param region AWS region name
         * @return list of cognito user pools
         */
        std::vector<Entity::Cognito::UserPool> ListUserPools(const std::string &region = {});

        /**
         * @brief Deletes an existing cognito user pool
         *
         * @param id cognito user pool ID
         * @throws DatabaseException
         */
        void DeleteUserPool(const std::string &id);

        /**
         * @brief Deletes all existing cognito user pools
         *
         * @throws DatabaseException
         */
        void DeleteAllUserPools();

        /**
         * @brief Check existence of cognito user
         *
         * @param region AWS region name
         * @param userPoolId user pool ID
         * @param userName name of the user
         * @return true if cognito user exists
         * @throws DatabaseException
         */
        bool UserExists(const std::string &region, const std::string &userPoolId, const std::string &userName);

        /**
         * Check existence of cognito user
         *
         * @param region AWS region name
         * @param userPoolId user pool ID
         * @param userName name of the user
         * @return true if cognito user exists
         * @throws DatabaseException
         */
        bool UserExists(const std::string &region, const std::string &userName);

        /**
         * @brief Create a new cognito user
         *
         * @param user cognito user entity to create
         * @return created cognito user entity.
         */
        Entity::Cognito::User CreateUser(Entity::Cognito::User &user);

        /**
         * @brief Returns a cognito user entity by primary key
         *
         * @param oid cognito user primary key
         * @return cognito user entity
         * @throws DatabaseException
         */
        Entity::Cognito::User GetUserById(bsoncxx::oid oid);

        /**
         * @brief Returns a cognito user entity by primary key
         *
         * @param oid cognito user primary key
         * @return cognito user entity
         * @throws DatabaseException
         */
        Entity::Cognito::User GetUserById(const std::string &oid);

        /**
         * @brief Returns a cognito user entity by region, userId and name.
         *
         * @param region aws-mock region.
         * @param userPoolId user pool ID
         * @param userName user name
         * @return cognito user entity
         * @throws DatabaseException
         */
        Entity::Cognito::User GetUserByUserName(const std::string &region, const std::string &userPoolId, const std::string &userName);

        /**
         * @brief Count all user pools
         *
         * @param region aws-mock region.
         * @param userPoolId user pool ID
         * @return total number of users.
         */
        long CountUsers(const std::string &region = {}, const std::string &userPoolId = {});

        /**
         * @brief Returns a list of cognito users.
         *
         * @param region AWS region name
         * @param userPoolId user pool ID
         * @return list of cognito users
         */
        std::vector<Entity::Cognito::User> ListUsers(const std::string &region = {}, const std::string &userPoolId = {});

        /**
         * @brief Returns a list of cognito users in given group.
         *
         * @param region AWS region name
         * @param userPoolId user pool ID
         * @param groupName name of the group
         * @return list of cognito users
         */
        std::vector<Entity::Cognito::User> ListUsersInGroup(const std::string &region, const std::string &userPoolId, const std::string &groupName);

        /**
         * @brief Updates an existing cognito user
         *
         * @param user user entity
         * @return updated cognito user entity.
         */
        Entity::Cognito::User UpdateUser(Entity::Cognito::User &user);

        /**
         * @brief Creates a new user or updates an existing user
         *
         * @param user user entity
         * @return created or updated Cognito user entity
         * @throws DatabaseException
         */
        Entity::Cognito::User CreateOrUpdateUser(Entity::Cognito::User &user);

        /**
         * @brief Deletes an existing cognito users
         *
         * @param user cognito user to delete
         * @throws DatabaseException
         */
        void DeleteUser(const Entity::Cognito::User &user);

        /**
         * @brief Deletes all existing cognito users
         *
         * @throws DatabaseException
         */
        void DeleteAllUsers();

        /**
         * @brief Check existence of cognito group
         *
         * @param region AWS region name
         * @param groupName group name
         * @return true if cognito group exists
         * @throws DatabaseException
         */
        bool GroupExists(const std::string &region, const std::string &groupName);

        /**
         * @brief Returns a cognito group entity by primary key
         *
         * @param oid cognito group primary key
         * @return cognito group entity
         * @throws DatabaseException
         */
        Entity::Cognito::Group GetGroupById(bsoncxx::oid oid);

        /**
         * @brief Returns a cognito group entity by region, userPoolId and groupName.
         *
         * @param region AWS region.
         * @param userPoolId user pool ID
         * @param groupName group name
         * @return cognito group entity
         * @throws DatabaseException
         */
        Entity::Cognito::Group GetGroupByGroupName(const std::string &region, const std::string &userPoolId, const std::string &groupName);

        /**
         * @brief Create a new cognito group
         *
         * @param group cognito group entity to create
         * @return created cognito group entity.
         */
        Entity::Cognito::Group CreateGroup(Entity::Cognito::Group &group);

        /**
         * @brief Returns a list of cognito groups.
         *
         * @param region AWS region name
         * @param userPoolId user pool ID
         * @return list of cognito groups
         */
        std::vector<Entity::Cognito::Group> ListGroups(const std::string &region = {}, const std::string &userPoolId = {});

        /**
         * @brief Deletes an existing cognito user group.
         *
         * @param region AWS region
         * @param userPoolId cognito user pool ID
         * @param groupName name of the group
         * @throws DatabaseException
         */
        void DeleteGroup(const std::string &region, const std::string &userPoolId, const std::string &groupName);

        /**
         * @brief Deletes all existing cognito user groups.
         *
         * @param region AWS region
         * @throws DatabaseException
         */
        void DeleteAllGroups(const std::string &region = {});

        /**
         * @brief Check existence of a client ID
         *
         * @param region AWS region name
         * @param clientId client ID
         * @return true if cognito client ID exists
         * @throws DatabaseException
         */
        bool ClientIdExists(const std::string &region, const std::string &clientId);

      private:

        /**
         * Database name
         */
        std::string _databaseName;

        /**
         * User pool collection name
         */
        std::string _userpoolCollectionName;

        /**
         * User pool collection name
         */
        std::string _userCollectionName;

        /**
         * Group collection name
         */
        std::string _groupCollectionName;

        /**
         * S3 in-memory database
         */
        CognitoMemoryDb &_memoryDb;
    };

}// namespace AwsMock::Database

#endif// AWSMOCK_REPOSITORY_COGNITO_DATABASE_H
