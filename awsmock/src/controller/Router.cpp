//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/controller/Router.h"

namespace AwsMock {

    Router::Router() : _logger(Poco::Logger::get("Router")) {
    }

    void Router::Initialize(Configuration *configuration, Core::MetricService *metricService) {
        _configuration = configuration;
        _metricService = metricService;

        Core::Logger::SetDefaultConsoleLogger("Router");

        AddRoute("s3", "AwsMock::Resource::Factory::S3Factory");
        AddRoute("sqs", "AwsMock::Resource::Factory::SQSFactory");
        AddRoute("sns", "AwsMock::Resource::Factory::SNSFactory");
    }

    Poco::Net::HTTPRequestHandler* Router::createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
        std::string scheme;
        std::string authInfo;
        request.getCredentials(scheme, authInfo);
        poco_debug(_logger, "Schema: " + scheme + " Authorization: " + authInfo);
        poco_debug(_logger, "URI: " + request.getURI() + " Method: " + request.getMethod());

        std::string service = GetService(authInfo);

        return GetResource(service, request.getURI());
    }

    Poco::Net::HTTPRequestHandler *Router::GetResource(const std::string &service, const std::string &route) {

        Poco::URI uri = Poco::URI(route);

        auto factoryIndex = _routingTable.find(service);
        if (factoryIndex == _routingTable.end()) {
            return new AwsMock::ResourceNotFound();
        }

        poco_debug(_logger, "Found request handler for route: " + route);

        Resource::Factory::IFactory *factory = Resource::Factory::Factory::createResourceFactory(factoryIndex->second);

        return factory->createResource(*_configuration, *_metricService);
    }

    void Router::AddRoute(const std::string &route, const std::string &factory) {
        poco_debug(_logger, "Route added, route: " + route + " factory: " + factory);
        _routingTable[route] = factory;
    }

    std::string Router::GetService(const std::string &authorization) {
        Poco::RegularExpression::MatchVec posVec;

        Poco::RegularExpression pattern(R"(Credential=([a-zA-Z]+)\/[0-9]{8}\/([a-zA-Z0-9\-]+)\/([a-zA-Z0-9]+)\/aws4_request,.*$)");
        if(!pattern.match(authorization, 0, posVec)) {
            throw Core::ResourceNotFoundException("Could not extract service");
        }
        std::string user = authorization.substr(posVec[1].offset, posVec[1].length);
        std::string region = authorization.substr(posVec[2].offset, posVec[2].length);
        std::string service = authorization.substr(posVec[3].offset, posVec[3].length);
        poco_debug(_logger, "Found user: " + user + " region: " + region + " service: " + service);
        return service;
    }
}

// add support to Poco ApacheConnector
POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)
        POCO_EXPORT_CLASS(AwsMock::Router)
POCO_END_MANIFEST