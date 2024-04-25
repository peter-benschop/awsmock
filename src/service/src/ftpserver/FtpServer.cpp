

// AwsMock includes
#include <awsmock/ftpserver/FtpServer.h>
#include <awsmock/ftpserver/FtpServerImpl.h>

#include <utility>

namespace AwsMock::FtpServer {

    FtpServer::FtpServer(const Core::Configuration &configuration, std::string serverName, int port, std::string address) : _configuration(configuration), _serverName(std::move(serverName)), _address(std::move(address)), _port(port) {

        _ftp_server = std::make_unique<FtpServerImpl>(_serverName, _address, _port, _configuration);
        log_debug << "FTP manager configured, name: " << _serverName << " endpoint: " << _address << ":" << port;
    }

    FtpServer::~FtpServer() = default;

    bool FtpServer::addUser(const std::string &username, const std::string &password, const std::string &local_root_path, const Permission permissions) {
        return _ftp_server->addUser(username, password, local_root_path, permissions);
    }

    bool FtpServer::addUserAnonymous(const std::string &local_root_path, const Permission permissions) {
        return _ftp_server->addUserAnonymous(local_root_path, permissions);
    }

    bool FtpServer::start(size_t thread_count) {
        assert(thread_count > 0);
        return _ftp_server->start(thread_count);
    }

    void FtpServer::stop() {
        _ftp_server->stop();
    }

    int FtpServer::getOpenConnectionCount() const {
        return _ftp_server->getOpenConnectionCount();
    }

    int FtpServer::getPort() const {
        return _port;
    }

    std::string FtpServer::getAddress() const {
        return _ftp_server->getAddress();
    }
}// namespace AwsMock::FtpServer
