//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/transfer/TransferServer.h>

namespace AwsMock::Service {

    TransferServer::TransferServer(Core::Configuration &configuration) : AbstractServer(configuration, "transfer", 10), AbstractWorker(configuration), _configuration(configuration), _transferDatabase(Database::TransferDatabase::instance()),
                                                                         _module("transfer") {

        // REST manager configuration
        _port = _configuration.getInt("awsmock.service.transfer.port", TRANSFER_DEFAULT_PORT);
        _host = _configuration.getString("awsmock.service.transfer.host", TRANSFER_DEFAULT_HOST);
        _maxQueueLength = _configuration.getInt("awsmock.service.transfer.max.queue", TRANSFER_DEFAULT_QUEUE_LENGTH);
        _maxThreads = _configuration.getInt("awsmock.service.transfer.max.threads", TRANSFER_DEFAULT_THREADS);
        _requestTimeout = _configuration.getInt("awsmock.service.transfer.timeout", TRANSFER_DEFAULT_TIMEOUT);
        _monitoringPeriod = _configuration.getInt("awsmock.service.transfer.monitoring.period", TRANSFER_DEFAULT_MONITORING_PERIOD);

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _bucket = _configuration.getString("awsmock.service.transfer.bucket", DEFAULT_TRANSFER_BUCKET);
        _baseDir = _configuration.getString("awsmock.service.transfer.base.dir", DEFAULT_BASE_DIR);

        // S3 module connection
        _s3ServiceHost = _configuration.getString("awsmock.service.s3.host", "localhost");
        _s3ServicePort = _configuration.getInt("awsmock.service.s3.port", 9501);
        _baseUrl = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort);
        log_debug << "S3 module endpoint: http://" << _s3ServiceHost << ":" << _s3ServicePort;

        // Ensure base directory exists
        Core::DirUtils::EnsureDirectory(_baseDir);
        log_debug << "Using baseDir: " << _baseDir;

        // Monitoring
        _transferMonitoring = std::make_unique<TransferMonitoring>(_monitoringPeriod);

        log_info << "Transfer manager initialized";
    }

    void TransferServer::Initialize() {

        // Check module active
        if (!IsActive("transfer")) {
            log_info << "Transfer module inactive";
            return;
        }
        log_info << "Transfer module starting";

        // Start monitoring
        _transferMonitoring->Start();

        // Start REST manager
        StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new TransferRequestHandlerFactory(_configuration));

        // Start all transfer servers
        StartTransferServers();
    }

    void TransferServer::Run() {
        log_trace << "TransferWorker processing started";
    }

    void TransferServer::Shutdown() {
        StopHttpServer();
    }

    void TransferServer::StartTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer manager thread
        _ftpServer = std::make_shared<FtpServer::FtpServer>(_configuration, server.serverId, server.port, server.listenAddress);
        _transferServerList[server.serverId] = _ftpServer;

        // Add users
        for (const auto &user: server.users) {

            std::string homeDir = _baseDir + Poco::Path::separator() + user.homeDirectory;

            // Ensure the home directory exists
            Core::DirUtils::EnsureDirectory(homeDir);
            log_debug << "Using homeDir: " << homeDir;

            // Add to FTP manager
            _ftpServer->addUser(user.userName, user.password, homeDir, FtpServer::Permission::All);
        }
        _ftpServer->start(server.concurrency);

        // Update database
        server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE);

        log_info << "Transfer manager " << server.serverId << " started ";
    }

    void TransferServer::StopTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer manager thread
        std::shared_ptr<FtpServer::FtpServer> ftpserver = _transferServerList[server.serverId];
        ftpserver->stop();

        // Update database
        server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE);

        log_debug << "Transfer manager " << server.serverId << " stopped ";
    }

    void TransferServer::StartTransferServers() {

        log_debug << "Starting transfer servers";
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase.ListServers(_region);

        for (auto &transfer: transfers) {
            if (transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE)) {
                StartTransferServer(transfer);
            }
        }
    }

    void TransferServer::CheckTransferServers() {

        log_trace << "Checking transfer servers";
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase.ListServers(_region);

        for (auto &transfer: transfers) {
            if (transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE)) {
                auto it = _transferServerList.find(transfer.serverId);
                if (it == _transferServerList.end()) {
                    StartTransferServer(transfer);
                }
            } else if (transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE)) {
                auto it = _transferServerList.find(transfer.serverId);
                if (it != _transferServerList.end()) {
                    StopTransferServer(transfer);
                }
            }
        }

        for (auto &transfer: _transferServerList) {
            if (!_transferDatabase.TransferExists(transfer.first)) {
                Database::Entity::Transfer::Transfer server = _transferDatabase.GetTransferByServerId(transfer.first);
                StopTransferServer(server);
            }
        }
    }

}// namespace AwsMock::Service
