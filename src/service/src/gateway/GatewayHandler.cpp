//
// Created by vogje01 on 5/27/24.
//

#include <awsmock/service/gateway/GatewayHandler.h>

namespace AwsMock::Service {

    const char *socket_path = "/var/run/awsmock/s3.sock";

    http::response<http::string_body> GatewayHandler::HandleGetRequest(http::request<http::string_body> &request) {

        Core::Configuration &configuration = Core::Configuration::instance();
        Core::MetricServiceTimer measure(MODULE_HTTP_TIMER, "GET");
        Core::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "GET");

        /*        ::unlink(socket_path);// Remove previous binding.

        boost::asio::io_context ctx;
        boost::asio::local::stream_protocol::endpoint endpoint(socket_path);
        boost::asio::local::stream_protocol::acceptor acceptor(ctx, endpoint);
        boost::asio::local::stream_protocol::socket socket(ctx);
        acceptor.accept(socket);

        socket.connect(endpoint);

        // Write to unix socket
        boost::asio::write(socket, boost::asio::buffer(request.body()), boost::asio::transfer_all());
        char buf[1024] = {0};

        size_t len = 0;
        std::string res{};
        while (1) {
            len += socket.read_some(boost::asio::buffer(buf + len, 2048 - len));
            std::cout << "read " << len << std::endl;
            if (buf[len] == '\0') {
                res += buf;
                break;
            }
            res += buf;
        }
        socket.close();*/
        return SendOkResponse(request);
    }

    http::response<http::string_body> GatewayHandler::HandlePutRequest(http::request<http::string_body> &request) {

        Core::MetricServiceTimer measure(MODULE_HTTP_TIMER, "PUT");
        Core::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "PUT");
    }

    http::response<http::string_body> GatewayHandler::HandlePostRequest(http::request<http::string_body> &request) {

        Core::MetricServiceTimer measure(MODULE_HTTP_TIMER, "POST");
        Core::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "POST");
    }

    http::response<http::string_body> GatewayHandler::HandleDeleteRequest(http::request<http::string_body> &request) {

        Core::MetricServiceTimer measure(MODULE_HTTP_TIMER, "DELETE");
        Core::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "DELETE");
    }

    http::response<http::string_body> GatewayHandler::HandleHeadRequest(http::request<http::string_body> &request) {

        Core::MetricServiceTimer measure(MODULE_HTTP_TIMER, "HEAD");
        Core::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "HEAD");
    }

    http::response<http::string_body> GatewayHandler::SendOkResponse(http::request<http::string_body> &request, const std::string &body) {
        // Prepare the response message
        http::response<http::string_body> response;
        response.version(request.version());
        response.result(http::status::ok);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");
        response.body() = body;
        response.prepare_payload();

        // Send the response to the client
        return response;
    }
}// namespace AwsMock::Service