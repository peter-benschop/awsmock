//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/GatewayRouter.h>

namespace AwsMock::Service {

  GatewayRouter::GatewayRouter(Core::Configuration &configuration, Core::MetricService &metricService) : _logger(Poco::Logger::get("Router")), _configuration(configuration), _metricService(metricService) {

    // Add routes
    _routingTable["s3"] = {.name="s3", .host="localhost", .port=9500};
    _routingTable["s3api"] = {.name="s3", .host="localhost", .port=9500};
    _routingTable["sqs"] = {.name="sqs", .host="localhost", .port=9501};
    _routingTable["sns"] = {.name="sns", .host="localhost", .port=9502};
    _routingTable["lambda"] = {.name="lambda", .host="localhost", .port=9503};
    _routingTable["transfer"] = {.name="transfer", .host="localhost", .port=9504};
    _routingTable["cognito-idp"] = {.name="cognito", .host="localhost", .port=9505};
    log_debug_stream(_logger) << "Gateway router initialized" << std::endl;
  }

  GatewayRouter::~GatewayRouter() {
    serverStopped.enable();
  }

  Poco::Net::HTTPRequestHandler *GatewayRouter::createRequestHandler(const Poco::Net::HTTPServerRequest &request) {

    // Get the authorization header
    std::string scheme, authInfo;
    request.getCredentials(scheme, authInfo);
    log_debug_stream(_logger) << "Schema: " << scheme << " Authorization: " << authInfo << "URI: " << request.getURI() << " Method: " + request.getMethod() << std::endl;

    // Get the module from the request authorization header. Currently, no credentials checks are made.
    std::string service = GetService(authInfo);

    return GetResource(service, request.getURI());
  }

  Poco::Net::HTTPRequestHandler *GatewayRouter::GetResource(const std::string &service, const std::string &route) {

    Poco::URI uri = Poco::URI(route);

    // Get the resource factory index for the module
    auto factoryIndex = _routingTable.find(service);
    if (factoryIndex == _routingTable.end()) {
      log_error_stream(_logger) << "No routing found, module: " + service << std::endl;
      //return new AwsMock::ResourceNotFound();
    }

    // Get the resource factory for the module
    std::string host = _routingTable[service].host;
    int port = _routingTable[service].port;
    log_debug_stream(_logger) << "Found request handler for route: " << route << " endpoint: " << host << ":" << port << std::endl;
    return new Service::GatewayHandler(_configuration, _metricService, host, port);
  }

  std::string GatewayRouter::GetService(const std::string &authorization) {

    Poco::RegularExpression::MatchVec posVec;
    Poco::RegularExpression pattern(R"(Credential=[a-zA-Z0-9]+\/[0-9]{8}\/[a-zA-Z0-9\-]+\/([a-zA-Z0-9\-]+)\/aws4_request,.*$)");
    if (!pattern.match(authorization, 0, posVec)) {
      log_error_stream(_logger) << "Could not extract module, authorization: " << authorization << std::endl;
      throw Core::ResourceNotFoundException("Could not extract module", Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND);
    }

    std::string service = authorization.substr(posVec[1].offset, posVec[1].length);
    log_debug_stream(_logger) << "Found module: " << service << std::endl;

    return service;
  }

} // namespace AwsMock::Service
