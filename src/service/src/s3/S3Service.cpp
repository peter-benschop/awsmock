//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/s3/S3Service.h>

namespace AwsMock::Service {

    Dto::S3::CreateBucketResponse S3Service::CreateBucket(const Dto::S3::CreateBucketRequest &s3Request) {
        log_trace << "Create bucket request, s3Request: " << s3Request.ToString();

        // Get region
        std::string region = s3Request.region;
        std::string accountId = Core::Configuration::instance().getString("awsmock.account.userPoolId");

        // Check existence
        if (_database.BucketExists({.region = region, .name = s3Request.name})) {
            log_warning << "Bucket exists already, region: " << region << " name: " << s3Request.name;
            Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(region, s3Request.name);
            log_debug << "Got bucket: " << s3Request.name;
            return {
                    .location = bucket.region,
                    .arn = Core::CreateArn("s3", region, accountId, s3Request.name)};
        }

        Dto::S3::CreateBucketResponse createBucketResponse;

        try {

            // Update database
            _database.CreateBucket({.region = region, .name = s3Request.name, .owner = s3Request.owner});

            createBucketResponse = Dto::S3::CreateBucketResponse(region, Core::CreateArn("s3", region, accountId, s3Request.name));
            log_trace << "S3 create bucket response: " << createBucketResponse.ToXml();
            log_info << "Bucket created, bucket: " << s3Request.name;

        } catch (Poco::Exception &exc) {
            log_error << "S3 create bucket failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
        return createBucketResponse;
    }

    Dto::S3::GetMetadataResponse S3Service::GetBucketMetadata(Dto::S3::GetMetadataRequest &request) {
        log_trace << "Get bucket metadata request, s3Request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            log_info << "Bucket " << request.bucket << " does not exist";
            throw Core::NotFoundException("Bucket does not exist");
        }

        try {

            Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(request.region, request.bucket);
            Dto::S3::GetMetadataResponse response = {
                    .region = bucket.region,
                    .bucket = bucket.name,
                    .created = bucket.created,
                    .modified = bucket.modified};

            log_trace << "S3 get bucket metadata response: " + response.ToString();
            log_info << "Metadata returned, bucket: " << request.bucket << " key: " << request.key;

            return response;

        } catch (Poco::Exception &ex) {
            log_warning << "S3 get object metadata failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::S3::GetMetadataResponse S3Service::GetObjectMetadata(Dto::S3::GetMetadataRequest &request) {
        log_trace << "Get metadata request, s3Request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            log_info << "Bucket " << request.bucket << " does not exist";
            throw Core::NotFoundException("Bucket does not exist");
        }

        if (!request.key.empty()) {
            if (!_database.ObjectExists({.region = request.region, .bucket = request.bucket, .key = request.key})) {
                log_info << "Object " << request.key << " does not exist";
                throw Core::NotFoundException("Object does not exist");
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
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::S3::GetObjectResponse S3Service::GetObject(Dto::S3::GetObjectRequest &request) {
        log_trace << "Get object request, s3Request: " << request.ToString();
        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            log_error << "Bucket " << request.bucket << " does not exist";
            throw Core::NotFoundException("Bucket does not exist");
        }

        if (!request.key.empty()) {
            if (!_database.ObjectExists({.region = request.region, .bucket = request.bucket, .key = request.key})) {
                log_error << "Object " << request.key << " does not exist";
                throw Core::NotFoundException("Object does not exist");
            }
        }

        try {
            Database::Entity::S3::Bucket bucketEntity = _database.GetBucketByRegionName(request.region, request.bucket);

            Database::Entity::S3::Object object;
            if (bucketEntity.IsVersioned() && !request.versionId.empty()) {
                object = _database.GetObjectVersion(request.region, request.bucket, request.key, request.versionId);
                if (object.oid.empty()) {
                    log_error << "Object " << request.key << " does not exist";
                    throw Core::ServiceException("Object does not exist");
                }
            } else {
                object = _database.GetObject(request.region, request.bucket, request.key);
            }

            std::string filename = dataDir + Poco::Path::separator() + object.internalName;

            // Check decryption
            CheckDecryption(bucketEntity, object, filename);

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
            throw Core::ServiceException(ex.message());
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
            throw Core::ServiceException(ex.message());
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
            throw Core::ServiceException(ex.message());
        }
    }

    void S3Service::PutBucketVersioning(const Dto::S3::PutBucketVersioningRequest &request) {
        log_trace << "Put bucket versioning request: " << request.ToString();

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::NotFoundException("Bucket does not exist");
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
            throw Core::NotFoundException("Bucket does not exist");
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
        std::copy(std::istream_iterator<unsigned char>(stream), std::istream_iterator<unsigned char>(), std::ostream_iterator<unsigned char>(ofs));
        ofs.close();
        log_trace << "Part uploaded, part: " << part << " dir: " << uploadDir;

        // Get md5sum as ETag
        std::string eTag = Core::Crypto::GetMd5FromFile(fileName);
        log_info << "Upload part succeeded, part: " << part << " filename: " << fileName;
        return eTag;
    }

    Dto::S3::CompleteMultipartUploadResult S3Service::CompleteMultipartUpload(const Dto::S3::CompleteMultipartUploadRequest &request) {
        log_trace << "CompleteMultipartUpload request, uploadId: " << request.uploadId << " bucket: " << request.bucket << " key: " << request.key << " region: " << request.region << " user: " << request.user;

        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);

        // Get all file parts
        std::string uploadDir = GetMultipartUploadDirectory(request.uploadId);
        std::vector<std::string> files = Core::DirUtils::ListFilesByPrefix(uploadDir, request.uploadId);

        // Output file
        std::string filename = Core::AwsUtils::CreateS3FileName();
        std::string outFile = dataS3Dir + Poco::Path::separator() + filename;
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
        if (!request.checksumAlgorithm.empty()) {

            S3HashCreator s3HashCreator;
            std::vector<std::string> algorithms = {request.checksumAlgorithm};
            boost::thread t(boost::ref(s3HashCreator), algorithms, object);
            t.detach();
            log_debug << "Checksums, bucket: " << request.bucket << " key: " << request.key << " sha1: " << object.sha1sum << " sha256: " << object.sha256sum;
            //Core::TaskPool::instance().Add<std::string, S3HashCreator>("s3-hashing", S3HashCreator({request.checksumAlgorithm}, object));
        }

        // Cleanup
        Core::DirUtils::DeleteDirectory(uploadDir);

        // Check notifications
        CheckNotifications(request.region, request.bucket, request.key, object.size, "ObjectCreated");

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
            throw Core::NotFoundException("Bucket does not exist");
        }

        try {
            // Get bucket
            Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(request.region, request.bucket);

            if (bucket.IsVersioned()) {
                return SaveVersionedObject(request, bucket, stream);
            } else {
                return SaveUnversionedObject(request, bucket, stream);
            }

        } catch (Poco::Exception &ex) {
            log_error << "S3 put object failed, message: " << ex.what() << " key: " << request.key;
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::S3::CopyObjectResponse S3Service::CopyObject(Dto::S3::CopyObjectRequest &request) {
        log_trace << "Copy object request: " << request.ToString();

        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);

        // Check existence of source bucket
        if (!_database.BucketExists({.region = request.region, .name = request.sourceBucket})) {
            log_error << "Source bucket does not exist, region: " << request.region + " bucket: " << request.sourceBucket;
            throw Core::NotFoundException("Source bucket does not exist");
        }

        // Check existence of source key
        if (!_database.ObjectExists({.region = request.region, .bucket = request.sourceBucket, .key = request.sourceKey})) {
            log_error << "Source object does not exist, region: " << request.region + " bucket: " << request.sourceBucket << " key: " << request.sourceKey;
            throw Core::NotFoundException("Source object does not exist");
        }

        Dto::S3::CopyObjectResponse response;
        Database::Entity::S3::Object sourceObject, targetObject;
        try {

            // Check existence of target bucket
            if (!_database.BucketExists({.region = request.region, .name = request.targetBucket})) {
                log_error << "Target bucket does not exist, region: " << request.region + " bucket: " << request.targetBucket;
                throw Core::NotFoundException("Target bucket does not exist");
            }

            // Get the source object from the database
            Database::Entity::S3::Bucket targetBucket = _database.GetBucketByRegionName(request.region, request.targetBucket);
            sourceObject = _database.GetObject(request.region, request.sourceBucket, request.sourceKey);

            // Copy physical file
            std::string targetFile = Core::AwsUtils::CreateS3FileName();
            std::string sourcePath = dataS3Dir + Poco::Path::separator() + sourceObject.internalName;
            std::string targetPath = dataS3Dir + Poco::Path::separator() + targetFile;
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
            CheckNotifications(targetObject.region, targetObject.bucket, targetObject.key, targetObject.size, "ObjectCreated");
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

        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);

        // Check existence of source bucket
        if (!_database.BucketExists({.region = request.region, .name = request.sourceBucket})) {
            log_error << "Source bucket does not exist, region: " << request.region + " bucket: " << request.sourceBucket;
            throw Core::NotFoundException("Source bucket does not exist");
        }

        // Check existence of source key
        if (!_database.ObjectExists({.region = request.region, .bucket = request.sourceBucket, .key = request.sourceKey})) {
            log_error << "Source object does not exist, region: " << request.region + " bucket: " << request.sourceBucket << " key: "
                      << request.sourceKey;
            throw Core::NotFoundException("Source object does not exist");
        }

        Dto::S3::CopyObjectResponse response;
        Database::Entity::S3::Object sourceObject, targetObject;
        try {

            // Check existence of target bucket
            if (!_database.BucketExists({.region = request.region, .name = request.targetBucket})) {
                log_error << "Target bucket does not exist, region: " << request.region + " bucket: " << request.targetBucket;
                throw Core::ServiceException("Target bucket does not exist");
            }

            // Get the source object from the database
            Database::Entity::S3::Bucket targetBucket = _database.GetBucketByRegionName(request.region, request.targetBucket);
            sourceObject = _database.GetObject(request.region, request.sourceBucket, request.sourceKey);

            // Copy physical file
            std::string targetFile = Core::AwsUtils::CreateS3FileName();
            std::string sourcePath = dataS3Dir + Poco::Path::separator() + sourceObject.internalName;
            std::string targetPath = dataS3Dir + Poco::Path::separator() + targetFile;
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
            CheckNotifications(targetObject.region, targetObject.bucket, targetObject.key, targetObject.size, "ObjectCreated");
            log_info << "Move object succeeded, sourceBucket: " << request.sourceBucket << " sourceKey: " << request.sourceKey << " targetBucket: "
                     << request.targetBucket << " targetKey: " << request.targetKey;

        } catch (Poco::Exception &ex) {
            log_error << "S3 copy object request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
        return {.eTag = targetObject.md5sum, .lastModified = Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FRAC_FORMAT)};
    }

    void S3Service::DeleteObject(const Dto::S3::DeleteObjectRequest &request) {
        log_trace << "Delete object request: " << request.ToString();

        // Check bucket existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::NotFoundException("Bucket does not exist, bucket: " + request.bucket);
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
                CheckNotifications(request.region, request.bucket, request.key, 0, "ObjectRemoved");

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
            throw Core::NotFoundException("Bucket does not exist");
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
                CheckNotifications(request.region, request.bucket, key, 0, "ObjectRemoved");
            }

            // Delete from database
            _database.DeleteObjects(request.bucket, request.keys);
            log_debug << "Database object deleted, count: " << request.keys.size();

            log_info << "Objects deleted, bucket: " << request.bucket << " count: " << request.keys.size();

        } catch (Poco::Exception &ex) {
            log_error << "S3 delete objects failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
        log_info << "DeleteObjects succeeded, bucket: " << request.bucket;
        return response;
    }

