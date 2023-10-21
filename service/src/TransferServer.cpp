//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/service/TransferServer.h>

namespace AwsMock::Service {

  TransferServer::TransferServer(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractWorker(configuration), _logger(Poco::Logger::get("TransferWorker")), _configuration(configuration), _metricService(metricService), _running(false) {

    // REST server configuration
    _port = _configuration.getInt("awsmock.service.transfer.port", TRANSFER_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.transfer.host", TRANSFER_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.transfer.max.queue", TRANSFER_DEFAULT_QUEUE_LENGTH);
    _maxThreads = _configuration.getInt("awsmock.service.transfer.max.threads", TRANSFER_DEFAULT_THREADS);

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

    // Ensure base directory exists
    Core::DirUtils::EnsureDirectory(_baseDir);
    log_debug_stream(_logger) << "Using baseDir: " << _baseDir << std::endl;

    log_info_stream(_logger) << "TransferWorker initialized" << std::endl;
  }

  TransferServer::~TransferServer() {
    if (_httpServer) {
      _httpServer->stopAll(true);
      delete _httpServer;
      log_info_stream(_logger) << "Transfer rest service stopped" << std::endl;
    }
  }

  void TransferServer::StartHttpServer() {

    // Set HTTP server parameter
    auto *httpServerParams = new Poco::Net::HTTPServerParams();
    httpServerParams->setMaxQueued(_maxQueueLength);
    httpServerParams->setMaxThreads(_maxThreads);
    log_debug_stream(_logger) << "HTTP server parameter set, maxQueue: " << _maxQueueLength << " maxThreads: " << _maxThreads << std::endl;

    _httpServer =
        new Poco::Net::HTTPServer(new TransferRequestHandlerFactory(_configuration, _metricService), Poco::Net::ServerSocket(Poco::UInt16(_port)), httpServerParams);

    _httpServer->start();
    log_info_stream(_logger) << "Transfer rest service started, endpoint: http://" << _host << ":" << _port << std::endl;
  }

  void TransferServer::StartTransferServer(Database::Entity::Transfer::Transfer &server) {

    // Create transfer server thread
    _ftpServer = std::make_shared<FtpServer::FtpServer>(_configuration, server.serverId, server.port, server.listenAddress);
    _transferServerList[server.serverId] = _ftpServer;

    // Add users
    for (const auto &user : server.users) {

      std::string homeDir = _baseDir + Poco::Path::separator() + user.homeDirectory;

      // Ensure the home directory exists
      Core::DirUtils::EnsureDirectory(homeDir);
      log_debug_stream(_logger) << "Using homeDir: " << homeDir << std::endl;

      // Add to FTP server
      _ftpServer->addUser(user.userName, user.password, homeDir, FtpServer::Permission::All);
    }
    _ftpServer->start(server.concurrency);

    // Update database
    server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE);

    log_info_stream(_logger) << "Transfer server " << server.serverId << " started " << std::endl;
  }

  void TransferServer::StopTransferServer(Database::Entity::Transfer::Transfer &server) {

    // Create transfer server thread
    std::shared_ptr<FtpServer::FtpServer> ftpserver = _transferServerList[server.serverId];
    ftpserver->stop();

    // Update database
    server.state = Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::OFFLINE);

    log_debug_stream(_logger) << "Transfer server " << server.serverId << " stopped " << std::endl;
  }

  void TransferServer::StartTransferServers() {

    log_debug_stream(_logger) << "Starting transfer servers" << std::endl;
    std::vector<Database::Entity::Transfer::Transfer> transfers = _transferDatabase->ListServers(_region);

    for (auto &transfer : transfers) {
      if (transfer.state == Database::Entity::Transfer::ServerStateToString(Database::Entity::Transfer::ServerState::ONLINE)) {
        StartTransferServer(transfer);
      }
    }
  }

  void TransferServer::CheckTransferServers() {

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

  void TransferServer::run() {

    log_info_stream(_logger) << "Transfer worker started" << std::endl;

    // Check service active
    /*if (!_serviceDatabase->IsActive("Lambda")) {
        return;
    }*/

    // Start REST server
    StartHttpServer();

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

  void TransferServer::SendCreateBucketRequest(const std::string &bucket) {

    std::string url = _baseUrl + "/" + bucket;
    Dto::S3::CreateBucketConstraint location = {.location=_region};
    std::string body = location.ToXml();
    SendPutRequest(url, body, CONTENT_TYPE_JSON);
    log_debug_stream(_logger) << "Create bucket message request send" << std::endl;
  }

  bool TransferServer::SendExistsBucketRequest(const std::string &bucket) {

    std::string url = _baseUrl + "/" + bucket;
    bool result = SendHeadRequest(url, CONTENT_TYPE_JSON);
    log_debug_stream(_logger) << "Bucket exists message request send, result: " << result << std::endl;
    return result;
  }
} // namespace AwsMock::Service
