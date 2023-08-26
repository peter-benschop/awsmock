//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/service/FtpServer.h"

namespace AwsMock::Service {

    FtpServer::FtpServer(const Core::Configuration &configuration)
        : _logger("FtpServer"), _configuration(configuration) {

        _port = _configuration.getInt("awsmock.service.ftp.port", FTP_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.ftp.host", FTP_DEFAULT_HOST);
        _maxThreads = _configuration.getInt("awsmock.service.ftp.max.threads", 4);
        _baseDir = _configuration.getString("awsmock.service.ftp.base.dir", FTP_BASE_DIR);
        log_debug_stream(_logger) << "FTP rest service initialized, endpoint: " << _host << ":" << _port << std::endl;

        // Create anonymous directory
        if (!Core::DirUtils::DirectoryExists(_baseDir)) {
            Core::DirUtils::MakeDirectory(_baseDir);
        }

        // Create server
        _ftpServer = std::make_shared<fineftp::FtpServer>(_port);

        // Create anonymous directory
        std::string anonymousDir = _baseDir + Poco::Path::separator() + "anonymous";
        if (!Core::DirUtils::DirectoryExists(anonymousDir)) {
            Core::DirUtils::MakeDirectory(anonymousDir);
        }
        _ftpServer->addUserAnonymous(anonymousDir, fineftp::Permission::All);
    }

    FtpServer::~FtpServer() {
        _ftpServer->stop();
    }

    void FtpServer::AddUser(const std::string &userName, const std::string &password, const std::string &homeDirectory) {

        // Create home directory
        std::string homeDir = _baseDir + Poco::Path::separator() + homeDirectory;
        if (!Core::DirUtils::DirectoryExists(homeDir)) {
            Core::DirUtils::MakeDirectory(homeDir);
        }

        // Add user to FTP server
        _ftpServer->addUser(userName, password, homeDir, fineftp::Permission::All);
    }

    void FtpServer::run() {

        _ftpServer->start(_maxThreads);
        log_info_stream(_logger) << "FTP service started, endpoint: ftp://" << _host << ":" << _port << std::endl;

        _running = true;
        while(_running) {
            Poco::Thread::sleep(1000);
        }
    }
}
