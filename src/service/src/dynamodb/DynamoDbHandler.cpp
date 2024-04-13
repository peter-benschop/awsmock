
#include "awsmock/service/dynamodb/DynamoDbHandler.h"

namespace AwsMock::Service {

  DynamoDbHandler::DynamoDbHandler(Core::Configuration &configuration, Core::MetricService &metricService) : DynamoDbCmdHandler(configuration, metricService), _logger(Poco::Logger::get("DynamoDbHandler")), _configuration(configuration),
                                                                                                             _metricService(metricService), _dynamoDbService(configuration, metricService) {
  }

  void DynamoDbHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, [[maybe_unused]]const std::string &user) {
    _metricService.IncrementCounter("gateway_get_counter");
    log_trace_stream(_logger) << "DynamoDb GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string version, action;
      Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("dynamodb", response, exc);
    } catch (Core::ResourceNotFoundException &exc) {
      SendXmlErrorResponse("dynamodb", response, exc);
    }
  }

  void DynamoDbHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
    _metricService.IncrementCounter("gateway_put_counter");
    log_trace_stream(_logger) << "DynamoDb PUT request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    try {

      std::string version, action;
      Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("dynamodb", response, exc);
    }
  }

  void DynamoDbHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    _metricService.IncrementCounter("gateway_post_counter");
    log_trace_stream(_logger) << "DynamoDb POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Dto::Common::DynamoDbClientCommand clientCommand;
    clientCommand.FromRequest(Dto::Common::HttpMethod::POST, request, region, user);

    DynamoDbCmdHandler::handlePost(request, response, clientCommand);
  }

  void DynamoDbHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    _metricService.IncrementCounter("gateway_delete_counter");
    log_trace_stream(_logger) << "DynamoDb DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {
      std::string version, action;
      Core::HttpUtils::GetVersionAction(request.getURI(), version, action);
      std::string body = Core::HttpUtils::GetBodyAsString(request);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("dynamodb", response, exc);
    }
  }

  void DynamoDbHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    _metricService.IncrementCounter("gateway_options_counter");
    log_trace_stream(_logger) << "DynamoDb OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void DynamoDbHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    _metricService.IncrementCounter("gateway_head_counter");
    log_trace_stream(_logger) << "DynamoDb HEAD request, address: " << request.clientAddress().toString() << std::endl;

    try {

      std::string version, action;
      Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

      HeaderMap headerMap;
      headerMap["Connection"] = "Keep-alive: 300";
      headerMap["Server"] = "AmazonS3";

      SendOkResponse(response, {}, headerMap);

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("dynamodb", response, exc);
    }
  }
}
