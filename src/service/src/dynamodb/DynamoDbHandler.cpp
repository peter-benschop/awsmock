
#include <awsmock/service/DynamoDbHandler.h>

namespace AwsMock::Service {

  DynamoDbHandler::DynamoDbHandler(Core::Configuration &configuration, Core::MetricService &metricService) : DynamoDbCliHandler(configuration, metricService), DynamoDbCppHandler(configuration, metricService),
                                                                                                             DynamoDbJava2Handler(configuration, metricService), _logger(Poco::Logger::get("DynamoDbHandler")), _configuration(configuration),
                                                                                                             _metricService(metricService), _dynamoDbService(configuration, metricService) {

    // Get environment
    _dynamoDbHost = _configuration.getString("awsmock.service.dynamodb.host", "localhost");
    _dynamoDbPort = 8000; //_configuration.getInt("awsmock.service.dynamodb.port", 8000);

  }

  void DynamoDbHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, [[maybe_unused]]const std::string &user) {
    _metricService.IncrementCounter("gateway_get_counter");
    log_trace_stream(_logger) << "DynamoDb GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string version, action;
      Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("DynamoDb", response, exc);
    } catch (Core::ResourceNotFoundException &exc) {
      SendXmlErrorResponse("DynamoDb", response, exc);
    }
  }

  void DynamoDbHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
    _metricService.IncrementCounter("gateway_put_counter");
    log_trace_stream(_logger) << "DynamoDb PUT request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    try {

      std::string version, action;
      Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("lambda", response, exc);
    }
  }

  void DynamoDbHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    _metricService.IncrementCounter("gateway_post_counter");
    log_trace_stream(_logger) << "DynamoDb POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      //DumpRequest(request);
      // Get the action
      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "dynamodb");

//      Poco::Net::HTTPServerRequestImpl copy = Poco::Net::HTTPServerRequestImpl(request);
      // Forward request to docker image
      //ForwardRequest(request, response, _dynamoDbHost, _dynamoDbPort);
      log_debug_stream(_logger) << "Command: " << userAgent.clientCommand << std::endl;

      switch (userAgent.type) {
      case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:
      case Dto::Common::UserAgentType::AWS_CLI: return DynamoDbCliHandler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_JAVA1: break;
      case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return DynamoDbJava2Handler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_CPP: return DynamoDbCppHandler::handlePost(request, response, region, user);

      }

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("lambda", response, exc);
    }
  }

  void DynamoDbHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    _metricService.IncrementCounter("gateway_delete_counter");
    log_trace_stream(_logger) << "DynamoDb DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {
      std::string version, action;
      Core::HttpUtils::GetVersionAction(request.getURI(), version, action);
      std::string body = GetBodyAsString(request);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("lambda", response, exc);
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
      GetVersionActionFromUri(request.getURI(), version, action);

      HeaderMap headerMap;
      headerMap["Connection"] = "Keep-alive: 300";
      headerMap["Server"] = "AmazonS3";

      SendOkResponse(response, {}, headerMap);

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("dynamodb", response, exc);
    }
  }

  void DynamoDbHandler::ForwardRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &host, int port) {

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(host, port);
    session.setReceiveTimeout(Poco::Timespan(120, 0));
    log_trace_stream(_logger) << "Forward session, host: " << host << " port: " << port << std::endl;

    // Send request with body
    Poco::StreamCopier::copyStream(request.stream(), session.sendRequest(request));
    log_trace_stream(_logger) << "Forward request send" << std::endl;

    // Get the response
    Poco::Net::HTTPResponse clientResponse;
    std::istream &is = session.receiveResponse(clientResponse);

    // Copy headers
    for (const auto &i : clientResponse) {
      response.set(i.first, i.second);
    }
    long send = Poco::StreamCopier::copyStream(is, response.send(), 1024 * 1024);
    log_trace_stream(_logger) << "Bytes send: " << send << std::endl;

    log_trace_stream(_logger) << "Backend module response send back to client" << std::endl;
  }
}
