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

// AwsMock includes
#include <awsmock/server/Session.h>
#include <awsmock/service/common/AbstractServer.h>

namespace AwsMock::Manager {

    /**
     * @brief Accepts incoming connections and launches the sessions
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Listener : public std::enable_shared_from_this<Listener> {

      public:

        /**
         * @brief Constructor
         *
         * @param ioc Boost IO context
         * @param endpoint HTTP endpoint
         * @param serverMap map of currently running modules
         */
        Listener(boost::asio::io_context &ioc, const boost::asio::ip::tcp::endpoint &endpoint, const Service::ServerMap &serverMap);

        /**
         * @brief Start accepting incoming connections
         *
         * We need to be executing within a strand to perform async operations on the I/O objects in this session. Although not strictly necessary
         * for single-threaded contexts, this example code is written to be thread-safe by default.
         */
        void Run();

      private:

        /**
         * @brief The new connection gets its own strand
         */
        void DoAccept();

        /**
         * @brief Accept callback
         *
         * @param ec error code
         * @param socket HTTP socket
         */
        void OnAccept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket);

        /**
         * Boost IO context
         */
        boost::asio::io_context &ioc_;

        /**
         * Boost acceptor
         */
        boost::asio::ip::tcp::acceptor acceptor_;

        /**
         * Map of currently running server
         */
        Service::ServerMap _serverMap;
    };

}// namespace AwsMock::Manager

#endif// AWSMOCK_MANAGER_LISTENER_H
