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

    // DynamoDB docker host, port
    _dockerHost = "localhost";
    _dockerPort = 8000;
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

      createTableResponse.body = SendDynamoDbRequest(request.body, request.headers);

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd create table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return createTableResponse;

  }

  Dto::DynamoDb::DeleteTableResponse DynamoDbService::DeleteTable(const Dto::DynamoDb::DeleteTableRequest &request) {
    log_debug_stream(_logger) << "Start creating a new DynamoDb table, region: " << request.region << " name: " << request.tableName << std::endl;

    if (!_dynamoDbDatabase->TableExists(request.region, request.tableName)) {
      log_warning_stream(_logger) << "DynamoDb table does not exist, region: " << request.region << " name: " << request.tableName << std::endl;
      throw Core::ServiceException("DynamoDb table exists already", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::DynamoDb::DeleteTableResponse deleteTableResponse;
    try {

      // Delete table in database
      _dynamoDbDatabase->DeleteTable(request.tableName);

      //deleteTableResponse = {.region=table.region, .tableName=table.name};
      log_info_stream(_logger) << "DynamoDb table created, name: " << request.tableName << std::endl;

      std::string body = SendDynamoDbRequest(request.body, request.headers);

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "DynamoDbd create table failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    return deleteTableResponse;

  }

  std::string DynamoDbService::SendDynamoDbRequest(const std::string &body, const std::map<std::string, std::string>& headers) {
    log_debug_stream(_logger) << "Sending DynamoDB request, endpoint: " << _dockerHost << ":" << _dockerPort << std::endl;

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
      throw Core::ServiceException("Send to docker container failed, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason());
    }

    std::stringstream bodyStream;
    Poco::StreamCopier::copyStream(istream, bodyStream);
    log_debug_stream(_logger) << "DynamoDB request request send, state: " << response.getStatus() << std::endl;

    return bodyStream.str();
  }

} // namespace AwsMock::Service
