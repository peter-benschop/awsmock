//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/S3Worker.h>
#include "awsmock/core/ResourceNotFoundException.h"

namespace AwsMock::Worker {

    S3Worker::S3Worker(const Core::Configuration &configuration)
        : AbstractWorker(configuration), _logger(Poco::Logger::get("S3Worker")), _configuration(configuration), _running(false) {

        _dataDir = _configuration.getString("awsmock.service.s3.data.dir");
        _tmpDir = _dataDir + Poco::Path::separator() + "tmp";
        log_debug_stream(_logger) << "Data directory path: " << _dataDir << std::endl;

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.s3.period", 10000);
        log_debug_stream(_logger) << "Worker period: " << _period << std::endl;

        // Create S3 directories
        if (!Core::DirUtils::DirectoryExists(_dataDir)) {
            Core::DirUtils::MakeDirectory(_dataDir);
        }

        // Create environment
        _region = _configuration.getString("awsmock.region", "eu-central_1");
        _accountId = _configuration.getString("awsmock.account.id", "000000000000");
        _clientId = _configuration.getString("awsmock.client.id", "00000000");
        _user = _configuration.getString("awsmock.user", "none");

        // S3 service connection
        _s3ServiceHost = _configuration.getString("awsmock.service.s3.host", "localhost");
        _s3ServicePort = _configuration.getInt("awsmock.service.s3.port", 9501);
        log_debug_stream(_logger) << "S3 service endpoint: http://" << _s3ServiceHost << ":" << _s3ServicePort << std::endl;

        // Database connections
        _serviceDatabase = std::make_unique<Database::ServiceDatabase>(_configuration);
        _s3Database = std::make_unique<Database::S3Database>(_configuration);
        log_debug_stream(_logger) << "S3Worker initialized" << std::endl;

    }

    void S3Worker::Synchronize() {

        // Check all local files against database
        for(const std::string& filePath : Core::DirUtils::ListFiles(_dataDir)) {

            // Don't consider directories
            if (Core::DirUtils::IsDirectory(filePath)) {
                continue;
            }

            //Core::FileUtils::Touch(filePath);
            // Get bucket, key
            std::string bucket, key;
            GetBucketKeyFromFile(filePath, bucket, key);

            // Check database
            if (!ExistsObject(bucket, key)) {
                CreateObject(filePath);
            }
            Poco::Thread::sleep(1000);
        }

        // Check all database files against file system
        Database::Entity::S3::ObjectList objects = _s3Database->ListObjects();
        for(const Database::Entity::S3::Object& object : objects) {

            // Get bucket, key
            std::string filePath;
            GetFileFromBucketKey(filePath, object.bucket, object.key);

            // Check file system
            if(!Core::FileUtils::FileExists(filePath)) {
                DeleteObject(object.bucket, object.key);
            }
        }
    }

    void S3Worker::run() {

        log_info_stream(_logger) << "S3 worker started" << std::endl;

        // Check service active
//        if (!_serviceDatabase->IsActive("S3")) {
//            return;
//        }

        // Synchronize current file system state
        Synchronize();

        _running = true;
        while (_running) {
            _logger.debug() << "S3Worker processing started" << std::endl;
            Poco::Thread::sleep(_period);
        }
    }

    void S3Worker::GetBucketKeyFromFile(const std::string &fileName, std::string &bucket, std::string &key) {

        // Remove data dir
        std::string file = Poco::replace(fileName, _dataDir.c_str(), "");

        // Remove starting slash
        bucket = Core::HttpUtils::GetPathParameter(file, 0);
        key = Core::HttpUtils::GetPathParametersFromIndex(file, 1);
    }

    void S3Worker::GetFileFromBucketKey(std::string &fileName, const std::string &bucket, const std::string &key) {
        fileName = _dataDir + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
    }

    void S3Worker::CreateBucket(const std::string &dirPath) {

        // Get bucket, key
        std::string bucket, key;
        GetBucketKeyFromFile(dirPath, bucket, key);

        // Set parameter
        std::string owner = Core::FileUtils::GetOwner(dirPath);

        SendCreateBucketRequest(bucket, "application/octet-stream");
    }

    void S3Worker::DeleteBucket(const std::string &dirPath) {

        // Get bucket, key
        std::string bucket, key;
        GetBucketKeyFromFile(dirPath, bucket, key);

        // Set parameter
        std::string owner = Core::FileUtils::GetOwner(dirPath);

        SendDeleteBucketRequest(bucket, "application/octet-stream");
    }

    void S3Worker::CreateObject(const std::string &filePath) {

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

    bool S3Worker::ExistsObject(const std::string &bucket, const std::string &key) {

        // Send object metadata request to S3 service, if the object is not existing return false
        return SendHeadObjectRequest(bucket, key, "application/octet-stream");
    }

    void S3Worker::DeleteObject(const std::string &bucket, const std::string &key) {

        // Send delete object request to S3 service
        SendDeleteObjectRequest(bucket, key, "application/octet-stream");
    }

    void S3Worker::SendCreateBucketRequest(const std::string &bucket, const std::string &contentType) {

        Dto::S3::CreateBucketConstraint constraint = {.location=_region};
        std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket;
        std::string body = constraint.ToXml();

        SendPutRequest(url, body, contentType);
        log_debug_stream(_logger) << "S3 create bucket request send" << std::endl;
    }

    void S3Worker::SendDeleteBucketRequest(const std::string &bucket, const std::string &contentType) {

        std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket;
        SendDeleteRequest(url, {}, contentType);
        log_debug_stream(_logger) << "S3 delete bucket request send" << std::endl;
    }

    void S3Worker::SendPutObjectRequest(const std::string &fileName,
                                        const std::string &bucket,
                                        const std::string &key,
                                        const std::string &md5Sum,
                                        const std::string &contentType,
                                        unsigned long fileSize) {

        std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key;
        std::map<std::string, std::string> headers;

        headers["Content-Length"] = std::to_string(fileSize);
        headers["Content-Type"] = contentType;
        headers["Content-MD5"] = md5Sum;
        headers["Content-Type"]= contentType;
        headers["Content-Intern"]= "true";

        SendFile(url, fileName, headers);
        log_debug_stream(_logger) << "S3 put object request send" << std::endl;
    }

    bool S3Worker::SendHeadObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType) {

        std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key;
        return SendHeadRequest(url, contentType);
    }

    void S3Worker::SendDeleteObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType) {

        std::string url = "http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key;
        SendDeleteRequest(url, {}, contentType);
        log_debug_stream(_logger) << "S3 delete object request send" << std::endl;
    }

} // namespace AwsMock::Worker
