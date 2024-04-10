//
// Created by vogje01 on 08/04/2024.
//

#include <awsmock/service/secretsmanager/SecretsManagerService.h>

namespace AwsMock::Service {

  SecretsManagerService::SecretsManagerService(Core::Configuration &configuration, Poco::Condition &condition)
    : _logger(Poco::Logger::get("SecretsManagerService")), _configuration(configuration), _database(Database::SecretsManagerDatabase::instance()), _condition(condition) {

    // Initialize environment
    _accountId = _configuration.getString("awsmock.account.userPoolId", DEFAULT_ACCOUNT_ID);

    // Simulation of KMS key
    _kmsKey = "aGYlaHJGZk5FMjNXN05kJmpvWVpvem9GT1M+WE1qWlg=";
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

      // Either string or binary data
      if (!request.secretString.empty()) {
        auto *plaintext = (unsigned char *) request.secretString.c_str();
        int len = (int) strlen(reinterpret_cast<const char *>(plaintext));
        secret.secretString = Core::Crypto::Base64Encode(Core::Crypto::Aes256EncryptString(plaintext, &len, _kmsKey));
      } else {
        secret.secretBinary = request.secretBinary;
      }
      secret = _database.CreateSecret(secret);

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "SecretManager create secret failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message());
    }
    return {.region=secret.region, .name=secret.name, .arn=secret.arn, .versionId=secret.versionId};
  }

  Dto::SecretsManager::DescribeSecretResponse SecretsManagerService::DescribeSecret(const Dto::SecretsManager::DescribeSecretRequest &request) {
    log_trace_stream(_logger) << "Describe secret request: " << request.ToString() << std::endl;

    // Check bucket existence
    if (!_database.SecretExists(request.secretId)) {
      log_warning_stream(_logger) << "Secret does not exist, secretId: " << request.secretId << std::endl;
      throw Core::ResourceNotFoundException("Secret does not exist, secretId: " + request.secretId);
    }

    Dto::SecretsManager::DescribeSecretResponse response;
    try {

      // Get object from database
      Database::Entity::SecretsManager::Secret secret = _database.GetSecretBySecretId(request.secretId);

      // Convert to DTO
      response.region = secret.region;
      response.name = secret.name;
      response.arn = secret.arn;
      log_debug_stream(_logger) << "Database secret described, secretId: " << request.secretId << std::endl;
      return response;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Secret describe secret failed, message: " + exc.message() << std::endl;
      throw Core::ServiceException(exc.message());
    }

    return {};
  }

  Dto::SecretsManager::GetSecretValueResponse SecretsManagerService::GetSecretValue(const Dto::SecretsManager::GetSecretValueRequest &request) {
    log_trace_stream(_logger) << "Get secret value request: " << request.ToString() << std::endl;

    // Check bucket existence
    if (!_database.SecretExists(request.secretId)) {
      log_warning_stream(_logger) << "Secret does not exist, secretId: " << request.secretId << std::endl;
      throw Core::ServiceException("Secret does not exist, secretId: " + request.secretId, Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::SecretsManager::GetSecretValueResponse response;
    try {

      // Get object from database
      Database::Entity::SecretsManager::Secret secret = _database.GetSecretBySecretId(request.secretId);

      // Convert to DTO
      response.name = secret.name;
      response.arn = secret.arn;
      response.versionId = secret.versionId;
      if (!secret.secretString.empty()) {
        std::string base64Decoded = Core::Crypto::Base64Decode(secret.secretString);
        int len = (int) base64Decoded.length();
        response.secretString = std::string(reinterpret_cast<char *>(Core::Crypto::Aes256DecryptString((unsigned char *) base64Decoded.c_str(), &len, _kmsKey)));
      } else {
        std::string base64Decoded = Core::Crypto::Base64Decode(secret.secretString);
        int len = (int) base64Decoded.length();
        response.secretBinary = std::string(reinterpret_cast<char *>(Core::Crypto::Aes256DecryptString((unsigned char *) base64Decoded.c_str(), &len, _kmsKey)));
      }
      log_debug_stream(_logger) << "Get secret value, secretId: " << request.secretId << std::endl;
      return response;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Secret describe secret failed, message: " + exc.message() << std::endl;
      throw Core::ServiceException(exc.message());
    }
  }

  Dto::SecretsManager::UpdateSecretResponse SecretsManagerService::UpdateSecret(const Dto::SecretsManager::UpdateSecretRequest &request) {
    log_trace_stream(_logger) << "Update secret request: " << request.ToString() << std::endl;

    // Check bucket existence
    if (!_database.SecretExists(request.secretId)) {
      log_warning_stream(_logger) << "Secret does not exist, secretId: " << request.secretId << std::endl;
      throw Core::ServiceException("Secret does not exist, secretId: " + request.secretId, Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    try {

      // Get object from database
      Database::Entity::SecretsManager::Secret secret = _database.GetSecretBySecretId(request.secretId);

      // Update database
      secret.kmsKeyId = request.kmsKeyId;
      secret.secretString = request.secretString;
      secret.secretBinary = request.secretBinary;
      secret.description = request.description;

      secret = _database.UpdateSecret(secret);

      // Convert to DTO
      log_debug_stream(_logger) << "Database secret described, secretId: " << request.secretId << std::endl;
      return {.region=secret.region, .name=secret.name, .arn=secret.arn, .versionId=secret.versionId};

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Secret describe secret failed, message: " + exc.message() << std::endl;
      throw Core::ServiceException(exc.message());
    }

    return {};
  }

  Dto::SecretsManager::DeleteSecretResponse SecretsManagerService::DeleteSecret(const Dto::SecretsManager::DeleteSecretRequest &request) {
    log_trace_stream(_logger) << "Delete secret request: " << request.ToString() << std::endl;

    // Check bucket existence
    if (!_database.SecretExists(request.region, request.name)) {
      log_warning_stream(_logger) << "Secret does not exist, name: " << request.name << std::endl;
      throw Core::ServiceException("Secret does not exist, name: " + request.name, Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::SecretsManager::DeleteSecretResponse response;
    try {

      // Get object from database
      Database::Entity::SecretsManager::Secret secret = _database.GetSecretByRegionName(request.region, request.name);

      // Delete from database
      _database.DeleteSecret(secret);
      log_debug_stream(_logger) << "Database secret deleted, region: " << request.region << " name: " << request.name << std::endl;
      return {.region=request.region, .name=secret.name, .arn=secret.arn, .deletionDate=static_cast<double>(Poco::Timestamp().epochTime())};

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "SecretManager delete secret failed, message: " + exc.message() << std::endl;
      throw Core::ServiceException(exc.message());
    }
  }

} // namespace AwsMock::Service
