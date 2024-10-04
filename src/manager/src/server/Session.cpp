//
// Created by vogje01 on 5/27/24.
//

#include <awsmock/server/Session.h>

namespace AwsMock::Manager {

    Session::Session(boost::asio::ip::tcp::socket &&socket, Service::ServerMap &serverMap) : stream_(std::move(socket)), _handler(serverMap) {
        static_assert(queue_limit > 0, "queue limit must be positive");
    }

    void Session::run() {
        boost::asio::dispatch(stream_.get_executor(), boost::beast::bind_front_handler(&Session::DoRead, this->shared_from_this()));
    }

    void Session::DoRead() {

        // Construct a new parser for each message
        parser_.emplace();

        // Apply a reasonable limit to the allowed size
        // of the body in bytes to prevent abuse.
        parser_->body_limit(boost::none);

        // Set the timeout.
        stream_.expires_after(std::chrono::seconds(30));

        // Read a request using the parser-oriented interface
        http::async_read(stream_, buffer_, *parser_, boost::beast::bind_front_handler(&Session::OnRead, this->shared_from_this()));
    }

    void Session::OnRead(boost::beast::error_code ec, std::size_t bytes_transferred) {

        boost::ignore_unused(bytes_transferred);

        // This means they closed the connection
        if (ec == http::error::end_of_stream)
            return DoClose();

        if (ec) {
            log_error << ec.message();
            return;
        }

        // Send the response
        QueueWrite(HandleRequest(parser_->release()));

        // If we aren't at the queue limit, try to pipeline another request
        if (response_queue_.size() < queue_limit)
            DoRead();
    }

    void Session::QueueWrite(http::message_generator response) {

        // Allocate and store the work
        response_queue_.push(std::move(response));

        // If there was no previous work, start the write loop
        if (response_queue_.size() == 1)
            DoWrite();
    }

    // Return a response for the given request.
    //
    // The concrete type of the response message (which depends on the
    // request), is type-erased in message_generator.
    template<class Body, class Allocator>
    http::message_generator Session::HandleRequest(http::request<Body, http::basic_fields<Allocator>> &&request) {

        // Make sure we can handle the method
        if (request.method() != http::verb::get && request.method() != http::verb::put && request.method() != http::verb::options) {
            return Core::HttpUtils::BadRequest(request, "Unknown HTTP-method");
        }

        // Ping request
        if (request.method() == http::verb::connect) {
            log_debug << "Handle CONNECT request";
            Monitoring::MetricServiceTimer headTimer(GATEWAY_HTTP_TIMER, "method", "CONNECT");
            Monitoring::MetricService::instance().IncrementCounter(GATEWAY_HTTP_COUNTER, "method", "CONNECT");
            return Core::HttpUtils::Ok(request);
        }

        // Request path must be absolute and not contain "..".
        if (request.target().empty() || request.target()[0] != '/' || request.target().find("..") != boost::beast::string_view::npos) {
            return Core::HttpUtils::BadRequest(request, "Invalid target path");
        }

        // Process OPTIONS requests
        if (request.method() == http::verb::options) {

            return HandleOptionsRequest(request);

        } else {
            switch (request.method()) {
                case http::verb::get: {
                    log_debug << "Handle GET request";
                    Monitoring::MetricServiceTimer measure(MODULE_HTTP_TIMER, "method", "GET");
                    Monitoring::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "GET");
                    return _handler.HandleGetRequest(request);
                }
                case http::verb::put: {
                    log_debug << "Handle PUT request";
                    Monitoring::MetricServiceTimer measure(MODULE_HTTP_TIMER, "method", "PUT");
                    Monitoring::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "PUT");
                    return _handler.HandlePutRequest(request);
                }
                case http::verb::post: {
                    log_debug << "Handle POST request";
                    Monitoring::MetricServiceTimer measure(MODULE_HTTP_TIMER, "method", "POST");
                    Monitoring::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "POST");
                    return _handler.HandlePostRequest(request);
                }
            }
        }
        return Core::HttpUtils::NotImplemented(request, "Not yet implemented");
    }

    // Called to start/continue the write-loop. Should not be called when
    // write_loop is already active.
    void Session::DoWrite() {
        if (!response_queue_.empty()) {
            bool keep_alive = response_queue_.front().keep_alive();
            async_write(stream_, std::move(response_queue_.front()), boost::beast::bind_front_handler(&Session::OnWrite, shared_from_this(), keep_alive));
        }
    }

    void Session::OnWrite(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec) {
            log_error << ec.message();
            return;
        }

        if (!keep_alive) {
            // This means we should close the connection, usually because the response indicated the "Connection: close" semantic.
            return DoClose();
        }
        return DoClose();

        // Resume the read if it has been paused
        if (response_queue_.size() == queue_limit)
            DoRead();

        response_queue_.pop();

        DoWrite();
    }

    void Session::DoClose() {

        // Send a TCP shutdown
        boost::beast::error_code ec;
        ec = stream_.socket().shutdown(boost::beast::net::ip::tcp::socket::shutdown_send, ec);
        if (ec) {
            //  log_error << "Could not shutdown socket, message: " << ec.message();
        }

        // At this point the connection is closed gracefully
    }

    http::response<http::string_body> Session::HandleOptionsRequest(const http::request<http::string_body> &request) {

        // Prepare the response message
        http::response<http::string_body> response{http::status::no_content, request.version()};
        response.version(request.version());
        response.result(http::status::ok);
        response.set(http::field::server, "awsmock");
        response.set(http::field::date, Core::DateTimeUtils::HttpFormat());
        response.set(http::field::allow, "*/*");
        response.set(http::field::access_control_allow_origin, "*");
        response.set(http::field::access_control_allow_headers, "*");
        response.set(http::field::access_control_allow_methods, "GET,PUT,POST,DELETE,HEAD,OPTIONS");
        response.set(http::field::access_control_max_age, "86400");
        response.set(http::field::vary, "Accept-Encoding, Origin");
        response.set(http::field::keep_alive, "timeout=10, max=100");
        response.set(http::field::connection, "Keep-Alive");

        // Send the response to the client
        return response;
    }

}// namespace AwsMock::Manager
