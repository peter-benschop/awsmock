//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/DynamoDbService.h>

namespace AwsMock::Service {

  DynamoDbService::DynamoDbService(Core::Configuration &configuration, Core::MetricService &metricService) :
    _logger(Poco::Logger::get("DynamoDbService")), _configuration(configuration), _metricService(metricService),_dynamoDbDatabase(Database::DynamoDbDatabase::instance()) {

    // Initialize environment
    _accountId = _configuration.getString("awsmock.account.id", "000000000000");
    _dockerService = std::make_shared<Service::DockerService>(_configuration);

    // DynamoDB docker host, port
    _dockerHost = "localhost";
    _dockerPort = _configuration.getInt("awsmock.dynamodb.port");
  }

  Dto::DynamoDb::CreateTableResponse DynamoDbService::CreateTable(const Dto::DynamoDb::CreateTableRequest &request) {
    log_debug_stream(_logger) << "Start creating a new DynamoDb table, region: " << request.region << " name: " << request.tableName << std::endl;

    if (_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table exists already, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table exists already", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::DynamoDb::CreateTableResponse createTableResponse;
    try {

      Database::Entity::DynamoDb::Table table = {
        .region=request.region,
        .name=request.tableName,
        .attributes=request.attributes,
        .tags=request.tags,
        .keySchemas=request.keySchemas
      };

      // Update database
      table = _dynamoDbDatabase.CreateTable(table);

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      createTableResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb table created, name: " << table.name << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd create table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return createTableResponse;

  }

  Dto::DynamoDb::ListTableResponse DynamoDbService::ListTables(const Dto::DynamoDb::ListTableRequest &request) {
    log_debug_stream(_logger) << "Starting list table request, region: " << request.region << std::endl;

    Dto::DynamoDb::ListTableResponse listTableResponse;
    try {

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      listTableResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb list tables, region: " << request.region << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd create table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return listTableResponse;
  }

  Dto::DynamoDb::DescribeTableResponse DynamoDbService::DescribeTable(const Dto::DynamoDb::DescribeTableRequest &request) {
    log_debug_stream(_logger) << "Describe DynamoDb table, region: " << request.region << " name: " << request.tableName << std::endl;

    Dto::DynamoDb::DescribeTableResponse describeTableResponse;
    describeTableResponse.region = request.region;
    describeTableResponse.tableName = request.tableName;
    describeTableResponse.body = {};

    try {
      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      describeTableResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb describe table, name: " << request.tableName << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDb describe table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return describeTableResponse;
  }

  Dto::DynamoDb::DeleteTableResponse DynamoDbService::DeleteTable(const Dto::DynamoDb::DeleteTableRequest &request) {
    log_debug_stream(_logger) << "Start creating a new DynamoDb table, region: " << request.region << " name: " << request.tableName << std::endl;

    if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table does not exist", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }

    Dto::DynamoDb::DeleteTableResponse deleteTableResponse;
    try {

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      deleteTableResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb table deleted, name: " << request.tableName << std::endl;

      // Delete table in database
      _dynamoDbDatabase.DeleteTable(request.region, request.tableName);

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd delete table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return deleteTableResponse;

  }

  void DynamoDbService::DeleteAllTables() {
    log_debug_stream(_logger) << "Deleting all tables" << std::endl;

    try {

      // Delete all tables from DynamoDB
      for (auto &table : _dynamoDbDatabase.ListTables()) {
        Dto::DynamoDb::DeleteTableRequest request;
        request.tableName = table.name;
        request.body = request.ToJson();
        request.headers["Region"] = "eu-central-1";
        request.headers["X-Amz-Target"] = "DynamoDB_20120810.DeleteTable";
        request.headers["User-Agent"] = "aws-cli/2.15.23 Python/3.11.6 Linux/6.1.0-18-amd64 exe/x86_64.debian.12 prompt/off command/dynamodb.delete-table";
        request.headers["Authorization"] =
          "AWS4-HMAC-SHA256 Credential=none/20240323/eu-central-1/dynamodb/aws4_request, SignedHeaders=content-type;host;x-amz-date;x-amz-security-token;x-amz-target, Signature=77d8a13cb188351689c92945509bbe6963e964d21b4c07d8d0f9cc2d195d0bfd";
        DeleteTable(request);
      }

      // Delete table in database
      _dynamoDbDatabase.DeleteAllTables();
      log_info_stream(_logger) << "DynamoDb tables deleted" << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd delete table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  Dto::DynamoDb::GetItemResponse DynamoDbService::GetItem(const Dto::DynamoDb::GetItemRequest &request) {
    log_debug_stream(_logger) << "Start get item, region: " << request.region << " name: " << request.tableName << std::endl;

    if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table exists already", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }

    Dto::DynamoDb::GetItemResponse getItemResponse;
    try {

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      getItemResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb get item, name: " << request.tableName << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd get item failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return getItemResponse;

  }

  Dto::DynamoDb::PutItemResponse DynamoDbService::PutItem(const Dto::DynamoDb::PutItemRequest &request) {
    log_debug_stream(_logger) << "Start put item, region: " << request.region << " name: " << request.tableName << std::endl;

    if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table exists already", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }

    Dto::DynamoDb::PutItemResponse putItemResponse;
    try {

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      putItemResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb put item, name: " << request.tableName << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDb put item failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return putItemResponse;

  }

  Dto::DynamoDb::QueryResponse DynamoDbService::Query(const Dto::DynamoDb::QueryRequest &request) {
    log_debug_stream(_logger) << "Start query, region: " << request.region << " name: " << request.tableName << std::endl;

    if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table exists already", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }

    Dto::DynamoDb::QueryResponse queryResponse;
    try {

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      queryResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb query item, name: " << request.tableName << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDb query failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return queryResponse;

  }

  Dto::DynamoDb::ScanResponse DynamoDbService::Scan(const Dto::DynamoDb::ScanRequest &request) {
    log_debug_stream(_logger) << "Start scan, region: " << request.region << " name: " << request.tableName << std::endl;

    if (!_dynamoDbDatabase.TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table exists already", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }

    Dto::DynamoDb::ScanResponse scanResponse;
    try {

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      scanResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb query item, name: " << request.tableName << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDb query failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return scanResponse;

  }

  Dto::DynamoDb::DeleteItemResponse DynamoDbService::DeleteItem(const Dto::DynamoDb::DeleteItemRequest &request) {
    log_debug_stream(_logger) << "Start creating a new DynamoDb item, region: " << request.region << " table: " << request.tableName << std::endl;

    /*if (!_dynamoDbDatabase.ItemExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb item does not exist, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb item exists already", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }*/

    Dto::DynamoDb::DeleteItemResponse deleteItemResponse;
    try {

      // Delete item in database
      _dynamoDbDatabase.DeleteItem(request.region, request.tableName, "");

      // Send request to docker container
      Dto::DynamoDb::DynamoDbResponse response = SendDynamoDbRequest(request.body, request.headers);
      deleteItemResponse = {.body=response.body, .headers=response.headers, .status=response.status};
      log_info_stream(_logger) << "DynamoDb item deleted, table: " << request.tableName << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd delete item failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return deleteItemResponse;

  }

  /*void DynamoDbService::DeleteItems(const std::string &tableName) {
    log_debug_stream(_logger) << "Deleting all items, table: " << tableName << std::endl;

    try {
      // Delete table in database
      _dynamoDbDatabase.DeleteAllTables();
      log_info_stream(_logger) << "DynamoDb tables deleted" << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd delete table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }*/

  Dto::DynamoDb::DynamoDbResponse DynamoDbService::SendDynamoDbRequest(const std::string &body, const std::map<std::string, std::string> &headers) {
    log_debug_stream(_logger) << "Sending DynamoDB container request, endpoint: " << _dockerHost << ":" << _dockerPort << std::endl;

    Poco::URI uri = Poco::URI("http://" + _dockerHost + ":" + std::to_string(_dockerPort) + "/");
    std::string path(uri.getPathAndQuery());
    log_debug_stream(_logger) << "Created URI, endpoint: " << path << std::endl;

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
    log_trace_stream(_logger) << "DynamoDB request defined, body: " + body << std::endl;

    // Copy headers
    for (const auto &header : headers) {
      request.add(header.first, header.second);
    }

    // Send request
    std::ostream &os = session.sendRequest(request);
    os << body;
    os.flush();

    // Get the response state
    Poco::Net::HTTPResponse response;
    std::istream &istream = session.receiveResponse(response);
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
      log_error_stream(_logger) << "HTTP error, status: " << response.getStatus() << " reason: " + response.getReason() << std::endl;
    }

    std::stringstream bodyStream;
    Poco::StreamCopier::copyStream(istream, bodyStream);
    log_debug_stream(_logger) << "DynamoDB request request send, status: " << response.getStatus() << std::endl;

    std::map<std::string, std::string> responseHeaders;
    for (const auto &header : response) {
      responseHeaders[header.first] = header.second;
    }
    return {.body=bodyStream.str(), .headers=responseHeaders, .status=response.getStatus()};
  }

} // namespace AwsMock::Service
