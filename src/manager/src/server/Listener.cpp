//
// Created by vogje01 on 5/27/24.
//

#include <awsmock/server/Listener.h>

namespace AwsMock::Manager {

    Listener::Listener(boost::asio::io_context &ioc, const boost::asio::ip::tcp::endpoint &endpoint, const Service::ServerMap &serverMap) : ioc_(ioc), acceptor_(boost::asio::make_strand(ioc)), _serverMap(std::move(serverMap)) {

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

    void Listener::Run() {
        boost::asio::dispatch(acceptor_.get_executor(), boost::beast::bind_front_handler(&Listener::DoAccept, this->shared_from_this()));
    }

    void Listener::DoAccept() {
        acceptor_.async_accept(boost::asio::make_strand(ioc_), boost::beast::bind_front_handler(&Listener::OnAccept, shared_from_this()));
    }

    void Listener::OnAccept(boost::beast::error_code ec, boost::asio::ip::tcp::socket socket) {
        if (ec) {
            log_error << ec.message();
        } else {
            // Create the http session and run it
            std::make_shared<Session>(std::move(socket), _serverMap)->run();
        }

        // Accept another connection
        DoAccept();
    }

}// namespace AwsMock::Manager
