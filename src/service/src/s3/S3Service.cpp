//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/S3Service.h>

namespace AwsMock::Service {

  S3Service::S3Service(Core::Configuration &configuration) : _logger(Poco::Logger::get("S3Service")), _configuration(configuration) {

    _accountId = _configuration.getString("awsmock.account.id");

    // Initialize directories
    _dataDir = _configuration.getString("awsmock.data.dir", DEFAULT_DATA_DIR);
    _dataS3Dir = _configuration.getString("awsmock.service.s3.data.dir", DEFAULT_S3_DATA_DIR);
    _transferDir = _configuration.getString("awsmock.service.ftp.base.dir", DEFAULT_TRANSFER_DATA_DIR);
    _transferBucket = _configuration.getString("awsmock.service.transfer.bucket", DEFAULT_TRANSFER_BUCKET);
    _tempDir = _dataDir + Poco::Path::separator() + "tmp";

    // Initialize database
    _database = std::make_unique<Database::S3Database>(_configuration);

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

  Dto::S3::CreateBucketResponse S3Service::CreateBucket(const std::string &name, const std::string &owner, const Dto::S3::CreateBucketRequest &s3Request) {
    log_trace_stream(_logger) << "Create bucket request, s3Request: " << s3Request.ToString() << std::endl;

    // Get region
    std::string region = s3Request._locationConstraint;

    // Check existence
    if (_database->BucketExists({.region=region, .name=name})) {
      log_warning_stream(_logger) << "Bucket exists already, region: " << region << " name: " << name << std::endl;
      throw Core::ServiceException("Bucket exists already", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::S3::CreateBucketResponse createBucketResponse;

    try {

      // Update database
      _database->CreateBucket({.region=region, .name=name, .owner=owner});

      createBucketResponse = Dto::S3::CreateBucketResponse(region, Core::AwsUtils::CreateArn("s3", region, _accountId, name));
      log_trace_stream(_logger) << "S3 create bucket response: " << createBucketResponse.ToXml() << std::endl;
      log_info_stream(_logger) << "Bucket created, bucket: " << name << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "S3 create bucket failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    return createBucketResponse;
  }

  Dto::S3::GetMetadataResponse S3Service::GetMetadata(Dto::S3::GetMetadataRequest &request) {
    log_trace_stream(_logger) << "Get metadata request, s3Request: " << request.ToString() << std::endl;

    // Check existence
    if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
      log_info_stream(_logger) << "Bucket " << request.bucket << " does not exist" << std::endl;
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    if (!request.key.empty()) {
      if (!_database->ObjectExists({.region=request.region, .bucket=request.bucket, .key=request.key})) {
        log_info_stream(_logger) << "Object " << request.key << " does not exist" << std::endl;
        throw Core::ServiceException("Object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
      }
    }

    try {
      Database::Entity::S3::Object object = _database->GetObject(request.region, request.bucket, request.key);

      Dto::S3::GetMetadataResponse response = {
          .bucket = object.bucket,
          .key = object.key,
          .md5Sum = object.md5sum,
          .contentType = object.contentType,
          .size = object.size,
          .metadata = object.metadata,
          .created = object.created,
          .modified = object.modified
      };

      log_trace_stream(_logger) << "S3 get object metadata response: " + response.ToString() << std::endl;
      log_info_stream(_logger) << "Metadata returned, bucket: " << request.bucket << " key: " << request.key << std::endl;

      return response;

    } catch (Poco::Exception &ex) {
      log_warning_stream(_logger) << "S3 get object metadata failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  Dto::S3::GetObjectResponse S3Service::GetObject(Dto::S3::GetObjectRequest &request) {
    log_trace_stream(_logger) << "Get object request, s3Request: " << request.ToString() << std::endl;

    // Check existence
    if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
      log_error_stream(_logger) << "Bucket " << request.bucket << " does not exist" << std::endl;
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    if (!request.key.empty()) {
      if (!_database->ObjectExists({.region=request.region, .bucket=request.bucket, .key=request.key})) {
        log_error_stream(_logger) << "Object " << request.key << " does not exist" << std::endl;
        throw Core::ServiceException("Object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
      }
    }

    try {
      Database::Entity::S3::Bucket bucketEntity = _database->GetBucketByRegionName(request.region, request.bucket);

      Database::Entity::S3::Object object;
      if (bucketEntity.IsVersioned() && !request.versionId.empty()) {
        object = _database->GetObjectVersion(request.region, request.bucket, request.key, request.versionId);
        if (object.oid.empty()) {
          log_error_stream(_logger) << "Object " << request.key << " does not exist" << std::endl;
          throw Core::ServiceException("Object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }
      } else {
        object = _database->GetObject(request.region, request.bucket, request.key);
      }

      std::string filename = _dataS3Dir + Poco::Path::separator() + object.internalName;
      Dto::S3::GetObjectResponse response = {
          .bucket = object.bucket,
          .key = object.key,
          .size = object.size,
          .filename = filename,
          .contentType = object.contentType,
          .metadata = object.metadata,
          .md5sum=object.md5sum,
          .modified = object.modified,
      };
      log_trace_stream(_logger) << "S3 get object response: " << response.ToString() << std::endl;
      log_info_stream(_logger) << "Object returned, bucket: " << request.bucket << " key: " << request.key << std::endl;
      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "S3 get object failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
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
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  Dto::S3::ListBucketResponse S3Service::ListBucket(const Dto::S3::ListBucketRequest &request) {
    log_trace_stream(_logger) << "List bucket request: " + request.ToString() << std::endl;

    try {

      Database::Entity::S3::ObjectList objectList = _database->ListBucket(request.name, request.prefix);
      Dto::S3::ListBucketResponse listBucketResponse = Dto::S3::ListBucketResponse(request.name, objectList);
      log_info_stream(_logger) << "Bucket list returned, count: " << objectList.size() << std::endl;

      return listBucketResponse;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "S3 list bucket failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void S3Service::PutBucketVersioning(const Dto::S3::PutBucketVersioningRequest &request) {
    log_trace_stream(_logger) << "Put bucket versioning request: " << request.ToString() << std::endl;

    // Check existence
    if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Update bucket
    Database::Entity::S3::Bucket bucket = _database->GetBucketByRegionName(request.region, request.bucket);
    bucket.versionStatus = Database::Entity::S3::BucketVersionStatusFromString(Poco::toLower(request.status));

    _database->UpdateBucket(bucket);
    log_info_stream(_logger) << "Put bucket versioning, bucket: " << request.bucket << " state: " << request.status << std::endl;
  }

  Dto::S3::InitiateMultipartUploadResult S3Service::CreateMultipartUpload(std::string &bucket, std::string &key, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "CreateMultipartUpload request, bucket: " + bucket << " key: " << key << " region: " << region << " user: " << user << std::endl;

    // Check existence
    if (!_database->BucketExists({.region=region, .name=bucket})) {
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    std::string uploadId = Core::StringUtils::GenerateRandomString(58);

    // Create upload directory, if not existing
    std::string uploadDir = GetMultipartUploadDirectory(uploadId);
    Core::DirUtils::EnsureDirectory(uploadDir);

    log_info_stream(_logger) << "Multipart upload started, bucket: " << bucket << " key: " << key << " uploadId: " << uploadId << std::endl;
    return {.bucket=bucket, .key=key, .uploadId=uploadId};
  }

  std::string S3Service::UploadPart(std::istream &stream, int part, const std::string &uploadId) {
    log_trace_stream(_logger) << "UploadPart request, part: " << part << " updateId: " << uploadId << std::endl;

    std::string uploadDir = GetMultipartUploadDirectory(uploadId);
    log_trace_stream(_logger) << "Using uploadDir: " << uploadDir << std::endl;

    std::string fileName = uploadDir + Poco::Path::separator() + uploadId + "-" + std::to_string(part);
    std::ofstream ofs(fileName);
    Poco::StreamCopier::copyStream(stream, ofs);
    ofs.close();
    log_trace_stream(_logger) << "Part uploaded, part: " << part << " dir: " << uploadDir << std::endl;

    // Get md5sum a ETag
    std::string eTag = Core::Crypto::Base64Encode(Core::Crypto::GetMd5FromFile(fileName));

    log_info_stream(_logger) << "Upload part succeeded, part: " << part << std::endl;
    return eTag;
  }

  Dto::S3::CompleteMultipartUploadResult S3Service::CompleteMultipartUpload(const std::string &uploadId, const std::string &bucket, const std::string &key, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "CompleteMultipartUpload request, uploadId: " << uploadId << " bucket: " << bucket << " key: " << key << " region: " << region << " user: " << user;

    // Get all file parts
    std::string uploadDir = GetMultipartUploadDirectory(uploadId);
    std::vector<std::string> files = Core::DirUtils::ListFilesByPrefix(uploadDir, uploadId);

    // Output file
    std::string filename = Core::AwsUtils::CreateS3FileName();
    std::string outFile = _dataS3Dir + Poco::Path::separator() + filename;
    log_trace_stream(_logger) << "Output file, outFile: " << outFile << std::endl;

    // Append all parts to the output file
    try {
      Core::FileUtils::AppendTextFiles(outFile, uploadDir, files);
      log_trace_stream(_logger) << "Input files appended to outfile, outFile: " << outFile << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Append to binary file failes, error: " << exc.message() << std::endl;
    }
    // Get file size, MD5 sum
    long fileSize = (long) Core::FileUtils::FileSize(outFile);
    std::string md5sum = Core::Crypto::GetMd5FromFile(outFile);
    std::string sha1sum = Core::Crypto::GetSha1FromFile(outFile);
    std::string sha256sum = Core::Crypto::GetSha256FromFile(outFile);
    log_debug_stream(_logger) << "Metadata, bucket: " << bucket << " key: " << key << " md5: " << md5sum << " sha256: " << sha256sum << std::endl;

    // Create database object
    Database::Entity::S3::Object object = _database->CreateOrUpdateObject(
        {
            .region=region,
            .bucket=bucket,
            .key=key,
            .owner=user,
            .size=fileSize,
            .md5sum=md5sum,
            .sha1sum=sha1sum,
            .sha256sum=sha256sum,
            .internalName=filename,
        });

    // Cleanup
    Core::DirUtils::DeleteDirectory(uploadDir);

    // Check notifications
    CheckNotifications(region, bucket, key, object.size, "s3:ObjectCreated:Put");

    log_info_stream(_logger) << "Multipart upload finished, bucket: " << bucket << " key: " << key << std::endl;
    return {
        .location=region,
        .bucket=bucket,
        .key=key,
        .etag=md5sum,
        .md5sum=md5sum,
        .checksumSha1=sha1sum,
        .checksumSha256=sha256sum
    };
  }

  Dto::S3::PutObjectResponse S3Service::PutObject(Dto::S3::PutObjectRequest &request, std::istream &stream) {
    log_trace_stream(_logger) << "Put object request: " << request.ToString() << std::endl;

    // Check existence
    if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
      log_error_stream(_logger) << "Bucket does not exist, region: " << request.region + " bucket: " << request.bucket << std::endl;
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    try {
      // Get bucket
      Database::Entity::S3::Bucket bucket = _database->GetBucketByRegionName(request.region, request.bucket);

      if (bucket.IsVersioned()) {
        return SaveVersionedObject(request, stream, bucket);
      } else {
        return SaveUnversionedObject(request, stream);
      }

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "S3 put object failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  Dto::S3::CopyObjectResponse S3Service::CopyObject(Dto::S3::CopyObjectRequest &request) {
    log_trace_stream(_logger) << "Copy object request: " << request.ToString() << std::endl;

    // Check existence of source bucket
    if (!_database->BucketExists({.region=request.region, .name=request.sourceBucket})) {
      log_error_stream(_logger) << "Source bucket does not exist, region: " << request.region + " bucket: " << request.sourceBucket << std::endl;
      throw Core::ServiceException("Source bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Check existence of source key
    if (!_database->ObjectExists({.region=request.region, .bucket=request.sourceBucket, .key=request.sourceKey})) {
      log_error_stream(_logger) << "Source object does not exist, region: " << request.region + " bucket: " << request.sourceBucket << " key: "
                                << request.sourceKey << std::endl;
      throw Core::ServiceException("Source object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::S3::CopyObjectResponse response;
    Database::Entity::S3::Object sourceObject, targetObject;
    try {
      // Check existence of target bucket
      if (!_database->BucketExists({.region=request.region, .name=request.targetBucket})) {
        log_error_stream(_logger) << "Target bucket does not exist, region: " << request.region + " bucket: " << request.targetBucket << std::endl;
        throw Core::ServiceException("Target bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
      }

      // Get the source object from the database
      Database::Entity::S3::Bucket targetBucket = _database->GetBucketByRegionName(request.region, request.targetBucket);
      sourceObject = _database->GetObject(request.region, request.sourceBucket, request.sourceKey);

      // Copy physical file
      std::string targetFile = Core::AwsUtils::CreateS3FileName();
      std::string sourcePath = _dataS3Dir + Poco::Path::separator() + sourceObject.internalName;
      std::string targetPath = _dataS3Dir + Poco::Path::separator() + targetFile;
      Core::FileUtils::CopyTo(sourcePath, targetPath);

      // Update database
      targetObject = {
          .region=request.region,
          .bucket=request.targetBucket,
          .key=request.targetKey,
          .owner=sourceObject.owner,
          .size=sourceObject.size,
          .md5sum=sourceObject.md5sum,
          .sha1sum=sourceObject.sha1sum,
          .sha256sum=sourceObject.sha256sum,
          .contentType=sourceObject.contentType,
          .metadata=request.metadata,
          .internalName=targetFile,
      };

      // Create version ID
      if (targetBucket.IsVersioned()) {
        targetObject.versionId = Core::AwsUtils::CreateS3VersionId();
      }

      // Create object
      targetObject = _database->CreateObject(targetObject);
      log_debug_stream(_logger) << "Database updated, bucket: " << targetObject.bucket << " key: " << targetObject.key << std::endl;

      // Check notification
      CheckNotifications(targetObject.region, targetObject.bucket, targetObject.key, targetObject.size, "s3:ObjectCreated:Put");
      log_info_stream(_logger) << "Copy object succeeded, sourceBucket: " << request.sourceBucket << " sourceKey: " << request.sourceKey << " targetBucket: "
                               << request.targetBucket << " targetKey: " << request.targetKey << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "S3 copy object request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    return {.eTag=targetObject.md5sum, .lastModified=Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FRAC_FORMAT)};
  }

  Dto::S3::MoveObjectResponse S3Service::MoveObject(Dto::S3::MoveObjectRequest &request) {
    log_trace_stream(_logger) << "Move object request: " << request.ToString() << std::endl;

    // Check existence of source bucket
    if (!_database->BucketExists({.region=request.region, .name=request.sourceBucket})) {
      log_error_stream(_logger) << "Source bucket does not exist, region: " << request.region + " bucket: " << request.sourceBucket << std::endl;
      throw Core::ServiceException("Source bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Check existence of source key
    if (!_database->ObjectExists({.region=request.region, .bucket=request.sourceBucket, .key=request.sourceKey})) {
      log_error_stream(_logger) << "Source object does not exist, region: " << request.region + " bucket: " << request.sourceBucket << " key: "
                                << request.sourceKey << std::endl;
      throw Core::ServiceException("Source object does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::S3::CopyObjectResponse response;
    Database::Entity::S3::Object sourceObject, targetObject;
    try {

      // Check existence of target bucket
      if (!_database->BucketExists({.region=request.region, .name=request.targetBucket})) {
        log_error_stream(_logger) << "Target bucket does not exist, region: " << request.region + " bucket: " << request.targetBucket << std::endl;
        throw Core::ServiceException("Target bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
      }

      // Get the source object from the database
      Database::Entity::S3::Bucket targetBucket = _database->GetBucketByRegionName(request.region, request.targetBucket);
      sourceObject = _database->GetObject(request.region, request.sourceBucket, request.sourceKey);

      // Copy physical file
      std::string targetFile = Core::AwsUtils::CreateS3FileName();
      std::string sourcePath = _dataS3Dir + Poco::Path::separator() + sourceObject.internalName;
      std::string targetPath = _dataS3Dir + Poco::Path::separator() + targetFile;
      Core::FileUtils::CopyTo(sourcePath, targetPath);

      // Update database
      targetObject = {
          .region=request.region,
          .bucket=request.targetBucket,
          .key=request.targetKey,
          .owner=sourceObject.owner,
          .size=sourceObject.size,
          .md5sum=sourceObject.md5sum,
          .sha1sum=sourceObject.sha1sum,
          .sha256sum=sourceObject.sha256sum,
          .contentType=sourceObject.contentType,
          .metadata=request.metadata,
          .internalName=targetFile,
      };

      // Create version ID
      if (targetBucket.IsVersioned()) {
        targetObject.versionId = Core::AwsUtils::CreateS3VersionId();
      }

      // Create object
      targetObject = _database->CreateObject(targetObject);
      log_debug_stream(_logger) << "Database updated, bucket: " << targetObject.bucket << " key: " << targetObject.key << std::endl;

      // Check notification
      CheckNotifications(targetObject.region, targetObject.bucket, targetObject.key, targetObject.size, "s3:ObjectCreated:Put");
      log_info_stream(_logger) << "Move object succeeded, sourceBucket: " << request.sourceBucket << " sourceKey: " << request.sourceKey << " targetBucket: "
                               << request.targetBucket << " targetKey: " << request.targetKey << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "S3 copy object request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    return {.eTag=targetObject.md5sum, .lastModified=Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::ISO8601_FRAC_FORMAT)};
  }

  void S3Service::DeleteObject(const Dto::S3::DeleteObjectRequest &request) {
    log_trace_stream(_logger) << "Delete object request: " << request.ToString() << std::endl;

    // Check bucket existence
    if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
      throw Core::ServiceException("Bucket does not exist, bucket: " + request.bucket, Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    if (_database->ObjectExists({.region=request.region, .bucket=request.bucket, .key=request.key})) {

      try {

        // Get object from database
        Database::Entity::S3::Object object = _database->GetObject(request.region, request.bucket, request.key);

        // Delete from database
        _database->DeleteObject(object);
        log_debug_stream(_logger) << "Database object deleted, bucket: " + request.bucket + " key: " << request.key << std::endl;

        // Delete file system object
        DeleteObject(object.bucket, object.key, object.internalName);

        // Check notifications
        CheckNotifications(request.region, request.bucket, request.key, 0, "s3:ObjectRemoved:Delete");

        log_info_stream(_logger) << "Object deleted, bucket: " << request.bucket << " key: " << request.key << std::endl;

      } catch (Poco::Exception &exc) {
        log_error_stream(_logger) << "S3 delete object failed, message: " + exc.message() << std::endl;
        throw Core::ServiceException(exc.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
      }
    }
  }

  Dto::S3::DeleteObjectsResponse S3Service::DeleteObjects(const Dto::S3::DeleteObjectsRequest &request) {
    log_trace_stream(_logger) << "Delete objects request: " << request.ToString() << std::endl;

    // Check existence
    if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    Dto::S3::DeleteObjectsResponse response;
    try {

      // Delete from database
      _database->DeleteObjects(request.bucket, request.keys);
      log_debug_stream(_logger) << "Database object deleted, count: " << request.keys.size() << std::endl;

      // Delete file system objects
      for (const auto &key : request.keys) {

        // Delete from database
        Database::Entity::S3::Object object = _database->GetObject(request.region, request.bucket, key);
        log_debug_stream(_logger) << "Database object deleted, count: " << request.keys.size() << std::endl;

        DeleteObject(object.bucket, object.key, object.internalName);
        log_debug_stream(_logger) << "File system object deleted: " << key << std::endl;

        // Check notifications
        CheckNotifications(request.region, request.bucket, key, 0, "s3:ObjectRemoved:Delete");
      }
      log_info_stream(_logger) << "Objects deleted, bucket: " << request.bucket << " count: " << request.keys.size() << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "S3 delete objects failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
    log_info_stream(_logger) << "DeleteObjects succeeded, bucket: " << request.bucket << std::endl;
    return response;
  }

  void S3Service::PutBucketNotification(const Dto::S3::PutBucketNotificationRequest &request) {
    log_trace_stream(_logger) << "Put bucket notification request, id: " << request.notificationId << std::endl;

    // Check bucket existence
    if (!_database->BucketExists({.region=request.region, .name=request.bucket})) {
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Check notification existence
    Database::Entity::S3::Bucket bucket = _database->GetBucketByRegionName(request.region, request.bucket);
    if (bucket.HasNotification(request.event)) {
      throw Core::ServiceException("Bucket notification exists already", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
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
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void S3Service::DeleteBucket(const std::string &region, const std::string &name) {
    log_trace_stream(_logger) << "Delete bucket request, name: " << name << std::endl;

    Database::Entity::S3::Bucket bucket = {.region=region, .name=name};

    // Check existence
    if (!_database->BucketExists(bucket)) {
      throw Core::ServiceException("Bucket does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Check empty
    if (_database->HasObjects(bucket)) {
      throw Core::ServiceException("Bucket is not empty", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Check transfer bucket
    if (name == _transferBucket) {
      throw Core::ServiceException("Transfer bucket cannot be deleted", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }

    try {

      // Delete directory
      DeleteBucket(name);

      // Delete bucket from database
      _database->DeleteBucket(bucket);
      log_info_stream(_logger) << "Bucket deleted, bucket: " << bucket.name << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "S3 Delete Bucket failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void S3Service::CheckNotifications(const std::string &region, const std::string &bucket, const std::string &key, long size, const std::string &event) {

    Database::Entity::S3::Bucket bucketEntity = _database->GetBucketByRegionName(region, bucket);

    if (bucketEntity.HasNotification(event)) {

      Database::Entity::S3::BucketNotification notification = bucketEntity.GetNotification(event);

      // Create the event record
      Dto::S3::Object s3Object = {.key=key, .size=size, .etag=Poco::UUIDGenerator().createRandom().toString()};
      Dto::S3::Bucket s3Bucket = {.name=bucketEntity.name};

      Dto::S3::S3 s3 = {.configurationId=notification.notificationId, .bucket=s3Bucket, .object=s3Object};

      Dto::S3::Record record = {.region=region, .eventName=event, .s3=s3};
      Dto::S3::EventNotification eventNotification;

      eventNotification.records.push_back(record);
      log_debug_stream(_logger) << "Found notification records, count: " << eventNotification.records.size() << std::endl;

      if (!notification.queueArn.empty()) {

        // Queue notification
        SendQueueNotificationRequest(eventNotification, notification.queueArn);
        log_trace_stream(_logger) << "SQS message created, eventNotification: " + eventNotification.ToString() << std::endl;
        log_debug_stream(_logger) << "SQS message created, queueArn: " << notification.queueArn << std::endl;

      } else if (!notification.lambdaArn.empty()) {

        // lambda notification
        SendLambdaInvocationRequest(eventNotification, notification);
        log_trace_stream(_logger) << "lambda function invoked, eventNotification: " + eventNotification.ToString() << std::endl;
        log_debug_stream(_logger) << "lambda function invoked, lambdaArn:" << notification.lambdaArn << std::endl;
      }
    } else {
      log_debug_stream(_logger) << "No notifications found, event: " << event << " bucket: " << bucket << " key: " << key << std::endl;
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

    return _dataS3Dir + Poco::Path::separator() + bucket + Poco::Path::separator() + GetDirFromKey(key);
  }

  std::string S3Service::GetFilename(const std::string &bucket, const std::string &key) {

    return _dataS3Dir + Poco::Path::separator() + bucket + Poco::Path::separator() + key;
  }

  void S3Service::DeleteObject(const std::string &bucket, const std::string &key, const std::string &internalName) {

    std::string filename = _dataS3Dir + Poco::Path::separator() + internalName;
    Core::FileUtils::DeleteFile(filename);
    log_debug_stream(_logger) << "File system object deleted, filename: " << filename << std::endl;

    if (bucket == _transferBucket) {
      filename = _transferDir + Poco::Path::separator() + key;
      Core::FileUtils::DeleteFile(filename);
      log_debug_stream(_logger) << "Transfer file system object deleted, filename: " << filename << std::endl;
    }
  }

  void S3Service::DeleteBucket(const std::string &bucket) {

    std::string bucketDir = _dataS3Dir + Poco::Path::separator() + bucket;
    if (Core::DirUtils::DirectoryExists(bucketDir)) {
      Core::DirUtils::DeleteDirectory(bucketDir, true);
      log_debug_stream(_logger) << "Bucket directory deleted, bucketDir: " + bucketDir << std::endl;
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

    // Get the response state
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
      log_error_stream(_logger) << "HTTP error, state: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
    }
    log_debug_stream(_logger) << "SQS message request send, state: " << response.getStatus() << std::endl;
  }

  void S3Service::SendLambdaInvocationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::BucketNotification &bucketNotification) {

    std::vector<std::string> parts = Core::StringUtils::Split(bucketNotification.lambdaArn, ':');
    std::string functionName = parts[6];
    log_debug_stream(_logger) << "Invocation request function name: " << functionName << std::endl;

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
    log_trace_stream(_logger) << "Invocation request created, body: " + body << std::endl;

    // Send request
    std::ostream &os = session.sendRequest(request);
    os << body;

    // Get the response state
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
      log_error_stream(_logger) << "HTTP error, state: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
    }
    log_debug_stream(_logger) << "Invocation request send, state: " << response.getStatus() << std::endl;
  }

  Dto::S3::PutObjectResponse S3Service::SaveUnversionedObject(Dto::S3::PutObjectRequest &request, std::istream &stream) {

    // Write file
    std::string fileName = Core::AwsUtils::CreateS3FileName();
    std::string filePath = _dataS3Dir + Poco::Path::separator() + fileName;
    std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
    long size = Poco::StreamCopier::copyStream(stream, ofs);
    ofs.close();
    log_debug_stream(_logger) << "File received, fileName: " << filePath << " size: " << size << std::endl;

    // Meta data
    std::string md5sum = Core::Crypto::GetMd5FromFile(filePath);
//    std::string sha1sum = Core::Crypto::GetSha1FromFile(filePath);
//    std::string sha256sum = Core::Crypto::GetSha256FromFile(filePath);
    log_info_stream(_logger) << "Checksum, bucket: " << request.bucket << " key: " << request.key << " md5: " << md5sum << std::endl;

    // Update database
    Database::Entity::S3::Object object = {
        .region=request.region,
        .bucket=request.bucket,
        .key=request.key,
        .owner=request.owner,
        .size=size,
        .md5sum=md5sum,
//        .sha1sum=sha1sum,
//        .sha256sum=sha256sum,
        .contentType=request.contentType,
        .metadata=request.metadata,
        .internalName=fileName
    };

    // Update database
    object = _database->CreateOrUpdateObject(object);
    log_debug_stream(_logger) << "Database updated, bucket: " << object.bucket << " key: " << object.key << std::endl;

    // Check notification
    CheckNotifications(request.region, request.bucket, request.key, object.size, "s3:ObjectCreated:Put");
    log_info_stream(_logger) << "Put object succeeded, bucket: " << request.bucket << " key: " << request.key << std::endl;

    return {
        .bucket=request.bucket,
        .key=request.key,
        .etag=md5sum,
        .md5Sum=md5sum,
        .contentLength=size,
        .checksumAlgorithm="SHA256",
//        .checksumSha256=sha256sum,
        .metadata=request.metadata
    };
  }

  Dto::S3::PutObjectResponse S3Service::SaveVersionedObject(Dto::S3::PutObjectRequest &request, std::istream &stream, Database::Entity::S3::Bucket &bucket) {

    // Write file
    std::string fileName = Core::AwsUtils::CreateS3FileName();
    std::string filePath = _dataS3Dir + Poco::Path::separator() + fileName;
    std::ofstream ofs(filePath, std::ios::out | std::ios::trunc);
    long size = Poco::StreamCopier::copyStream(stream, ofs);
    ofs.close();
    log_debug_stream(_logger) << "File received, filePath: " << filePath << " size: " << size << std::endl;

    // Meta data
    std::string md5sum = Core::Crypto::GetMd5FromFile(filePath);
    //std::string sha1sum = Core::Crypto::GetSha1FromFile(filePath);
    //std::string sha256sum = Core::Crypto::GetSha256FromFile(filePath);
    log_info_stream(_logger) << "Checksum, bucket: " << request.bucket << " key: " << request.key << "md5: " << md5sum << std::endl;

    Database::Entity::S3::Object object;

    // Check existence by
    Database::Entity::S3::Object existingObject = _database->GetObjectMd5(request.region, request.bucket, request.key, md5sum);
    if (existingObject.oid.empty()) {

      // Version ID
      std::string versionId = Core::AwsUtils::CreateS3VersionId();

      // Create new version of new object
      object = {
          .region=request.region,
          .bucket=request.bucket,
          .key=request.key,
          .owner=request.owner,
          .size=size,
          .md5sum=md5sum,
//          .sha1sum=sha1sum,
//          .sha256sum=sha256sum,
          .contentType=request.contentType,
          .metadata=request.metadata,
          .internalName=fileName,
          .versionId=versionId,
      };

      // Create new version in database
      object = _database->CreateObject(object);
      log_debug_stream(_logger) << "Database updated, bucket: " << object.bucket << " key: " << object.key << std::endl;

      // Check notification
      CheckNotifications(request.region, request.bucket, request.key, object.size, "s3:ObjectCreated:Put");
      log_info_stream(_logger) << "Put object succeeded, bucket: " << request.bucket << " key: " << request.key << std::endl;

    } else {

      // Delete local file
      Core::FileUtils::DeleteFile(filePath);
    }

    return {
        .bucket=request.bucket,
        .key=request.key,
        .etag=md5sum,
        .md5Sum=md5sum,
        .contentLength=size,
        .checksumAlgorithm="SHA256",
//        .checksumSha256=sha256sum,
        .metadata=request.metadata,
        .versionId=object.versionId
    };
  }
} // namespace AwsMock::Service
