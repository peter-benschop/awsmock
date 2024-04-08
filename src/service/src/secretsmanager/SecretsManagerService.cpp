//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/secretsmanager/SecretsManagerService.h>

namespace AwsMock::Service {

  SecretsManagerService::SecretsManagerService(Core::Configuration &configuration, Poco::Condition &condition)
    : _logger(Poco::Logger::get("SecretsManagerService")), _configuration(configuration), _database(Database::SecretsManagerDatabase::instance()), _condition(condition) {

    // Initialize environment
    _accountId = _configuration.getString("awsmock.account.id", DEFAULT_ACCOUNT_ID);
  }

  Dto::SecretsManager::CreateSecretResponse SecretsManagerService::CreateSecret(const Dto::SecretsManager::CreateSecretRequest& request) {

    Dto::SecretsManager::CreateSecretResponse response;
    response.name = request.name;
    response.versionId = Poco::UUIDGenerator().createRandom().toString();
    response.arn = Core::AwsUtils::CreateSecretArn(request.region, _accountId, response.name);

    return response;
  }
} // namespace AwsMock::Service
