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
        _anonymousDir = _configuration.getString("awsmock.service.ftp.anonymous.dir", FTP_ANONYMOUS_DIR);
        log_debug_stream(_logger) << "FTP rest service initialized, endpoint: " << _host << ":" << _port << std::endl;

        // Create anonymous directory
        if (!Core::DirUtils::DirectoryExists(_anonymousDir)) {
            Core::DirUtils::MakeDirectory(_anonymousDir);
        }
    }

    FtpServer::~FtpServer() {
        _ftpServer->stop();
    }

    void FtpServer::run() {

        // Set HTTP server parameter
        _ftpServer = std::make_shared<fineftp::FtpServer>(_port);

        _ftpServer->addUserAnonymous(_anonymousDir, fineftp::Permission::All);
        _ftpServer->start(_maxThreads);

        log_info_stream(_logger) << "FTP service started, endpoint: ftp://" << _host << ":" << _port << std::endl;

        _running = true;
        while(_running) {
            Poco::Thread::sleep(1000);
        }
    }
}
