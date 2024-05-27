//
// Created by vogje01 on 04/01/2023.
//

#include <awsmock/controller/Router.h>

namespace AwsMock::Manager {

    Router::Router(Service::ServerMap &serverMap) : _serverMap(serverMap) {

        // Add routes
        AddRoute("module", "AwsMock::Resource::Factory::ModuleFactory");
        log_debug << "Router initialized";
    }

    Poco::Net::HTTPRequestHandler *Router::createRequestHandler(const Poco::Net::HTTPServerRequest &request) {
        std::string service = request["Target"];
        return GetResource(service, request.getURI());
    }

    Poco::Net::HTTPRequestHandler *Router::GetResource(const std::string &service, const std::string &route) {

        Poco::URI uri = Poco::URI(route);

        // Get the resource factory index for the module
        auto factoryIndex = _routingTable.find(service);
        if (factoryIndex == _routingTable.end()) {
            log_error << "No routing found, module: " + service;
            return new AwsMock::Manager::ResourceNotFound();
        }

        // Get the resource factory for the module
        Manager::IFactory *factory = Manager::Factory::Factory::createResourceFactory(factoryIndex->second);
        if (!factory) {
            log_error << "Request handler for route: " << route << " not found";
            return new AwsMock::Manager::ResourceNotFound();
        }
        log_debug << "Found request handler for route: " << route << " factory: " << factoryIndex->second;
        return factory->createResource(_serverMap);
    }

    void Router::AddRoute(const std::string &route, const std::string &factory) {

        log_debug << "Route added, route: " << route << " factory: " << factory;
        _routingTable[route] = factory;
    }

}// namespace AwsMock::Manager
