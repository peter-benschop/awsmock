
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
          SendOkResponse(response, tableResponse.body);
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
          SendOkResponse(response, tableResponse.body, tableResponse.headers);
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
          SendOkResponse(response, tableResponse.body, tableResponse.headers);
          break;
        }

        case Dto::Common::DynamoDbCommandType::DELETE_TABLE: {

          Dto::DynamoDb::DeleteTableRequest tableRequest;
          tableRequest.FromJson(payload);

          // Copy headers
          for (const auto &header : request) {
            tableRequest.headers[header.first] = header.second;
          }

          Dto::DynamoDb::DeleteTableResponse tableResponse = _dynamoDbService.DeleteTable(tableRequest);
          SendOkResponse(response, tableResponse.body, tableResponse.headers);
          break;
        }

        case Dto::Common::DynamoDbCommandType::UNKNOWN: {
          log_error_stream(_logger) << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command) << std::endl;
          throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::DynamoDbCommandTypeToString(clientCommand.command));
        }

        default:log_error_stream(_logger) << "Bad request, method: POST clientCommand: " << Dto::Common::DynamoDbCommandTypeToString(clientCommand.command) << std::endl;
          SendOkResponse(response);
      }
/*
      if (action == "GetItem") {

        Dto::DynamoDb::GetItemRequest itemRequest;
        itemRequest.FromJson(payload);

        // Copy headers
        for (const auto &header : request) {
          itemRequest.headers[header.first] = header.second;
        }

        Dto::DynamoDb::GetItemResponse itemResponse = _dynamoDbService.GetItem(itemRequest);
        SendOkResponse(response, itemResponse.body);

      } else if (action == "PutItem") {

        Dto::DynamoDb::PutItemRequest itemRequest;
        itemRequest.FromJson(payload);

        // Copy headers
        for (const auto &header : request) {
          itemRequest.headers[header.first] = header.second;
        }

        Dto::DynamoDb::PutItemResponse itemResponse = _dynamoDbService.PutItem(itemRequest);
        SendOkResponse(response, itemResponse.body);

      } else if (action == "Query") {

        Dto::DynamoDb::QueryRequest queryRequest;
        queryRequest.FromJson(payload);

        // Copy headers
        for (const auto &header : request) {
          queryRequest.headers[header.first] = header.second;
        }

        Dto::DynamoDb::QueryResponse queryResponse = _dynamoDbService.Query(queryRequest);
        SendOkResponse(response, queryResponse.body);

      } else if (action == "DeleteTable") {

        Dto::DynamoDb::DeleteTableRequest tableRequest;
        tableRequest.FromJson(payload);

        // Copy headers
        for (const auto &header : request) {
          tableRequest.headers[header.first] = header.second;
        }

        Dto::DynamoDb::DeleteTableResponse tableResponse = _dynamoDbService.DeleteTable(tableRequest);
        SendOkResponse(response, tableResponse.body);
      }*/

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("DynamoDb", response, exc);
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
