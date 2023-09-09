//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/TransferWorker.h>

namespace AwsMock::Worker {

    [[maybe_unused]] TransferWorker::TransferWorker(const Core::Configuration &configuration)
        : AbstractWorker(configuration), _logger(Poco::Logger::get("TransferWorker")), _configuration(configuration), _running(false) {

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.transfer.period", 10000);
        log_debug_stream(_logger) << "Lambda worker period: " << _period << std::endl;

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _clientId = _configuration.getString("awsmock.client.id", "00000000");
        _user = _configuration.getString("awsmock.user", "none");
        _transferDatabase = std::make_unique<Database::TransferDatabase>(_configuration);

        // Bucket
        _bucket = _configuration.getString("awsmock.service.ftp.bucket", DEFAULT_TRANSFER_BUCKET);

        // S3 service connection
        _s3ServiceHost = _configuration.getString("awsmock.service.s3.host", "localhost");
        _s3ServicePort = _configuration.getInt("awsmock.service.s3.port", 9501);
        log_debug_stream(_logger) << "S3 service endpoint: http://" << _s3ServiceHost << ":" << _s3ServicePort << std::endl;

        log_debug_stream(_logger) << "TransferWorker initialized" << std::endl;
    }

    void TransferWorker::StartTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer server thread
        std::shared_ptr<Service::FtpServer> ftpserver = std::make_shared<Service::FtpServer>(_configuration);
        _transferServerList[server.serverId] = ftpserver;

        // Add users
        for (const auto &user : server.users) {
            ftpserver->AddUser(user.userName, user.password, user.homeDirectory);
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
        if (!SendExistsBucketRequest(_bucket, "application/json")) {
            SendCreateBucketRequest(_bucket, "application/json");
            log_debug_stream(_logger) << "Sending S3 create bucket: " << _bucket << std::endl;
        }

        // Start all lambda functions
        StartTransferServers();

        _running = true;
        while (_running) {
            log_debug_stream(_logger) << "TransferWorker processing started" << std::endl;
            Poco::Thread::sleep(_period);
            //CheckTransferServers();
        }
    }

    void TransferWorker::SendCreateBucketRequest(const std::string &bucket, const std::string &contentType) {

        std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket;
        Dto::S3::CreateBucketConstraint location = {.location=_region};
        std::string body = location.ToXml();
        SendPutRequest(url, body, contentType);
        log_debug_stream(_logger) << "S3 create bucket message request send" << std::endl;
    }

    bool TransferWorker::SendExistsBucketRequest(const std::string &bucket, const std::string &contentType) {

        std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket;
        bool result = SendHeadRequest(url, contentType);
        log_debug_stream(_logger) << "S3 exists bucket message request send, result: " << result << std::endl;
        return result;
    }

} // namespace AwsMock::Worker
