//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWS_MOCK_CORE_AWS_UTILS_H
#define AWS_MOCK_CORE_AWS_UTILS_H

// C++ standard includes
#include <string>
#include <iostream>

// Poco includes
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CryptoUtils.h>

#define S3_FILE_NAME_LENGTH 64
#define S3_VERSION_ID_LENGTH 64

#define SQS_RECEIPT_HANDLE_LENGTH 512
#define SQS_DEFAULT_ACCOUNT_ID "000000000000"

#define GATEWAY_DEFAULT_PORT 4566
#define GATEWAY_DEFAULT_PROTOCOL std::string("http")
#define GATEWAY_DEFAULT_REGION "eu-central-1"

namespace AwsMock::Core {

  /**
   * General AWS utilities.
   *
   * @author jens.vogt@opitz-consulting.com
   */
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
     * <p>
     * @verbatim
     * The queue name has the format 'http://<host>:<port>/<accountId>/<queueName>'
     * @endverbatim
     * </p>
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
     * Create transfer manager ARN
     *
     * <p>Syntax arn:aws:secretsmanager:us-west-2:123456789012:secret:MyDatabaseSecretName-a1b2c3</p>
     *
     * @param region AWS region
     * @param accountId AWS account ID
     * @param secretId ID of the secret (name + 6 hex digits)
     */
    static std::string CreateSecretArn(const std::string &region, const std::string &accountId, const std::string &secretId);

    /**
     * Returns a request ID.
     *
     * @return request ID
     */
    static std::string CreateRequestId();

    /**
     * Returns a message ID.
     *
     * <p>Used for SQS and SNS to generate a message ID, which is basically a UUID.</p>
     *
     * @return message ID
     */
    static std::string CreateMessageId();

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
      int port = configuration.getInt("awsmock.service.gateway.port", GATEWAY_DEFAULT_PORT);
      std::string hostname = configuration.getString("awsmock.service.sqs.hostname", SystemUtils::GetHostName());
      return GATEWAY_DEFAULT_PROTOCOL + "://" + hostname + ":" + std::to_string(port);
    }

    /**
     * Returns the HTTP authorization header
     *
     * @param configuration current AwsMock configuration
     * @param module AwsMock module
     * @return HTTP authorization header
     */
    static std::string GetAuthorizationHeader(const Configuration &configuration, const std::string &module);

  };

} // namespace AwsMock::Core

#endif // AWS_MOCK_CORE_AWS_UTILS_H
