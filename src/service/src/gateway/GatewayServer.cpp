//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/gateway/GatewayServer.h>

namespace AwsMock::Service {
    GatewayServer::GatewayServer(boost::asio::io_service &ios) : AbstractServer("gateway"), _ios(ios) {
        // Get HTTP configuration values
        Core::YamlConfiguration &configuration = Core::YamlConfiguration::instance();
        _port = configuration.GetValueInt("awsmock.gateway.http.port");
        _host = configuration.GetValueString("awsmock.gateway.http.host");
        _address = configuration.GetValueString("awsmock.gateway.http.address");
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
} // namespace AwsMock::Service
