//
// Created by vogje01 on 5/28/24.
//

#include <awsmock/core/DomainSocket.h>

namespace AwsMock::Core {

    DomainSocketResult DomainSocket::SendJson(http::verb method, const std::string &path, const std::string &body, const std::map<std::string, std::string> &headers) {

        boost::system::error_code ec;

        boost::asio::io_context ctx;
        boost::asio::local::stream_protocol::endpoint endpoint(_path);
        boost::asio::local::stream_protocol::socket socket(ctx);
        socket.connect(endpoint, ec);
        if (ec) {
            log_error << "Could not connect to docker UNIX domain socket, error: " << ec.message();
            return {.statusCode = http::status::internal_server_error, .body = "Could not connect to docker UNIX domain socket, error: " + ec.message()};
        }

        // Prepare message
        http::request<http::string_body> request = PrepareJsonMessage(method, path, body, headers);

        // Write to unix socket
        std::ostringstream oss;
        oss << request;
        boost::asio::write(socket, boost::asio::buffer(oss.str()), boost::asio::transfer_all());

        boost::beast::flat_buffer buffer;
        http::response<http::string_body> response;
        read(socket, buffer, response, ec);
        if (ec) {
            log_error << "Read from docker daemon failed, error: " << ec.message();
            return {.statusCode = http::status::internal_server_error, .body = "Read from docker daemon failed, error: " + ec.message()};
        }
        socket.close();
        return PrepareResult(response);
    }

    // TODO:: test the solution, once the boost is finiahed.
    DomainSocketResult DomainSocket::SendBinary(http::verb method, const std::string &path, const std::string &filename, const std::map<std::string, std::string> &headers) {

        boost::system::error_code ec;

        boost::asio::io_context ctx;
        boost::asio::local::stream_protocol::endpoint endpoint(_path);
        boost::asio::local::stream_protocol::socket socket(ctx);
        socket.connect(endpoint, ec);
        if (ec) {
            log_error << "Could not connect to docker UNIX domain socket";
            return {.statusCode = http::status::internal_server_error, .body = "Could not connect to docker UNIX domain socket"};
        }

        // Prepare message
        http::request<http::file_body> request = PrepareBinaryMessage(method, path, filename, headers);

        // Write to unix socket
        boost::beast::http::write(socket, request);

        boost::beast::flat_buffer buffer;
        http::response<http::string_body> response;
        read(socket, buffer, response, ec);
        if (!ec && ec.message() != "Success") {
            log_error << "Send to docker daemon failed, error: " << ec.message();
        }
        socket.close();
        return PrepareResult(response);
    }

    http::request<http::string_body> DomainSocket::PrepareJsonMessage(http::verb method, const std::string &path, const std::string &body, const std::map<std::string, std::string> &headers) {

        http::request<http::string_body> request;

        request.method(method);
        request.target(path);
        request.body() = body;
        request.prepare_payload();
        request.base().set(http::field::host, "localhost");
        request.base().set(http::field::content_type, "application/json");
        request.base().set(http::field::content_length, std::to_string(body.size()));

        if (!headers.empty()) {
            for (const auto &header: headers) {
                request.base().set(header.first, header.second);
            }
        }
        return request;
    }

    http::request<http::file_body> DomainSocket::PrepareBinaryMessage(http::verb method, const std::string &path, const std::string &filename, const std::map<std::string, std::string> &headers) {

        boost::system::error_code ec;
        http::request<http::file_body> request;
        request.method(method);
        request.target(path);
        request.base().set("Host", "localhost");
        request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        request.body().open(filename.c_str(), boost::beast::file_mode::scan, ec);
        request.prepare_payload();

        if (!headers.empty()) {
            for (const auto &header: headers) {
                request.base().set(header.first, header.second);
            }
        }
        return request;
    }

    DomainSocketResult DomainSocket::PrepareResult(http::response<http::string_body> response) {

        DomainSocketResult domainSocketResult;
        domainSocketResult.body = response.body();
        domainSocketResult.statusCode = response.result();
        return domainSocketResult;
    }

}// namespace AwsMock::Core
