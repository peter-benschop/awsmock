//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_COGNITO_SERVICE_H
#define AWSMOCK_SERVICE_COGNITO_SERVICE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include "awsmock/dto/cognito/DescribeUserPoolResponse.h"
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/core/monitoring/MetricDefinition.h>
#include <awsmock/core/monitoring/MetricServiceTimer.h>
#include <awsmock/dto/cognito/AdminAddUserToGroupRequest.h>
#include <awsmock/dto/cognito/AdminCreateUserRequest.h>
#include <awsmock/dto/cognito/AdminCreateUserResponse.h>
#include <awsmock/dto/cognito/AdminDeleteUserRequest.h>
#include <awsmock/dto/cognito/CreateGroupRequest.h>
#include <awsmock/dto/cognito/CreateGroupResponse.h>
#include <awsmock/dto/cognito/CreateUserPoolClientRequest.h>
#include <awsmock/dto/cognito/CreateUserPoolClientResponse.h>
#include <awsmock/dto/cognito/CreateUserPoolDomainRequest.h>
#include <awsmock/dto/cognito/CreateUserPoolDomainResponse.h>
#include <awsmock/dto/cognito/CreateUserPoolRequest.h>
#include <awsmock/dto/cognito/CreateUserPoolResponse.h>
#include <awsmock/dto/cognito/DeleteGroupRequest.h>
#include <awsmock/dto/cognito/DeleteUserPoolClientRequest.h>
#include <awsmock/dto/cognito/DeleteUserPoolRequest.h>
#include <awsmock/dto/cognito/DescribeUserPoolClientRequest.h>
#include <awsmock/dto/cognito/DescribeUserPoolClientResponse.h>
#include <awsmock/dto/cognito/DescribeUserPoolRequest.h>
#include <awsmock/dto/cognito/DescribeUserPoolResponse.h>
#include <awsmock/dto/cognito/ListGroupsRequest.h>
#include <awsmock/dto/cognito/ListGroupsResponse.h>
#include <awsmock/dto/cognito/ListUserPoolClientsRequest.h>
#include <awsmock/dto/cognito/ListUserPoolClientsResponse.h>
#include <awsmock/dto/cognito/ListUserPoolRequest.h>
#include <awsmock/dto/cognito/ListUserPoolResponse.h>
#include <awsmock/dto/cognito/ListUsersInGroupRequest.h>
#include <awsmock/dto/cognito/ListUsersInGroupResponse.h>
#include <awsmock/dto/cognito/ListUsersRequest.h>
#include <awsmock/dto/cognito/ListUsersResponse.h>
#include <awsmock/dto/cognito/SignUpRequest.h>
#include <awsmock/dto/cognito/SignUpResponse.h>
#include <awsmock/dto/cognito/UpdateUserPoolClientRequest.h>
#include <awsmock/dto/cognito/UpdateUserPoolRequest.h>
#include <awsmock/dto/cognito/mapper/Mapper.h>
#include <awsmock/repository/CognitoDatabase.h>
#include <awsmock/service/secretsmanager/SecretsManagerService.h>

namespace AwsMock::Service {

    using std::chrono::system_clock;

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
         * @brief Constructor
         */
        explicit CognitoService();

        /**
         * @brief Create a new cognito user pool
         *
         * @param request create user pool request
         * @return CreateUserPoolRequest DTO
         */
        Dto::Cognito::CreateUserPoolResponse CreateUserPool(const Dto::Cognito::CreateUserPoolRequest &request);

        /**
         * @brief Updates an existing cognito user pool
         *
         * @param request update user pool request
         */
        void UpdateUserPool(const Dto::Cognito::UpdateUserPoolRequest &request);

        /**
         * @brief List cognito user pools
         *
         * @param request list user pool request
         * @return ListUserPoolResponse DTO
         */
        Dto::Cognito::ListUserPoolResponse ListUserPools(const Dto::Cognito::ListUserPoolRequest &request);

