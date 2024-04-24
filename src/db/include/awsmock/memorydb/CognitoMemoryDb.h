//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_COGNITO_MEMORYDB_H
#define AWSMOCK_REPOSITORY_COGNITO_MEMORYDB_H

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
#include <awsmock/entity/cognito/User.h>
#include <awsmock/entity/cognito/UserPool.h>

namespace AwsMock::Database {

    /**
     * Cognito in-memory database.
     *
     * @author jens.vogt@opitz-consulting.com
     */
    class CognitoMemoryDb {

      public:

        /**
         * Constructor
         */
        CognitoMemoryDb() = default;

        /**
         * Singleton instance
         */
        static CognitoMemoryDb &instance() {
            static Poco::SingletonHolder <CognitoMemoryDb> sh;
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
         * @param id user pool userPoolId
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
         * Returns a cognito user pool entity by region and name
         *
         * @param region AWS region
         * @param name cognito user pool name
         * @return cognito entity
         * @throws DatabaseException
         */
        Entity::Cognito::UserPool GetUserPoolByRegionName(const std::string &region, const std::string &name);

        /**
         * Count all user pools
         *
         * @param region aws-mock region.
         * @return total number of user pools.
         */
        long CountUserPools(const std::string &region = {});

        /**
         * Returns a list of cognito user pools.
         *
         * @param region AWS region name
         * @return list of cognito user pools
         */
        std::vector <Entity::Cognito::UserPool> ListUserPools(const std::string &region);

        /**
         * Updates an existing cognito user pool
         *
         * @param userPool cognito user pool entity
         * @return updated cognito user pool entity.
         */
        Entity::Cognito::UserPool UpdateUserPool(const Entity::Cognito::UserPool &userPool);

        /**
         * Deletes an existing cognito user pool
         *
         * @param userPoolId cognito user pool ID
         * @throws DatabaseException
         */
        void DeleteUserPool(const std::string &userPoolId);

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
        Entity::Cognito::User GetUserByOid(const std::string &oid);

        /**
         * Returns a cognito user entity by region, userId and name.
         *
         * @param region aws-mock region.
         * @param userPoolId user pool ID
         * @param userName user name
         * @return cognito user entity
         * @throws DatabaseException
         */
        Entity::Cognito::User GetUserByUserName(const std::string &region,
                                                const std::string &userPoolId,
                                                const std::string &userName);

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
        std::vector <Entity::Cognito::User> ListUsers(const std::string &region = {}, const std::string &userPoolId = {});

        /**
         * Updates an existing cognito user
         *
         * @param user user entity
         * @return updated cognito user entity.
         */
        Entity::Cognito::User UpdateUser(const Entity::Cognito::User &user);

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
         * Cognito user pool map
         */
        std::map <std::string, Entity::Cognito::UserPool> _userPools{};

        /**
         * Cognito user map
         */
        std::map <std::string, Entity::Cognito::User> _users{};

        /**
         * Cognito user pool mutex
         */
        Poco::Mutex _userPoolMutex;

        /**
         * Cognito user mutex
         */
        Poco::Mutex _userMutex;
    };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_COGNITO_MEMORYDB_H
