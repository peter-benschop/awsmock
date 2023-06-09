//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_S3SERVICE_H
#define AWSMOCK_SERVICE_S3SERVICE_H

// C++ standard includes
#include <string>

// Poco includes
#include <Poco/Logger.h>
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Node.h"

// AwsMock includes
#include "awsmock/core/CryptoUtils.h"
#include "awsmock/core/ServiceException.h"
#include "awsmock/db/S3Database.h"
#include "awsmock/dto/s3/CompleteMultipartUploadResult.h"
#include "awsmock/dto/s3/CreateBucketRequest.h"
#include "awsmock/dto/s3/CreateBucketResponse.h"
#include "awsmock/dto/s3/DeleteObjectRequest.h"
#include "awsmock/dto/s3/DeleteObjectsRequest.h"
#include "awsmock/dto/s3/DeleteObjectsResponse.h"
#include "awsmock/dto/s3/EventNotification.h"
#include "awsmock/dto/s3/GetMetadataRequest.h"
#include "awsmock/dto/s3/GetMetadataResponse.h"
#include "awsmock/dto/s3/GetObjectRequest.h"
#include "awsmock/dto/s3/GetObjectResponse.h"
#include "awsmock/dto/s3/InitiateMultipartUploadResult.h"
#include "awsmock/dto/s3/ListBucketResult.h"
#include "awsmock/dto/s3/ListAllBucketResponse.h"
#include "awsmock/dto/s3/PutBucketNotificationRequest.h"
#include "awsmock/dto/s3/PutObjectRequest.h"
#include "awsmock/dto/s3/PutObjectResponse.h"

namespace AwsMock::Service {

    typedef std::map<std::string, std::ofstream> MultiPartUploads;

    class S3Service {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit S3Service(const Core::Configuration &configuration);

      /**
       * Returns the meta data of an S3 object
       *
       * @param name name of the bucket
       * @param owner owner of the bucket
       * @param s3Request S3 create request
       * @return CreateBucketResponse
       */
      Dto::S3::GetMetadataResponse GetMetadata(Dto::S3::GetMetadataRequest &request);

      /**
       * Creates a new bucket
       *
       * @param name name of the bucket
       * @param owner owner of the bucket
       * @param s3Request S3 create request
       * @return CreateBucketResponse
       */
      Dto::S3::CreateBucketResponse CreateBucket(const std::string &name, const std::string &owner, const Dto::S3::CreateBucketRequest &s3Request);

      /**
       * Lists all buckets
       *
       * @return ListAllBucketResponse
       */
      Dto::S3::ListAllBucketResponse ListAllBuckets();

      /**
       * Lists contents of bucket
       *
       * @param name name of the bucket
       * @param s3Request S3 create request
       * @return CreateBucketResponse
       */
      Dto::S3::ListBucketResult ListBucket(const std::string &bucket);

      /**
       * Creates a new bucket
       *
       * @param bucket bucket name
       * @param key object key
       * @param region AWS region
       * @param user AWS user
       * @return Dto::S3::InitiateMultipartUploadResult
       */
      Dto::S3::InitiateMultipartUploadResult CreateMultipartUpload(std::string &bucket, std::string &key, const std::string &region, const std::string &user);

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
       * @param uploadId upload ID
       * @param bucket bucket name
       * @param key object key
       * @param region AWS region
       * @param user AWS user
       * @return Dto::S3::InitiateMultipartUploadResult
       */
      Dto::S3::CompleteMultipartUploadResult CompleteMultipartUpload(const std::string &uploadId,
                                                                     const std::string &bucket,
                                                                     const std::string &key,
                                                                     const std::string &region,
                                                                     const std::string &user);

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
      Dto::S3::PutObjectResponse PutObject(Dto::S3::PutObjectRequest &request, std::istream *stream = nullptr);

      /**
       * Delete object
       *
       * @param request delete object request
       * @return DeleteObjectResponse
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
      void PutBucketNotification(const Dto::S3::PutBucketNotificationRequest& request);

      /**
       * Delete a bucket
       *
       * @param name name of the bucket
       */
      void DeleteBucket(const std::string &region, const std::string &name);

    private:

      /**
       * Initialize the service
       */
      void Initialize();

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
       * @param object S3 object.
       * @param region AWS region.
       * @param event S3 event type.
       */
      void CheckNotifications(const Database::Entity::S3::Object& object, const std::string &region, const std::string &event);

      /**
       * Get the temporary upload directory for a uploadId.
       *
       * @param uploadId S3 multipart uplaod ID
       * @return temporary directory path.
       */
      std::string GetMultipartUploadDirectory(const std::string &uploadId);

      /**
       * Returns a event notification.
       *
       * @param key S3 object key
       * @return all directories before file
       */
      static std::string GetEventNotification(const std::string &key);

      /**
       * Create a queue notification
       *
       * @param request put bucket notification request.
       * @return BucketNotification.
       */
      Database::Entity::S3::BucketNotification CreateQueueConfiguration(const Dto::S3::PutBucketNotificationRequest &request);

      /**
       * Create a lambda function notification
       *
       * @param request put bucket notification request.
       * @return BucketNotification.
       */
      Database::Entity::S3::BucketNotification CreateFunctionConfiguration(const Dto::S3::PutBucketNotificationRequest &request);

      /**
       * Deletes an object
       *
       * @param bucket S3 bucket name
       * @param key S3 object key
       */
      void DeleteObject(const std::string &bucket, const std::string &key);

      /**
       * Deletes an bucket
       *
       * <p>This method is recursive, if the bucket contains objects, also all object are removed </p>
       *
       * @param bucket S3 bucket name
       */
      void DeleteBucket(const std::string &bucket);

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Data directory
       */
      std::string _dataDir;

      /**
       * Temp directory
       */
      std::string _tempDir;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Database connection
       */
      std::unique_ptr<Database::S3Database> _database;

      /**
       * Multipart uploads map
       */
      MultiPartUploads _uploads;

      /**
       * Lock
       */
      Poco::Mutex _mutex;

    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_S3SERVICE_H
