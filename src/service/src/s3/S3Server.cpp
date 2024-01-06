//
// Created by vogje01 on 04/01/2023.
//

#include "awsmock/service/S3Server.h"

namespace AwsMock::Service {

  S3Server::S3Server(Core::Configuration &configuration, Core::MetricService &metricService)
      : AbstractWorker(configuration), AbstractServer(configuration, "s3"), _logger(Poco::Logger::get("S3Server")), _configuration(configuration), _metricService(metricService), _module("s3") {

    // Get HTTP configuration values
    _port = _configuration.getInt("awsmock.service.s3.port", S3_DEFAULT_PORT);
    _host = _configuration.getString("awsmock.service.s3.host", S3_DEFAULT_HOST);
    _maxQueueLength = _configuration.getInt("awsmock.service.s3.max.queue", S3_DEFAULT_QUEUE_SIZE);
    _maxThreads = _configuration.getInt("awsmock.service.s3.max.threads", S3_DEFAULT_MAX_THREADS);
    _requestTimeout = _configuration.getInt("awsmock.service.s3.timeout", S3_DEFAULT_TIMEOUT);

    // Directories
    _dataDir = _configuration.getString("awsmock.service.s3.data.dir");
    Core::DirUtils::EnsureDirectory(_dataDir);
    log_debug_stream(_logger) << "Data directory path: " << _dataDir << std::endl;

    // Sleeping period
    _period = _configuration.getInt("awsmock.worker.s3.period", 10000);
    log_debug_stream(_logger) << "Worker period: " << _period << std::endl;

    // Create environment
    _region = _configuration.getString("awsmock.region", "eu-central_1");
    _accountId = _configuration.getString("awsmock.account.id", "000000000000");
    _clientId = _configuration.getString("awsmock.client.id", "00000000");
    _user = _configuration.getString("awsmock.user", "none");

    // S3 module connection
    _s3ServiceHost = _configuration.getString("awsmock.service.s3.host", "localhost");
    _s3ServicePort = _configuration.getInt("awsmock.service.s3.port", 9501);
    log_debug_stream(_logger) << "S3 module endpoint: http://" << _s3ServiceHost << ":" << _s3ServicePort << std::endl;

    // Database connections
    _serviceDatabase = std::make_unique<Database::ModuleDatabase>(_configuration);
    _s3Database = std::make_unique<Database::S3Database>(_configuration);
    log_debug_stream(_logger) << "S3 module initialized, endpoint: " << _host << ":" << _port << std::endl;
  }

  S3Server::~S3Server() {
    StopServer();
  }

  void S3Server::MainLoop() {

    // Check module active
    if (!IsActive("s3")) {
      log_info_stream(_logger) << "S3 module inactive" << std::endl;
      return;
    }
    log_info_stream(_logger) << "S3 module starting" << std::endl;

    // Start monitoring thread
    StartMonitoringServer();

    // Start REST module
    StartHttpServer(_maxQueueLength, _maxThreads, _requestTimeout, _host, _port, new S3RequestHandlerFactory(_configuration, _metricService));

    while (IsRunning()) {

      log_debug_stream(_logger) << "S3 processing started" << std::endl;

      // Wait for timeout or condition
      if (InterruptableSleep(_period)) {
        StopMonitoringServer();
        break;
      }
      UpdateCounters();
    }
  }

  void S3Server::StartMonitoringServer() {
    _threadPool.StartThread(_configuration, _metricService, _condition);
  }

  void S3Server::StopMonitoringServer() {
    _threadPool.stopAll();
  }

  void S3Server::UpdateCounters() {
    long buckets = _s3Database->BucketCount();
    long objects = _s3Database->ObjectCount();
    _metricService.SetGauge("s3_bucket_count", buckets);
    _metricService.SetGauge("s3_object_count", objects);
  }

  void S3Server::GetBucketKeyFromFile(const std::string &fileName, std::string &bucket, std::string &key) {

    // Remove data dir
    std::string file = Poco::replace(fileName, _dataDir.c_str(), "");

    // Remove starting slash
    bucket = Core::HttpUtils::GetPathParameter(file, 0);
    key = Core::HttpUtils::GetPathParametersFromIndex(file, 1);
  }

