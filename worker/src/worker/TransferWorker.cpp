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

        // S3 service connection
        _s3ServiceHost = _configuration.getString("awsmock.service.s3.host", "localhost");
        _s3ServicePort = _configuration.getInt("awsmock.service.s3.port", 9501);
        _baseUrl = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort);
        log_debug_stream(_logger) << "S3 service endpoint: http://" << _s3ServiceHost << ":" << _s3ServicePort << std::endl;

        // Send create bucket request
        if (!Core::DirUtils::DirectoryExists(_baseDir)) {
            Core::DirUtils::MakeDirectory(_baseDir);
            log_debug_stream(_logger) << "Using baseDir: " << _baseDir << std::endl;
        }

        // Start _watcher
        _watcher = std::make_shared<Core::DirectoryWatcher>(_baseDir);
        _watcher->itemAdded += Poco::delegate(this, &TransferWorker::OnFileAdded);
        _watcher->itemModified += Poco::delegate(this, &TransferWorker::OnFileModified);
        _watcher->itemDeleted += Poco::delegate(this, &TransferWorker::OnFileDeleted);
        log_debug_stream(_logger) << "TransferWorker initialized" << std::endl;
    }

    void TransferWorker::StartTransferServer(Database::Entity::Transfer::Transfer &server) {

        // Create transfer server thread
        _ftpServer = std::make_shared<FtpServer::FtpServer>(_configuration);
        _transferServerList[server.serverId] = _ftpServer;
        _ftpServer->setName(server.serverId);

        // Add users
        for (const auto &user : server.users) {
            std::string homeDir = _baseDir + Poco::Path::separator() + user.homeDirectory;
            _ftpServer->addUser(user.userName, user.password, homeDir, FtpServer::Permission::All);
        }
        _ftpServer->start(4);

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

        // Start file watcher, they will call the delegate methods, if they find a file system event.
        _watcherThread.start(*_watcher);

        _running = true;
        while (_running) {
            log_debug_stream(_logger) << "TransferWorker processing started" << std::endl;
            Poco::Thread::sleep(_period);
            CheckTransferServers();
        }
    }

    void TransferWorker::OnFileAdded(const Core::DirectoryEvent &addedEvent) {
        log_info_stream(_logger) << "File added, path: " << addedEvent.item << std::endl;

        // Get key
        std::string key = GetKey(addedEvent.item);
        std::string user = GetUser(key);
        SendCreateObjectRequest(_bucket, key, user, addedEvent.item);
    }

    void TransferWorker::OnFileModified(const Core::DirectoryEvent &modifiedEvent) {
        log_info_stream(_logger) << "File modified, path: " << modifiedEvent.item << std::endl;

        // Get key
        std::string key = GetKey(modifiedEvent.item);
        std::string user = GetUser(key);
        SendCreateObjectRequest(_bucket, key, user, modifiedEvent.item);
    }

    void TransferWorker::OnFileDeleted(const Core::DirectoryEvent &deleteEvent) {
        log_info_stream(_logger) << "File deleted path: " << deleteEvent.item << std::endl;

        // Get key
        std::string key = GetKey(deleteEvent.item);
        SendDeleteObjectRequest(_bucket, key);
    }

    void TransferWorker::SendCreateBucketRequest(const std::string &bucket) {

        std::string url = _baseUrl + "/" + bucket;
        Dto::S3::CreateBucketConstraint location = {.location=_region};
        std::string body = location.ToXml();
        SendPutRequest(url, body, CONTENT_TYPE_JSON);
        log_debug_stream(_logger) << "Create bucket message request send" << std::endl;
    }

    void TransferWorker::SendCreateObjectRequest(const std::string &bucket, const std::string &key, const std::string &user, const std::string &fileName) {

       // std::string serverName = _ftpServer->GetServerName();
        std::string url = _baseUrl + "/" + bucket + "/" + key;
        std::map<std::string, std::string> headers;
        headers["Content-MD5"] = Core::Crypto::Base64Encode(Core::Crypto::GetMd5FromFile(fileName));
        headers["Content-Length"] = std::to_string(Core::FileUtils::FileSize(fileName));
        headers["x-amz-sdk-checksum-algorithm"] = "SHA256";
        headers["x-amz-checksum-sha256"] = Core::Crypto::GetSha256FromFile(fileName);
        headers["x-amz-meta-user-agent"] = "AWSTransfer";
        //headers["x-amz-meta-user-agent-id"] = user + "@" + serverName;
        SendFile(url, fileName, headers);
        log_debug_stream(_logger) << "Create object message request send, url: " << url << std::endl;
    }

    bool TransferWorker::SendExistsBucketRequest(const std::string &bucket) {

        std::string url = _baseUrl + "/" + bucket;
        bool result = SendHeadRequest(url, CONTENT_TYPE_JSON);
        log_debug_stream(_logger) << "Bucket exists message request send, result: " << result << std::endl;
        return result;
    }

    void TransferWorker::SendDeleteObjectRequest(const std::string &bucket, const std::string &key) {

        std::string url = _baseUrl + "/" + bucket + "/" + key;
        SendDeleteRequest(url, {}, CONTENT_TYPE_JSON);
        log_debug_stream(_logger) << "Delete bucket message request send" << std::endl;
    }

    std::string TransferWorker::GetKey(const std::string &path) {
        std::string key = Core::StringUtils::StripBeginning(path, _baseDir);
        if (!key.empty() && key[0] == '/') {
            return key.substr(1);
        }
        return key;
    }

    std::string TransferWorker::GetUser(const std::string &path) {
        std::vector<std::string> parts = Core::StringUtils::Split(path, '/');
        if(parts.empty()) {
          return {};
        }
        return parts[1];
    }
} // namespace AwsMock::Worker
