//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/s3/S3Service.h>

namespace AwsMock::Service {

    template<class F, class entity>
    void CallAsyncCalculateHashes(F *&&fun, entity &&e) {
        std::make_unique<std::future<void>>((std::async(std::launch::async, [&fun, &e]() {
            fun->CalculateHashes(e);
        }))).reset();
    }

    S3Service::S3Service(const Core::Configuration &configuration) : _configuration(configuration), _database(Database::S3Database::instance()) {

        _accountId = _configuration.getString("awsmock.account.userPoolId");

        // Initialize directories
        _dataDir = _configuration.getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        _transferDir = _configuration.getString("awsmock.service.ftp.base.dir", DEFAULT_TRANSFER_DATA_DIR);
        _transferBucket = _configuration.getString("awsmock.service.transfer.bucket", DEFAULT_TRANSFER_BUCKET);
        _dataS3Dir = _dataDir + Poco::Path::separator() + "s3";
        _tempDir = _dataDir + Poco::Path::separator() + "tmp";

        // SQS module connection
        _sqsServiceHost = _configuration.getString("awsmock.module.sqs.host", "localhost");
        _sqsServicePort = _configuration.getInt("awsmock.module.sqs.port", 9501);

        // lambda module connection
        _lambdaServiceHost = _configuration.getString("awsmock.module.lambda.host", "localhost");
        _lambdaServicePort = _configuration.getInt("awsmock.module.lambda.port", 9503);

        // Create directories
        Core::DirUtils::EnsureDirectory(_tempDir);
        Core::DirUtils::EnsureDirectory(_dataDir);
        Core::DirUtils::EnsureDirectory(_dataS3Dir);
    }

