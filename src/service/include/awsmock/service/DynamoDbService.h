//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_DYNAMODB_SERVICE_H
#define AWSMOCK_SERVICE_DYNAMODB_SERVICE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/NotificationQueue.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/dto/dynamodb/CreateTableRequest.h>
#include <awsmock/dto/dynamodb/CreateTableResponse.h>
#include <awsmock/repository/DynamoDbDatabase.h>
#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

  /**
   * AWS DynamoDb module. Handles all DynamoDb related requests:
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class DynamoDbService {

    public:

      /**
       * Constructor
       *
       * @param configuration module configuration
       * @param metricService aws-mock monitoring module
       */
      explicit DynamoDbService(Core::Configuration &configuration, Core::MetricService &metricService);

      /**
       * Creates a new table
       *
       * @param request create table request DTO
       * @return CreateTableResponse
       */
      Dto::DynamoDb::CreateTableResponse CreateTable(const Dto::DynamoDb::CreateTableRequest &request);

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * AWS region
       */
      std::string _region;

      /**
       * AWS account ID
       */
      std::string _accountId;

      /**
       * Configuration
       */
      Core::Configuration &_configuration;

      /**
       * Monitoring
       */
      Core::MetricService &_metricService;

      /**
       * Docker module
       */
      std::shared_ptr<Service::DockerService> _dockerService;

      /**
       * Database connection
       */
      std::shared_ptr<Database::DynamoDbDatabase> _dynamoDbDatabase;

  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_DYNAMODB_SERVICE_H
