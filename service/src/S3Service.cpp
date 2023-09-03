//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/S3Service.h>

namespace AwsMock::Service {

    S3Service::S3Service(const Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Service")), _configuration(configuration) {

        // Initialize environment
        _dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data") + Poco::Path::separator() + "s3";
        _watcherDir = _dataDir + Poco::Path::separator() + "watcher";
        _tempDir = _dataDir + Poco::Path::separator() + "tmp";
        _database = std::make_unique<Database::S3Database>(_configuration);

        // SQS service connection
        _sqsServiceHost = _configuration.getString("awsmock.service.sqs.host", "localhost");
        _sqsServicePort = _configuration.getInt("awsmock.service.sqs.port", 9501);

        // Lambda service connection
        _lambdaServiceHost = _configuration.getString("awsmock.service.lambda.host", "localhost");
        _lambdaServicePort = _configuration.getInt("awsmock.service.lambda.port", 9503);

        // Create temp directory
        if (!Core::DirUtils::DirectoryExists(_tempDir)) {
            Core::DirUtils::MakeDirectory(_tempDir);
        }
    }

    Dto::S3::CreateBucketResponse S3Service::CreateBucket(const std::string &name, const std::string &owner, const Dto::S3::CreateBucketRequest &s3Request) {
        log_trace_stream(_logger) << "Create bucket request, s3Request: " << s3Request.ToString() << std::endl;

        // Get region
        std::string region = s3Request._locationConstraint;

        // Check existence
        if (_database->BucketExists({.region=region, .name=name})) {
            throw Core::ServiceException("Bucket exists already", 403);
        }

        Dto::S3::CreateBucketResponse createBucketResponse;
        try {
            // Create directory
            std::string bucketDir = _dataDir + Poco::Path::separator() + name;
            if (!Core::DirUtils::DirectoryExists(bucketDir)) {
                Core::DirUtils::MakeDirectory(bucketDir);
            }

            // Create watcher directory
            std::string watcherDir = _watcherDir + Poco::Path::separator() + name;
            if (!Core::DirUtils::DirectoryExists(watcherDir)) {
                Core::DirUtils::MakeDirectory(watcherDir);
            }

            // Update database
            _database->CreateBucket({.region=region, .name=name, .owner=owner});

            createBucketResponse = Dto::S3::CreateBucketResponse(region, "arn");
            log_trace_stream(_logger) << "S3 create bucket response: " << createBucketResponse.ToXml() << std::endl;
            log_info_stream(_logger) << "Bucket created, bucket: " << name << std::endl;

        } catch (Poco::Exception &exc) {
            log_error_stream(_logger) << "S3 create bucket failed, message: " << exc.message() << std::endl;
            throw Core::ServiceException(exc.message(), 500);
        }
        return createBucketResponse;
    }

    Dto::S3::GetMetadataResponse S3Service::GetMetadata(Dto::S3::GetMetadataRequest &request) {
        log_trace_stream(_logger) << "Get metadata request, s3Request: " << request.ToString() << std::endl;

        // Check existence
        if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", 403);
        }

        if (!_database->ObjectExists({.bucket=request.bucket, .key=request.key})) {
            throw Core::ServiceException("Object does not exist", 403);
        }

        Dto::S3::GetMetadataResponse getMetadataResponse;
        try {
            Database::Entity::S3::Object object = _database->GetObject(request.region, request.bucket, request.key);

            getMetadataResponse.bucket = object.bucket;
            getMetadataResponse.key = object.key;
            getMetadataResponse.size = object.size;
            getMetadataResponse.md5Sum = object.md5sum;
            getMetadataResponse.contentType = object.contentType;
            getMetadataResponse.modified = object.modified;
            getMetadataResponse.created = object.modified;
            log_trace_stream(_logger) << "S3 get object metadata response: " + getMetadataResponse.ToString() << std::endl;
            log_info_stream(_logger) << "Metadata returned, bucket: " << request.bucket << " key: " << request.key << std::endl;

        } catch (Poco::Exception &ex) {
            log_warning_stream(_logger) << "S3 get object metadata failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
        return getMetadataResponse;
    }

