
#include "awsmock/service/DynamoDbJava2Handler.h"

namespace AwsMock::Service {

  DynamoDbJava2Handler::DynamoDbJava2Handler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("DynamoDbJava2Handler")), _configuration(configuration),
                                                                                                                       _metricService(metricService), _dynamoDbService(configuration, metricService) {
  }

  void DynamoDbJava2Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "DynamoDb GET request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void DynamoDbJava2Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "DynamoDb PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void DynamoDbJava2Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    try {

      std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
      std::string payload = GetBodyAsString(request);
      std::string action = GetActionFromHeader(request, payload);

      if(action == "CreateTable") {

        Dto::DynamoDb::CreateTableRequest tableRequest;
        tableRequest.FromJson(payload);

        Dto::DynamoDb::CreateTableResponse tableResponse = _dynamoDbService.CreateTable(tableRequest);
        SendOkResponse(response,tableResponse.ToJson());

      }

    } catch (Core::ServiceException &exc) {
      _logger.error() << "DynamoDb module exception: " << exc.message() << std::endl;
      SendJsonErrorResponse("DynamoDb", response, exc);
    }
  }

  void DynamoDbJava2Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "DynamoDb DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
    DumpResponse(response);
  }

  void DynamoDbJava2Handler::handleOptions(Poco::Net::HTTPServerResponse &response) {

    log_debug_stream(_logger) << "DynamoDb OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void DynamoDbJava2Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "DynamoDb HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::string DynamoDbJava2Handler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request, const std::string &payload) {

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
