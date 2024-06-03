//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/gateway/GatewayServer.h>

namespace AwsMock::Service {

    GatewayServer::GatewayServer() : AbstractServer("gateway") {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.gateway.http.port", GATEWAY_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.gateway.http.host", GATEWAY_DEFAULT_HOST);
        _address = configuration.getString("awsmock.service.gateway.http.address", GATEWAY_DEFAULT_ADDRESS);
        _maxQueueLength = configuration.getInt("awsmock.service.gateway.http.max.queue", GATEWAY_MAX_QUEUE);
        _maxThreads = configuration.getInt("awsmock.service.gateway.http.max.threads", GATEWAY_MAX_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.gateway.http.timeout", GATEWAY_TIMEOUT);

        // Sleeping period
        _period = configuration.getInt("awsmock.worker.gateway.period", 10000);
        log_debug << "Gateway worker period: " << _period;

        // Create environment
        _region = configuration.getString("awsmock.region");
        log_debug << "GatewayServer initialized";
    }

    void GatewayServer::Initialize() {

        // Check module active
        if (!IsActive("gateway")) {
            log_info << "Gateway module inactive";
            return;
        }
        log_info << "Gateway server starting";

        // Start HTTP manager
        //StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new GatewayRouter(_configuration, _metricService));
    }

    void GatewayServer::Run() {

        // Set running
        SetRunning();
        
        // The io_context is required for all I/O
        boost::asio::io_context ioc{_maxThreads};

        // Create and launch a listening port
        auto address = ip::make_address(_address);
        std::make_shared<GatewayListener>(ioc, ip::tcp::endpoint{address, _port})->Run();

        // Run the I/O service on the requested number of threads
        _threads.reserve(_maxThreads - 1);
        for (auto i = _maxThreads - 1; i > 0; --i)
            _threads.emplace_back(
                    [&ioc] {
                        ioc.run();
                    });
        ioc.run();
    }

    void GatewayServer::Shutdown() {
        StopHttpServer();
    }

}// namespace AwsMock::Service
