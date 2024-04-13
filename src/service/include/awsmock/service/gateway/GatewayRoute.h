//
// Created by vogje01 on 4/13/24.
//

#ifndef AWSMOCK_SERVICE_GATEWAY_GATEWAY_ROUTE_H
#define AWSMOCK_SERVICE_GATEWAY_GATEWAY_ROUTE_H

// C++ standard includes
#include <map>
#include <string>

// AwsMock includes
#include <awsmock/service/common/AbstractHandler.h>

namespace AwsMock::Service {

  struct GatewayRoute {

    /**
     * Service name
     */
    std::string _name;

    /**
     * Service host
     */
    std::string _host;

    /**
     * Service port
     */
    int _port;

    /**
     * Service handler
     */
    AbstractHandler *_handler;

    GatewayRoute(std::string name, std::string host, int port, AbstractHandler *handler) : _name(std::move(name)), _host(std::move(host)), _port(port), _handler(handler) {}
  };

} // namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_GATEWAY_GATEWAY_ROUTE_H
