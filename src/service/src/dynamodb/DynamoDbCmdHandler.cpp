
#include <awsmock/service/DynamoDbCmdHandler.h>

namespace AwsMock::Service {

  DynamoDbCmdHandler::DynamoDbCmdHandler(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractHandler(), _logger(Poco::Logger::get("DynamoDbCmdHandler")), _configuration(configuration), _metricService(metricService), _dynamoDbService(configuration, metricService) {
  }

  void DynamoDbCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::DynamoDbClientCommand &clientCommand) {
    log_debug_stream(_logger) << "DynamoDb POST request, URI: " << request.getURI() << " region: " << clientCommand.region << " user: " << clientCommand.user << " command: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command) << std::endl;

    try {

      std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
      std::string payload = GetBodyAsString(request);
      std::string action = GetActionFromHeader(request, payload);

      switch (clientCommand.command) {

        case Dto::Common::DynamoDbCommandType::CREATE_TABLE: {

          Dto::DynamoDb::CreateTableRequest tableRequest;
          tableRequest.FromJson(payload);
          tableRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            tableRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::CreateTableResponse tableResponse = _dynamoDbService.CreateTable(tableRequest);

          if(tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, tableResponse.body, tableResponse.headers);
          } else {
            SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
          }
          log_info_stream(_logger) << "Table created, name: " << tableRequest.tableName << std::endl;

          break;
        }

        case Dto::Common::DynamoDbCommandType::LIST_TABLES: {

          Dto::DynamoDb::ListTableRequest tableRequest;
          tableRequest.FromJson(payload);
          tableRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            tableRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::ListTableResponse tableResponse = _dynamoDbService.ListTables(tableRequest);
          if(tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, tableResponse.body, tableResponse.headers);
          } else {
            SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
          }
          log_info_stream(_logger) << "Table listed, region: " << tableRequest.region << std::endl;

          break;
        }

        case Dto::Common::DynamoDbCommandType::DESCRIBE_TABLE: {

          Dto::DynamoDb::DescribeTableRequest tableRequest;
          tableRequest.FromJson(payload);
          tableRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            tableRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::DescribeTableResponse tableResponse = _dynamoDbService.DescribeTable(tableRequest);
          if(tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, tableResponse.body, tableResponse.headers);
          } else {
            SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
          }

          break;
        }

        case Dto::Common::DynamoDbCommandType::DELETE_TABLE: {

          Dto::DynamoDb::DeleteTableRequest tableRequest;
          tableRequest.FromJson(payload);
          tableRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            tableRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::DeleteTableResponse tableResponse = _dynamoDbService.DeleteTable(tableRequest);
          if(tableResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, tableResponse.body, tableResponse.headers);
          } else {
            SendErrorResponse(response, tableResponse.body, tableResponse.headers, tableResponse.status);
          }

          break;
        }

        case Dto::Common::DynamoDbCommandType::GET_ITEM: {

          Dto::DynamoDb::GetItemRequest itemRequest;
          itemRequest.FromJson(payload);
          itemRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            itemRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::GetItemResponse itemResponse = _dynamoDbService.GetItem(itemRequest);
          if(itemResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, itemResponse.body, itemResponse.headers);
          } else {
            SendErrorResponse(response, itemResponse.body, itemResponse.headers, itemResponse.status);
          }

          break;
        }

        case Dto::Common::DynamoDbCommandType::PUT_ITEM: {

          Dto::DynamoDb::PutItemRequest itemRequest;
          itemRequest.FromJson(payload);
          itemRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            itemRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::PutItemResponse itemResponse = _dynamoDbService.PutItem(itemRequest);
          if(itemResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, itemResponse.body, itemResponse.headers);
          } else {
            SendErrorResponse(response, itemResponse.body, itemResponse.headers, itemResponse.status);
          }

          break;
        }

        case Dto::Common::DynamoDbCommandType::QUERY: {

          Dto::DynamoDb::QueryRequest queryRequest;
          queryRequest.FromJson(payload);
          queryRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            queryRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::QueryResponse queryResponse = _dynamoDbService.Query(queryRequest);
          if(queryResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, queryResponse.body, queryResponse.headers);
          } else {
            SendErrorResponse(response, queryResponse.body, queryResponse.headers, queryResponse.status);
          }

          break;
        }

        case Dto::Common::DynamoDbCommandType::SCAN: {

          Dto::DynamoDb::ScanRequest scanRequest;
          scanRequest.FromJson(payload);
          scanRequest.region = clientCommand.region;

          // Copy headers
          for (const auto &header : request) {
            scanRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::ScanResponse scanResponse = _dynamoDbService.Scan(scanRequest);
          if(scanResponse.status == Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK) {
            SendOkResponse(response, scanResponse.body, scanResponse.headers);
          } else {
            SendErrorResponse(response, scanResponse.body, scanResponse.headers, scanResponse.status);
          }

          break;
        }

        case Dto::Common::DynamoDbCommandType::UNKNOWN: {
          log_error_stream(_logger) << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command) << std::endl;
          throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::DynamoDbCommandTypeToString(clientCommand.command));
        }

        default: {
          log_error_stream(_logger) << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command) << std::endl;
          SendOkResponse(response);
        }
      }

    } catch (Poco::Exception &exc) {
      SendJsonErrorResponse("DynamoDb", response, exc);
    }
  }

  std::string DynamoDbCmdHandler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request, const std::string &payload) {

    std::string action;
    std::string contentType = request["Content-Type"];
    if (Core::StringUtils::ContainsIgnoreCase(contentType, "application/x-www-form-urlencoded")) {

      action = Core::HttpUtils::GetQueryParameterValueByName(payload, "Action");

    } else if (Core::StringUtils::ContainsIgnoreCase(contentType, "application/x-amz-json-1.0")) {

      std::string headerValue = request["X-Amz-Target"];
      action = Core::StringUtils::Split(headerValue, '.')[1];

    }
    return action;
  }
}
