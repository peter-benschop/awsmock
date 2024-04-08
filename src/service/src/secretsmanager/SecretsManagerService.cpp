//
// Created by vogje01 on 08/04/2024.
//

#include <awsmock/service/secretsmanager/SecretsManagerService.h>

namespace AwsMock::Service {

  SecretsManagerService::SecretsManagerService(Core::Configuration &configuration, Poco::Condition &condition)
    : _logger(Poco::Logger::get("SecretsManagerService")), _configuration(configuration), _database(Database::SecretsManagerDatabase::instance()), _condition(condition) {

    // Initialize environment
    _accountId = _configuration.getString("awsmock.account.id", DEFAULT_ACCOUNT_ID);
  }

  Dto::SecretsManager::CreateSecretResponse SecretsManagerService::CreateSecret(const Dto::SecretsManager::CreateSecretRequest &request) {
    log_trace_stream(_logger) << "Create secret request, request: " << request.ToString() << std::endl;

    // Get region
    std::string region = request.region;

    // Check existence
    if (_database.SecretExists(request.region, request.name)) {
      log_warning_stream(_logger) << "Secret exists already, region: " << region << " name: " << request.name << std::endl;
      throw Core::ServiceException("Secret exists already", Poco::Net::HTTPResponse::HTTP_REASON_BAD_GATEWAY);
    }

    Database::Entity::SecretsManager::Secret secret = {.region=region, .name=request.name};
    try {

      // Update database
      secret.versionId = Poco::UUIDGenerator().createRandom().toString();
      secret.secretId = request.name + "-" + Core::StringUtils::GenerateRandomHexString(6);
      secret.arn = Core::AwsUtils::CreateSecretArn(request.region, _accountId, secret.secretId);

      secret = _database.CreateSecret(secret);

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "S3 create bucket failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    return {.region=secret.region, .name=secret.name, .arn=secret.arn, .versionId=secret.versionId};
  }

  Dto::SecretsManager::DeleteSecretResponse SecretsManagerService::DeleteSecret(const Dto::SecretsManager::DeleteSecretRequest &request) {
    log_trace_stream(_logger) << "Delete secret request: " << request.ToString() << std::endl;

    // Check bucket existence
    if (!_database.SecretExists(request.region, request.name)) {
      log_warning_stream(_logger) << "Secret does not exist, name: " << request.name << std::endl;
      throw Core::ServiceException("Secret does not exist, name: " + request.name, Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    try {

      // Get object from database
      Database::Entity::SecretsManager::Secret secret = _database.GetSecretByRegionName(request.region, request.name);

      // Delete from database
      _database.DeleteSecret(secret);
      log_debug_stream(_logger) << "Database secret deleted, region: " << request.region<< " name: "<< request.name << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "S3 delete object failed, message: " + exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return {};
  }

} // namespace AwsMock::Service
