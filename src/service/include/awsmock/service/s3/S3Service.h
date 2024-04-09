//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_S3_SERVICE_H
#define AWSMOCK_SERVICE_S3_SERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// AwsMock includes
#include "awsmock/core/CryptoUtils.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/core/ServiceException.h"
#include "awsmock/repository/S3Database.h"
#include "awsmock/dto/s3/CompleteMultipartUploadResult.h"
#include "awsmock/dto/s3/CopyObjectRequest.h"
#include "awsmock/dto/s3/CopyObjectResponse.h"
#include "awsmock/dto/s3/CompleteMultipartUploadRequest.h"
#include "awsmock/dto/s3/CreateBucketRequest.h"
#include "awsmock/dto/s3/CreateBucketResponse.h"
#include "awsmock/dto/s3/CreateMultipartUploadRequest.h"
#include "awsmock/dto/s3/DeleteBucketRequest.h"
#include "awsmock/dto/s3/DeleteObjectRequest.h"
#include "awsmock/dto/s3/DeleteObjectsRequest.h"
#include "awsmock/dto/s3/DeleteObjectsResponse.h"
#include "awsmock/dto/s3/EventNotification.h"
#include "awsmock/dto/s3/GetMetadataRequest.h"
#include "awsmock/dto/s3/GetMetadataResponse.h"
#include "awsmock/dto/s3/GetObjectRequest.h"
#include "awsmock/dto/s3/GetObjectResponse.h"
#include "awsmock/dto/s3/CreateMultipartUploadResult.h"
#include "awsmock/dto/s3/ListBucketRequest.h"
#include "awsmock/dto/s3/ListBucketResponse.h"
#include "awsmock/dto/s3/ListAllBucketResponse.h"
#include "awsmock/dto/s3/MoveObjectRequest.h"
#include "awsmock/dto/s3/MoveObjectResponse.h"
#include "awsmock/dto/s3/PutBucketNotificationRequest.h"
#include "awsmock/dto/s3/PutBucketVersioningRequest.h"
#include "awsmock/dto/s3/PutObjectRequest.h"
#include "awsmock/dto/s3/PutObjectResponse.h"
#include "awsmock/service/lambda/LambdaService.h"

#define DEFAULT_DATA_DIR  "/tmp/awsmock/data"
#define DEFAULT_S3_DATA_DIR  "/tmp/awsmock/data/s3"
#define DEFAULT_TRANSFER_DATA_DIR  "/tmp/awsmock/data/transfer"
#define DEFAULT_TRANSFER_BUCKET  "transfer-server"

namespace AwsMock::Service {

  typedef std::map<std::string, std::ofstream> MultiPartUploads;

  class S3Service {

  public:

    /**
     * Constructor
     *
     * @param configuration module configuration
     */
    explicit S3Service(Core::Configuration &configuration);

    /**
     * Returns the meta data of an S3 object
     *
     * @param request get metadata request
     * @return CreateBucketResponse
     */
    Dto::S3::GetMetadataResponse GetMetadata(Dto::S3::GetMetadataRequest &request);

    /**
     * Creates a new bucket
     *
     * @param s3Request S3 create request
     * @return CreateBucketResponse
     */
    Dto::S3::CreateBucketResponse CreateBucket(const Dto::S3::CreateBucketRequest &s3Request);

    /**
     * Lists all buckets
     *
     * @return ListAllBucketResponse
     */
    Dto::S3::ListAllBucketResponse ListAllBuckets();

    /**
     * Lists contents of bucket
     *
     * @param s3Request S3 create request
     * @return CreateBucketResponse
     */
    Dto::S3::ListBucketResponse ListBucket(const Dto::S3::ListBucketRequest &s3Request);

    /**
     * Put bucket versioning
     *
     * @param s3Request S3 put versioning request
     */
    void PutBucketVersioning(const Dto::S3::PutBucketVersioningRequest &s3Request);

    /**
     * Creates a new bucket
     *
     * @param s3Request S3 multi part upload request
     * @return Dto::S3::CreateMultipartUploadResult
     */
    Dto::S3::CreateMultipartUploadResult CreateMultipartUpload(const Dto::S3::CreateMultipartUploadRequest &s3Request);

    /**
     * Upload a partial file
     *
     * @param stream input stream
     * @param part part number
     * @param updateId upload ID
     * @return ETag
     */
    std::string UploadPart(std::istream &stream, int part, const std::string &updateId);

    /**
     * Completes a multipart upload.
     *
     * @param request multipart upload request
     * @return Dto::S3::CreateMultipartUploadResult
     */
    Dto::S3::CompleteMultipartUploadResult CompleteMultipartUpload(const Dto::S3::CompleteMultipartUploadRequest &request);

    /**
     * Get object
     *
     * @param request put object request
     * @return GetObjectResponse
     */
    Dto::S3::GetObjectResponse GetObject(Dto::S3::GetObjectRequest &request);

    /**
     * Put object
     *
     * @param request put object request
     * @param stream input stream
     * @return PutObjectResponse
     */
    Dto::S3::PutObjectResponse PutObject(Dto::S3::PutObjectRequest &request, std::istream &stream);

    /**
     * Copy object
     *
     * @param request copy object request
     * @return PutObjectResponse
     */
    Dto::S3::CopyObjectResponse CopyObject(Dto::S3::CopyObjectRequest &request);

    /**
     * Move object
     *
     * @param request move object request
     * @return PutObjectResponse
     */
    Dto::S3::MoveObjectResponse MoveObject(Dto::S3::MoveObjectRequest &request);

