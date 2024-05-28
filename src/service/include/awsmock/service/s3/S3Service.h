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
#include "awsmock/core/exception/NotFoundException.h"
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/s3/CompleteMultipartUploadRequest.h>
#include <awsmock/dto/s3/CompleteMultipartUploadResult.h>
#include <awsmock/dto/s3/CopyObjectRequest.h>
#include <awsmock/dto/s3/CopyObjectResponse.h>
#include <awsmock/dto/s3/CreateBucketRequest.h>
#include <awsmock/dto/s3/CreateBucketResponse.h>
#include <awsmock/dto/s3/CreateMultipartUploadRequest.h>
#include <awsmock/dto/s3/CreateMultipartUploadResult.h>
#include <awsmock/dto/s3/DeleteBucketRequest.h>
#include <awsmock/dto/s3/DeleteObjectRequest.h>
#include <awsmock/dto/s3/DeleteObjectsRequest.h>
#include <awsmock/dto/s3/DeleteObjectsResponse.h>
#include <awsmock/dto/s3/GetMetadataRequest.h>
#include <awsmock/dto/s3/GetMetadataResponse.h>
#include <awsmock/dto/s3/GetObjectRequest.h>
#include <awsmock/dto/s3/GetObjectResponse.h>
#include <awsmock/dto/s3/ListAllBucketResponse.h>
#include <awsmock/dto/s3/ListBucketRequest.h>
#include <awsmock/dto/s3/ListBucketResponse.h>
#include <awsmock/dto/s3/ListObjectVersionsRequest.h>
#include <awsmock/dto/s3/ListObjectVersionsResponse.h>
#include <awsmock/dto/s3/MoveObjectRequest.h>
#include <awsmock/dto/s3/MoveObjectResponse.h>
#include <awsmock/dto/s3/PutBucketEncryptionRequest.h>
#include <awsmock/dto/s3/PutBucketNotificationConfigurationRequest.h>
#include <awsmock/dto/s3/PutBucketNotificationConfigurationResponse.h>
#include <awsmock/dto/s3/PutBucketNotificationRequest.h>
#include <awsmock/dto/s3/PutBucketVersioningRequest.h>
#include <awsmock/dto/s3/PutObjectRequest.h>
#include <awsmock/dto/s3/PutObjectResponse.h>
#include <awsmock/dto/s3/mapper/Mapper.h>
#include <awsmock/dto/s3/model/EventNotification.h>
#include <awsmock/dto/s3/model/TopicConfiguration.h>
#include <awsmock/entity/s3/LambdaNotification.h>
#include <awsmock/entity/s3/QueueNotification.h>
#include <awsmock/entity/s3/TopicNotification.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/kms/KMSService.h>
#include <awsmock/service/lambda/LambdaExecutor.h>
#include <awsmock/service/lambda/LambdaService.h>
#include <awsmock/service/s3/S3HashCreator.h>
#include <awsmock/service/sns/SNSService.h>
#include <awsmock/service/sqs/SQSService.h>

#define DEFAULT_USER "none"
#define DEFAULT_REGION "eu-central-1"
#define DEFAULT_DATA_DIR "/home/awsmock/data"
#define DEFAULT_TRANSFER_DATA_DIR "/tmp/awsmock/data/transfer"
#define DEFAULT_TRANSFER_BUCKET_NAME "transfer-server"

namespace AwsMock::Service {

    typedef std::map<std::string, std::ofstream> MultiPartUploads;

    /**
     * @brief S3 service.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class S3Service {

      public:

        /**
         * Constructor
         */
        explicit S3Service();

        /**
         * Returns the meta data of an S3 bucket
         *
         * @param request get metadata request
         * @return GetMetadataResponse
         */
        Dto::S3::GetMetadataResponse GetBucketMetadata(Dto::S3::GetMetadataRequest &request);

        /**
         * Returns the meta data of an S3 object
         *
         * @param request get metadata request
         * @return GetMetadataResponse
         */
        Dto::S3::GetMetadataResponse GetObjectMetadata(Dto::S3::GetMetadataRequest &request);

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
         * Adds a bucket notification configuration
         *
         * @param request bucket notification configuration request.
         * @return PutBucketNotificationConfigurationResponse,
         * @see PutBucketNotificationConfigurationRequest
         * @see PutBucketNotificationConfigurationResponse
         */
        Dto::S3::PutBucketNotificationConfigurationResponse PutBucketNotificationConfiguration(const Dto::S3::PutBucketNotificationConfigurationRequest &request);

        /**
         * Adds a bucket encryption configuration
         *
         * @param request bucket encryption configuration request.
         * @see PutBucketEncryptionRequest
         */
        void PutBucketEncryption(const Dto::S3::PutBucketEncryptionRequest &request);

