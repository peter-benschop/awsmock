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
        parser_->body_limit(10000);

        // Set the timeout.
        stream_.expires_after(std::chrono::seconds(30));

        // Read a request using the parser-oriented interface
        boost::beast::http::async_read(stream_, buffer_, *parser_, boost::beast::bind_front_handler(&Session::OnRead, shared_from_this()));
    }

    void Session::OnRead(boost::beast::error_code ec, std::size_t bytes_transferred) {

        boost::ignore_unused(bytes_transferred);

        // This means they closed the connection
        if (ec == boost::beast::http::error::end_of_stream)
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

    void Session::QueueWrite(boost::beast::http::message_generator response) {

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
    boost::beast::http::message_generator Session::HandleRequest(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> &&req) {

        // Returns a bad request response
        auto const bad_request =
                [&req](boost::beast::string_view why) {
                    boost::beast::http::response<boost::beast::http::dynamic_body> res{boost::beast::http::status::bad_request, req.version()};
                    res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                    res.set(boost::beast::http::field::content_type, "text/html");
                    res.keep_alive(req.keep_alive());
                    // Body
                    boost::beast::net::streambuf sb;
                    sb.commit(boost::beast::net::buffer_copy(sb.prepare(res.body().size()), res.body().cdata()));
                    res.prepare_payload();
                    return res;
                };

        // Make sure we can handle the method
        if (req.method() != boost::beast::http::verb::get && req.method() != boost::beast::http::verb::put) {
            return bad_request("Unknown HTTP-method");
        }

        // Request path must be absolute and not contain "..".
        if (req.target().empty() || req.target()[0] != '/' || req.target().find("..") != boost::beast::string_view::npos) {
            return bad_request("Illegal request-target");
        }

        boost::beast::http::response<boost::beast::http::dynamic_body> res;

        switch (req.method()) {
            case boost::beast::http::verb::get:
                log_debug << "Handle GET request";
                res = _handler.HandleGetRequest(req);
                break;
            case boost::beast::http::verb::put:
                log_debug << "Handle PUT request";
                res = _handler.HandlePutRequest(req);
                break;
            case boost::beast::http::verb::post:
                log_debug << "Handle POST request";
                res = _handler.HandlePostRequest(req);
                break;
        }
        return res;
    }

    // Called to start/continue the write-loop. Should not be called when
    // write_loop is already active.
    void Session::DoWrite() {
        if (!response_queue_.empty()) {
            bool keep_alive = response_queue_.front().keep_alive();
            boost::beast::async_write(stream_, std::move(response_queue_.front()), boost::beast::bind_front_handler(&Session::OnWrite, shared_from_this(), keep_alive));
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

        // Resume the read if it has been paused
        if (response_queue_.size() == queue_limit)
            DoRead();

        response_queue_.pop();

        DoWrite();
    }

    void Session::DoClose() {
        // Send a TCP shutdown
        boost::beast::error_code ec;
        stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }

}// namespace AwsMock::Manager
