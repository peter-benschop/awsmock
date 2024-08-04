#include "awsmock/ftpserver/FtpServerImpl.h"

#include "awsmock/ftpserver/FtpSession.h"

#include <iostream>
#include <memory>
#include <utility>

namespace AwsMock::FtpServer {

    FtpServerImpl::FtpServerImpl(std::string serverName, std::string address, uint16_t port, Core::Configuration &configuration)
        : _serverName(std::move(serverName)), _port(port), _address(std::move(address)), _acceptor(_ioService), _openConnectionCount(0), _configuration(configuration) {}

    FtpServerImpl::~FtpServerImpl() {
        stop();
    }

    bool FtpServerImpl::addUser(const std::string &username, const std::string &password, const std::string &local_root_path, const Permission permissions) {
        return _ftpUsers.addUser(username, password, local_root_path, permissions);
    }

    bool FtpServerImpl::addUserAnonymous(const std::string &local_root_path, const Permission permissions) {
        return _ftpUsers.addUser("anonymous", "", local_root_path, permissions);
    }

    bool FtpServerImpl::start(size_t thread_count) {
        auto ftp_session = std::make_shared<FtpSession>(_ioService, _ftpUsers, _serverName, _configuration, [this]() { _openConnectionCount--; });

        // set up the acceptor to listen on the tcp port
        asio::error_code make_address_ec;
        const asio::ip::tcp::endpoint endpoint(asio::ip::make_address(_address, make_address_ec), _port);
        if (make_address_ec) {
            log_error << "Error creating address from string \"" << _address << "\": " << make_address_ec.message();
            return false;
        }

        {
            asio::error_code ec;
            ec = _acceptor.open(endpoint.protocol(), ec);
            if (ec) {
                log_error << "Error opening acceptor: " << ec.message();
                return false;
            }
        }

        {
            asio::error_code ec;
            ec = _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true), ec);
            if (ec) {
                log_error << "Error setting reuse_address option: " << ec.message();
                return false;
            }
        }

        {
            asio::error_code ec;
            ec = _acceptor.bind(endpoint, ec);
            if (ec) {
                log_error << "Error binding acceptor: " << ec.message();
                return false;
            }
        }

        {
            asio::error_code ec;
            ec = _acceptor.listen(asio::socket_base::max_listen_connections, ec);
            if (ec) {
                log_error << "Error listening on acceptor: " << ec.message();
                return false;
            }
        }

        log_debug << "FTP Handler created.";
        log_info << "Listening at address " << _acceptor.local_endpoint().address() << ":" << _acceptor.local_endpoint().port();

        _acceptor.async_accept(ftp_session->getSocket(), [this, ftp_session](auto ec) {
            _openConnectionCount++;

            acceptFtpSession(ftp_session, ec);
        });

        for (size_t i = 0; i < thread_count; i++) {
            _threadPool.emplace_back([this] { _ioService.run(); });
        }
        log_info << "Listening threads started, count: " << thread_count;

        return true;
    }

    void FtpServerImpl::stop() {
        _ioService.stop();
        for (std::thread &thread: _threadPool) {
            thread.join();
        }
        _threadPool.clear();
    }

    void FtpServerImpl::acceptFtpSession(const std::shared_ptr<FtpSession> &ftp_session, asio::error_code const &error) {
        if (error) {
            log_error << "Error handling connection: " << error.message();
            return;
        }
        log_debug << "FTP Client connected: " << ftp_session->getSocket().remote_endpoint().address().to_string() << ":"
                  << ftp_session->getSocket().remote_endpoint().port();

        ftp_session->start();

        auto new_session = std::make_shared<FtpSession>(_ioService, _ftpUsers, _serverName, _configuration, [this]() { _openConnectionCount--; });

        _acceptor.async_accept(new_session->getSocket(), [this, new_session](auto ec) {
            _openConnectionCount++;
            acceptFtpSession(new_session, ec);
        });
    }

    int FtpServerImpl::getOpenConnectionCount() {
        return _openConnectionCount;
    }

    uint16_t FtpServerImpl::getPort() {
        return _acceptor.local_endpoint().port();
    }

    std::string FtpServerImpl::getAddress() {
        return _acceptor.local_endpoint().address().to_string();
    }
}// namespace AwsMock::FtpServer