    /**
     * Delete object
     *
     * @param request delete object request
     */
    void DeleteObject(const Dto::S3::DeleteObjectRequest &request);

    /**
     * Delete objects
     *
     * @param request delete objects request
     * @return DeleteObjectsResponse
     */
    Dto::S3::DeleteObjectsResponse DeleteObjects(const Dto::S3::DeleteObjectsRequest &request);

    /**
     * Adds a bucket notification
     *
     * @param request bucket notification request.
     */
    void PutBucketNotification(const Dto::S3::PutBucketNotificationRequest &request);

    /**
     * Delete a bucket
     *
     * @param request bucket delete request.
     */
    void DeleteBucket(const Dto::S3::DeleteBucketRequest &request);

  private:

    /**
     * Sends a message to the corresponding SQS queue.
     *
     * @param eventNotification S3 event notification.
     * @param queueArn ARN of the SQS queue.
     */
    void SendQueueNotificationRequest(const Dto::S3::EventNotification &eventNotification, const std::string &queueArn);

    /**
     * Send lambda function invocation request to lambda module.
     *
     * <p>This will send a lambda invocation requst to the lambda module. The lambda module will StartServer the corresponding lambda function and will send the S3
     * notification request to the lambda function.</p>
     *
     * @param eventNotification S3 event notification
     * @param bucketNotification S3 bucket notification
     */
    void SendLambdaInvocationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::BucketNotification &bucketNotification);

    /**
     * Get the directory from the object key.
     *
     * @param key S3 object key
     * @return all directories before file
     */
    static std::string GetDirFromKey(const std::string &key);

    /**
     * Get the directory for a given bucket/key combination.
     *
     * @param bucket S3 bucket name
     * @param key S3 object key.
     * @return directory path.
     */
    std::string GetDirectory(const std::string &bucket, const std::string &key);

    /**
     * Get the absolute filename for a given bucket/key combination.
     *
     * @param bucket S3 bucket name
     * @param key S3 object key.
     * @return absolute filename path.
     */
    std::string GetFilename(const std::string &bucket, const std::string &key);

    /**
     * Check for bucket notifications.
     *
     * @param region AWS region.
     * @param bucket bucket name.
     * @param key S3 object key.
     * @param size S3 object size in bytes.
     * @param event S3 event type.
     */
    void CheckNotifications(const std::string &region, const std::string &bucket, const std::string &key, long size, const std::string &event);

    /**
     * Get the temporary upload directory for a uploadId.
     *
     * @param uploadId S3 multipart uplaod ID
     * @return temporary directory path.
     */
    std::string GetMultipartUploadDirectory(const std::string &uploadId);

    /**
     * Create a queue notification
     *
     * @param bucket bucket to modify
     * @param request put bucket notification request.
     * @return updated bucket.
     */
    Database::Entity::S3::Bucket CreateQueueConfiguration(const Database::Entity::S3::Bucket &bucket, const Dto::S3::PutBucketNotificationRequest &request);

    /**
     * Create a lambda function notification
     *
     * @param bucket bucket to modify
     * @param request put bucket notification request.
     * @return updated bucket.
     */
    Database::Entity::S3::Bucket CreateLambdaConfiguration(const Database::Entity::S3::Bucket &bucket, const Dto::S3::PutBucketNotificationRequest &request);

    /**
     * Deletes an object
     *
     * @param bucket S3 bucket
     * @param key S3 object key
     * @param internalName S3 internal name
     */
    void DeleteObject(const std::string &bucket, const std::string &key, const std::string &internalName);

    /**
     * Deletes an bucket
     *
     * <p>This method is recursive, if the bucket contains objects, also all object are removed </p>
     *
     * @param bucket S3 bucket name
     */
    void DeleteBucket(const std::string &bucket);

  private:

    /**
     * Save a versioned S3 object.
     *
     * @param request put object request
     * @param stream input stream
     * @param bucket bucket entity
     * @return file name
     */
    Dto::S3::PutObjectResponse SaveVersionedObject(Dto::S3::PutObjectRequest &request, std::istream &stream, Database::Entity::S3::Bucket &bucket);

    /**
     * Save a unversioned S3 object.
     *
     * @param request put object request
     * @param stream input stream
     * @return file name
     */
    Dto::S3::PutObjectResponse SaveUnversionedObject(Dto::S3::PutObjectRequest &request, std::istream &stream);

    /**
     * Logger
     */
    Core::LogStream _logger;

    /**
     * Data directory
     */
    std::string _dataDir;

    /**
     * Data S3 dir
     */
    std::string _dataS3Dir;

    /**
     * Transfer manager base directory
     */
    std::string _transferDir;

    /**
     * Transfer manager bucket
     */
    std::string _transferBucket;

    /**
     * Temp directory
     */
    std::string _tempDir;

    /**
     * Configuration
     */
    Core::Configuration &_configuration;

    /**
     * Database connection
     */
    Database::S3Database& _database;

    /**
     * Multipart uploads map
     */
    MultiPartUploads _uploads;

    /**
     * SQS module port
     */
    int _sqsServicePort;

    /**
     * SQS module host
     */
    std::string _sqsServiceHost;

    /**
     * lambda module port
     */
    int _lambdaServicePort;

    /**
     * lambda module host
     */
    std::string _lambdaServiceHost;

    /**
     * S3 account id
     */
    std::string _accountId;
  };

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_S3_SERVICE_H
