//
// Created by vogje01 on 04/01/2023.
//

//#include "awsmock/service/FtpServer.h"

namespace AwsMock::Service {

    /*FtpServer::FtpServer(const Core::Configuration &configuration)
        : _logger(Poco::Logger::get("FtpServer")), _configuration(configuration) {

        _port = _configuration.getInt("awsmock.service.ftp.port", FTP_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.ftp.host", FTP_DEFAULT_HOST);
        _maxThreads = _configuration.getInt("awsmock.service.ftp.max.threads", 4);
        _dataDir = _configuration.getString("awsmock.worker.transfer.base.dir", FTP_BASE_DIR);
        log_debug_stream(_logger) << "FTP rest service initialized, endpoint: " << _host << ":" << _port << std::endl;

        // Create server
        _ftpServer = std::make_shared<FtpServer>(_port);
    }

    FtpServer::~FtpServer() {
        _ftpServer->stop();
    }

    std::string FtpServer::CreateHomeDir(const std::string &homeDirectory) {
        std::string homeDir = _dataDir + Poco::Path::separator() + homeDirectory;
        if (!Core::DirUtils::DirectoryExists(homeDir)) {
            Core::DirUtils::MakeDirectory(homeDir);
            log_debug_stream(_logger) << "Home dir created, homeDirectory: " << homeDirectory << std::endl;
        }
        return homeDir;
    }

    void FtpServer::AddUser(const std::string &userName, const std::string &password, const std::string &homeDirectory) {

        // Create home directory
        std::string homeDir = CreateHomeDir(homeDirectory);

        if(userName == "anonymous") {
            _ftpServer->addUserAnonymous(homeDir, fineftp::Permission::All);
        } else {
            _ftpServer->addUser(userName, password, homeDir, fineftp::Permission::All);
        }
        log_info_stream(_logger) << "User added, userName: " << userName << std::endl;
    }

    void FtpServer::RestartServer() {
        _ftpServer->stop();
        _ftpServer->start();
    }

    void FtpServer::StopServer() {
        _ftpServer->stop();
        _running = false;
    }

    void FtpServer::SetServerName(const std::string &name) {
        _ftpServer->setName(name);
    }

    std::string FtpServer::GetServerName() {
        return _ftpServer->getName();
    }

    void FtpServer::run() {

        _ftpServer->start(_maxThreads);
        log_info_stream(_logger) << "FTP service started, endpoint: ftp://" << _host << ":" << _port << std::endl;

        _running = true;
        while (_running) {
            Poco::Thread::sleep(1000);
        }

    }*/
}
