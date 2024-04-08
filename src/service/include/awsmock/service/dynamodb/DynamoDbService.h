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
#include "awsmock/core/AwsUtils.h"
#include "awsmock/core/CryptoUtils.h"
#include "awsmock/core/MetricServiceTimer.h"
#include "awsmock/core/ServiceException.h"
#include "awsmock/core/StringUtils.h"
#include "awsmock/core/SystemUtils.h"
#include "awsmock/core/TarUtils.h"
#include "awsmock/dto/dynamodb/CreateTableRequest.h"
#include "awsmock/dto/dynamodb/CreateTableResponse.h"
#include "awsmock/dto/dynamodb/DeleteItemRequest.h"
#include "awsmock/dto/dynamodb/DeleteItemResponse.h"
#include "awsmock/dto/dynamodb/DeleteTableRequest.h"
#include "awsmock/dto/dynamodb/DeleteTableResponse.h"
#include "awsmock/dto/dynamodb/DescribeTableRequest.h"
#include "awsmock/dto/dynamodb/DescribeTableResponse.h"
#include "awsmock/dto/dynamodb/DynamoDbResponse.h"
#include "awsmock/dto/dynamodb/GetItemRequest.h"
#include "awsmock/dto/dynamodb/GetItemResponse.h"
#include "awsmock/dto/dynamodb/ListTableRequest.h"
#include "awsmock/dto/dynamodb/ListTableResponse.h"
#include "awsmock/dto/dynamodb/PutItemRequest.h"
#include "awsmock/dto/dynamodb/PutItemResponse.h"
#include "awsmock/dto/dynamodb/QueryRequest.h"
#include "awsmock/dto/dynamodb/QueryResponse.h"
#include "awsmock/dto/dynamodb/ScanRequest.h"
#include "awsmock/dto/dynamodb/ScanResponse.h"
#include "awsmock/repository/DynamoDbDatabase.h"
#include "awsmock/service/common/DockerService.h"

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

    /**
     * Lists all available tables
     *
     * @param request list table request DTO
     * @return ListTableResponse
     */
    Dto::DynamoDb::ListTableResponse ListTables(const Dto::DynamoDb::ListTableRequest &request);

    /**
     * Describes a table
     *
     * @param request describe table request DTO
     * @return DescribeTableResponse
     */
    Dto::DynamoDb::DescribeTableResponse DescribeTable(const Dto::DynamoDb::DescribeTableRequest &request);

    /**
     * Deletes a table
     *
     * @param request delete table request DTO
     * @return DeleteTableResponse
     */
    Dto::DynamoDb::DeleteTableResponse DeleteTable(const Dto::DynamoDb::DeleteTableRequest &request);

    /**
     * Deletes all tables with all items
     */
    void DeleteAllTables();

    /**
     * Gets an item
     *
     * @param request get item request DTO
     * @return GetItemResponse
     */
    Dto::DynamoDb::GetItemResponse GetItem(const Dto::DynamoDb::GetItemRequest &request);

    /**
     * Puts an item
     *
     * @param request put item request DTO
     * @return GetItemResponse
     */
    Dto::DynamoDb::PutItemResponse PutItem(const Dto::DynamoDb::PutItemRequest &request);

    /**
     * Query the database
     *
     * @param request query item request DTO
     * @return QueryResponse
     */
    Dto::DynamoDb::QueryResponse Query(const Dto::DynamoDb::QueryRequest &request);

    /**
     * Scan the database
     *
     * @param request scan request DTO
     * @return ScanResponse
     */
    Dto::DynamoDb::ScanResponse Scan(const Dto::DynamoDb::ScanRequest &request);

    /**
     * Deletes a item
     *
     * @param request delete item request DTO
     * @return DeleteItemResponse
     */
    Dto::DynamoDb::DeleteItemResponse DeleteItem(const Dto::DynamoDb::DeleteItemRequest &request);

    private:

    /**
     * Send the request to the DynamoDB container
     *
     * @param body original HTTP request body
     * @param headers original HTTP request headers
     * @return response body
     */
    Dto::DynamoDb::DynamoDbResponse SendDynamoDbRequest(const std::string &body, const std::map<std::string, std::string> &headers);

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
    Database::DynamoDbDatabase& _dynamoDbDatabase;

    /**
     * DynamoDb docker host
     */
    std::string _dockerHost;

    /**
     * DynamoDb docker port
     */
    int _dockerPort;

  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_DYNAMODB_SERVICE_H
