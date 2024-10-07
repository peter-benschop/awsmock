//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/gateway/GatewayServer.h>

namespace AwsMock::Service {

    GatewayServer::GatewayServer(boost::asio::thread_pool &pool) : AbstractServer("gateway"), _pool(pool) {

        // Get HTTP configuration values
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.gateway.http.port", GATEWAY_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.gateway.http.host", GATEWAY_DEFAULT_HOST);
        _address = configuration.getString("awsmock.service.gateway.http.address", GATEWAY_DEFAULT_ADDRESS);
        _maxQueueLength = configuration.getInt("awsmock.service.gateway.http.max.queue", GATEWAY_MAX_QUEUE);
        _maxThreads = configuration.getInt("awsmock.service.gateway.http.max.threads", GATEWAY_MAX_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.gateway.http.timeout", GATEWAY_TIMEOUT);
        log_debug << "Gateway server initialized";

        boost::thread(&GatewayServer::Run, this).detach();
        log_debug << "Gateway server started";
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

        // Create and launch a listening port
        auto address = ip::make_address(_address);
        std::make_shared<GatewayListener>(ioc, ip::tcp::endpoint{address, _port})->Run();

        for (auto i = 0; i < _maxThreads; i++) {
            _threadGroup.create_thread([ObjectPtr = &ioc] { return ObjectPtr->run(); });
        }

        log_info << "Gateway service started";
        ioc.run();
        log_info << "Gateway stopped";
    }

    void GatewayServer::Shutdown() {
        log_info << "Initialize gateway shutdown";
        ioc.stop();
        _threadGroup.interrupt_all();
        _threadGroup.join_all();
        log_info << "Gateway service stopped";
    }

}// namespace AwsMock::Service