    Dto::S3::GetObjectResponse S3Service::GetObject(Dto::S3::GetObjectRequest &request) {
        log_trace_stream(_logger) << "Get object request, s3Request: " << request.ToString() << std::endl;

        Dto::S3::GetObjectResponse getObjectResponse;
        try {

            Database::Entity::S3::Object object = _database->GetObject(request.bucket, request.bucket, request.key);

            std::string filename = _dataDir + Poco::Path::separator() + request.bucket + Poco::Path::separator() + request.key;
            getObjectResponse.bucket = object.bucket;
            getObjectResponse.key = object.key;
            getObjectResponse.size = object.size;
            getObjectResponse.contentType = object.contentType;
            getObjectResponse.filename = filename;
            getObjectResponse.modified = object.modified;
            log_trace_stream(_logger) << "S3 get object response: " << getObjectResponse.ToString() << std::endl;
            log_info_stream(_logger) << "Object returned, bucket: " << request.bucket << " key: " << request.key << std::endl;

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 get object failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
        return getObjectResponse;
    }

    Dto::S3::ListAllBucketResponse S3Service::ListAllBuckets() {
        log_trace_stream(_logger) << "List all buckets request" << std::endl;

        try {

            Database::Entity::S3::BucketList bucketList = _database->ListBuckets();
            auto listAllBucketResponse = Dto::S3::ListAllBucketResponse(bucketList);
            log_debug_stream(_logger) << "Count all buckets, size: " << bucketList.size() << std::endl;

            return listAllBucketResponse;

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 Create Bucket failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    Dto::S3::ListBucketResult S3Service::ListBucket(const Dto::S3::ListBucketRequest &request) {
        log_trace_stream(_logger) << "List bucket request: " + request.ToString() << std::endl;

        try {

            Database::Entity::S3::ObjectList objectList = _database->ListBucket(request.name, request.prefix);
            Dto::S3::ListBucketResult listBucketResult = Dto::S3::ListBucketResult(request.name, objectList);
            log_info_stream(_logger) << "Bucket list returned, count: " << objectList.size() << std::endl;

            return listBucketResult;

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 list bucket failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    Dto::S3::InitiateMultipartUploadResult S3Service::CreateMultipartUpload(std::string &bucket, std::string &key, const std::string &region, const std::string &user) {
        log_trace_stream(_logger) << "CreateMultipartUpload request, bucket: " + bucket << " key: " << key << " region: " << region << " user: " << user << std::endl;

        // Check existence
        if (!_database->BucketExists({.region=region, .name=bucket})) {
            throw Core::ServiceException("Bucket does not exist", 403);
        }

        std::string uploadId = Core::StringUtils::GenerateRandomString(58);

        // Create upload directory, if not existing
        std::string uploadDir = GetMultipartUploadDirectory(uploadId);
        if (!Core::DirUtils::DirectoryExists(uploadDir)) {
            Core::DirUtils::MakeDirectory(uploadDir);
        }
        log_info_stream(_logger) << "Multipart upload started, bucket: " << bucket << " key: " << key << std::endl;
        return {.bucket=bucket, .key=key, .uploadId=uploadId};
    }

    std::string S3Service::UploadPart(std::istream &stream, int part, const std::string &uploadId) {
        log_trace_stream(_logger) << "UploadPart request, part: " << part << " updateId: " << uploadId << std::endl;

        std::string uploadDir = GetMultipartUploadDirectory(uploadId);
        log_trace_stream(_logger) << "Using uploadDir: " << uploadDir << std::endl;

        std::ofstream ofs(uploadDir + Poco::Path::separator() + uploadId + "-" + std::to_string(part));
        ofs << stream.rdbuf();
        log_trace_stream(_logger) << "Part uploaded, part: " << part << " dir: " << uploadDir << std::endl;

        log_info_stream(_logger) << "Upload part succeeded, part: " << part << std::endl;
        return Core::StringUtils::GenerateRandomString(40);
    }

    Dto::S3::CompleteMultipartUploadResult S3Service::CompleteMultipartUpload(const std::string &uploadId,
                                                                              const std::string &bucket,
                                                                              const std::string &key,
                                                                              const std::string &region,
                                                                              const std::string &user) {
        log_trace_stream(_logger) << "CompleteMultipartUpload request, uploadId: " << uploadId << " bucket: " << bucket << " key: " << key << " region: " << region
                                  << " user: " << user;

        // Get all file parts
        std::string uploadDir = GetMultipartUploadDirectory(uploadId);
        std::vector<std::string> files = Core::DirUtils::ListFilesByPrefix(uploadDir, uploadId);

        // Create bucket directory, if not existing
        std::string fileDir = _dataDir + Poco::Path::separator() + bucket + Poco::Path::separator() + GetDirFromKey(key);
        if (!Core::DirUtils::DirectoryExists(fileDir)) {
            Core::DirUtils::MakeDirectory(fileDir);
        }

        // Output file
        std::string outFile = _dataDir + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
        log_trace_stream(_logger) << "Output file, outFile: " << outFile << std::endl;

        // Append all parts to the output file
        Core::FileUtils::AppendBinaryFiles(outFile, _tempDir, files);
        log_trace_stream(_logger) << "Input files appended to outfile, outFile: " << outFile << std::endl;

        // Get file size, MD5 sum
        long fileSize = (long) Core::FileUtils::FileSize(outFile);
        std::string md5sum = Core::Crypto::GetMd5FromFile(outFile);
        log_trace_stream(_logger) << "Got file metadata, md5sum: " << md5sum << " size: " << fileSize << " outFile: " << outFile << std::endl;

        // Create database object
        Database::Entity::S3::Object object = _database->CreateOrUpdateObject({
            .region=region,
            .bucket=bucket,
            .key=key,
            .owner=user,
            .size=fileSize,
            .md5sum=md5sum
        });

        // Cleanup
        Core::DirUtils::DeleteDirectory(uploadDir);

        // Check notifications
        CheckNotifications(region, bucket, key, object.size, "s3:ObjectCreated:Put");

        log_info_stream(_logger) << "Multipart upload finished, bucket: " << bucket << " key: " << key << std::endl;
        return {.location=region, .bucket=bucket, .key=key, .etag=Core::StringUtils::GenerateRandomString(40)};
    }

    Dto::S3::PutObjectResponse S3Service::PutObject(Dto::S3::PutObjectRequest &request, std::istream *stream) {
        log_trace_stream(_logger) << "Put object request: " << request.ToString() << std::endl;

        // Check existence
        if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
            log_error_stream(_logger) << "Bucket does not exist, region: " << request.region + " bucket: " << request.bucket << std::endl;
            throw Core::ServiceException("Bucket does not exist", 403);
        }

        try {
            // Create directory, if not existing
            std::string directory = GetDirectory(request.bucket, request.key);
            if (!Core::DirUtils::DirectoryExists(directory)) {
                Core::DirUtils::MakeDirectory(directory);
                log_debug_stream(_logger) << "Local bucket directory created, path: " << directory << std::endl;
            }

            // Write file
            std::string fileName = GetFilename(request.bucket, request.key);
            if (stream) {
                std::ofstream ofs(fileName);
                ofs << stream->rdbuf();
                ofs.flush();
                ofs.close();
            }

            // Meta data
            long size = Core::FileUtils::FileSize(fileName);
            std::string md5sum = size > 0 ? Core::Crypto::GetMd5FromFile(fileName) : "d41d8cd98f00b204e9800998ecf8427e";
            log_info_stream(_logger) << "MD5sum: " << md5sum << " bucket: " << request.bucket << " key: " << request.key << std::endl;

            // Update database
            Database::Entity::S3::Object object = {
                .region=request.region,
                .bucket=request.bucket,
                .key=request.key,
                .owner=request.owner,
                .size=size,
                .md5sum=md5sum,
                .contentType=request.contentType};
            object = _database->CreateOrUpdateObject(object);
            log_debug_stream(_logger) << "Database updated, bucket: " << object.bucket << " key: " << object.key << std::endl;

            // Check notification
            CheckNotifications(request.region, request.bucket, request.key, object.size, "s3:ObjectCreated:Put");
            log_info_stream(_logger) << "Put object succeeded, bucket: " << request.bucket << " key: " << request.key << std::endl;

            return {.bucket=request.bucket, .key=request.key, .etag=md5sum, .contentLength=size};

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 put object failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    Dto::S3::CopyObjectResponse S3Service::CopyObject(Dto::S3::CopyObjectRequest &request) {
        log_trace_stream(_logger) << "Copy object request: " << request.ToString() << std::endl;

        // Check existence of source bucket
        if (!_database->BucketExists({.region=request.region, .name=request.sourceBucket})) {
            log_error_stream(_logger) << "Source bucket does not exist, region: " << request.region + " bucket: " << request.sourceBucket << std::endl;
            throw Core::ServiceException("Source bucket does not exist", 403);
        }

        // Check existence of source key
        if (!_database->ObjectExists({.region=request.region, .bucket=request.sourceBucket, .key=request.sourceKey})) {
            log_error_stream(_logger) << "Source object does not exist, region: " << request.region + " bucket: " << request.sourceBucket << " key: "
                                      << request.sourceKey << std::endl;
            throw Core::ServiceException("Source object does not exist", 403);
        }

        Dto::S3::CopyObjectResponse response;
        Database::Entity::S3::Object sourceObject, targetObject;
        try {
            // Check existence of target bucket
            if (!_database->BucketExists({.region=request.region, .name=request.targetBucket})) {
                log_error_stream(_logger) << "Target bucket does not exist, region: " << request.region + " bucket: " << request.targetBucket << std::endl;
                throw Core::ServiceException("Target bucket does not exist", 403);
            }

            sourceObject = _database->GetObject(request.region, request.sourceBucket, request.sourceKey);

            // Update database
            targetObject = {
                .region=request.region,
                .bucket=request.targetBucket,
                .key=request.targetKey,
                .owner=sourceObject.owner,
                .size=sourceObject.size,
                .md5sum=sourceObject.md5sum,
                .contentType=sourceObject.contentType};
            targetObject = _database->CreateObject(targetObject);
            log_debug_stream(_logger) << "Database updated, bucket: " << targetObject.bucket << " key: " << targetObject.key << std::endl;

            // Copy physical file
            std::string sourcePath = GetFilename(request.sourceBucket, request.sourceKey);
            std::string targetPath = GetFilename(request.targetBucket, request.targetKey);
            Core::FileUtils::CopyTo(sourcePath, targetPath);

            // Check notification
            CheckNotifications(targetObject.region, targetObject.bucket, targetObject.key, targetObject.size, "s3:ObjectCreated:Put");
            log_info_stream(_logger) << "Copy object succeeded, sourceBucket: " << request.sourceBucket << " sourceKey: " << request.sourceKey << " targetBucket: "
                                     << request.targetBucket << " targetKey: " << request.targetKey << std::endl;

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 copy object request failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
        return {.eTag=targetObject.md5sum, .lastModified=Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FRAC_FORMAT)};
    }

    void S3Service::DeleteObject(const Dto::S3::DeleteObjectRequest &request) {
        log_trace_stream(_logger) << "Delete object request: " << request.ToString() << std::endl;

        // Check bucket existence
        if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", 403);
        }

        if (!_database->ObjectExists({.bucket=request.bucket, .key=request.key})) {
            throw Core::ServiceException("Object does not exist", 403);
        }

        try {
            // Delete from database
            Database::Entity::S3::Object object = {.region=request.region, .bucket=request.bucket, .key=request.key};
            _database->DeleteObject(object);
            log_debug_stream(_logger) << "Database object deleted, key: " << request.key << std::endl;

            // Delete file system object
            DeleteObject(request.bucket, request.key);

            // Check notification
            CheckNotifications(request.region, request.bucket, request.key, 0, "s3:ObjectRemoved:Delete");

            log_info_stream(_logger) << "Object deleted, bucket: " << request.bucket << " key: " << request.key << std::endl;

        } catch (Poco::Exception &exc) {
            log_error_stream(_logger) << "S3 delete object failed, message: " + exc.message() << std::endl;
            throw Core::ServiceException(exc.message(), 500);
        }
        log_info_stream(_logger) << "DeleteObject succeeded, bucket: " << request.bucket << " key: " << request.key << std::endl;
    }

    Dto::S3::DeleteObjectsResponse S3Service::DeleteObjects(const Dto::S3::DeleteObjectsRequest &request) {
        log_trace_stream(_logger) << "Delete objects request: " << request.ToString() << std::endl;

        // Check existence
        if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", 403);
        }

        Dto::S3::DeleteObjectsResponse response;
        try {
            // Delete from database
            _database->DeleteObjects(request.bucket, request.keys);
            log_debug_stream(_logger) << "Database object deleted, count: " << request.keys.size() << std::endl;

            // Delete file system objects
            for (const auto &key : request.keys) {

                DeleteObject(request.bucket, key);
                log_debug_stream(_logger) << "File system object deleted: " << key << std::endl;

                // Check notifications
                CheckNotifications(request.region, request.bucket, key, 0, "s3:ObjectRemoved:Delete");
            }
            log_info_stream(_logger) << "Objects deleted, bucket: " << request.bucket << " count: " << request.keys.size() << std::endl;

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 delete objects failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
        log_info_stream(_logger) << "DeleteObjects succeeded, bucket: " << request.bucket << std::endl;
        return response;
    }

    void S3Service::PutBucketNotification(const Dto::S3::PutBucketNotificationRequest &request) {
        log_trace_stream(_logger) << "Put bucket notification request, id: " << request.notificationId << std::endl;

        // Check bucket existence
        if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", 403);
        }

        // Check notification existence
        Database::Entity::S3::Bucket bucket = _database->GetBucketByRegionName(request.region, request.bucket);
        if (bucket.HasNotification(request.event)) {
            throw Core::ServiceException("Bucket notification exists already", 403);
        }

        try {
            if (!request.lambdaArn.empty()) {
                CreateLambdaConfiguration(bucket, request);
            } else if (!request.queueArn.empty()) {
                CreateQueueConfiguration(bucket, request);
            }
            log_info_stream(_logger) << "PutBucketNotification succeeded, bucket: " << request.bucket << std::endl;

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 put bucket notification request failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    void S3Service::DeleteBucket(const std::string &region, const std::string &name) {
        log_trace_stream(_logger) << "Delete bucket request, name: " << name << std::endl;

        Database::Entity::S3::Bucket bucket = {.region=region, .name=name};

        // Check existence
        if (!_database->BucketExists(bucket)) {
            throw Core::ServiceException("Bucket does not exist", 403);
        }

        // Check empty
        if (_database->HasObjects(bucket)) {
            throw Core::ServiceException("Bucket is not empty", 403);
        }

        try {
            // Delete directory
            DeleteBucket(name);

            // Delete bucket from database
            _database->DeleteBucket(bucket);
            log_info_stream(_logger) << "Bucket deleted, bucket: " << bucket << std::endl;

        } catch (Poco::Exception &ex) {
            log_error_stream(_logger) << "S3 Delete Bucket failed, message: " << ex.message() << std::endl;
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    void S3Service::CheckNotifications(const std::string &region, const std::string &bucketName, const std::string &key, long size, const std::string &event) {

        Database::Entity::S3::Bucket dbBucket = _database->GetBucketByRegionName(region, bucketName);

        if (dbBucket.HasNotification(event)) {

            Database::Entity::S3::BucketNotification notification = dbBucket.GetNotification(event);

            // Create the event record
            Dto::S3::Object obj = {.key=key, .size=size, .etag=Poco::UUIDGenerator().createRandom().toString()};
            Dto::S3::Bucket bucket = {.name=dbBucket.name};

            Dto::S3::S3 s3 = {.configurationId=notification.notificationId, .bucket=bucket, .object=obj,};

            Dto::S3::Record record = {.region=region, .eventName=event, .s3=s3};
            Dto::S3::EventNotification eventNotification;

            eventNotification.records.push_back(record);
            log_debug_stream(_logger) << "Found record, count: " << eventNotification.records.size() << std::endl;

            if (!notification.queueArn.empty()) {

                // Queue notification
                SendQueueNotificationRequest(eventNotification, notification.queueArn);
                log_debug_stream(_logger) << "SQS message created, eventNotification: " + eventNotification.ToString() << std::endl;

            } else if (!notification.lambdaArn.empty()) {

                // Lambda notification
                SendLambdaInvocationRequest(eventNotification, notification);
                log_debug_stream(_logger) << "Lambda function invoked, eventNotification: " + eventNotification.ToString() << std::endl;
            }
        } else {
            log_debug_stream(_logger) << "No notifications found, bucket: " << bucketName << " key: " << key << std::endl;
        }
    }

    Database::Entity::S3::Bucket S3Service::CreateQueueConfiguration(const Database::Entity::S3::Bucket &bucket, const Dto::S3::PutBucketNotificationRequest &request) {

        Database::Entity::S3::BucketNotification bucketNotification = {.event=request.event, .notificationId=request.notificationId, .queueArn = request.queueArn};
        return _database->CreateBucketNotification(bucket, bucketNotification);
    }

    Database::Entity::S3::Bucket S3Service::CreateLambdaConfiguration(const Database::Entity::S3::Bucket &bucket,
                                                                      const Dto::S3::PutBucketNotificationRequest &request) {

        Database::Entity::S3::BucketNotification bucketNotification = {.event=request.event, .notificationId=request.notificationId, .lambdaArn=request.lambdaArn};
        return _database->CreateBucketNotification(bucket, bucketNotification);
    }

    std::string S3Service::GetDirFromKey(const std::string &key) {

        if (key.find('/') != std::string::npos) {
            return key.substr(0, key.find_last_of('/'));
        }
        return {};
    }

    std::string S3Service::GetDirectory(const std::string &bucket, const std::string &key) {

        return _dataDir + Poco::Path::separator() + bucket + Poco::Path::separator() + GetDirFromKey(key);
    }

    std::string S3Service::GetFilename(const std::string &bucket, const std::string &key) {

        return _dataDir + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
    }

    void S3Service::DeleteObject(const std::string &bucket, const std::string &key) {

        std::string filename = _dataDir + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
        if (Core::FileUtils::FileExists(filename)) {
            Core::FileUtils::DeleteFile(filename);
            log_debug_stream(_logger) << "File system object deleted, bucket: " << bucket << " key: " << key << std::endl;
        }
    }

    void S3Service::DeleteBucket(const std::string &bucket) {

        std::string bucketDir = _dataDir + Poco::Path::separator() + bucket;
        if (Core::DirUtils::DirectoryExists(bucketDir)) {
            Core::DirUtils::DeleteDirectory(bucketDir, true);
            log_debug_stream(_logger) << "Bucket directory deleted, bucketDir: " + bucketDir << std::endl;
        }

        std::string watcherDir = _watcherDir + Poco::Path::separator() + bucket;
        if (Core::DirUtils::DirectoryExists(watcherDir)) {
            Core::DirUtils::DeleteDirectory(watcherDir, true);
            log_debug_stream(_logger) << "Watcher directory deleted, watcherDir: " + watcherDir << std::endl;
        }
    }

    std::string S3Service::GetMultipartUploadDirectory(const std::string &uploadId) {
        return _tempDir + Poco::Path::separator() + uploadId;
    }

    void S3Service::SendQueueNotificationRequest(const Dto::S3::EventNotification &eventNotification, const std::string &queueArn) {

        //"Credential=none/20230618/eu-central-1/s3/aws4_request, SignedHeaders=content-md5;content-type;host;x-amz-content-sha256;x-amz-date;x-amz-security-token, Signature=fe9766ea2c032ac7b17033a567f6b361192bddcf73f89d25c15019977c544e1c"
        Poco::URI uri("http://" + _sqsServiceHost + ":" + std::to_string(_sqsServicePort) + "/");
        std::string path(uri.getPathAndQuery());

        // Set payload
        std::string body = "Action=SendMessage&QueueArn=" + queueArn + "&MessageBody=" + eventNotification.ToJson();

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.setContentLength((long) body.length());
        request.add("Content-Type", "application/json");
        request.add("Authorization",
                    "AWS4-HMAC-SHA256 Credential=none/20230618/eu-central-1/lambda/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840");
        log_debug_stream(_logger) << "SQS message request created, body: " + body << std::endl;

        // Send request
        std::ostream &os = session.sendRequest(request);
        os << body;

        // Get the response status
        Poco::Net::HTTPResponse response;
        session.receiveResponse(response);
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "SQS message request send, status: " << response.getStatus() << std::endl;
    }

    void S3Service::SendLambdaInvocationRequest(const Dto::S3::EventNotification &eventNotification,
                                                const Database::Entity::S3::BucketNotification &bucketNotification) {

        std::vector<std::string> parts = Core::StringUtils::Split(bucketNotification.lambdaArn, ':');
        std::string functionName = parts[6];

        //"Credential=none/20230618/eu-central-1/s3/aws4_request, SignedHeaders=content-md5;content-type;host;x-amz-content-sha256;x-amz-date;x-amz-security-token, Signature=fe9766ea2c032ac7b17033a567f6b361192bddcf73f89d25c15019977c544e1c"
        Poco::URI uri("http://" + _lambdaServiceHost + ":" + std::to_string(_lambdaServicePort) + "/2015-03-31/functions/" + functionName + "/invocations");
        std::string path(uri.getPathAndQuery());

        // Set payload
        std::string body = eventNotification.ToJson();

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.setContentLength((long) body.length());
        request.add("Content-Type", "application/json");
        request.add("Authorization",
                    "AWS4-HMAC-SHA256 Credential=none/20230618/eu-central-1/lambda/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840");
        log_debug_stream(_logger) << "Invocation request created, body: " + body << std::endl;

        // Send request
        std::ostream &os = session.sendRequest(request);
        os << body;

        // Get the response status
        Poco::Net::HTTPResponse response;
        session.receiveResponse(response);
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "Invocation request send, status: " << response.getStatus() << std::endl;
    }

} // namespace AwsMock::Service
