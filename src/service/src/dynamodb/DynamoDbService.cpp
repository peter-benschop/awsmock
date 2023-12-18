//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/DynamoDbService.h>

namespace AwsMock::Service {

  DynamoDbService::DynamoDbService(Core::Configuration &configuration, Core::MetricService &metricService) :
    _logger(Poco::Logger::get("DynamoDbService")), _configuration(configuration), _metricService(metricService) {

    // Initialize environment
    _accountId = _configuration.getString("awsmock.account.id", "000000000000");
    _dockerService = std::make_shared<Service::DockerService>(_configuration);
    _dynamoDbDatabase = std::make_shared<Database::DynamoDbDatabase>(_configuration);

  }

  void DynamoDbService::StartInstance(const std::string &region, const std::string &name) {

    log_debug_stream(_logger) << "Start creating a new DynamoDb instance, region: " << region << " name: " << name << std::endl;

    // Make local copy
    Database::Entity::DynamoDb::DynamoDb dynamoDBEntity = _dynamoDbDatabase->GetDatabaseByName(region, name);

    // Docker tag
    //std::string dockerTag = GetDockerTag(lambdaEntity);
    //log_debug_stream(_logger) << "Using docker tag: " << dockerTag << std::endl;

    // Build the docker image, if not existing
    //if (!_dockerService.ImageExists(lambdaEntity.function, dockerTag)) {
    //CreateDockerImage(functionCode, lambdaEntity, dockerTag);
    //}
  }

} // namespace AwsMock::Service
