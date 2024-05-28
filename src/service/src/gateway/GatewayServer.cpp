//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/gateway/GatewayServer.h>

namespace AwsMock::Service {

    GatewayServer::GatewayServer(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractServer(configuration, "gateway"), _configuration(configuration), _metricService(metricService), _running(false) {

        // Get HTTP configuration values
        _port = _configuration.getInt("awsmock.service.gateway.http.port", GATEWAY_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.gateway.http.host", GATEWAY_DEFAULT_HOST);
        _address = _configuration.getString("awsmock.service.gateway.http.host", GATEWAY_DEFAULT_ADDRESS);
        _maxQueueLength = _configuration.getInt("awsmock.service.gateway.http.max.queue", GATEWAY_MAX_QUEUE);
        _maxThreads = _configuration.getInt("awsmock.service.gateway.http.max.threads", GATEWAY_MAX_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.gateway.http.timeout", GATEWAY_TIMEOUT);

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
        log_debug << "Gateway worker period: " << _period;

        // Create environment
        _region = _configuration.getString("awsmock.region");
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

        int threads = Core::Configuration::instance().getInt("awsmock.service.gateway.http.max.threads");
        std::string hostAddress = Core::Configuration::instance().getString("awsmock.service.gateway.http.address");
        unsigned short port = Core::Configuration::instance().getInt("awsmock.service.gateway.http.port");

        // The io_context is required for all I/O
        boost::asio::io_context ioc{threads};

        // Create and launch a listening port
        auto address = boost::asio::ip::make_address(hostAddress);
        std::make_shared<GatewayListener>(ioc, boost::asio::ip::tcp::endpoint{address, port})->Run();

        // Run the I/O service on the requested number of threads
        _threads.reserve(threads - 1);
        for (auto i = threads - 1; i > 0; --i)
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
