//
// Created by vogje01 on 5/27/24.
//

#ifndef AWSMOCK_MANAGER_LISTENER_H
#define AWSMOCK_MANAGER_LISTENER_H

// C++ includes
#include <memory>

// Boost includes
#include "awsmock/core/LogStream.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core/bind_handler.hpp>

#include <awsmock/server/Session.h>

namespace AwsMock::Manager {

    /**
     * @brief Accepts incoming connections and launches the sessions
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Listener : public std::enable_shared_from_this<Listener> {

        boost::asio::io_context &ioc_;
        boost::asio::ip::tcp::acceptor acceptor_;

      public:

        Listener(boost::asio::io_context &ioc, const boost::asio::ip::tcp::endpoint &endpoint, const Service::ServerMap &serverMap) : ioc_(ioc), acceptor_(boost::asio::make_strand(ioc)), _serverMap(std::move(serverMap)) {

            boost::beast::error_code ec;

            // Open the acceptor
            ec = acceptor_.open(endpoint.protocol(), ec);
            if (ec) {
                log_error << ec.message();
                return;
            }

            // Allow address reuse
            ec = acceptor_.set_option(boost::asio::socket_base::reuse_address(true), ec);
            if (ec) {
                log_error << ec.message();
                return;
            }

            // Bind to the server address
            ec = acceptor_.bind(endpoint, ec);
            if (ec) {
                log_error << ec.message();
                return;
            }

            // Start listening for connections
            ec = acceptor_.listen(boost::asio::socket_base::max_listen_connections, ec);
            if (ec) {
                log_error << ec.message();
                return;
            }
        }

        /**
         * @brief Start accepting incoming connections
         *
         * We need to be executing within a strand to perform async operations on the I/O objects in this session. Although not strictly necessary
         * for single-threaded contexts, this example code is written to be thread-safe by default.
         */
        void run() {
            boost::asio::dispatch(acceptor_.get_executor(), boost::beast::bind_front_handler(&Listener::do_accept, this->shared_from_this()));
        }

      private:

        /**
         * @brief The new connection gets its own strand
         */
        void do_accept() {
            acceptor_.async_accept(boost::asio::make_strand(ioc_), boost::beast::bind_front_handler(&Listener::on_accept, shared_from_this()));
        }

        void on_accept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
            if (ec) {
                log_error << ec.message();
            } else {
                // Create the http session and run it
                std::make_shared<Session>(std::move(socket), _serverMap)->run();
            }

            // Accept another connection
            do_accept();
        }
        Service::ServerMap _serverMap;
    };

}// namespace AwsMock::Manager

#endif// AWSMOCK_MANAGER_LISTENER_H
