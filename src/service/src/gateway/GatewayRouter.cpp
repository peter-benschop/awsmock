//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/service/gateway/GatewayRouter.h>

namespace AwsMock::Service {

  GatewayRouter::GatewayRouter(Core::Configuration &configuration, Core::MetricService &metricService) : _logger(Poco::Logger::get("GatewayRouter")), _configuration(configuration), _metricService(metricService) {

    // Add routes
    _routingTable["s3"] = {._name="s3", ._handlerType=HandlerType::S3};
    _routingTable["s3api"] = {._name="s3", ._handlerType=HandlerType::S3};
    _routingTable["sqs"] = {._name="sqs", ._handlerType=HandlerType::SQS};
    _routingTable["sns"] = {._name="sns", ._handlerType=HandlerType::SNS};
    _routingTable["lambda"] = {._name="lambda", ._handlerType=HandlerType::LAMBDA};
    _routingTable["transfer"] = {._name="transfer", ._handlerType=HandlerType::TRANSFER};
    _routingTable["cognito-idp"] = {._name="cognito", ._handlerType=HandlerType::COGNITO};
    _routingTable["cognito-identity"] = {._name="cognito", ._handlerType=HandlerType::COGNITO};
    _routingTable["dynamodb"] = {._name="dynamodb", ._handlerType=HandlerType::DYNAMODB};
    _routingTable["secretsmanager"] = {._name="secretsmanager", ._handlerType=HandlerType::SECRETS_MANAGER};
    log_debug_stream(_logger) << "Gateway router initialized" << std::endl;
  }

  GatewayRouter::~GatewayRouter() {
    serverStopped.enable();
  }

  Poco::Net::HTTPRequestHandler *GatewayRouter::createRequestHandler(const Poco::Net::HTTPServerRequest &request) {

    // Get the authorization header
    std::string scheme, authInfo;
    request.getCredentials(scheme, authInfo);
    log_trace_stream(_logger) << "Schema: " << scheme << " Authorization: " << authInfo << "URI: " << request.getURI() << " Method: " + request.getMethod() << std::endl;

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
    log_trace_stream(_logger) << "Found request handler for route: " << route << std::endl;
    return new Service::GatewayHandler(_configuration, _metricService, _routingTable[service]);
  }

  std::string GatewayRouter::GetService(const std::string &authorization) {

    Poco::RegularExpression::MatchVec posVec;
    Poco::RegularExpression pattern(R"(Credential=[a-zA-Z0-9]+\/[0-9]{8}\/[a-zA-Z0-9\-]+\/([a-zA-Z0-9\-]+)\/aws4_request,.*$)");
    if (!pattern.match(authorization, 0, posVec)) {
      log_error_stream(_logger) << "Could not extract module, authorization: " << authorization << std::endl;
      throw Core::ResourceNotFoundException("Could not extract module", Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND);
    }

    std::string service = authorization.substr(posVec[1].offset, posVec[1].length);
    log_trace_stream(_logger) << "Found module: " << service << std::endl;

    return service;
  }

} // namespace AwsMock::Service
