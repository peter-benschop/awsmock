//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_MANAGER_SESSION_H
#define AWSMOCK_MANAGER_SESSION_H

// C++ includes
#include <memory>
#include <queue>

// Boost includes
#include <boost/asio/dispatch.hpp>
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/server/Handler.h>

namespace AwsMock::Manager {

    /**
     * @brief HTTP session manager
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Session : public std::enable_shared_from_this<Session> {

      public:

        /**
         * @brief HTTP session
         *
         * Takes ownership of the socket.
         *
         * @param socket
         * @param serverMap
         */
        Session(boost::asio::ip::tcp::socket &&socket, Service::ServerMap &serverMap);

        /**
         * @brief Start the session
         *
         * We need to be executing within a strand to perform async operations on the I/O objects in this session. Although not strictly necessary
         * for single-threaded contexts, this example code is written to be thread-safe by default.
         */
        void run();

      private:

        /**
         * @brief Read callback
         */
        void DoRead();

        /**
         * @brief On read callback
         */
        void OnRead(boost::beast::error_code ec, std::size_t bytes_transferred);

        /**
         * @brief Queue write callback
         */
        void QueueWrite(boost::beast::http::message_generator response);

        /**
         * @brief Return a response for the given request.
         *
         * The concrete type of the response message (which depends on the request), is type-erased in message_generator.
         *
         * @tparam Body HTTP body
         * @tparam Allocator allocator
         * @param req HTTP request
         * @return
         */
        template<class Body, class Allocator>
        boost::beast::http::message_generator HandleRequest(boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>> &&req);

        /**
         * @brief Called to start/continue the write-loop.
         *
         * Should not be called when write_loop is already active.
         */
        void DoWrite();

        /**
         * @brief On read callback
         *
         * @param keep_alive keep alive flag
         * @param ec error code
         * @param bytes_transferred number of bytes transferred
         */
        void OnWrite(bool keep_alive, boost::beast::error_code ec, std::size_t bytes_transferred);

        /**
         * @brief On close callback
         */
        void DoClose();

        /**
         * TCP stream
         */
        boost::beast::tcp_stream stream_;

        /**
         * Read buffer
         */
        boost::beast::flat_buffer buffer_;

        /**
         * Queue limit
         */
        static constexpr std::size_t queue_limit = 8;

        /**
         * HTTP request queue
         */
        std::queue<boost::beast::http::message_generator> response_queue_;

        /**
         * The parser is stored in an optional container so we can construct it from scratch it at the beginning of each new message.
         */
        boost::optional<boost::beast::http::request_parser<boost::beast::http::string_body>> parser_;

        /**
         * HTTP request handler
         */
        Handler _handler;
    };

}// namespace AwsMock::Manager

#endif//AWSMOCK_MANAGER_SESSION_H
