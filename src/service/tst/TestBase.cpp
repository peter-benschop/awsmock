//
// Created by vogje01 on 1/5/25.
//

#include "TestBase.h"

namespace AwsMock::Service {

    void TestBase::StartGateway() {

        // Define endpoint. This is the endpoint of the SQS server, not the gateway
        const std::string _port = _configuration.GetValueString("awsmock.gateway.http.port");
        const std::string _host = _configuration.GetValueString("awsmock.gateway.http.host");
        const std::string _address = _configuration.GetValueString("awsmock.gateway.http.address");

        // Set test config
        _endpoint = "http://" + _host + ":" + _port;

        // Start gateway server
        _gatewayServer = std::make_shared<Service::GatewayServer>(_ios);
        _thread = boost::thread([&]() {
            boost::asio::io_service::work work(_ios);
            _ios.run();
        });
    }

    void TestBase::StartGateway(const int port) {

        // Define endpoint. This is the endpoint of the SQS server, not the gateway
        _configuration.SetValueInt("awsmock.gateway.http.port", port + 1);
        _configuration.SetValueString("awsmock.gateway.http.host", "localhost");

        // Start the gateway
        StartGateway();
    }


    void TestBase::StopGateway() {
        _ios.stop();
    }

}// namespace AwsMock::Service