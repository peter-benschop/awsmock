//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_MANAGER_SESSION_H
#define AWSMOCK_MANAGER_SESSION_H

// C++ includes
#include <memory>
#include <queue>

// Boost includes
#include "awsmock/core/LogStream.h"
#include <boost/asio/dispatch.hpp>
#include <boost/beast.hpp>

namespace AwsMock::Manager {

    /**
     * @brief HTTP session manager
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Session : public std::enable_shared_from_this<Session> {

        boost::beast::tcp_stream stream_;
        boost::beast::flat_buffer buffer_;

        static constexpr std::size_t queue_limit = 8;
        std::queue<boost::beast::http::message_generator> response_queue_;

        // The parser is stored in an optional container so we can
        // construct it from scratch it at the beginning of each new message.
        boost::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> parser_;
        Handler _handler;

      public:

        /**
         * @brief HTTP session
         *
         * Takes ownership of the socket.
         *
         * @param socket
         * @param serverMap
         */
        Session(boost::asio::ip::tcp::socket &&socket, Service::ServerMap &serverMap) : stream_(std::move(socket)), _handler(serverMap) {
            static_assert(queue_limit > 0, "queue limit must be positive");
        }

        /**
         * @brief Start the session
         *
         * We need to be executing within a strand to perform async operations on the I/O objects in this session. Although not strictly necessary
         * for single-threaded contexts, this example code is written to be thread-safe by default.
         */
        void run() {
            boost::asio::dispatch(stream_.get_executor(), boost::beast::bind_front_handler(&Session::do_read, this->shared_from_this()));
        }

      private:

        void do_read() {
            // Construct a new parser for each message
            parser_.emplace();

            // Apply a reasonable limit to the allowed size
            // of the body in bytes to prevent abuse.
            parser_->body_limit(10000);

            // Set the timeout.
            stream_.expires_after(std::chrono::seconds(30));

            // Read a request using the parser-oriented interface
            boost::beast::http::async_read(stream_, buffer_, *parser_, boost::beast::bind_front_handler(&Session::on_read, shared_from_this()));
        }

        void on_read(boost::beast::error_code ec, std::size_t bytes_transferred) {

            boost::ignore_unused(bytes_transferred);

            // This means they closed the connection
            if (ec == boost::beast::http::error::end_of_stream)
                return do_close();

            if (ec) {
                log_error << ec.message();
                return;
            }

            // Send the response
            queue_write(handle_request(parser_->release()));

            // If we aren't at the queue limit, try to pipeline another request
            if (response_queue_.size() < queue_limit)
                do_read();
        }

        void queue_write(boost::beast::http::message_generator response) {

            // Allocate and store the work
            response_queue_.push(std::move(response));

            // If there was no previous work, start the write loop
            if (response_queue_.size() == 1)
                do_write();
        }

        // Return a response for the given request.
        //
        // The concrete type of the response message (which depends on the
        // request), is type-erased in message_generator.
        template<class Body, class Allocator>
        boost::beast::http::message_generator handle_request(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> &&req) {

            // Returns a bad request response
            auto const bad_request =
                    [&req](boost::beast::string_view why) {
                        boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::bad_request, req.version()};
                        res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                        res.set(boost::beast::http::field::content_type, "text/html");
                        res.keep_alive(req.keep_alive());
                        res.body() = std::string(why);
                        res.prepare_payload();
                        return res;
                    };

            // Returns a server error response
            auto const server_error =
                    [&req](boost::beast::string_view what) {
                        boost::beast::http::response<boost::beast::http::string_body> res{boost::beast::http::status::internal_server_error, req.version()};
                        res.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
                        res.set(boost::beast::http::field::content_type, "text/html");
                        res.keep_alive(req.keep_alive());
                        res.body() = "An error occurred: '" + std::string(what) + "'";
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

            boost::beast::http::response<boost::beast::http::string_body> res;

            switch (req.method()) {
                case boost::beast::http::verb::get:
                    log_debug << "Handle GET request";
                    res = _handler.HandleGetRequest(req);
                    break;
                case boost::beast::http::verb::put:
                    log_debug << "Handle PUT request";
                    res = _handler.HandlePutRequest(req);
                    break;
            }
            return res;
        }

        // Called to start/continue the write-loop. Should not be called when
        // write_loop is already active.
        void do_write() {
            if (!response_queue_.empty()) {
                bool keep_alive = response_queue_.front().keep_alive();
                boost::beast::async_write(stream_, std::move(response_queue_.front()), boost::beast::bind_front_handler(&Session::on_write, shared_from_this(), keep_alive));
            }
        }

        void on_write(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred) {
            boost::ignore_unused(bytes_transferred);

            if (ec) {
                log_error << ec.message();
                return;
            }

            if (!keep_alive) {
                // This means we should close the connection, usually because
                // the response indicated the "Connection: close" semantic.
                return do_close();
            }

            // Resume the read if it has been paused
            if (response_queue_.size() == queue_limit)
                do_read();

            response_queue_.pop();

            do_write();
        }

        void do_close() {
            // Send a TCP shutdown
            boost::beast::error_code ec;
            stream_.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);

            // At this point the connection is closed gracefully
        }
    };

}// namespace AwsMock::Manager

#endif//AWSMOCK_MANAGER_SESSION_H