    Dto::S3::CreateBucketResponse S3Service::CreateBucket(const Dto::S3::CreateBucketRequest &s3Request) {
        log_trace << "Create bucket request, s3Request: " << s3Request.ToString();

        // Get region
        std::string region = s3Request.region;

        // Check existence
        if (_database.BucketExists({.region = region, .name = s3Request.name})) {
            log_warning << "Bucket exists already, region: " << region << " name: " << s3Request.name;
            Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(region, s3Request.name);
            log_debug << "Got bucket: " << s3Request.name;
            return {
                    .location = bucket.region,
                    .arn = Core::AwsUtils::CreateArn("s3", region, _accountId, s3Request.name)};
            //      throw Core::ServiceException("Bucket exists already", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        Dto::S3::CreateBucketResponse createBucketResponse;

        try {

            // Update database
            _database.CreateBucket({.region = region, .name = s3Request.name, .owner = s3Request.owner});

            createBucketResponse = Dto::S3::CreateBucketResponse(region, Core::AwsUtils::CreateArn("s3", region, _accountId, s3Request.name));
            log_trace << "S3 create bucket response: " << createBucketResponse.ToXml();
            log_info << "Bucket created, bucket: " << s3Request.name;

        } catch (Poco::Exception &exc) {
            log_error << "S3 create bucket failed, message: " << exc.message();
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
        return createBucketResponse;
    }

    Dto::S3::GetMetadataResponse S3Service::GetMetadata(Dto::S3::GetMetadataRequest &request) {
        log_trace << "Get metadata request, s3Request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            log_info << "Bucket " << request.bucket << " does not exist";
            throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        if (!request.key.empty()) {
            if (!_database.ObjectExists({.region = request.region, .bucket = request.bucket, .key = request.key})) {
                log_info << "Object " << request.key << " does not exist";
                throw Core::ServiceException("Object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            }
        }

        try {
            Database::Entity::S3::Object object = _database.GetObject(request.region, request.bucket, request.key);

            Dto::S3::GetMetadataResponse response = {
                    .bucket = object.bucket,
                    .key = object.key,
                    .md5Sum = object.md5sum,
                    .contentType = object.contentType,
                    .size = object.size,
                    .metadata = object.metadata,
                    .created = object.created,
                    .modified = object.modified};

            log_trace << "S3 get object metadata response: " + response.ToString();
            log_info << "Metadata returned, bucket: " << request.bucket << " key: " << request.key;

            return response;

        } catch (Poco::Exception &ex) {
            log_warning << "S3 get object metadata failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    Dto::S3::GetObjectResponse S3Service::GetObject(Dto::S3::GetObjectRequest &request) {
        log_trace << "Get object request, s3Request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            log_error << "Bucket " << request.bucket << " does not exist";
            throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        if (!request.key.empty()) {
            if (!_database.ObjectExists({.region = request.region, .bucket = request.bucket, .key = request.key})) {
                log_error << "Object " << request.key << " does not exist";
                throw Core::ServiceException("Object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            }
        }

        try {
            Database::Entity::S3::Bucket bucketEntity = _database.GetBucketByRegionName(request.region, request.bucket);

            Database::Entity::S3::Object object;
            if (bucketEntity.IsVersioned() && !request.versionId.empty()) {
                object = _database.GetObjectVersion(request.region, request.bucket, request.key, request.versionId);
                if (object.oid.empty()) {
                    log_error << "Object " << request.key << " does not exist";
                    throw Core::ServiceException("Object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                }
            } else {
                object = _database.GetObject(request.region, request.bucket, request.key);
            }

            std::string filename = _dataS3Dir + Poco::Path::separator() + object.internalName;
            Dto::S3::GetObjectResponse response = {
                    .bucket = object.bucket,
                    .key = object.key,
                    .size = object.size,
                    .filename = filename,
                    .contentType = object.contentType,
                    .metadata = object.metadata,
                    .md5sum = object.md5sum,
                    .modified = object.modified,
            };
            log_trace << "S3 get object response: " << response.ToString();
            log_info << "Object returned, bucket: " << request.bucket << " key: " << request.key;
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "S3 get object failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    Dto::S3::ListAllBucketResponse S3Service::ListAllBuckets() {
        log_trace << "List all buckets request";

        try {

            Database::Entity::S3::BucketList bucketList = _database.ListBuckets();
            auto listAllBucketResponse = Dto::S3::ListAllBucketResponse(bucketList);
            log_debug << "Count all buckets, size: " << bucketList.size();

            return listAllBucketResponse;

        } catch (Poco::Exception &ex) {
            log_error << "S3 Create Bucket failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    Dto::S3::ListBucketResponse S3Service::ListBucket(const Dto::S3::ListBucketRequest &request) {
        log_trace << "List bucket request: " + request.ToString();

        try {

            Database::Entity::S3::ObjectList objectList = _database.ListBucket(request.name, request.prefix);
            Dto::S3::ListBucketResponse listBucketResponse = Dto::S3::ListBucketResponse(request.name, objectList);
            log_debug << "Bucket list returned, count: " << objectList.size();

            return listBucketResponse;

        } catch (Poco::Exception &ex) {
            log_error << "S3 list bucket failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    void S3Service::PutBucketVersioning(const Dto::S3::PutBucketVersioningRequest &request) {
        log_trace << "Put bucket versioning request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Update bucket
        Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(request.region, request.bucket);
        bucket.versionStatus = Database::Entity::S3::BucketVersionStatusFromString(Poco::toLower(request.status));

        _database.UpdateBucket(bucket);
        log_info << "Put bucket versioning, bucket: " << request.bucket << " state: " << request.status;
    }

    Dto::S3::CreateMultipartUploadResult S3Service::CreateMultipartUpload(const Dto::S3::CreateMultipartUploadRequest &request) {
        log_trace << "CreateMultipartUpload request, bucket: " + request.bucket << " key: " << request.key << " region: " << request.region << " user: " << request.user;

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        std::string uploadId = Core::StringUtils::GenerateRandomString(58);

        // Create upload directory, if not existing
        std::string uploadDir = GetMultipartUploadDirectory(uploadId);
        Core::DirUtils::EnsureDirectory(uploadDir);

        log_info << "Multipart upload started, bucket: " << request.bucket << " key: " << request.key << " uploadId: " << uploadId;
        return {.region = request.region, .bucket = request.bucket, .key = request.key, .uploadId = uploadId};
    }

    std::string S3Service::UploadPart(std::istream &stream, int part, const std::string &uploadId) {
        log_trace << "UploadPart request, part: " << part << " updateId: " << uploadId;

        std::string uploadDir = GetMultipartUploadDirectory(uploadId);
        log_trace << "Using uploadDir: " << uploadDir;

        std::string fileName = uploadDir + Poco::Path::separator() + uploadId + "-" + std::to_string(part);
        std::ofstream ofs(fileName);
        long size = Poco::StreamCopier::copyStream(stream, ofs);
        ofs.close();
        log_trace << "Part uploaded, part: " << part << " dir: " << uploadDir;

        // Get md5sum as ETag
        std::string eTag = Core::Crypto::GetMd5FromFile(fileName);
        log_info << "Upload part succeeded, part: " << part << " size: " << size << " filename: " << fileName;
        return eTag;
    }

    Dto::S3::CompleteMultipartUploadResult S3Service::CompleteMultipartUpload(const Dto::S3::CompleteMultipartUploadRequest &request) {
        log_trace << "CompleteMultipartUpload request, uploadId: " << request.uploadId << " bucket: " << request.bucket << " key: " << request.key << " region: " << request.region << " user: " << request.user;

        // Get all file parts
        std::string uploadDir = GetMultipartUploadDirectory(request.uploadId);
        std::vector<std::string> files = Core::DirUtils::ListFilesByPrefix(uploadDir, request.uploadId);

        // Output file
        std::string filename = Core::AwsUtils::CreateS3FileName();
        std::string outFile = _dataS3Dir + Poco::Path::separator() + filename;
        log_debug << "Output file, outFile: " << outFile;

        // Append all parts to the output file
        long fileSize = 0;
        try {

            fileSize = Core::FileUtils::AppendTextFiles(outFile, uploadDir, files);
            log_debug << "Input files appended to outfile, outFile: " << outFile << " size: " << fileSize;

        } catch (Poco::Exception &exc) {
            log_error << "Append to binary file failed, error: " << exc.message();
        }

        // Get file size, MD5 sum
        std::string md5sum = Core::Crypto::GetMd5FromFile(outFile);
        log_debug << "Metadata, bucket: " << request.bucket << " key: " << request.key << " md5: " << md5sum;

        // Create database object
        Database::Entity::S3::Object object = _database.CreateOrUpdateObject(
                {
                        .region = request.region,
                        .bucket = request.bucket,
                        .key = request.key,
                        .owner = request.user,
                        .size = fileSize,
                        .md5sum = md5sum,
                        .internalName = filename,
                });

        // Calculate the hashes asynchronously
        if (request.checksumAlgorithm == "SHA1" || request.checksumAlgorithm == "SHA256") {
            CallAsyncCalculateHashes(this, object);
            log_debug << "Checksums, bucket: " << request.bucket << " key: " << request.key << " sha1: " << object.sha1sum << " sha256: " << object.sha256sum;
        }

        // Cleanup
        Core::DirUtils::DeleteDirectory(uploadDir);

        // Check notifications
        CheckNotifications(request.region, request.bucket, request.key, object.size, "s3:ObjectCreated:Put");

        log_info << "Multipart upload finished, bucket: " << request.bucket << " key: " << request.key;
        return {
                .location = request.region,
                .bucket = request.bucket,
                .key = request.key,
                .etag = md5sum,
                .md5sum = md5sum};
    }

    Dto::S3::PutObjectResponse S3Service::PutObject(Dto::S3::PutObjectRequest &request, std::istream &stream) {
        log_trace << "Put object request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            log_error << "Bucket does not exist, region: " << request.region + " bucket: " << request.bucket;
            throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        try {
            // Get bucket
            Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(request.region, request.bucket);

            if (bucket.IsVersioned()) {
                return SaveVersionedObject(request, stream, bucket);
            } else {
                return SaveUnversionedObject(request, stream);
            }

        } catch (Poco::Exception &ex) {
            log_error << "S3 put object failed, message: " << ex.what() << " key: " << request.key;
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::S3::CopyObjectResponse S3Service::CopyObject(Dto::S3::CopyObjectRequest &request) {
        log_trace << "Copy object request: " << request.ToString();

        // Check existence of source bucket
        if (!_database.BucketExists({.region = request.region, .name = request.sourceBucket})) {
            log_error << "Source bucket does not exist, region: " << request.region + " bucket: " << request.sourceBucket;
            throw Core::ServiceException("Source bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Check existence of source key
        if (!_database.ObjectExists({.region = request.region, .bucket = request.sourceBucket, .key = request.sourceKey})) {
            log_error << "Source object does not exist, region: " << request.region + " bucket: " << request.sourceBucket << " key: " << request.sourceKey;
            throw Core::ServiceException("Source object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        Dto::S3::CopyObjectResponse response;
        Database::Entity::S3::Object sourceObject, targetObject;
        try {

            // Check existence of target bucket
            if (!_database.BucketExists({.region = request.region, .name = request.targetBucket})) {
                log_error << "Target bucket does not exist, region: " << request.region + " bucket: " << request.targetBucket;
                throw Core::ServiceException("Target bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            }

            // Get the source object from the database
            Database::Entity::S3::Bucket targetBucket = _database.GetBucketByRegionName(request.region, request.targetBucket);
            sourceObject = _database.GetObject(request.region, request.sourceBucket, request.sourceKey);

            // Copy physical file
            std::string targetFile = Core::AwsUtils::CreateS3FileName();
            std::string sourcePath = _dataS3Dir + Poco::Path::separator() + sourceObject.internalName;
            std::string targetPath = _dataS3Dir + Poco::Path::separator() + targetFile;
            Core::FileUtils::CopyTo(sourcePath, targetPath);

            // Update database
            targetObject = {
                    .region = request.region,
                    .bucket = request.targetBucket,
                    .key = request.targetKey,
                    .owner = sourceObject.owner,
                    .size = sourceObject.size,
                    .md5sum = sourceObject.md5sum,
                    .sha1sum = sourceObject.sha1sum,
                    .sha256sum = sourceObject.sha256sum,
                    .contentType = sourceObject.contentType,
                    .metadata = request.metadata,
                    .internalName = targetFile,
            };

            // Create version ID
            if (targetBucket.IsVersioned()) {
                targetObject.versionId = Core::AwsUtils::CreateS3VersionId();
            }

            // Create object
            targetObject = _database.CreateObject(targetObject);
            log_debug << "Database updated, bucket: " << targetObject.bucket << " key: " << targetObject.key;

            // Check notification
            CheckNotifications(targetObject.region, targetObject.bucket, targetObject.key, targetObject.size, "s3:ObjectCreated:Put");
            log_info << "Copy object succeeded, sourceBucket: " << request.sourceBucket << " sourceKey: " << request.sourceKey << " targetBucket: "
                     << request.targetBucket << " targetKey: " << request.targetKey;

        } catch (Poco::Exception &ex) {
            log_error << "S3 copy object request failed, error: " << ex.what();
            throw Core::ServiceException(ex.message());
        }
        return {.eTag = targetObject.md5sum, .lastModified = Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FRAC_FORMAT)};
    }

    Dto::S3::MoveObjectResponse S3Service::MoveObject(Dto::S3::MoveObjectRequest &request) {
        log_trace << "Move object request: " << request.ToString();

        // Check existence of source bucket
        if (!_database.BucketExists({.region = request.region, .name = request.sourceBucket})) {
            log_error << "Source bucket does not exist, region: " << request.region + " bucket: " << request.sourceBucket;
            throw Core::ServiceException("Source bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Check existence of source key
        if (!_database.ObjectExists({.region = request.region, .bucket = request.sourceBucket, .key = request.sourceKey})) {
            log_error << "Source object does not exist, region: " << request.region + " bucket: " << request.sourceBucket << " key: "
                      << request.sourceKey;
            throw Core::ServiceException("Source object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        Dto::S3::CopyObjectResponse response;
        Database::Entity::S3::Object sourceObject, targetObject;
        try {

            // Check existence of target bucket
            if (!_database.BucketExists({.region = request.region, .name = request.targetBucket})) {
                log_error << "Target bucket does not exist, region: " << request.region + " bucket: " << request.targetBucket;
                throw Core::ServiceException("Target bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            }

            // Get the source object from the database
            Database::Entity::S3::Bucket targetBucket = _database.GetBucketByRegionName(request.region, request.targetBucket);
            sourceObject = _database.GetObject(request.region, request.sourceBucket, request.sourceKey);

            // Copy physical file
            std::string targetFile = Core::AwsUtils::CreateS3FileName();
            std::string sourcePath = _dataS3Dir + Poco::Path::separator() + sourceObject.internalName;
            std::string targetPath = _dataS3Dir + Poco::Path::separator() + targetFile;
            Core::FileUtils::CopyTo(sourcePath, targetPath);

            // Update database
            targetObject = {
                    .region = request.region,
                    .bucket = request.targetBucket,
                    .key = request.targetKey,
                    .owner = sourceObject.owner,
                    .size = sourceObject.size,
                    .md5sum = sourceObject.md5sum,
                    .sha1sum = sourceObject.sha1sum,
                    .sha256sum = sourceObject.sha256sum,
                    .contentType = sourceObject.contentType,
                    .metadata = request.metadata,
                    .internalName = targetFile,
            };

            // Create version ID
            if (targetBucket.IsVersioned()) {
                targetObject.versionId = Core::AwsUtils::CreateS3VersionId();
            }

            // Create object
            targetObject = _database.CreateObject(targetObject);
            log_debug << "Database updated, bucket: " << targetObject.bucket << " key: " << targetObject.key;

            // Check notification
            CheckNotifications(targetObject.region, targetObject.bucket, targetObject.key, targetObject.size, "s3:ObjectCreated:Put");
            log_info << "Move object succeeded, sourceBucket: " << request.sourceBucket << " sourceKey: " << request.sourceKey << " targetBucket: "
                     << request.targetBucket << " targetKey: " << request.targetKey;

        } catch (Poco::Exception &ex) {
            log_error << "S3 copy object request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
        return {.eTag = targetObject.md5sum, .lastModified = Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FRAC_FORMAT)};
    }

    void S3Service::DeleteObject(const Dto::S3::DeleteObjectRequest &request) {
        log_trace << "Delete object request: " << request.ToString();

        // Check bucket existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::ServiceException("Bucket does not exist, bucket: " + request.bucket);
        }

        if (_database.ObjectExists({.region = request.region, .bucket = request.bucket, .key = request.key})) {

            try {

                // Get object from database
                Database::Entity::S3::Object object = _database.GetObject(request.region, request.bucket, request.key);

                // Delete from database
                _database.DeleteObject(object);
                log_debug << "Database object deleted, bucket: " + request.bucket + " key: " << request.key;

                // Delete file system object
                DeleteObject(object.bucket, object.key, object.internalName);

                // Check notifications
                CheckNotifications(request.region, request.bucket, request.key, 0, "s3:ObjectRemoved:Delete");

                log_info << "Object deleted, bucket: " << request.bucket << " key: " << request.key;

            } catch (Poco::Exception &exc) {
                log_error << "S3 delete object failed, message: " + exc.message();
                throw Core::ServiceException(exc.message());
            }
        }
    }

    Dto::S3::DeleteObjectsResponse S3Service::DeleteObjects(const Dto::S3::DeleteObjectsRequest &request) {
        log_trace << "Delete objects request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        Dto::S3::DeleteObjectsResponse response;
        try {

            // Delete file system objects
            for (const auto &key: request.keys) {

                // Delete from database
                Database::Entity::S3::Object object = _database.GetObject(request.region, request.bucket, key);
                log_debug << "Database object deleted, count: " << request.keys.size();

                DeleteObject(object.bucket, object.key, object.internalName);
                log_debug << "File system object deleted: " << key;

                // Check notifications
                CheckNotifications(request.region, request.bucket, key, 0, "s3:ObjectRemoved:Delete");
            }

            // Delete from database
            _database.DeleteObjects(request.bucket, request.keys);
            log_debug << "Database object deleted, count: " << request.keys.size();

            log_info << "Objects deleted, bucket: " << request.bucket << " count: " << request.keys.size();

        } catch (Poco::Exception &ex) {
            log_error << "S3 delete objects failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
        log_info << "DeleteObjects succeeded, bucket: " << request.bucket;
        return response;
    }

    void S3Service::PutBucketNotification(const Dto::S3::PutBucketNotificationRequest &request) {
        log_trace << "Put bucket notification request, userPoolId: " << request.notificationId;

        // Check bucket existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Check notification existence
        Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(request.region, request.bucket);
        if (bucket.HasNotification(request.event)) {
            throw Core::ServiceException("Bucket notification exists already", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        try {
            if (!request.lambdaArn.empty()) {
                CreateLambdaConfiguration(bucket, request);
            } else if (!request.queueArn.empty()) {
                CreateQueueConfiguration(bucket, request);
            }
            log_info << "PutBucketNotification succeeded, bucket: " << request.bucket;

        } catch (Poco::Exception &ex) {
            log_error << "S3 put bucket notification request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    Dto::S3::ListObjectVersionsResponse S3Service::ListObjectVersions(const Dto::S3::ListObjectVersionsRequest request) {
        log_trace << "List object versions request: " << request.ToString();

        Dto::S3::ListObjectVersionsResponse response;
        return response;
    }

    void S3Service::DeleteBucket(const Dto::S3::DeleteBucketRequest &request) {
        log_trace << "Delete bucket request, name: " << request.bucket;

        Database::Entity::S3::Bucket bucket = {.region = request.region, .name = request.bucket};

        // Check existence
        if (!_database.BucketExists(bucket)) {
            throw Core::ServiceException("Bucket does not exist");
        }

        // Check empty
        if (_database.HasObjects(bucket)) {
            throw Core::ServiceException("Bucket is not empty");
        }

        // Check transfer bucket
        if (request.bucket == _transferBucket) {
            throw Core::ServiceException("Transfer bucket cannot be deleted");
        }

        try {

            // Delete directory
            DeleteBucket(request.bucket);

            // Delete bucket from database
            _database.DeleteBucket(bucket);
            log_info << "Bucket deleted, bucket: " << bucket.name;

        } catch (Poco::Exception &ex) {
            log_error << "S3 Delete Bucket failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void S3Service::CheckNotifications(const std::string &region, const std::string &bucket, const std::string &key, long size, const std::string &event) {

        Database::Entity::S3::Bucket bucketEntity = _database.GetBucketByRegionName(region, bucket);

        if (bucketEntity.HasNotification(event)) {

            Database::Entity::S3::BucketNotification notification = bucketEntity.GetNotification(event);

            // Create the event record
            Dto::S3::Object s3Object = {.key = key, .size = size, .etag = Poco::UUIDGenerator().createRandom().toString()};
            Dto::S3::Bucket s3Bucket = {.name = bucketEntity.name};

            Dto::S3::S3 s3 = {.configurationId = notification.notificationId, .bucket = s3Bucket, .object = s3Object};

            Dto::S3::Record record = {.region = region, .eventName = event, .s3 = s3};
            Dto::S3::EventNotification eventNotification;

            eventNotification.records.push_back(record);
            log_debug << "Found notification records, count: " << eventNotification.records.size();

            if (!notification.queueArn.empty()) {

                // Queue notification
                SendQueueNotificationRequest(eventNotification, notification.queueArn);
                log_trace << "SQS message created, eventNotification: " + eventNotification.ToString();
                log_debug << "SQS message created, queueArn: " << notification.queueArn;

            } else if (!notification.lambdaArn.empty()) {

                // lambda notification
                SendLambdaInvocationRequest(eventNotification, notification);
                log_trace << "lambda function invoked, eventNotification: " + eventNotification.ToString();
                log_debug << "lambda function invoked, lambdaArn:" << notification.lambdaArn;
            }
        } else {
            log_debug << "No notifications found, event: " << event << " bucket: " << bucket << " key: " << key;
        }
    }

    Database::Entity::S3::Bucket S3Service::CreateQueueConfiguration(const Database::Entity::S3::Bucket &bucket, const Dto::S3::PutBucketNotificationRequest &request) {

        Database::Entity::S3::BucketNotification bucketNotification = {.event = request.event, .notificationId = request.notificationId, .queueArn = request.queueArn};
        return _database.CreateBucketNotification(bucket, bucketNotification);
    }

    Database::Entity::S3::Bucket S3Service::CreateLambdaConfiguration(const Database::Entity::S3::Bucket &bucket,
                                                                      const Dto::S3::PutBucketNotificationRequest &request) {

        Database::Entity::S3::BucketNotification bucketNotification = {.event = request.event, .notificationId = request.notificationId, .lambdaArn = request.lambdaArn};
        return _database.CreateBucketNotification(bucket, bucketNotification);
    }

    Dto::S3::PutBucketNotificationConfigurationResponse S3Service::PutBucketNotificationConfiguration(const Dto::S3::PutBucketNotificationConfigurationRequest &request) {
        Dto::S3::PutBucketNotificationConfigurationResponse response;
        return response;
    }

    std::string S3Service::GetDirFromKey(const std::string &key) {

        if (key.find('/') != std::string::npos) {
            return key.substr(0, key.find_last_of('/'));
        }
        return {};
    }

    std::string S3Service::GetDirectory(const std::string &bucket, const std::string &key) {

        return _dataS3Dir + Poco::Path::separator() + bucket + Poco::Path::separator() + GetDirFromKey(key);
    }

    std::string S3Service::GetFilename(const std::string &bucket, const std::string &key) {

        return _dataS3Dir + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
    }

    void S3Service::DeleteObject(const std::string &bucket, const std::string &key, const std::string &internalName) {

        std::string filename = _dataS3Dir + Poco::Path::separator() + internalName;
        Core::FileUtils::DeleteFile(filename);
        log_debug << "File system object deleted, filename: " << filename;

        if (bucket == _transferBucket) {
            filename = _transferDir + Poco::Path::separator() + key;
            Core::FileUtils::DeleteFile(filename);
            log_debug << "Transfer file system object deleted, filename: " << filename;
        }
    }

    void S3Service::DeleteBucket(const std::string &name) {

        std::string bucketDir = _dataS3Dir + Poco::Path::separator() + name;
        if (Core::DirUtils::DirectoryExists(bucketDir)) {
            Core::DirUtils::DeleteDirectory(bucketDir, true);
            log_debug << "Bucket directory deleted, bucketDir: " + bucketDir;
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
        log_debug << "SQS message request created, body: " + body;

        // Send request
        std::ostream &os = session.sendRequest(request);
        os << body;

        // Get the response state
        Poco::Net::HTTPResponse response;
        session.receiveResponse(response);
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "HTTP error, state: " + std::to_string(response.getStatus()) + " reason: " + response.getReason();
        }
        log_debug << "SQS message request send, state: " << response.getStatus();
    }

    void S3Service::SendLambdaInvocationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::BucketNotification &bucketNotification) {

        std::vector<std::string> parts = Core::StringUtils::Split(bucketNotification.lambdaArn, ':');
        std::string functionName = parts[6];
        log_debug << "Invocation request function name: " << functionName;

        std::string body = eventNotification.ToJson();
        std::map<std::string, std::string> headers;
        headers["Content-Type"] = "application/json";
        headers["Content-Length"] = std::to_string(body.length());
        headers["Authorization"] = "AWS4-HMAC-SHA256 Credential=none/20230618/eu-central-1/lambda/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840";

        std::string url = "http://" + _lambdaServiceHost + ":" + std::to_string(_lambdaServicePort) + "/2015-03-31/functions/" + functionName + "/invocations";
        Core::CurlUtils _curlUtils;
        Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", url, headers, body);
        if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "HTTP error, status: " << response.statusCode << " reason: " + response.output;
        }
        log_debug << "Lambda invocation finished send, status: " << response.statusCode;
    }

    Dto::S3::PutObjectResponse S3Service::SaveUnversionedObject(Dto::S3::PutObjectRequest &request, std::istream &stream) {

        // Write file
        std::string fileName = Core::AwsUtils::CreateS3FileName();
        std::string filePath = _dataS3Dir + Poco::Path::separator() + fileName;
        std::ofstream ofs(filePath);
        long size = Poco::StreamCopier::copyStream(stream, ofs);
        ofs.close();

        //Core::FileUtils::StripChunkSignature(filePath);
        log_debug << "File received, fileName: " << filePath << " size: " << size;

        // Create entity
        Database::Entity::S3::Object object = {
                .region = request.region,
                .bucket = request.bucket,
                .key = request.key,
                .owner = request.owner,
                .size = size,
                .contentType = request.contentType,
                .metadata = request.metadata,
                .internalName = fileName};

        // Meta data
        object.md5sum = Core::Crypto::GetMd5FromFile(filePath);
        log_debug << "Checksum, bucket: " << request.bucket << " key: " << request.key << " md5: " << object.md5sum;
        if (request.checksumAlgorithm == "SHA1" || request.checksumAlgorithm == "SHA256") {
            CallAsyncCalculateHashes(this, object);
            log_debug << "Checksums, bucket: " << request.bucket << " key: " << request.key << " sha1: " << object.sha1sum << " sha256: " << object.sha256sum;
        }

        // Update database
        object = _database.CreateOrUpdateObject(object);
        log_debug << "Database updated, bucket: " << object.bucket << " key: " << object.key;

        // Check notification
        CheckNotifications(request.region, request.bucket, request.key, object.size, "s3:ObjectCreated:Put");
        log_info << "Put object succeeded, bucket: " << request.bucket << " key: " << request.key;

        return {
                .bucket = request.bucket,
                .key = request.key,
                .etag = object.md5sum,
                .md5Sum = object.md5sum,
                .contentLength = size,
                .checksumSha1 = object.sha1sum,
                .checksumSha256 = object.sha256sum,
                .metadata = request.metadata};
    }

    Dto::S3::PutObjectResponse S3Service::SaveVersionedObject(Dto::S3::PutObjectRequest &request, std::istream &stream, Database::Entity::S3::Bucket &bucket) {

        // Write file
        std::string fileName = Core::AwsUtils::CreateS3FileName();
        std::string filePath = _dataS3Dir + Poco::Path::separator() + fileName;
        std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
        long size = Poco::StreamCopier::copyStream(stream, ofs);
        ofs.close();
        log_debug << "File received, filePath: " << filePath << " size: " << size;

        Database::Entity::S3::Object object;

        // Check existence by
        Database::Entity::S3::Object existingObject = _database.GetObjectMd5(request.region, request.bucket, request.key, request.md5Sum);
        if (existingObject.oid.empty()) {

            // Version ID
            std::string versionId = Core::AwsUtils::CreateS3VersionId();

            // Create new version of new object
            object = {
                    .region = request.region,
                    .bucket = request.bucket,
                    .key = request.key,
                    .owner = request.owner,
                    .size = size,
                    .contentType = request.contentType,
                    .metadata = request.metadata,
                    .internalName = fileName,
                    .versionId = versionId,
            };

            // Checksums
            object.md5sum = Core::Crypto::GetMd5FromFile(filePath);
            log_debug << "Checksum, bucket: " << request.bucket << " key: " << request.key << " md5: " << object.md5sum;

            // Create new version in database
            object = _database.CreateObject(object);
            log_debug << "Database updated, bucket: " << object.bucket << " key: " << object.key;

            // Checksums
            if (request.checksumAlgorithm == "SHA1" || request.checksumAlgorithm == "SHA256") {
                CallAsyncCalculateHashes(this, object);
                log_debug << "Checksums, bucket: " << request.bucket << " key: " << request.key << " sha1: " << object.sha1sum << " sha256: " << object.sha256sum;
            }

            // Check notification
            CheckNotifications(request.region, request.bucket, request.key, object.size, "s3:ObjectCreated:Put");
            log_info << "Put object succeeded, bucket: " << request.bucket << " key: " << request.key;

        } else {

            // Delete local file
            Core::FileUtils::DeleteFile(filePath);
        }

        // Meta data
        object.md5sum = Core::Crypto::GetMd5FromFile(filePath);
        log_info << "Checksum, bucket: " << request.bucket << " key: " << request.key << "md5: " << object.md5sum;
        if (request.checksumAlgorithm == "SHA1") {
            object.sha1sum = Core::Crypto::GetSha1FromFile(filePath);
            log_debug << "Checksum SHA1, bucket: " << request.bucket << " key: " << request.key << " sha1: " << object.sha1sum;
        }
        if (request.checksumAlgorithm == "SHA256") {
            object.sha256sum = Core::Crypto::GetSha256FromFile(filePath);
            log_debug << "Checksum SHA256, bucket: " << request.bucket << " key: " << request.key << " sha256: " << object.sha256sum;
        }

        return {
                .bucket = request.bucket,
                .key = request.key,
                .etag = object.md5sum,
                .md5Sum = object.md5sum,
                .contentLength = size,
                .checksumSha1 = object.sha1sum,
                .checksumSha256 = object.sha256sum,
                .metadata = request.metadata,
                .versionId = object.versionId};
    }

    void S3Service::CalculateHashes(Database::Entity::S3::Object &object) {
        std::string filename = _dataS3Dir + Poco::Path::separator() + object.internalName;
        object.sha1sum = Core::Crypto::GetSha1FromFile(filename);
        object.sha256sum = Core::Crypto::GetSha256FromFile(filename);
        _database.UpdateObject(object);
        log_debug << "Calculated hashes, key: " << object.key;
    }
}// namespace AwsMock::Service
