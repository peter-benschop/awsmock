//
// Created by vogje01 on 5/28/24.
//

#include <awsmock/core/HttpSocket.h>

namespace AwsMock::Core {

    HttpSocketResponse HttpSocket::SendJson(http::verb method, const std::string &host, int port, const std::string &path, const std::string &body, const std::map<std::string, std::string> &headers) {

        boost::asio::io_context ctx;

        boost::asio::ip::tcp::resolver resolver(ctx);
        boost::beast::tcp_stream stream(ctx);

        // Resolve host/port
        auto const results = resolver.resolve(host, std::to_string(port));

        // Connect
        stream.connect(results);

        // Prepare message
        http::request<http::string_body> request = PrepareJsonMessage(method, host, path, body, headers);

        // Write to TCP socket
        http::write(stream, request);

        boost::beast::flat_buffer buffer;
        boost::system::error_code ec;
        http::response<http::string_body> response;

        http::read(stream, buffer, response);
        if (!ec && ec.message() != "Success") {
            log_error << "Send to " << host << ":" << port << " failed, error: " << ec.message();
        }

        // Cleanup
        stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        return PrepareResult(response);
    }

    // TODO:: test the solution, once the boost is finiahed.
    /*DomainSocketResult DomainSocket::SendBinary(http::verb method, const std::string &path, const std::string &filename, const std::map<std::string, std::string> &headers) {

        boost::asio::io_context ctx;
        boost::asio::local::stream_protocol::endpoint endpoint(_path);
        boost::asio::local::stream_protocol::socket socket(ctx);
        socket.connect(endpoint);

        // Prepare message
        http::request<http::file_body> request = PrepareBinaryMessage(method, path, filename, headers);

        // Write to unix socket
        boost::beast::http::write(socket, request);

        boost::beast::flat_buffer buffer;
        boost::system::error_code ec;
        http::response<http::dynamic_body> response;
        read(socket, buffer, response, ec);
        if (!ec && ec.message() != "Success") {
            log_error << "Send to docker daemon failed, error: " << ec.message();
        }
        socket.close();
        return PrepareResult(response);
    }*/

    http::request<http::string_body> HttpSocket::PrepareJsonMessage(http::verb method, const std::string &host, const std::string &path, const std::string &body, const std::map<std::string, std::string> &headers) {

        http::request<http::string_body> request;

        request.method(method);
        request.set(http::field::host, host);
        request.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        request.target(path);
        request.body() = body;
        request.prepare_payload();
        request.base().set("Host", "localhost");

        if (!headers.empty()) {
            for (const auto &header: headers) {
                request.base().set(header.first, header.second);
            }
        }
        return request;
    }

    http::request<http::file_body> HttpSocket::PrepareBinaryMessage(http::verb method, const std::string &path, const std::string &filename, const std::map<std::string, std::string> &headers) {

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

    HttpSocketResponse HttpSocket::PrepareResult(http::response<http::string_body> response) {
        return {.statusCode = response.result(), .body = response.body()};
    }

}// namespace AwsMock::Core
