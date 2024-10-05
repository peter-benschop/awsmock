//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/s3/S3Service.h"
#include <awsmock/service/transfer/TransferServer.h>

namespace AwsMock::Service {

    TransferServer::TransferServer(boost::asio::thread_pool &pool) : AbstractServer("transfer"), _transferDatabase(Database::TransferDatabase::instance()), _module("transfer"), _pool(pool) {

        // REST manager configuration
        Core::Configuration &configuration = Core::Configuration::instance();
        _port = configuration.getInt("awsmock.service.transfer.http.port", TRANSFER_DEFAULT_PORT);
        _host = configuration.getString("awsmock.service.transfer.http.host", TRANSFER_DEFAULT_HOST);
        _maxQueueLength = configuration.getInt("awsmock.service.transfer.http.max.queue", TRANSFER_DEFAULT_QUEUE_LENGTH);
        _maxThreads = configuration.getInt("awsmock.service.transfer.http.max.threads", TRANSFER_DEFAULT_THREADS);
        _requestTimeout = configuration.getInt("awsmock.service.transfer.http.timeout", TRANSFER_DEFAULT_TIMEOUT);
        _monitoringPeriod = configuration.getInt("awsmock.service.transfer.monitoring.period", TRANSFER_DEFAULT_MONITORING_PERIOD);

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
        boost::asio::post(_pool, [this] { _transferMonitoring->Start(); });

        // Create transfer bucket
        CreateTransferBucket();

        // Start all transfer servers
        StartTransferServers();

        // Set running
        SetRunning();
        log_debug << "All online transfer servers started";
    }

    void TransferServer::Run() {
        // Intentionally left empty
    }

    void TransferServer::Shutdown() {
        _transferMonitoring->Stop();
    }

    void TransferServer::CreateTransferBucket() {

        Service::S3Service s3Service;

        Dto::S3::CreateBucketRequest request;
        request.name = "transfer-server";
        request.owner = Core::Configuration::instance().getString("awsmock.user");
        request.region = Core::Configuration::instance().getString("awsmock.region");
        if (!s3Service.BucketExists(request.region, request.name)) {
            s3Service.CreateBucket(request);
        }
    }

    void TransferServer::StartTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer manager thread
        _ftpServer = std::make_shared<FtpServer::FtpServer>(server.serverId, server.port, server.listenAddress);
        _transferServerList[server.serverId] = _ftpServer;

        // Get base dir
        std::string baseDir = Core::Configuration::instance().getString("awsmock.service.transfer.base.dir", DEFAULT_BASE_DIR);

        // Add users
        for (const auto &user: server.users) {

            std::string homeDir = baseDir + Poco::Path::separator() + user.homeDirectory;

            // Ensure the home directory exists
            Core::DirUtils::EnsureDirectory(homeDir);
            log_debug << "User created, userId: " << user.userName << " homeDir: " << homeDir;

            // Add to FTP manager
            _ftpServer->addUser(user.userName, user.password, homeDir, FtpServer::Permission::All);
        }
        _ftpServer->start(server.concurrency);

        // Update database
        server.state = Database::Entity::Transfer::ServerState::ONLINE;

        log_debug << "Transfer server started, serverId: " << server.serverId;
    }

    void TransferServer::StopTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer manager thread
        std::shared_ptr<FtpServer::FtpServer> ftpserver = _transferServerList[server.serverId];
        ftpserver->stop();

        // Update database
        server.state = Database::Entity::Transfer::ServerState::OFFLINE;

        log_debug << "Transfer server " << server.serverId << " stopped ";
    }

    void TransferServer::StartTransferServers() {

        log_debug << "Starting transfer servers";
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase.ListServers(_region);

        for (auto &transfer: transfers) {
            if (transfer.state == Database::Entity::Transfer::ServerState::ONLINE) {
                StartTransferServer(transfer);
            }
        }
    }

    void TransferServer::CheckTransferServers() {

        log_trace << "Checking transfer servers";
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase.ListServers(_region);

        for (auto &transfer: transfers) {
            if (transfer.state == Database::Entity::Transfer::ServerState::ONLINE) {
                auto it = _transferServerList.find(transfer.serverId);
                if (it == _transferServerList.end()) {
                    StartTransferServer(transfer);
                    log_info << "Transfer server started, serverId: " << transfer.serverId;
                }
            } else if (transfer.state == Database::Entity::Transfer::ServerState::OFFLINE) {
                auto it = _transferServerList.find(transfer.serverId);
                if (it != _transferServerList.end()) {
                    StopTransferServer(transfer);
                    log_info << "Transfer server stopped, serverId: " << transfer.serverId;
                }
            }
        }

        for (auto &transfer: _transferServerList) {
            if (!_transferDatabase.TransferExists(transfer.first)) {
                Database::Entity::Transfer::Transfer server = _transferDatabase.GetTransferByServerId(transfer.first);
                StopTransferServer(server);
                log_info << "Transfer server stopped, serverId: " << transfer.first;
            }
        }
    }

}// namespace AwsMock::Service
