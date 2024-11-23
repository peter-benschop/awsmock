//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/gateway/GatewayServer.h>

namespace AwsMock::Service {

    GatewayServer::GatewayServer(boost::asio::io_service &ios) : AbstractServer("gateway"), _ios(ios) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.gateway.http.port", GATEWAY_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.gateway.http.host", GATEWAY_DEFAULT_HOST);
        _address = configuration.getString("awsmock.service.gateway.http.address", GATEWAY_DEFAULT_ADDRESS);
        log_debug << "Gateway server initialized";

        // Check module active
        if (!IsActive("gateway")) {
            log_info << "Gateway module inactive";
            return;
        }

        // Set running
        SetRunning();

        // Create and launch a listening port
        const auto address = ip::make_address(_address);
        std::make_shared<GatewayListener>(_ios, ip::tcp::endpoint{address, _port})->Run();
        log_debug << "Gateway server started, port: " << _port;
    }

}// namespace AwsMock::Service
