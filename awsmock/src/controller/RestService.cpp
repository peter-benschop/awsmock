//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/controller/RestService.h"

namespace AwsMock {

    RestService::RestService(Core::Configuration &configuration)
        : _logger(Poco::Logger::get("RestService")), _configuration(configuration), _port(DEFAULT_PORT), _host(DEFAULT_HOST) {

        Core::Logger::SetDefaultConsoleLogger("RestService");

        _port = _configuration.getInt("awsmock.rest.port", DEFAULT_PORT);
        _host = _configuration.getString("awsmock.rest.host", DEFAULT_HOST);
    }

    RestService::~RestService() {
        httpServer->stop();
        delete _router;
    }

    void RestService::setPort(int port) {
        _port = port;
    }

    void RestService::setRouter(Poco::Net::HTTPRequestHandlerFactory *router) {
        _router = router;
    }

    Poco::Net::HTTPRequestHandlerFactory *RestService::getRouter() {
        return _router;
    }

    void RestService::start() {
        auto *httpServerParams = new Poco::Net::HTTPServerParams();

        httpServerParams->setMaxQueued(250);
        httpServerParams->setMaxThreads(50);

        httpServer = new Poco::Net::HTTPServer(getRouter(), Poco::Net::ServerSocket(Poco::UInt16(_port)), httpServerParams);

        httpServer->start();
        poco_information(_logger, "Restful Web Service started, endpoint: http://" + _host + ":" + std::to_string(_port));
    }

    void RestService::start(Poco::Net::HTTPRequestHandlerFactory *router, int port) {
        setPort(port);
        setRouter(router);
        start();
    }
}
