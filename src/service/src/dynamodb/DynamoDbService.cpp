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

  Dto::DynamoDb::CreateTableResponse DynamoDbService::CreateTable(const Dto::DynamoDb::CreateTableRequest &request) {
    log_debug_stream(_logger) << "Start creating a new DynamoDb table, region: " << request.region << " name: " << request.tableName << std::endl;

    if (_dynamoDbDatabase->TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table exists already, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table exists already", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::DynamoDb::CreateTableResponse createTableResponse;
    try {

      Database::Entity::DynamoDb::Table table = {
        .region=request.region,
        .name=request.tableName,
        .attributes=request.attributes,
        .tags=request.tags
      };

      // Update database
      table = _dynamoDbDatabase->CreateTable(table);

      createTableResponse = {.region=table.region, .tableName=table.name, .tags=table.tags, .attributes=table.attributes};
      log_info_stream(_logger) << "DynamoDb table created, name: " << table.name << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd create table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return createTableResponse;

  }
} // namespace AwsMock::Service
