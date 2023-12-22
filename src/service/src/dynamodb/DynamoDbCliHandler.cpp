
#include <awsmock/service/DynamoDbCliHandler.h>

namespace AwsMock::Service {

  DynamoDbCliHandler::DynamoDbCliHandler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("DynamoDbCliHandler")), _configuration(configuration), _metricService(metricService), _dynamoDbService(configuration,metricService) {
  }

  void DynamoDbCliHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "DynamoDb GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "DynamoDb");
      //DumpRequest(request);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("DynamoDb", response, exc);
    }
  }

  void DynamoDbCliHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "DynamoDb PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "DynamoDb");


    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("DynamoDb", response, exc);
    }
  }

  void DynamoDbCliHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "DynamoDb POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
      std::string payload = GetBodyAsString(request);
      std::string action = GetActionFromHeader(request, payload);

      if (action == "CreateTable") {

        Dto::DynamoDb::CreateTableRequest tableRequest;
        tableRequest.FromJson(payload);

        // Copy headers
        for (const auto &header : request) {
          tableRequest.headers[header.first] = header.second;
        }

        Dto::DynamoDb::CreateTableResponse tableResponse = _dynamoDbService.CreateTable(tableRequest);
        SendOkResponse(response, tableResponse.body);

      } else if (action == "ListTables") {

        Dto::DynamoDb::ListTableRequest tableRequest;
        tableRequest.FromJson(payload);

        // Copy headers
        for (const auto &header : request) {
          tableRequest.headers[header.first] = header.second;
        }

        Dto::DynamoDb::ListTableResponse tableResponse = _dynamoDbService.ListTables(tableRequest);
        SendOkResponse(response, tableResponse.body);

      } else if (action == "GetItem") {

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
      }


    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("DynamoDb", response, exc);
    }
  }

  void DynamoDbCliHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "DynamoDb DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      // Get user agent
      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "DynamoDb");

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("DynamoDb", response, exc);
    }
  }

  void DynamoDbCliHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "DynamoDb HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_debug_stream(_logger) << "DynamoDb HEAD request, bucket: " << bucket << " key: " << key << std::endl;

     /* Dto::dynamoDb::GetMetadataRequest DynamoDbRequest = {.region=region, .bucket=bucket, .key=key};
      Dto::DynamoDb::GetMetadataResponse DynamoDbResponse = _DynamoDbService.GetMetadata(DynamoDbRequest);*/

      HeaderMap headerMap;
      headerMap["Server"] = "awsmock";
      headerMap["Content-Type"] = "application/json";
//      headerMap["Last-Modified"] = Poco::DateTimeFormatter().format(DynamoDbResponse.modified, Poco::DateTimeFormat::HTTP_FORMAT);
//      headerMap["Content-Length"] = std::to_string(DynamoDbResponse.size);
//      headerMap["ETag"] = "\"" + DynamoDbResponse.md5Sum + "\"";
      headerMap["accept-ranges"] = "bytes";
      headerMap["x-amz-id-2"] = Core::StringUtils::GenerateRandomString(30);
      headerMap["x-amz-request-id"] = Poco::UUIDGenerator().createRandom().toString();
      headerMap["x-amz-version-id"] = Core::StringUtils::GenerateRandomString(30);

      // User supplied metadata
      /*for (const auto &m : DynamoDbResponse.metadata) {
        headerMap["x-amz-meta-" + m.first] = m.second;
      }*/
      SendHeadResponse(response, headerMap);

    } catch (Poco::Exception &exc) {
      log_warning_stream(_logger) << exc.message() << std::endl;
      SendXmlErrorResponse("DynamoDb", response, exc);
    } catch (std::exception &exc) {
      log_error_stream(_logger) << exc.what() << std::endl;
    }
  }

  void DynamoDbCliHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "DynamoDb OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::string DynamoDbCliHandler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request, const std::string &payload) {

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