  std::string S3Server::GetFileFromBucketKey(const std::string &bucket, const std::string &key) {
    return _dataDir + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
  }

  void S3Server::CreateBucket(const std::string &dirPath) {

    // Get bucket, key
    std::string bucket, key;
    GetBucketKeyFromFile(dirPath, bucket, key);

    // Set parameter
    std::string owner = Core::FileUtils::GetOwner(dirPath);

    SendCreateBucketRequest(bucket, "application/octet-stream");
  }

  void S3Server::DeleteBucket(const std::string &dirPath) {

    // Get bucket, key
    std::string bucket, key;
    GetBucketKeyFromFile(dirPath, bucket, key);

    // Set parameter
    std::string owner = Core::FileUtils::GetOwner(dirPath);

    SendDeleteBucketRequest(bucket, "application/octet-stream");
  }

  void S3Server::CreateObject(const std::string &filePath) {

    // Get bucket, key
    std::string bucket, key;
    GetBucketKeyFromFile(filePath, bucket, key);

    // Get file size, MD5 sum
    if (Core::FileUtils::FileExists(filePath)) {
      unsigned long size = Core::FileUtils::FileSize(filePath);
      std::string md5sum = Core::Crypto::GetMd5FromFile(filePath);
      std::string owner = Core::FileUtils::GetOwner(filePath);
      SendPutObjectRequest(filePath, bucket, key, md5sum, "application/octet-stream", size);
    }
  }

  bool S3Server::ExistsObject(const std::string &bucket, const std::string &key) {

    // Send object metadata request to S3 module, if the object is not existing return false
    return SendHeadObjectRequest(bucket, key, "application/octet-stream");
  }

  bool S3Server::ExistsBucket(const std::string &bucket) {

    // Send object metadata request to S3 module, if the object is not existing return false
    return SendHeadObjectRequest(bucket, "application/octet-stream");
  }

  void S3Server::DeleteObject(const std::string &bucket, const std::string &key) {

    // Send delete object request to S3 module
    SendDeleteObjectRequest(bucket, key, "application/octet-stream");
  }

  void S3Server::SendCreateBucketRequest(const std::string &bucket, const std::string &contentType) {

    Dto::S3::CreateBucketConstraint constraint = {.location=_region};
    std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket;
    std::string body = constraint.ToXml();

    SendPutRequest(_module, url, body, contentType);
    log_debug_stream(_logger) << "S3 create bucket request send" << std::endl;
  }

  void S3Server::SendDeleteBucketRequest(const std::string &bucket, const std::string &contentType) {

    std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket;
    SendDeleteRequest(_module, url, {}, contentType);
    log_debug_stream(_logger) << "S3 delete bucket request send" << std::endl;
  }

  void S3Server::SendPutObjectRequest(const std::string &fileName, const std::string &bucket, const std::string &key, const std::string &md5Sum, const std::string &contentType, unsigned long fileSize) {

    std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key;
    std::map<std::string, std::string> headers;

    headers["Content-Length"] = std::to_string(fileSize);
    headers["Content-Type"] = contentType;
    headers["Content-MD5"] = md5Sum;
    headers["Content-Type"] = contentType;
    headers["Content-Intern"] = "true";

    SendFile(_module, url, fileName, headers);
    log_debug_stream(_logger) << "S3 put object request send" << std::endl;
  }

  bool S3Server::SendHeadObjectRequest(const std::string &bucket, const std::string &contentType) {

    std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket;
    return SendHeadRequest(_module, url, contentType);
  }

  bool S3Server::SendHeadObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType) {

    std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key;
    return SendHeadRequest(_module, url, contentType);
  }

  void S3Server::SendDeleteObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType) {

    std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key;
    SendDeleteRequest(_module, url, {}, contentType);
    log_debug_stream(_logger) << "S3 delete object request send" << std::endl;
  }
}
