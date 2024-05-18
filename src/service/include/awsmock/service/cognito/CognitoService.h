//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_SERVICE_H
#define AWSMOCK_SERVICE_COGNITO_SERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricDefinition.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/cognito/AdminCreateUserRequest.h>
#include <awsmock/dto/cognito/AdminCreateUserResponse.h>
#include <awsmock/dto/cognito/AdminDeleteUserRequest.h>
#include <awsmock/dto/cognito/CreateUserPoolRequest.h>
#include <awsmock/dto/cognito/CreateUserPoolResponse.h>
#include <awsmock/dto/cognito/DeleteUserPoolRequest.h>
#include <awsmock/dto/cognito/ListUserPoolRequest.h>
#include <awsmock/dto/cognito/ListUserPoolResponse.h>
#include <awsmock/dto/cognito/ListUsersRequest.h>
#include <awsmock/dto/cognito/ListUsersResponse.h>
#include <awsmock/dto/cognito/mapper/Mapper.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/service/secretsmanager/SecretsManagerService.h>

namespace AwsMock::Service {

    /**
     * @brief Cognito service
     *
     * Handles all Cognito requests finally.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CognitoService {

      public:

        /**
         * Constructor
         */
        explicit CognitoService();

        /**
         * Create a new cognito user pool
         *
         * @param request create user pool request
         * @return CreateUserPoolRequest DTO
         */
        Dto::Cognito::CreateUserPoolResponse CreateUserPool(const Dto::Cognito::CreateUserPoolRequest &request);

        /**
         * List cognito user pools
         *
         * @param request list user pool request
         * @return ListUserPoolResponse DTO
         */
        Dto::Cognito::ListUserPoolResponse ListUserPools(const Dto::Cognito::ListUserPoolRequest &request);

        /**
         * Delete a cognito user pool
         *
         * @param request delete user pool request
         */
        void DeleteUserPool(const Dto::Cognito::DeleteUserPoolRequest &request);

        /**
         * Create a new cognito user
         *
         * @param request create user request
         * @return AdminCreateUserResponse DTO
         */
        Dto::Cognito::AdminCreateUserResponse AdminCreateUser(const Dto::Cognito::AdminCreateUserRequest &request);

        /**
         * List cognito users
         *
         * @param request list user request
         * @return ListUsersResponse DTO
         */
        Dto::Cognito::ListUsersResponse ListUsers(const Dto::Cognito::ListUsersRequest &request);

        /**
         * Deletes a cognito user
         *
         * @param request delete user request
         */
        void AdminDeleteUser(const Dto::Cognito::AdminDeleteUserRequest &request);

      private:

        /**
         * Database connection
         */
        Database::CognitoDatabase &_database;

        /**
         * S3 account userPoolId
         */
        std::string _accountId;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_COGNITO_SERVICE_H
