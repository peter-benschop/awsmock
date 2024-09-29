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
        log_debug << "GatewayServer initialized";
    }

    void GatewayServer::Initialize() {

        // Check module active
        if (!Database::ModuleDatabase::instance().IsActive("gateway")) {
            log_info << "Gateway module inactive";
            return;
        }
        log_info << "Gateway server starting";
    }

    void GatewayServer::Start() {
        boost::thread(&GatewayServer::Run, this).detach();
    }

    void GatewayServer::Run() {

        // Set running
        Database::ModuleDatabase::instance().SetState("gateway", Database::Entity::Module::ModuleState::RUNNING);

        // The io_context is required for all I/O
        boost::asio::io_context ioc{_maxThreads};

        // Create and launch a listening port
        auto address = ip::make_address(_address);
        std::make_shared<GatewayListener>(ioc, ip::tcp::endpoint{address, _port})->Run();

        // Capture SIGINT and SIGTERM to perform a clean shutdown
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait(
                [&](boost::beast::error_code const &, int) {
                    // Stop the `io_context`. This will cause `run()` to return immediately, eventually
                    // destroying the `io_context` and all the sockets in it.
                    log_info << "Manager stopped on signal";
                    ioc.stop();
                });

        boost::thread_group threadGroup;
        for (auto i = 0; i < _maxThreads; i++) {
            threadGroup.create_thread(
                    [ObjectPtr = &ioc] { return ObjectPtr->run(); });
        }
        threadGroup.join_all();
    }

    void GatewayServer::Shutdown() {
        /* _ioc.stop();
        for (auto &t: _threads) {
            t.join();
        }*/
    }

}// namespace AwsMock::Service
