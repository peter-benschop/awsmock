//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/service/gateway/GatewayRouter.h"

namespace AwsMock::Service {

  GatewayRouter::GatewayRouter(Core::Configuration &configuration, Core::MetricService &metricService) : _logger(Poco::Logger::get("GatewayRouter")), _configuration(configuration), _metricService(metricService) {

    // Get the ports
    int s3Port = _configuration.getInt("awsmock.service.s3.port", 9500);
    int sqsPort = _configuration.getInt("awsmock.service.sqs.port", 9501);
    int snsPort = _configuration.getInt("awsmock.service.sns.port", 9502);
    int lambdaPort = _configuration.getInt("awsmock.service.lambda.port", 9503);
    int transferPort = _configuration.getInt("awsmock.service.transfer.port", 9504);
    int cognitoPort = _configuration.getInt("awsmock.service.cognito.port", 9505);
    int dynamodbPort = _configuration.getInt("awsmock.service.dynamodb.port", 9506);
    int secretsManagerPort = _configuration.getInt("awsmock.service.secretsmanager.port", 9507);

    // Add routes
    _routingTable["s3"] = new GatewayRoute("s3", "localhost", s3Port, new Service::S3Handler(configuration, metricService));
    _routingTable["s3api"] = new GatewayRoute("s3", "localhost", s3Port, new Service::S3Handler(configuration, metricService));
    _routingTable["sqs"] = new GatewayRoute("sqs", "localhost", sqsPort, new Service::SQSHandler(configuration, metricService));
    _routingTable["sns"] = new GatewayRoute("sns", "localhost", snsPort, new Service::SNSHandler(configuration, metricService));
    _routingTable["lambda"] = new GatewayRoute("lambda", "localhost", lambdaPort, new Service::LambdaHandler(configuration, metricService));
    _routingTable["transfer"] = new GatewayRoute("transfer", "localhost", transferPort, new Service::TransferHandler(configuration, metricService));
    _routingTable["cognito-idp"] = new GatewayRoute("cognito", "localhost", cognitoPort, new Service::CognitoHandler(configuration, metricService));
    _routingTable["cognito-identity"] = new GatewayRoute("cognito", "localhost", cognitoPort, new Service::CognitoHandler(configuration, metricService));
    _routingTable["dynamodb"] = new GatewayRoute("dynamodb", "localhost", dynamodbPort, new Service::DynamoDbHandler(configuration, metricService));
    _routingTable["secretsmanager"] = new GatewayRoute("secretsmanager", "localhost", secretsManagerPort, new Service::SecretsManagerHandler(configuration, metricService));
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
    std::string host = _routingTable[service]->_host;
    int port = _routingTable[service]->_port;
    c(_logger) << "Found request handler for route: " << route << " endpoint: " << host << ":" << port << std::endl;
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