        /**
         * @brief Describes a user pool
         *
         * @param request describe user pool request
         * @return DescribeUserPoolResponse DTO
         */
        Dto::Cognito::DescribeUserPoolResponse DescribeUserPool(const Dto::Cognito::DescribeUserPoolRequest &request);

        /**
         * @brief Delete a cognito user pool
         *
         * @param request delete user pool request
         */
        void DeleteUserPool(const Dto::Cognito::DeleteUserPoolRequest &request);

        /**
         * @brief Create a new cognito user pool domain
         *
         * @param request create user pool domain request
         * @return CreateUserPoolDomainResponse DTO
         */
        Dto::Cognito::CreateUserPoolDomainResponse CreateUserPoolDomain(const Dto::Cognito::CreateUserPoolDomainRequest &request);

        /**
         * @brief Create a new cognito user pool client
         *
         * @param request create user pool client request
         * @return CreateUserPoolClientResponse DTO
         */
        Dto::Cognito::CreateUserPoolClientResponse CreateUserPoolClient(const Dto::Cognito::CreateUserPoolClientRequest &request);

        /**
         * @brief List cognito user pool clients
         *
         * @param request list user pool clients request
         * @return ListUserPoolClientsResponse DTO
         */
        Dto::Cognito::ListUserPoolClientsResponse ListUserPoolClients(const Dto::Cognito::ListUserPoolClientsRequest &request);

        /**
         * @brief Describes a user pool client
         *
         * @param request describe user pool client request
         * @return DescribeUserPoolResponse DTO
         */
        Dto::Cognito::DescribeUserPoolClientResponse DescribeUserPoolClient(const Dto::Cognito::DescribeUserPoolClientRequest &request);

        /**
         * @brief Updates an existing cognito user pool client
         *
         * @param request update user pool client request
         */
        void UpdateUserPoolClient(const Dto::Cognito::UpdateUserPoolClientRequest &request);

        /**
         * @brief Deletes a cognito user pool client
         *
         * @param request create user pool client request
         * @return CreateUserPoolClientResponse DTO
         */
        void DeleteUserPoolClient(const Dto::Cognito::DeleteUserPoolClientRequest &request);

        /**
         * @brief Create a new cognito user
         *
         * @param request create user request
         * @return AdminCreateUserResponse DTO
         */
        Dto::Cognito::AdminCreateUserResponse AdminCreateUser(const Dto::Cognito::AdminCreateUserRequest &request);

        /**
         * @brief List cognito users
         *
         * @param request list user request
         * @return ListUsersResponse DTO
         */
        Dto::Cognito::ListUsersResponse ListUsers(const Dto::Cognito::ListUsersRequest &request);

        /**
         * @brief Adds a user to a group
         *
         * @param request add user to group request
         */
        void AdminAddUserToGroup(const Dto::Cognito::AdminAddUserToGroupRequest &request);

        /**
         * @brief Lists the users in a group
         *
         * @param request list user in group request
         */
        Dto::Cognito::ListUsersInGroupResponse ListUsersInGroup(const Dto::Cognito::ListUsersInGroupRequest &request);

        /**
         * @brief Deletes a cognito user
         *
         * @param request delete user request
         */
        void AdminDeleteUser(const Dto::Cognito::AdminDeleteUserRequest &request);

        /**
         * @brief Create a new cognito user pool
         *
         * @param request create user pool request
         * @return CreateUserPoolResponse DTO
         */
        Dto::Cognito::CreateGroupResponse CreateGroup(const Dto::Cognito::CreateGroupRequest &request);

        /**
         * @brief Lists all available groups
         *
         * @param request list groups request
         * @return ListGroupsResponse DTO
         */
        Dto::Cognito::ListGroupsResponse ListGroups(const Dto::Cognito::ListGroupsRequest &request);

        /**
         * @brief Delete a cognito group
         *
         * @param request delete group request
         */
        void DeleteGroup(const Dto::Cognito::DeleteGroupRequest &request);

        /**
         * @brief Sign up a user
         *
         * @param request sign up request
         * @return SignUpResponse DTO
         */
        Dto::Cognito::SignUpResponse SignUp(const Dto::Cognito::SignUpRequest &request);

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
