//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/CognitoService.h>

namespace AwsMock::Service {

  CognitoService::CognitoService(Core::Configuration &configuration) : _logger(Poco::Logger::get("CognitoService")), _configuration(configuration) {

    _accountId = _configuration.getString("awsmock.account.id");

    // Initialize directories
//    _dataDir = _configuration.getString("awsmock.data.dir", DEFAULT_DATA_DIR);
//    _dataS3Dir = _configuration.getString("awsmock.service.s3.data.dir", DEFAULT_S3_DATA_DIR);

    // Initialize database
    _database = std::make_unique<Database::CognitoDatabase>(_configuration);
  }

  Dto::Cognito::CreateUserPoolResponse CognitoService::CreateUserPool(const Dto::Cognito::CreateUserPoolRequest &request) {
    log_debug_stream(_logger) << "Create user pool request, region:  " << request.region << " name: " << request.name << std::endl;

    Dto::Cognito::CreateUserPoolResponse response{};
    if (_database->UserPoolExists(request.region, request.name)) {
      throw Core::ServiceException("User pool exists already, region: " + request.region + " name: " + request.name);
    }

    try {
      Database::Entity::Cognito::UserPool userPool = {
          .region=request.region,
          .id=request.region + "_" + Core::StringUtils::GenerateRandomString(9),
          .name=request.name
      };

      userPool = _database->CreateUserPool(userPool);
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

      std::vector<Database::Entity::Cognito::UserPool> userPools = _database->ListUserPools(request.region);
      response = Dto::Cognito::ListUserPoolResponse(userPools);
      log_trace_stream(_logger) << "User pool list outcome: " + response.ToJson() << std::endl;
      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "User pool list request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  void CognitoService::DeleteUserPool(const Dto::Cognito::DeleteUserPoolRequest &request) {
    log_debug_stream(_logger) << "Delete user pool request, id:  " << request.id << std::endl;

    if (!_database->UserPoolExists(request.id)) {
      throw Core::ServiceException("User pool does not exists, id: " + request.id);
    }

    try {

      _database->DeleteUserPool(request.id);
      log_trace_stream(_logger) << "User pool deleted, id: " + request.id << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "Create user pool request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }
  }

} // namespace AwsMock::Service