        /**
         * Returns a list object versions
         *
         * @param s3Request list object versions request
         * @return ListObjectVersionsResponse
         * @see AwsMock::Dto::S3::ListObjectVersionsRequest
         ** @see AwsMock::Dto::S3::ListObjectVersionsResponse
         */
        Dto::S3::ListObjectVersionsResponse ListObjectVersions(const Dto::S3::ListObjectVersionsRequest &s3Request);

        /**
         * Delete a bucket
         *
         * @param request bucket delete request.
         */
        void DeleteBucket(const Dto::S3::DeleteBucketRequest &request);

        /**
         * Calculates the MD5, SHA1, SHA256 asynchronously
         *
         * @param object S3 object
         */
        void CalculateHashes(Database::Entity::S3::Object &object);

      private:

        /**
         * Sends a message to the corresponding SQS queue.
         *
         * @param eventNotification S3 event notification.
         * @param queueNotification queue notification.
         */
        void SendQueueNotificationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::QueueNotification &queueNotification);

        /**
         * Sends a message to the corresponding SNS topic.
         *
         * @param eventNotification S3 event notification.
         * @param topicNotification topic notification.
         */
        void SendTopicNotificationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::TopicNotification &topicNotification);

        /**
         * Send lambda function invocation request to lambda module.
         *
         * <p>This will send a lambda invocation request to the lambda module. The lambda module will StartServer the corresponding lambda function and will send the S3
         * notification request to the lambda function.</p>
         *
         * @param eventNotification S3 event notification
         * @param lambdaNotification S3 lambda notification
         */
        void SendLambdaInvocationRequest(const Dto::S3::EventNotification &eventNotification, const Database::Entity::S3::LambdaNotification &lambdaNotification);

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
         * @brief Checks the encryption status and encrypt the internal file using the KMS key supplied in the encryption object of the bucket.
         *
         * @param bucket S3 bucket
         * @param object S3 object
         */
        void CheckEncryption(const Database::Entity::S3::Bucket &bucket, const Database::Entity::S3::Object &object);

        /**
         * @brief Checks the decryption status and decrypts the internal file using the KMS key supplied in the encryption object of the bucket.
         *
         * <p>
         * The decrypted file will be written to outFile. This file needs to be deleted, after the file has been send back to the client.
         * </p>
         *
         * @param bucket S3 bucket
         * @param object S3 object
         * @param outFile name of the output file
         */
        void CheckDecryption(const Database::Entity::S3::Bucket &bucket, const Database::Entity::S3::Object &object, std::string &outFile);

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

        /**
         * @brief Save a versioned S3 object.
         *
         * @param request put object request
         * @param bucket S3 bucket
         * @param stream input stream
         * @return file name
         */
        Dto::S3::PutObjectResponse SaveVersionedObject(Dto::S3::PutObjectRequest &request, const Database::Entity::S3::Bucket &bucket, std::istream &stream);

        /**
         * Save a unversioned S3 object.
         *
         * @param request put object request
         * @param bucket S3 bucket
         * @param stream input stream
         * @return file name
         */
        Dto::S3::PutObjectResponse SaveUnversionedObject(Dto::S3::PutObjectRequest &request, const Database::Entity::S3::Bucket &bucket, std::istream &stream);

        /**
         * Adds the queue notification configuration to the provided bucket.
         *
         * @param bucket bucket entity.
         * @param queueConfigurations queue notification configurations vector.
         */
        static void GetQueueNotificationConfigurations(Database::Entity::S3::Bucket &bucket, const std::vector<Dto::S3::QueueConfiguration> &queueConfigurations);

        /**
         * Adds the topic notification configuration to the provided bucket.
         *
         * @param bucket bucket entity.
         * @param topicConfigurations topic notification configurations vector.
         */
        static void GetTopicNotificationConfigurations(Database::Entity::S3::Bucket &bucket, const std::vector<Dto::S3::TopicConfiguration> &topicConfigurations);

        /**
         * Adds the lambda notification configuration to the provided bucket.
         *
         * @param bucket bucket entity.
         * @param lambdaConfigurations lambda notification configurations vector.
         */
        static void GetLambdaNotificationConfigurations(Database::Entity::S3::Bucket &bucket, const std::vector<Dto::S3::LambdaConfiguration> &lambdaConfigurations);

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
         * Database connection
         */
        Database::S3Database &_database;

        /**
         * SQS service
         */
        //SQSService _sqsService;

        /**
         * SNS service
         */
        //SNSService _snsService;

        /**
         * Lambda service
         */
        LambdaService _lambdaService;

        /**
         * Multipart uploads map
         */
        MultiPartUploads _uploads;

        /**
         * AWS account ID
         */
        std::string _accountId;

        /**
         * AWS user
         */
        std::string _user;

        /**
         * AWS region
         */
        std::string _region;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_S3_SERVICE_H
