
// C++ includes
#include <memory>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/ftpserver/FtpServer.h>
#include <awsmock/ftpserver/FtpServerImpl.h>

namespace AwsMock::FtpServer {

    //FtpServer::FtpServer(const std::string &address, uint16_t port) : _ftp_server(std::make_unique<FtpServerImpl>(address, port)) {}

    //FtpServer::FtpServer(uint16_t port) : FtpServer(std::string("0.0.0.0"), port) {}

    FtpServer::FtpServer(const Core::Configuration &configuration) : _configuration(configuration) {
        _port = _configuration.getInt("awsmock.service.ftp.port", FTP_DEFAULT_PORT);
        _address = _configuration.getString("awsmock.service.ftp.address", FTP_DEFAULT_ADDRESS);
        _maxThreads = _configuration.getInt("awsmock.service.ftp.max.threads", 4);
        _dataDir = _configuration.getString("awsmock.worker.transfer.base.dir", FTP_BASE_DIR);

        _ftp_server = std::make_unique<FtpServerImpl>(_address, _port);
    }

    // Move
    FtpServer::FtpServer(FtpServer &&) noexcept = default;
    //FtpServer &FtpServer::operator=(FtpServer &&) noexcept = default;

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
}
