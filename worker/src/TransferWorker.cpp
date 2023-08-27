//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/TransferWorker.h>

namespace AwsMock::Worker {

    [[maybe_unused]] TransferWorker::TransferWorker(const Core::Configuration &configuration)
        : _logger(Poco::Logger::get("LambdaWorker")), _configuration(configuration), _running(false) {

        Initialize();
    }

    void TransferWorker::Initialize() {

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.transfer.period", 10000);
        log_debug_stream(_logger) << "Lambda worker period: " << _period << std::endl;

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _clientId = _configuration.getString("awsmock.client.id", "00000000");
        _user = _configuration.getString("awsmock.user", "none");
        _transferDatabase = std::make_unique<Database::TransferDatabase>(_configuration);

        log_debug_stream(_logger) << "TransferWorker initialized" << std::endl;
    }

    void TransferWorker::StartTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer server thread
        std::shared_ptr<Service::FtpServer> ftpserver = std::make_shared<Service::FtpServer>(_configuration);
        _transferServerList[server.serverId] = ftpserver;

        // Add users
        for (const auto &user : server.users) {
            if (user.userName != "anonymous") {
                ftpserver->AddUser(user.userName, user.password, user.homeDirectory);
            }
        }
        Poco::ThreadPool::defaultPool().start(*ftpserver);

        // Update database
        server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE);

        log_debug_stream(_logger) << "Transfer server " << server.serverId << " started " << std::endl;
    }

    void TransferWorker::StopTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer server thread
        std::shared_ptr<Service::FtpServer> ftpserver = _transferServerList[server.serverId];

        ftpserver->StopServer();

        // Update database
        server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE);

        log_debug_stream(_logger) << "Transfer server " << server.serverId << " stopped " << std::endl;
    }

    void TransferWorker::StartTransferServers() {

        log_debug_stream(_logger) << "Starting transfer servers" << std::endl;
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase->ListServers(_region);

        for (auto &transfer : transfers) {
            if(transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE)) {
                StartTransferServer(transfer);
            }
        }
    }

    void TransferWorker::CheckTransferServers() {

        log_debug_stream(_logger) << "Checking transfer servers" << std::endl;
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase->ListServers(_region);

        for (auto &transfer : transfers) {
            if(transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE)) {
                std::map<std::string, std::shared_ptr<Service::FtpServer>>::iterator it = _transferServerList.find(transfer.serverId);
                if (it == _transferServerList.end()) {
                    StartTransferServer(transfer);
                }
            } else  if(transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE)) {
                std::map<std::string, std::shared_ptr<Service::FtpServer>>::iterator it = _transferServerList.find(transfer.serverId);
                if (it != _transferServerList.end()) {
                    StopTransferServer(transfer);
                }
            }

        }
    }

    void TransferWorker::run() {

        log_info_stream(_logger) << "Transfer worker started" << std::endl;

        // Check service active
        /*if (!_serviceDatabase->IsActive("Lambda")) {
            return;
        }*/

        // Start all lambda functions
        StartTransferServers();

        _running = true;
        while (_running) {
            log_debug_stream(_logger) << "TransferWorker processing started" << std::endl;
            Poco::Thread::sleep(_period);
            CheckTransferServers();
        }
    }

} // namespace AwsMock::Worker
