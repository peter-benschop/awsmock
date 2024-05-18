//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/cognito/CognitoService.h>

namespace AwsMock::Service {

    Dto::Cognito::CreateUserPoolResponse CognitoService::CreateUserPool(const Dto::Cognito::CreateUserPoolRequest &request) {
        log_debug << "Create user pool request, region:  " << request.region << " name: " << request.name;

        Dto::Cognito::CreateUserPoolResponse response{};
        if (_database.UserPoolExists(request.region, request.name)) {
            log_error << "User pool exists already, region: " << request.region << " name: " << request.name;
            throw Core::ServiceException("User pool exists already, region: " + request.region + " name: " + request.name);
        }

        try {
            std::string userPoolId = Core::AwsUtils::CreateCognitoUserPoolId(request.region);
            Database::Entity::Cognito::UserPool userPool = {
                    .region = request.region,
                    .userPoolId = userPoolId,
                    .name = request.name,
                    .arn = Core::AwsUtils::CreateCognitoUserPoolArn(request.region, _accountId, userPoolId),
            };

            userPool = _database.CreateUserPool(userPool);
            response = {
                    .region = userPool.region,
                    .name = userPool.name};
            log_trace << "Create user pool outcome: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "Create user pool request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::Cognito::ListUserPoolResponse CognitoService::ListUserPools(const Dto::Cognito::ListUserPoolRequest &request) {
        log_debug << "List user pools request, maxResults: " << request.maxResults;

        Dto::Cognito::ListUserPoolResponse response{};

        try {

            std::vector<Database::Entity::Cognito::UserPool> userPools = _database.ListUserPools(request.region);
            response = Dto::Cognito::ListUserPoolResponse(userPools);
            log_trace << "User pool list outcome: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "User pool list request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void CognitoService::DeleteUserPool(const Dto::Cognito::DeleteUserPoolRequest &request) {
        log_debug << "Delete user pool request, userPoolId:  " << request.userPoolId;

        if (!_database.UserPoolExists(request.userPoolId)) {
            log_error << "User pool does not exists, userPoolId: " << request.userPoolId;
            throw Core::ServiceException("User pool does not exists, userPoolId: " + request.userPoolId);
        }

        try {

            _database.DeleteUserPool(request.userPoolId);
            log_trace << "User pool deleted, userPoolId: " + request.userPoolId;

        } catch (Poco::Exception &ex) {
            log_error << "Create user pool request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::Cognito::AdminCreateUserResponse CognitoService::AdminCreateUser(const Dto::Cognito::AdminCreateUserRequest &request) {
        log_debug << "Admin create user request, userName:  " << request.userName << " userPoolId: " << request.userPoolId;

        if (!_database.UserPoolExists(request.userPoolId)) {
            throw Core::ServiceException("User pool does not exists, userPoolId: " + request.userPoolId);
        }

        if (_database.UserExists(request.region, request.userPoolId, request.userName)) {
            throw Core::ServiceException("User exists exists already, userPoolId: " + request.userPoolId + " userName: " + request.userName);
        }

        try {
            Database::Entity::Cognito::User user = {
                    .region = request.region,
                    .userPoolId = request.userPoolId,
                    .userName = request.userName,
                    .enabled = true,
                    .created = Poco::DateTime(),
                    .modified = Poco::DateTime(),
            };

            user = _database.CreateUser(user);
            Dto::Cognito::AdminCreateUserResponse response = {
                    .region = user.region,
                    .userName = user.userName,
                    .enabled = user.enabled};
            log_trace << "Create user response: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "Create user request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::Cognito::ListUsersResponse CognitoService::ListUsers(const Dto::Cognito::ListUsersRequest &request) {
        log_debug << "List users request, region: " << request.region << " userPoolId: " << request.userPoolId;

        Dto::Cognito::ListUsersResponse response{};

        try {

            Database::Entity::Cognito::UserList users = _database.ListUsers(request.region, request.userPoolId);
            response.users = users;
            log_trace << "Users list outcome: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "User list request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void CognitoService::AdminDeleteUser(const Dto::Cognito::AdminDeleteUserRequest &request) {
        log_debug << "Admin delete user request, userName:  " << request.userName << " userPoolId: " << request.userPoolId;

        if (!_database.UserPoolExists(request.userPoolId)) {
            throw Core::ServiceException("User pool does not exists, userPoolId: " + request.userPoolId);
        }

        if (!_database.UserExists(request.region, request.userPoolId, request.userName)) {
            throw Core::ServiceException("User does not exists, userPoolId: " + request.userPoolId + " userName: " + request.userName);
        }

        try {
            Database::Entity::Cognito::User user = _database.GetUserByUserName(request.region, request.userPoolId, request.userName);

            _database.DeleteUser(user);
            log_trace << "User deleted, userName:  " << request.userName << " userPoolId: " << request.userPoolId;

        } catch (Poco::Exception &ex) {
            log_error << "Delete user request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }
}// namespace AwsMock::Service
