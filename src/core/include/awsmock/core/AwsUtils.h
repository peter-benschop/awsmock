//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWSMOCK_CORE_AWSUTILS_H
#define AWSMOCK_CORE_AWSUTILS_H

// C++ standard includes
#include <string>
#include <iostream>

// Poco includes
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/Configuration.h>

#define S3_FILE_NAME_LENGTH 64
#define S3_VERSION_ID_LENGTH 64

#define SQS_RECEIPT_HANDLE_LENGTH 512
#define SQS_DEFAULT_ACCOUNT_ID "000000000000"

#define GATEWAY_DEFAULT_PORT 4566
#define GATEWAY_DEFAULT_PROTOCOL std::string("http")
#define GATEWAY_DEFAULT_REGION "eu-central-1"

namespace AwsMock::Core {

  class AwsUtils {

  public:

    /**
     * Create Amazon Resource Names (ARNs)
     *
     * @param service AWS module name
     * @param region AWS region
     * @param accountId AWS accountId
     * @param resourceId AWS resourceId
     */
    static std::string CreateArn(const std::string &service, const std::string &region, const std::string &accountId, const std::string &resourceId);

    /**
     * Create S3 Amazon bucket/key ARN
     *
     * @param region AWS region
     * @param accountId AWS account ID
     * @param bucket bucket name
     * @param key object key
     */
    static std::string CreateS3Arn(const std::string &region, const std::string &accountId, const std::string &bucket, const std::string &key);

    /**
     * Create lambda function ARN
     *
     * @param region AWS region
     * @param accountId AWS account ID
     * @param function lambda function name
     */
    static std::string CreateLambdaArn(const std::string &region, const std::string &accountId, const std::string &function);

    /**
     * Generate a SQS queue URL.
     *
     * <p>The queue name has the format 'http://<host>:<port>/<accountId>/<queueName>'</p>
     *
     * @param configuration current AwsMock configuration
     * @param queueName name of the queue
     * @return SQS queue URL
     */
    static std::string CreateSqsQueueUrl(const Configuration &configuration, const std::string &queueName);

    /**
     * Create SQS queue ARN
     *
     * @param configuration current AwsMock configuration
     * @param queueName name of the queue
     * @return SQS queue ARN
     */
    static std::string CreateSqsQueueArn(const Configuration &configuration, const std::string &queueName);

    /**
     * Create SNS topic ARN
     *
     * @param region AWS region
     * @param accountId AWS account ID
     * @param topicName name of the topic
     */
    static std::string CreateSNSTopicArn(const std::string &region, const std::string &accountId, const std::string &topicName);

    /**
     * Converts a queue ARN to a queue URL
     *
     * @param configuration current AwsMock configuration
     * @param queueArn ARN of the queue
     * @return URL of the queue
     */
    static std::string ConvertSQSQueueArnToUrl(const Configuration &configuration, const std::string &queueArn);

    /**
     * Create SNS subscription ARN
     *
     * <p>Syntax arn:aws:sns:us-west-2:123456789012:MyTopic:6b0e71bd-7e97-4d97-80ce-4a0994e55286</p>
     *
     * @param region AWS region
     * @param accountId AWS account ID
     * @param topicName name of the topic
     */
    static std::string CreateSNSSubscriptionArn(const std::string &region, const std::string &accountId, const std::string &topicName);

    /**
     * Create transfer manager ARN
     *
     * <p>Syntax arn:aws:sns:us-west-2:123456789012:serverId</p>
     *
     * @param region AWS region
     * @param accountId AWS account ID
     * @param serverId ID of the transfer manager
     */
    static std::string CreateTransferArn(const std::string &region, const std::string &accountId, const std::string &serverId);

    /**
     * Returns a request ID.
     *
     * @return request ID
     */
    static std::string CreateRequestId() {
      return Poco::UUIDGenerator().createRandom().toString();
    }

    /**
     * Returns a receipt handle.
     *
     * @return receipt handle
     */
    static std::string CreateSqsReceiptHandler() {
      return StringUtils::GenerateRandomString(SQS_RECEIPT_HANDLE_LENGTH);
    }

    /**
     * Generate a S3 file name
     *
     * @return random file name
     */
    static std::string CreateS3FileName() {
      return StringUtils::GenerateRandomHexString(S3_FILE_NAME_LENGTH);
    }

    /**
     * Generate a S3 version ID
     *
     * @return random version ID
     */
    static std::string CreateS3VersionId() {
      return StringUtils::GenerateRandomVersion(S3_VERSION_ID_LENGTH);
    }

    /**
     * Returns the HTTP endpoint
     *
     * @param configuration current AwsMock configuration
     * @return HTTP endpoint
     */
    static std::string GetEndpoint(const Configuration &configuration) {
      int port = configuration.getInt("awsmock.gateway.port", GATEWAY_DEFAULT_PORT);
      return GATEWAY_DEFAULT_PROTOCOL + "://" + SystemUtils::GetNodeName() + ":" + std::to_string(port);
    }

    /**
     * Returns the HTTP endpoint
     *
     * @param configuration current AwsMock configuration
     * @return HTTP endpoint
     */
    static std::string GetAuthorizationHeader(const Configuration &configuration, const std::string &module);

  };

} // namespace AwsMock::Core

#endif // AWSMOCK_CORE_AWSUTILS_H
