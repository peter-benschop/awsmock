//
// Created by vogje01 on 1/5/25.
//

#ifndef AWSMOCK_SERVICE_TEST_BASE_H
#define AWSMOCK_SERVICE_TEST_BASE_H

#include <awsmock/core/config/Configuration.h>
#include <awsmock/service/gateway/GatewayServer.h>

namespace AwsMock::Service {

    class TestBase {

      public:

        /**
         * @brief Starts the gateway server
         */
        void StartGateway();

        /**
         * @brief Starts the gateway server on a given port
         *
         * @param port gateway port
         */
        void StartGateway(int port);

        /**
         * @brief Stops the gateway server
         */
        void StopGateway();

        /**
         * @brief Returns the current region.
         *
         * @return current region
         */
        std::string GetRegion() { return _region; }

        /**
         * @brief Returns the current endpoint.
         *
         * @return current endpoint
         */
        std::string GetEndpoint() { return _endpoint; }

      private:

        boost::thread _thread;
        std::string _endpoint, _region;
        boost::asio::io_service _ios{10};
        std::shared_ptr<GatewayServer> _gatewayServer;
        Core::Configuration &_configuration = Core::Configuration::instance();
    };
}// namespace AwsMock::Service
#endif// AWSMOCK_SERVICE_TEST_BASE_H