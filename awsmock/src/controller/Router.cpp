//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/controller/Router.h"

namespace AwsMock::Controller {

    Router::Router(Configuration &configuration, Core::MetricService &metricService)
        : _logger(Poco::Logger::get("Router")), _configuration(configuration), _metricService(metricService) {

        // Add routes
        AddRoute("s3", "AwsMock::Resource::Factory::S3Factory");
        AddRoute("s3api", "AwsMock::Resource::Factory::S3Factory");
        AddRoute("sqs", "AwsMock::Resource::Factory::SQSFactory");
        AddRoute("sns", "AwsMock::Resource::Factory::SNSFactory");
        AddRoute("lambda", "AwsMock::Resource::Factory::LambdaFactory");
        AddRoute("transfer", "AwsMock::Resource::Factory::TransferFactory");
        log_debug_stream(_logger) << "Router initialized" << std::endl;
    }

    Poco::Net::HTTPRequestHandler *Router::createRequestHandler(const Poco::Net::HTTPServerRequest &request) {

        // Get the authorization header
        std::string scheme, authInfo;
        request.getCredentials(scheme, authInfo);
        log_debug_stream(_logger) << "Schema: " << scheme << " Authorization: " << authInfo << "URI: " << request.getURI() << " Method: " + request.getMethod() << std::endl;

        // Get the service from the request authorization header. Currently, no credentials checks are made.
        std::string service = GetService(authInfo);

        return GetResource(service, request.getURI());
    }

    Poco::Net::HTTPRequestHandler *Router::GetResource(const std::string &service, const std::string &route) {

        Poco::URI uri = Poco::URI(route);

        // Get the resource factory index for the service
        auto factoryIndex = _routingTable.find(service);
        if (factoryIndex == _routingTable.end()) {
            log_error_stream(_logger) << "No routing found, service: " + service << std::endl;
            return new AwsMock::ResourceNotFound();
        }

        // Get the resource factory for the service
        Resource::Factory::IFactory *factory = Resource::Factory::Factory::createResourceFactory(factoryIndex->second);
        if (!factory) {
            log_error_stream(_logger) << "Request handler for route: " << route << " not found" << std::endl;
            return new AwsMock::ResourceNotFound();
        }
        log_debug_stream(_logger) << "Found request handler for route: " << route << " factory: " << factoryIndex->second << std::endl;
        return factory->createResource(_configuration, _metricService);
    }

    void Router::AddRoute(const std::string &route, const std::string &factory) {

        log_debug_stream(_logger) << "Route added, route: " << route << " factory: " << factory << std::endl;
        _routingTable[route] = factory;
    }

    std::string Router::GetService(const std::string &authorization) {

        Poco::RegularExpression::MatchVec posVec;
        Poco::RegularExpression pattern(R"(Credential=[a-zA-Z0-9]+\/[0-9]{8}\/[a-zA-Z0-9\-]+\/([a-zA-Z0-9]+)\/aws4_request,.*$)");
        if (!pattern.match(authorization, 0, posVec)) {
            log_error_stream(_logger) << "Could not extract service, authorization: " << authorization << std::endl;
            throw Core::ResourceNotFoundException("Could not extract service");
        }

        std::string service = authorization.substr(posVec[1].offset, posVec[1].length);
        log_debug_stream(_logger) << "Found service: " << service << std::endl;

        return service;
    }
} // namespace AwsMock::Controller
