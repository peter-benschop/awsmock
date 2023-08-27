//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/S3Worker.h>
#include "awsmock/core/ResourceNotFoundException.h"

namespace AwsMock::Worker {

    S3Worker::S3Worker(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Worker")), _configuration(configuration), _running(false) {

        Initialize();
    }

    S3Worker::~S3Worker() {
        _watcherThread.wakeUp();
        delete _watcher;
    }

    void S3Worker::Initialize() {

        _dataDir = _configuration.getString("awsmock.service.s3.data.dir");
        _tmpDir = _dataDir + Poco::Path::separator() + "tmp";
        _watcherDir = _dataDir + Poco::Path::separator() + "watcher";
        log_debug_stream(_logger) << "Watching path: " << _watcherDir << std::endl;

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.s3.period", 10000);
        log_debug_stream(_logger) << "Worker period: " << _period << std::endl;

        // Create S3 directories
        if (!Core::DirUtils::DirectoryExists(_dataDir)) {
            Core::DirUtils::MakeDirectory(_dataDir);
        }
        if (!Core::DirUtils::DirectoryExists(_watcherDir)) {
            Core::DirUtils::MakeDirectory(_watcherDir);
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

        // Start _watcher
        _watcher = new Core::DirectoryWatcher(_watcherDir);
        _watcher->itemAdded += Poco::delegate(this, &S3Worker::OnFileAdded);
        _watcher->itemModified += Poco::delegate(this, &S3Worker::OnFileModified);
        _watcher->itemDeleted += Poco::delegate(this, &S3Worker::OnFileDeleted);
        log_debug_stream(_logger) << "Directory _watcher added, path: " << _watcherDir << std::endl;

        log_debug_stream(_logger) << "S3Worker initialized" << std::endl;
    }

    void S3Worker::Synchronize() {

        // Check all local files against database
        for(const std::string& filePath : Core::DirUtils::ListFiles(_dataDir)) {

            // Don't consider directories
            if (Core::DirUtils::IsDirectory(filePath) || Core::StringUtils::StartsWith(filePath, _watcherDir) || Core::StringUtils::StartsWith(filePath, _tmpDir)) {
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

        // Start file watcher, they will call the delegate methods, if they find a file system event.
        _watcherThread.start(_watcher);

        // Synchronize current file system state
        Synchronize();

        _running = true;
        while (_running) {
            _logger.debug() << "S3Worker processing started" << std::endl;
            Poco::Thread::sleep(_period);
        }
    }

    void S3Worker::OnFileAdded(const Core::DirectoryEvent &addedEvent) {
        log_debug_stream(_logger) << "Added path: " << addedEvent.item.path() << std::endl;

        if (Core::DirUtils::IsDirectory(addedEvent.item.path())) {
            CreateBucket(addedEvent.item.path());
        } else {
            CreateObject(addedEvent.item.path());
        }
    }

    void S3Worker::OnFileModified(const Core::DirectoryEvent &modifiedEvent) {
        log_debug_stream(_logger) << "Changed path: " << modifiedEvent.item.path() << std::endl;

        if(Core::DirUtils::IsDirectory(modifiedEvent.item.path())) {
            return;
        }

        // Get bucket, key
        std::string bucket, key;
        GetBucketKeyFromFile(modifiedEvent.item.path(), bucket, key);

        // Get file size, MD5 sum
        long size = Core::FileUtils::FileSize(modifiedEvent.item.path());
        std::string md5sum = Core::Crypto::GetMd5FromFile(modifiedEvent.item.path());
        std::string owner = Core::FileUtils::GetOwner(modifiedEvent.item.path());

        SendPutObjectRequest(modifiedEvent.item.path(), bucket, key, md5sum, "application/octet-stream", size);
    }

    void S3Worker::OnFileDeleted(const Core::DirectoryEvent &deleteEvent) {
        log_debug_stream(_logger) << "Deleted path: " << deleteEvent.item.path() << std::endl;

        // Get bucket, key
        std::string bucketName, key;
        GetBucketKeyFromFile(deleteEvent.item.path(), bucketName, key);

        SendDeleteObjectRequest(bucketName, key, "application/octet-stream");
    }

    void S3Worker::GetBucketKeyFromFile(const std::string &fileName, std::string &bucket, std::string &key) {

        std::string file;
        if (Core::StringUtils::Contains(fileName, "watcher")) {
            file = Poco::replace(fileName, _watcherDir.c_str(), "");
        } else {
            file = Poco::replace(fileName, _dataDir.c_str(), "");
        }

        Poco::RegularExpression::MatchVec posVec;
        Poco::RegularExpression pattern(R"(/([a-zA-Z0-9-.]+)/?([a-zA-Z0-9-_/.*'()]+)?$)");
        if (!pattern.match(file, 0, posVec)) {
            throw Core::ResourceNotFoundException("Could not extract bucket and key");
        }

        if (posVec.size() > 1) {
            bucket = file.substr(posVec[1].offset, posVec[1].length);
        }
        if (posVec.size() > 2) {
            key = file.substr(posVec[2].offset, posVec[2].length);
        }
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
        unsigned long size = Core::FileUtils::FileSize(filePath);
        std::string md5sum = Core::Crypto::GetMd5FromFile(filePath);
        std::string owner = Core::FileUtils::GetOwner(filePath);

        SendPutObjectRequest(filePath, bucket, key, md5sum, "application/octet-stream", size);
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

    void S3Worker::SendDeleteBucketRequest(const std::string &bucket, const std::string &contentType) {

        Poco::URI uri("http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_DELETE, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "S3 delete bucket message request created, bucket: " + bucket << std::endl;

        // Send request
        session.sendRequest(request);

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "S3 delete bucket message request send, status: " << response.getStatus() << std::endl;
    }

    void S3Worker::SendPutObjectRequest(const std::string &fileName,
                                        const std::string &bucket,
                                        const std::string &key,
                                        const std::string &md5Sum,
                                        const std::string &contentType,
                                        unsigned long fileSize) {

        Poco::URI uri("http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Length", std::to_string(fileSize));
        request.add("Content-Type", contentType);
        request.add("Content-MD5", md5Sum);
        AddAuthorization(request);
        log_debug_stream(_logger) << "S3 put object message request created, bucket: " + bucket << " key: " << key << std::endl;

        // Send request
        std::ifstream ifs(fileName);
        std::ostream &os = session.sendRequest(request);
        os << ifs.rdbuf();
        ifs.close();

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "S3 put object request send, status: " << response.getStatus() << std::endl;
    }

    bool S3Worker::SendHeadObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType) {

        Poco::URI uri("http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_HEAD, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        request.add("WriteFile", "false");
        AddAuthorization(request);
        log_debug_stream(_logger) << "S3 put object message request created, bucket: " + bucket << " key: " << key << std::endl;

        // Send request
        session.sendRequest(request);

        // Get the response status
        Poco::Net::HTTPResponse response;
        log_debug_stream(_logger) << "S3 head object request send, status: " << response.getStatus() << std::endl;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            return false;
        }
        return response.getContentLength() > 0;
    }

    void S3Worker::SendDeleteObjectRequest(const std::string &bucket, const std::string &key, const std::string &contentType) {

        Poco::URI uri("http://" + _s3ServiceHost + ":" + std::to_string(_s3ServicePort) + "/" + bucket + "/" + key);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_DELETE, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        request.add("WriteFile", "false");
        AddAuthorization(request);
        log_debug_stream(_logger) << "S3 delete object request created, bucket: " + bucket << " key: " << key << std::endl;

        // Send request
        session.sendRequest(request);

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "S3 delete object request send, status: " << response.getStatus() << std::endl;
    }

    void S3Worker::AddAuthorization(Poco::Net::HTTPRequest &request) {
        request.add("Authorization",
                    "AWS4-HMAC-SHA256 Credential=" + _user + "/" + _clientId + "/" + _region
                        + "/s3/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840");

    }

} // namespace AwsMock::Worker
