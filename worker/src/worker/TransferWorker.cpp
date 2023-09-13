//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/TransferWorker.h>

namespace AwsMock::Worker {

    [[maybe_unused]] TransferWorker::TransferWorker(const Core::Configuration &configuration)
        : AbstractWorker(configuration), _logger(Poco::Logger::get("TransferWorker")), _configuration(configuration), _running(false) {

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.transfer.period", 10000);
        log_debug_stream(_logger) << "Transfer server worker period: " << _period << std::endl;

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _transferDatabase = std::make_unique<Database::TransferDatabase>(_configuration);

        // Bucket
        _bucket = _configuration.getString("awsmock.service.transfer.bucket", DEFAULT_TRANSFER_BUCKET);
        _baseDir = _configuration.getString("awsmock.worker.transfer.base.dir", DEFAULT_BASE_DIR);

        // Send create bucket request
        if (!Core::DirUtils::DirectoryExists(_baseDir)) {
            Core::DirUtils::MakeDirectory(_baseDir);
            log_debug_stream(_logger) << "Using baseDir: " << _baseDir << std::endl;
        }
        log_debug_stream(_logger) << "TransferWorker initialized" << std::endl;
    }

    void TransferWorker::StartTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer server thread
        _ftpServer = std::make_shared<FtpServer::FtpServer>(_configuration,server.serverId);
        _transferServerList[server.serverId] = _ftpServer;

        // Add users
        for (const auto &user : server.users) {
            std::string homeDir = _baseDir + Poco::Path::separator() + user.homeDirectory;
            _ftpServer->addUser(user.userName, user.password, homeDir, FtpServer::Permission::All);
        }
        _ftpServer->start(10);

        // Update database
        server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE);

        log_debug_stream(_logger) << "Transfer server " << server.serverId << " started " << std::endl;
    }

    void TransferWorker::StopTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer server thread
        std::shared_ptr<FtpServer::FtpServer> ftpserver = _transferServerList[server.serverId];
        ftpserver->stop();

        // Update database
        server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE);

        log_debug_stream(_logger) << "Transfer server " << server.serverId << " stopped " << std::endl;
    }

    void TransferWorker::StartTransferServers() {

        log_debug_stream(_logger) << "Starting transfer servers" << std::endl;
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase->ListServers(_region);

        for (auto &transfer : transfers) {
            if (transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE)) {
                StartTransferServer(transfer);
            }
        }
    }

    void TransferWorker::CheckTransferServers() {

        log_debug_stream(_logger) << "Checking transfer servers" << std::endl;
        std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase->ListServers(_region);

        for (auto &transfer : transfers) {
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

        for (auto &transfer : _transferServerList) {
            if (!_transferDatabase->TransferExists(transfer.first)) {
                Database::Entity::Transfer::Transfer server = _transferDatabase->GetTransferByServerId(transfer.first);
                StopTransferServer(server);
            }
        }
    }

    void TransferWorker::run() {

        log_info_stream(_logger) << "Transfer worker started" << std::endl;

        // Check service active
        /*if (!_serviceDatabase->IsActive("Lambda")) {
            return;
        }*/

        // Send create bucket request
        if (!SendExistsBucketRequest(_bucket)) {
            SendCreateBucketRequest(_bucket);
            log_debug_stream(_logger) << "Sending S3 create bucket: " << _bucket << std::endl;
        }

        // Start all lambda functions
        StartTransferServers();

        _running = true;
        while (_running) {
            log_debug_stream(_logger) << "TransferWorker processing started" << std::endl;
            Poco::Thread::sleep(_period);
            CheckTransferServers();
        }
    }

    void TransferWorker::SendCreateBucketRequest(const std::string &bucket) {

        std::string url = _baseUrl + "/" + bucket;
        Dto::S3::CreateBucketConstraint location = {.location=_region};
        std::string body = location.ToXml();
        SendPutRequest(url, body, CONTENT_TYPE_JSON);
        log_debug_stream(_logger) << "Create bucket message request send" << std::endl;
    }

    bool TransferWorker::SendExistsBucketRequest(const std::string &bucket) {

        std::string url = _baseUrl + "/" + bucket;
        bool result = SendHeadRequest(url, CONTENT_TYPE_JSON);
        log_debug_stream(_logger) << "Bucket exists message request send, result: " << result << std::endl;
        return result;
    }
} // namespace AwsMock::Worker
