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
                std::map<std::string, std::shared_ptr<Service::FtpServer>>::iterator it = _transferServerList.find(transfer.serverId);
                if (it == _transferServerList.end()) {
                    StartTransferServer(transfer);
                }
            } else if (transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE)) {
                std::map<std::string, std::shared_ptr<Service::FtpServer>>::iterator it = _transferServerList.find(transfer.serverId);
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
            CheckTransferServers();
        }
    }

    void TransferWorker::SendCreateBucketRequest(const std::string &bucket, const std::string &contentType) {

        Poco::URI uri("http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket);
        std::string path(uri.getPathAndQuery());

        // Get the body
        std::string body = std::string(
            "<CreateBucketConfiguration xmlns=\"http://s3.amazonaws.com/doc/2006-03-01/\">\n<LocationConstraint>" + _region
                + "</LocationConstraint>\n</CreateBucketConfiguration>");

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "S3 create bucket message request created, bucket: " + bucket << std::endl;

        // Send request
        std::ostream &os = session.sendRequest(request);
        os << body;

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "S3 create bucket message request send, status: " << response.getStatus() << std::endl;
    }

    bool TransferWorker::SendExistsBucketRequest(const std::string &bucket, const std::string &contentType) {

        Poco::URI uri("http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_HEAD, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "S3 exists bucket message request created, bucket: " + bucket << std::endl;

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_debug_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
            return false;
        }
        log_debug_stream(_logger) << "S3 exists bucket message request send, status: " << response.getStatus() << std::endl;
        return true;
    }

    void TransferWorker::AddAuthorization(Poco::Net::HTTPRequest &request) {
        request.add("Authorization",
                    "AWS4-HMAC-SHA256 Credential=" + _user + "/" + _clientId + "/" + _region
                        + "/s3/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840");

    }

} // namespace AwsMock::Worker
