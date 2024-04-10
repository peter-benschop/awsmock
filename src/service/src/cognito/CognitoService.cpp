//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/service/cognito/CognitoService.h"

namespace AwsMock::Service {

  CognitoService::CognitoService(Core::Configuration &configuration) : _logger(Poco::Logger::get("CognitoService")), _configuration(configuration), _database(Database::CognitoDatabase::instance()) {
  }

  Dto::Cognito::CreateUserPoolResponse CognitoService::CreateUserPool(const Dto::Cognito::CreateUserPoolRequest &request) {
    log_debug_stream(_logger) << "Create user pool request, region:  " << request.region << " name: " << request.name << std::endl;

    Dto::Cognito::CreateUserPoolResponse response{};
    if (_database.UserPoolExists(request.region, request.name)) {
      throw Core::ServiceException("User pool exists already, region: " + request.region + " name: " + request.name);
    }

    try {
      Database::Entity::Cognito::UserPool userPool = {
          .region=request.region,
          .userPoolId=request.region + "_" + Core::StringUtils::GenerateRandomString(9),
          .name=request.name
      };

      userPool = _database.CreateUserPool(userPool);
      response = {
          .region=userPool.region,
          .name=userPool.name
      };
      log_trace_stream(_logger) << "Create user pool outcome: " + response.ToJson() << std::endl;
      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "Create user pool request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  Dto::Cognito::ListUserPoolResponse CognitoService::ListUserPools(const Dto::Cognito::ListUserPoolRequest &request) {
    log_debug_stream(_logger) << "List user pools request, maxResults: " << request.maxResults << std::endl;

    Dto::Cognito::ListUserPoolResponse response{};

    try {

      std::vector<Database::Entity::Cognito::UserPool> userPools = _database.ListUserPools(request.region);
      response = Dto::Cognito::ListUserPoolResponse(userPools);
      log_trace_stream(_logger) << "User pool list outcome: " + response.ToJson() << std::endl;
      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "User pool list request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  void CognitoService::DeleteUserPool(const Dto::Cognito::DeleteUserPoolRequest &request) {
    log_debug_stream(_logger) << "Delete user pool request, userPoolId:  " << request.userPoolId << std::endl;

    if (!_database.UserPoolExists(request.userPoolId)) {
      throw Core::ServiceException("User pool does not exists, userPoolId: " + request.userPoolId);
    }

    try {

      _database.DeleteUserPool(request.userPoolId);
      log_trace_stream(_logger) << "User pool deleted, userPoolId: " + request.userPoolId << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "Create user pool request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  Dto::Cognito::AdminCreateUserResponse CognitoService::AdminCreateUser(const Dto::Cognito::AdminCreateUserRequest &request) {
    log_debug_stream(_logger) << "Admin create user request, userName:  " << request.userName << " userPoolId: " << request.userPoolId << std::endl;

    if (!_database.UserPoolExists(request.userPoolId)) {
      throw Core::ServiceException("User pool does not exists, userPoolId: " + request.userPoolId);
    }

    if (_database.UserExists(request.region, request.userPoolId, request.userName)) {
      throw Core::ServiceException("User exists exists already, userPoolId: " + request.userPoolId + " userName: " + request.userName);
    }

    try {
      Database::Entity::Cognito::User user = {
          .region=request.region,
          .userPoolId=request.userPoolId,
          .userName=request.userName,
          .enabled=true,
          .created=Poco::DateTime(),
          .modified=Poco::DateTime(),
      };

      user = _database.CreateUser(user);
      Dto::Cognito::AdminCreateUserResponse response = {
          .region=user.region,
          .userName=user.userName,
          .enabled=user.enabled
      };
      log_trace_stream(_logger) << "Create user response: " + response.ToJson() << std::endl;
      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "Create user request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }

  }

  Dto::Cognito::ListUsersResponse CognitoService::ListUsers(const Dto::Cognito::ListUsersRequest &request) {
    log_debug_stream(_logger) << "List users request, region: " << request.region << " userPoolId: " << request.userPoolId << std::endl;

    Dto::Cognito::ListUsersResponse response{};

    try {

      Database::Entity::Cognito::UserList users = _database.ListUsers(request.region, request.userPoolId);
      response.users = users;
      log_trace_stream(_logger) << "Users list outcome: " + response.ToJson() << std::endl;
      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "User list request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  void CognitoService::AdminDeleteUser(const Dto::Cognito::AdminDeleteUserRequest &request) {
    log_debug_stream(_logger) << "Admin delete user request, userName:  " << request.userName << " userPoolId: " << request.userPoolId << std::endl;

    if (!_database.UserPoolExists(request.userPoolId)) {
      throw Core::ServiceException("User pool does not exists, userPoolId: " + request.userPoolId);
    }

    if (!_database.UserExists(request.region, request.userPoolId, request.userName)) {
      throw Core::ServiceException("User does not exists, userPoolId: " + request.userPoolId + " userName: " + request.userName);
    }

    try {
      Database::Entity::Cognito::User user = _database.GetUserByUserName(request.region, request.userPoolId, request.userName);

      _database.DeleteUser(user);
      log_trace_stream(_logger) << "User deleted, userName:  " << request.userName << " userPoolId: " << request.userPoolId << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "Delete user request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }

  }
} // namespace AwsMock::Service