    void S3Service::PutBucketNotification(const Dto::S3::PutBucketNotificationRequest &request) {
        log_trace << "Put bucket notification request, userPoolId: " << request.notificationId;

        // Check bucket existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::NotFoundException("Bucket does not exist");
        }

        // Check notification existence
        Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(request.region, request.bucket);
        if (bucket.HasNotification(request.event)) {
            throw Core::NotFoundException("Bucket notification exists already");
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
            throw Core::ServiceException(ex.message());
        }
    }

    void S3Service::PutBucketEncryption(const Dto::S3::PutBucketEncryptionRequest &request) {
        log_trace << "Put bucket encryption request, algorithm: " << request.sseAlgorithm;

        // Check bucket existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::NotFoundException("Bucket does not exist");
        }

        try {

            Database::Entity::S3::Bucket bucketEntity = _database.GetBucketByRegionName(request.region, request.bucket);

            Database::Entity::S3::BucketEncryption bucketEncryption = {.sseAlgorithm = request.sseAlgorithm, .kmsKeyId = request.kmsKeyId};
            bucketEntity.bucketEncryption = bucketEncryption;
            bucketEntity = _database.UpdateBucket(bucketEntity);
            log_info << "PutBucketEncryption succeeded, bucket: " << request.bucket;

        } catch (Poco::Exception &ex) {
            log_error << "S3 put bucket encryption request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::S3::ListObjectVersionsResponse S3Service::ListObjectVersions(const Dto::S3::ListObjectVersionsRequest &request) {
        log_trace << "List object versions request: " << request.ToString();

        // Check bucket existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::NotFoundException("Bucket does not exist");
        }

        // Get bucket
        Database::Entity::S3::Bucket bucketEntity = _database.GetBucketByRegionName(request.region, request.bucket);
        if (!bucketEntity.IsVersioned()) {
            throw Core::NotFoundException("Bucket is not versioned");
        }

        Dto::S3::ListObjectVersionsResponse response;
        try {

            std::vector<Database::Entity::S3::Object> objectList = _database.GetBucketObjectList(request.region, request.bucket, request.pageSize);
            return Dto::S3::Mapper::map(request, objectList);

        } catch (Poco::Exception &ex) {
            log_error << "S3 put bucket encryption request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void S3Service::DeleteBucket(const Dto::S3::DeleteBucketRequest &request) {
        log_trace << "Delete bucket request, name: " << request.bucket;

        Database::Entity::S3::Bucket bucket = {.region = request.region, .name = request.bucket};

        // Check existence
        if (!_database.BucketExists(bucket)) {
            throw Core::NotFoundException("Bucket does not exist");
        }

        // Check empty
        if (_database.HasObjects(bucket)) {
            throw Core::NotFoundException("Bucket is not empty");
        }

        // Check transfer bucket
        std::string transferBucket = Core::Configuration::instance().getString("awsmock.service.transfer.bucket", DEFAULT_TRANSFER_BUCKET_NAME);
        if (request.bucket == transferBucket) {
            throw Core::NotFoundException("Transfer bucket cannot be deleted");
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
        log_debug << "Check notifications, region: " << region << " bucket: " << bucket << " event: " << event;

        Database::Entity::S3::Bucket bucketEntity = _database.GetBucketByRegionName(region, bucket);

        if (bucketEntity.HasQueueNotification(event)) {

            Database::Entity::S3::QueueNotification notification = bucketEntity.GetQueueNotification(event);

            if (notification.CheckFilter(key)) {

                // Create the event record
                Dto::S3::Object s3Object = {.key = key, .size = size, .etag = Poco::UUIDGenerator().createRandom().toString()};
                Dto::S3::Bucket s3Bucket = {.name = bucketEntity.name};

                Dto::S3::S3 s3 = {.configurationId = notification.id, .bucket = s3Bucket, .object = s3Object};

                Dto::S3::Record record = {.region = region, .eventName = event, .s3 = s3};
                Dto::S3::EventNotification eventNotification;

                eventNotification.records.push_back(record);
                log_debug << "Found notification records, count: " << eventNotification.records.size();

                // Queue notification
                SendQueueNotificationRequest(eventNotification, notification);
                log_trace << "SQS message created, eventNotification: " + eventNotification.ToString();
                log_debug << "SQS message created, queueArn: " << notification.queueArn;
            }
        }

        if (bucketEntity.HasTopicNotification(event)) {

            Database::Entity::S3::TopicNotification notification = bucketEntity.GetTopicNotification(event);

            if (notification.CheckFilter(key)) {

                // Create the event record
                Dto::S3::Object s3Object = {.key = key, .size = size, .etag = Poco::UUIDGenerator().createRandom().toString()};
                Dto::S3::Bucket s3Bucket = {.name = bucketEntity.name};

                Dto::S3::S3 s3 = {.configurationId = notification.id, .bucket = s3Bucket, .object = s3Object};

                Dto::S3::Record record = {.region = region, .eventName = event, .s3 = s3};
                Dto::S3::EventNotification eventNotification;

                eventNotification.records.push_back(record);
                log_debug << "Found notification records, count: " << eventNotification.records.size();

                // Queue notification
                SendTopicNotificationRequest(eventNotification, notification);
                log_trace << "SNS message created, eventNotification: " + eventNotification.ToString();
                log_debug << "SNS message created, topicArn: " << notification.topicArn;
            }
        }

        if (bucketEntity.HasLambdaNotification(event)) {

            Database::Entity::S3::LambdaNotification notification = bucketEntity.GetLambdaNotification(event);

            if (notification.CheckFilter(key)) {

                // Create the event record
                Dto::S3::Object s3Object = {.key = key, .size = size, .etag = Poco::UUIDGenerator().createRandom().toString()};
                Dto::S3::Bucket s3Bucket = {.name = bucketEntity.name};

                Dto::S3::S3 s3 = {.configurationId = notification.id, .bucket = s3Bucket, .object = s3Object};

                Dto::S3::Record record = {.region = region, .eventName = event, .s3 = s3};
                Dto::S3::EventNotification eventNotification;

                eventNotification.records.push_back(record);
                log_debug << "Found notification records, count: " << eventNotification.records.size();

                // Lambda notification
                SendLambdaInvocationRequest(eventNotification, notification);
                log_trace << "lambda function invoked, eventNotification: " + eventNotification.ToString();
                log_debug << "lambda function invoked, lambdaArn:" << notification.lambdaArn;
            }
        }
    }

    Database::Entity::S3::Bucket S3Service::CreateQueueConfiguration(const Database::Entity::S3::Bucket &bucket, const Dto::S3::PutBucketNotificationRequest &request) {

        Database::Entity::S3::BucketNotification bucketNotification = {.event = request.event, .notificationId = request.notificationId, .queueArn = request.queueArn};
        return _database.CreateBucketNotification(bucket, bucketNotification);
    }

    Database::Entity::S3::Bucket S3Service::CreateLambdaConfiguration(const Database::Entity::S3::Bucket &bucket, const Dto::S3::PutBucketNotificationRequest &request) {

        Database::Entity::S3::BucketNotification bucketNotification = {.event = request.event, .notificationId = request.notificationId, .lambdaArn = request.lambdaArn};
        return _database.CreateBucketNotification(bucket, bucketNotification);
    }

    Dto::S3::PutBucketNotificationConfigurationResponse S3Service::PutBucketNotificationConfiguration(const Dto::S3::PutBucketNotificationConfigurationRequest &request) {

        // Check existence
        if (!_database.BucketExists({.region = request.region, .name = request.bucket})) {
            throw Core::NotFoundException("Bucket does not exist");
        }

        Dto::S3::PutBucketNotificationConfigurationResponse response;
        try {

            // Get bucket
            Database::Entity::S3::Bucket bucket = _database.GetBucketByRegionName(request.region, request.bucket);
            log_debug << "Bucket received, region:" << bucket.region << " bucket: " << bucket.name;

            // Add notification configurations
            if (!request.queueConfigurations.empty()) {
                GetQueueNotificationConfigurations(bucket, request.queueConfigurations);
            }
            if (!request.topicConfigurations.empty()) {
                GetTopicNotificationConfigurations(bucket, request.topicConfigurations);
            }
            if (!request.lambdaConfigurations.empty()) {
                GetLambdaNotificationConfigurations(bucket, request.lambdaConfigurations);
            }

            // Update database
            bucket = _database.UpdateBucket(bucket);
            log_debug << "Bucket updated, region:" << bucket.region << " bucket: " << bucket.name;

            response.queueConfigurations = request.queueConfigurations;
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "S3 put notification configurations failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void S3Service::DeleteObject(const std::string &bucket, const std::string &key, const std::string &internalName) {

        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        std::string transferDir = dataDir + Poco::Path::separator() + "transfer";
        Core::DirUtils::EnsureDirectory(dataS3Dir);
        Core::DirUtils::EnsureDirectory(transferDir);

        std::string filename = dataS3Dir + Poco::Path::separator() + internalName;
        Core::FileUtils::DeleteFile(filename);
        log_debug << "File system object deleted, filename: " << filename;

        std::string transferBucket = Core::Configuration::instance().getString("awsmock.service.transfer.bucket", DEFAULT_TRANSFER_BUCKET_NAME);
        if (bucket == transferBucket) {
            filename = transferDir + Poco::Path::separator() + key;
            Core::FileUtils::DeleteFile(filename);
            log_debug << "Transfer file system object deleted, filename: " << filename;
        }
    }

    void S3Service::DeleteBucket(const std::string &name) {

        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);

        std::string bucketDir = dataS3Dir + Poco::Path::separator() + name;
        if (Core::DirUtils::DirectoryExists(bucketDir)) {
            Core::DirUtils::DeleteDirectory(bucketDir, true);
            log_debug << "Bucket directory deleted, bucketDir: " + bucketDir;
        }
    }

    std::string S3Service::GetMultipartUploadDirectory(const std::string &uploadId) {
        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string tempDir = dataDir + Poco::Path::separator() + "tmp";
        Core::DirUtils::EnsureDirectory(tempDir);
        return tempDir + Poco::Path::separator() + uploadId;
    }

    void S3Service::SendQueueNotificationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::QueueNotification &queueNotification) {

        std::string region = Core::Configuration::instance().getString("awsmock.region", DEFAULT_REGION);

        SQSService _sqsService;
        Dto::SQS::SendMessageRequest request = {.region = region, .queueArn = queueNotification.queueArn, .body = eventNotification.ToJson()};
        Dto::SQS::SendMessageResponse response = _sqsService.SendMessage(request);
        log_debug << "SQS message request send, messageId: " << response.messageId;
    }

    void S3Service::SendTopicNotificationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::TopicNotification &topicNotification) {

        std::string region = Core::Configuration::instance().getString("awsmock.region", DEFAULT_REGION);

        SNSService _snsService;
        Dto::SNS::PublishRequest request = {.region = region, .targetArn = topicNotification.topicArn, .message = eventNotification.ToJson()};
        Dto::SNS::PublishResponse response = _snsService.Publish(request);
        log_debug << "SNS message request send, messageId: " << response.messageId;
    }

    void S3Service::SendLambdaInvocationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::LambdaNotification &lambdaNotification) {

        std::string region = Core::Configuration::instance().getString("awsmock.region", DEFAULT_REGION);
        std::string user = Core::Configuration::instance().getString("awsmock.user", DEFAULT_USER);

        std::vector<std::string> parts = Core::StringUtils::Split(lambdaNotification.lambdaArn, ':');
        std::string functionName = parts[6];
        log_debug << "Invocation request function name: " << functionName;

        _lambdaService.InvokeLambdaFunction(functionName, eventNotification.ToJson(), region, user);
        log_debug << "Lambda invocation finished send";
    }

    Dto::S3::PutObjectResponse S3Service::SaveUnversionedObject(Dto::S3::PutObjectRequest &request, const Database::Entity::S3::Bucket &bucket, std::istream &stream) {

        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);

        // Write file
        std::string fileName = Core::AwsUtils::CreateS3FileName();
        std::string filePath = dataS3Dir + Poco::Path::separator() + fileName;
        std::ofstream ofs(filePath, std::ios::binary);
        ofs << stream.rdbuf();
        ofs.close();

        long size = Core::FileUtils::FileSize(filePath);
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
        if (!request.checksumAlgorithm.empty()) {
            S3HashCreator s3HashCreator;
            std::vector<std::string> algorithms = {request.checksumAlgorithm};
            boost::thread t(boost::ref(s3HashCreator), algorithms, object);
            t.detach();
            //Core::TaskPool::instance().Add<std::string, S3HashCreator>("s3-hashing", S3HashCreator({request.checksumAlgorithm}, object));
            log_debug << "Checksums, bucket: " << request.bucket << " key: " << request.key << " sha1: " << object.sha1sum << " sha256: " << object.sha256sum;
        }

        // Update database
        object = _database.CreateOrUpdateObject(object);
        log_debug << "Database updated, bucket: " << object.bucket << " key: " << object.key;

        // Check encryption
        CheckEncryption(bucket, object);
        log_info << "Put object succeeded, bucket: " << request.bucket << " key: " << request.key;

        // Check notification
        CheckNotifications(request.region, request.bucket, request.key, object.size, "ObjectCreated");
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

    Dto::S3::PutObjectResponse S3Service::SaveVersionedObject(Dto::S3::PutObjectRequest &request, const Database::Entity::S3::Bucket &bucket, std::istream &stream) {
        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);

        // Write file
        std::string fileName = Core::AwsUtils::CreateS3FileName();
        std::string filePath = dataS3Dir + Poco::Path::separator() + fileName;
        std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
        ofs << stream.rdbuf();
        //long size = Poco::StreamCopier::copyStream(stream, ofs);
        ofs.close();

        // Get size
        long size = Core::FileUtils::FileSize(filePath);
        log_debug << "File received, filePath: " << filePath << " size: " << size;

        Database::Entity::S3::Object object;

        // Check existence by
        std::string md5sum = Core::Crypto::HexEncode(Core::Crypto::Base64Decode(request.md5Sum));
        Database::Entity::S3::Object existingObject = _database.GetObjectMd5(request.region, request.bucket, request.key, md5sum);
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
            if (!request.checksumAlgorithm.empty()) {
                S3HashCreator s3HashCreator;
                std::vector<std::string> algorithms = {request.checksumAlgorithm};
                boost::thread t(boost::ref(s3HashCreator), algorithms, object);
                t.detach();
                //Core::TaskPool::instance().Add<std::string, S3HashCreator>("s3-hashing", S3HashCreator({request.checksumAlgorithm}, object));
                log_debug << "Checksums, bucket: " << request.bucket << " key: " << request.key << " sha1: " << object.sha1sum << " sha256: " << object.sha256sum;
            }

            // Check encryption
            CheckEncryption(bucket, object);
            log_info << "Put object succeeded, bucket: " << request.bucket << " key: " << request.key;

            // Check notification
            CheckNotifications(request.region, request.bucket, request.key, object.size, "ObjectCreated");
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

    void S3Service::GetQueueNotificationConfigurations(Database::Entity::S3::Bucket &bucket, const std::vector<Dto::S3::QueueConfiguration> &queueConfigurations) {

        for (auto &queueConfiguration: queueConfigurations) {

            // Check existence
            if (!queueConfiguration.id.empty() && bucket.HasQueueNotificationId(queueConfiguration.id)) {
                break;
            }

            // General attributes
            std::string id = queueConfiguration.id.empty() ? Poco::UUIDGenerator().createOne().toString() : queueConfiguration.id;
            Database::Entity::S3::QueueNotification queueNotification = {
                    .id = id,
                    .queueArn = queueConfiguration.queueArn,
            };

            // Get events
            for (const auto &event: queueConfiguration.events) {
                queueNotification.events.emplace_back(Dto::S3::EventTypeToString(event));
            }

            // Get filter rules
            for (const auto &filterRule: queueConfiguration.filterRules) {
                Database::Entity::S3::FilterRule filterRuleEntity = {.name = Dto::S3::NameTypeToString(filterRule.name), .value = filterRule.value};
                queueNotification.filterRules.emplace_back(filterRuleEntity);
            }
            bucket.queueNotifications.emplace_back(queueNotification);
            log_debug << "Added queue notification configurations, count: " << bucket.queueNotifications.size();
        }
    }

    void S3Service::GetTopicNotificationConfigurations(Database::Entity::S3::Bucket &bucket, const std::vector<Dto::S3::TopicConfiguration> &topicConfigurations) {

        for (auto &topicConfiguration: topicConfigurations) {

            // Check existence
            if (!topicConfiguration.id.empty() && bucket.HasTopicNotificationId(topicConfiguration.id)) {
                break;
            }

            // General attributes
            std::string id = topicConfiguration.id.empty() ? Poco::UUIDGenerator().createOne().toString() : topicConfiguration.id;
            Database::Entity::S3::TopicNotification topicNotification = {
                    .id = id,
                    .topicArn = topicConfiguration.topicArn,
            };

            // Get events
            for (const auto &event: topicConfiguration.events) {
                topicNotification.events.emplace_back(Dto::S3::EventTypeToString(event));
            }

            // Get filter rules
            for (const auto &filterRule: topicConfiguration.filterRules) {
                Database::Entity::S3::FilterRule filterRuleEntity = {.name = Dto::S3::NameTypeToString(filterRule.name), .value = filterRule.value};
                topicNotification.filterRules.emplace_back(filterRuleEntity);
            }
            bucket.topicNotifications.emplace_back(topicNotification);
            log_debug << "Added queue notification configurations, count: " << bucket.queueNotifications.size();
        }
    }

    void S3Service::GetLambdaNotificationConfigurations(Database::Entity::S3::Bucket &bucket, const std::vector<Dto::S3::LambdaConfiguration> &lambdaConfigurations) {


        for (auto &lambdaConfiguration: lambdaConfigurations) {

            // Check existence
            if (!lambdaConfiguration.id.empty() && bucket.HasLambdaNotificationId(lambdaConfiguration.id)) {
                break;
            }

            // General attributes
            std::string id = lambdaConfiguration.id.empty() ? Poco::UUIDGenerator().createOne().toString() : lambdaConfiguration.id;
            Database::Entity::S3::LambdaNotification lambdaNotification = {
                    .id = id,
                    .lambdaArn = lambdaConfiguration.lambdaArn,
            };

            // Get events
            for (const auto &event: lambdaConfiguration.events) {
                lambdaNotification.events.emplace_back(Dto::S3::EventTypeToString(event));
            }

            // Get filter rules
            for (const auto &filterRule: lambdaConfiguration.filterRules) {
                Database::Entity::S3::FilterRule filterRuleEntity = {.name = Dto::S3::NameTypeToString(filterRule.name), .value = filterRule.value};
                lambdaNotification.filterRules.emplace_back(filterRuleEntity);
            }
            bucket.lambdaNotifications.emplace_back(lambdaNotification);
            log_debug << "Added queue notification configurations, count: " << bucket.queueNotifications.size();
        }
    }

    void S3Service::CheckEncryption(const Database::Entity::S3::Bucket &bucket, const Database::Entity::S3::Object &object) {
        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);
        if (bucket.HasEncryption()) {
            Database::KMSDatabase &kmsDatabase = Database::KMSDatabase::instance();
            Database::Entity::KMS::Key kmsKey = kmsDatabase.GetKeyByKeyId(bucket.bucketEncryption.kmsKeyId);
            log_debug << kmsKey.keyId << " " << kmsKey.aes256Key;
            unsigned char *rawKey = Core::Crypto::HexDecode(kmsKey.aes256Key);
            Core::Crypto::Aes256EncryptFile(dataS3Dir + "/" + object.internalName, rawKey);
        }
    }

    void S3Service::CheckDecryption(const Database::Entity::S3::Bucket &bucket, const Database::Entity::S3::Object &object, std::string &outFile) {
        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", DEFAULT_DATA_DIR);
        std::string dataS3Dir = dataDir + Poco::Path::separator() + "s3";
        Core::DirUtils::EnsureDirectory(dataS3Dir);
        if (bucket.HasEncryption()) {
            Database::KMSDatabase &kmsDatabase = Database::KMSDatabase::instance();
            Database::Entity::KMS::Key kmsKey = kmsDatabase.GetKeyByKeyId(bucket.bucketEncryption.kmsKeyId);
            log_debug << kmsKey.keyId << " " << kmsKey.aes256Key;
            unsigned char *rawKey = Core::Crypto::HexDecode(kmsKey.aes256Key);
            Core::Crypto::Aes256DecryptFile(dataS3Dir + "/" + object.internalName, outFile, rawKey);
        }
    }

}// namespace AwsMock::Service
