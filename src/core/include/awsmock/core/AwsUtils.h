//
// Created by vogje01 on 06/06/2023.
//

#ifndef AWS_MOCK_CORE_AWS_UTILS_H
#define AWS_MOCK_CORE_AWS_UTILS_H

// C++ standard includes
#include <chrono>
#include <iostream>
#include <string>

// Poco includes
#include <Poco/Net/HTTPRequest.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/exception/NotFoundException.h>
#include <awsmock/core/exception/UnauthorizedException.h>

#define S3_FILE_NAME_LENGTH 64
#define S3_VERSION_ID_LENGTH 64

#define SQS_RECEIPT_HANDLE_LENGTH 512
#define SQS_DEFAULT_ACCOUNT_ID "000000000000"

#define GATEWAY_DEFAULT_PORT 4566
#define GATEWAY_DEFAULT_PROTOCOL std::string("http")
#define GATEWAY_DEFAULT_REGION "eu-central-1"

namespace AwsMock::Core {

    struct AuthorizationHeaderKeys {

        /**
         * AWS signing version, i.e: AWS4-HMAC-SHA256
         */
        std::string signingVersion;

        /**
         * Secret access key
         */
        std::string secretAccessKey;

        /**
         * Date time
         */
        std::string dateTime;

        /**
         * Date time
         */
        std::string isoDateTime;

        /**
         * Scope
         */
        std::string scope;

        /**
         * Region
         */
        std::string region;

        /**
         * Module
         */
        std::string module;

        /**
         * Request version
         */
        std::string requestVersion;

        /**
         * Signed headers
         */
        std::string signedHeaders;

        /**
         * Signature
         */
        std::string signature;
    };

    /**
     * @brief General AWS utilities.
     *
     * AWS utilities
     *
     * @author jens.vogt\@opitz-consulting.com
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
         * @endcode
         * </p>
         *
         * @param configuration current AwsMock configuration
         * @param queueName name of the queue
         * @return SQS queue URL
         */
        static std::string CreateSQSQueueUrl(const Configuration &configuration, const std::string &queueName);

        /**
         * Create SQS queue ARN
         *
         * @param configuration current AwsMock configuration
         * @param queueName name of the queue
         * @return SQS queue ARN
         */
        static std::string CreateSQSQueueArn(const Configuration &configuration, const std::string &queueName);

        /**
         * Converts a queue ARN to a queue URL
         *
         * @param configuration current AwsMock configuration
         * @param queueArn ARN of the queue
         * @return URL of the queue
         */
        static std::string ConvertSQSQueueArnToUrl(const Configuration &configuration, const std::string &queueArn);

        /**
         * Create SNS topic ARN
         *
         * @param region AWS region
         * @param accountId AWS account ID
         * @param topicName name of the topic
         */
        static std::string CreateSNSTopicArn(const std::string &region, const std::string &accountId, const std::string &topicName);

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
         * Create secrets manager ARN
         *
         * <p>Syntax arn:aws:secrets manager:us-west-2:123456789012:secret:MyDatabaseSecretName-a1b2c3</p>
         *
         * @param region AWS region
         * @param accountId AWS account ID
         * @param secretId ID of the secret (name + 6 hex digits)
         * @return secrets manager secrets ARN
         */
        static std::string CreateSecretArn(const std::string &region, const std::string &accountId, const std::string &secretId);

        /**
         * Create KMS key ARN
         *
         * <p>Syntax arn:aws:kms:us-west-2:123456789012:name</p>
         *
         * @param region AWS region
         * @param accountId AWS account ID
         * @param kmsId ID of the key
         * @return KMS key ARN
         */
        static std::string CreateKMSKeyArn(const std::string &region, const std::string &accountId, const std::string &kmsId);

        /**
         * Create Cognito user pool ID
         *
         * <p>region_<9-random-digit></p>
         *
         * @param region AWS region
         * @param return ID of the user pool
         */
        static std::string CreateCognitoUserPoolId(const std::string &region);

        /**
         * Create Cognito user pool ARN
         *
         * <p>Syntax arn:aws:cognito:us-west-2:123456789012:userPoolId</p>
         *
         * @param region AWS region
         * @param accountId AWS account ID
         * @param userPoolId ID of the user pool
         * @return user pool ARN
         */
        static std::string CreateCognitoUserPoolArn(const std::string &region, const std::string &accountId, const std::string &userPoolId);

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
         * @brief Add the AWS v4 signed authorization header
         *
         * Adds the AWS authorization header, based on the supplied Poco HTTP request.
         *
         * @param request HTTP request
         * @param module AwsMock module
         * @param contentType HTTP content type
         * @param signedHeaders signed header names
         * @param payload HTTP payload
         */
        static void AddAuthorizationHeader(Poco::Net::HTTPRequest &request, const std::string &module, const std::string &contentType, const std::string &signedHeaders, const std::string &payload);

        /**
         * @brief Add the AWS v4 signed authorization header
         *
         * Adds the AWS authorization header, based on the supplied Curl request HTTP request.
         *
         * @param request HTTP request
         * @param module AwsMock module
         * @param contentType HTTP content type
         * @param signedHeaders signed header names
         * @param payload HTTP payload
         */
        static void AddAuthorizationHeader(const std::string &method, const std::string &path, std::map<std::string, std::string> &headers, const std::string &module, const std::string &contentType, const std::string &signedHeaders, const std::string &payload);

        /**
         * @brief Verify the request signature
         *
         * @param request HTTP request
         * @param payload HTTP payload
         * @param secretAccessKey AWS secret access key
         * @return true if signature could be verified
         */
        static bool VerifySignature(const Poco::Net::HTTPRequest &request, const std::string &payload, const std::string &secretAccessKey);

      private:

        /**
         * @brief Returns the canonical request.
         *
         * @param request HTTP request
         * @param payload HTTP payload
         * @param authorizationHeaderKeys
         * @return
         */
        static std::string GetCanonicalRequest(const Poco::Net::HTTPRequest &request, const std::string &payload, const AuthorizationHeaderKeys &authorizationHeaderKeys);

        /**
         * @brief Returns the canonical request.
         *
         * This is used by the Curl base request.
         *
         * @param method HTTP method
         * @param path HTTP path, including query/path parameter
         * @param headers HTTP headers
         * @param payload HTTP payload
         * @param authorizationHeaderKeys
         * @return
         */
        static std::string GetCanonicalRequest(const std::string &method, const std::string &path, std::map<std::string, std::string> &headers, const std::string &payload, const AuthorizationHeaderKeys &authorizationHeaderKeys);

        /**
         * @brief Creates the string to sign.
         *
         * @param canonicalRequest canonical request
         * @param authorizationHeaderKeys authorization summary
         * @return string to sign
         */
        static std::string GetStringToSign(const std::string &canonicalRequest, const AuthorizationHeaderKeys &authorizationHeaderKeys);

        /**
         * @brief Returns the canonical query parameters
         *
         * This is used by the Curl base request.
         *
         * @param request HTTP request
         * @return canonical request parameters
         */
        static std::string GetCanonicalQueryParameters(const std::string &path);

        /**
         * @brief Returns the canonical query parameters
         *
         * @param request HTTP request
         * @return canonical request parameters
         */
        static std::string GetCanonicalQueryParameters(const Poco::Net::HTTPRequest &request);

        /**
         * @brief Returns the canonical header string.
         *
         * @param request HTTP request
         * @param authorizationHeaderKeys authorization parameter
         * @return canonical header string
         */
        static std::string GetCanonicalHeaders(const Poco::Net::HTTPRequest &request, const AuthorizationHeaderKeys &authorizationHeaderKeys);

        /**
         * @brief Returns the canonical header string.
         *
         * This is used by the Curl base request.
         *
         * @param request HTTP request
         * @param authorizationHeaderKeys authorization parameter
         * @return canonical header string
         */
        static std::string GetCanonicalHeaders(std::map<std::string, std::string> &headers, const AuthorizationHeaderKeys &authorizationHeaderKeys);

        /**
         * @brief Returns the hashed payload.
         *
         * @param payload HTTP payload
         * @return hashed payload
         */
        static std::string GetHashedPayload(const std::string &payload);

        /**
         * @brief Splits the authorization header into pieces and stores the result into a struct.
         *
         * @param request HTTP request
         * @param secretAccessKey AWS secret access key
         * @return AuthorizationHeaderKeys
         */
        static AuthorizationHeaderKeys GetAuthorizationKeys(const Poco::Net::HTTPRequest &request, const std::string &secretAccessKey);

        /**
         * @brief Returns the signature for the request
         *
         * @param authorizationHeaderKeys authorization header
         * @param stringToSign string to sign
         * @return key encoded signature
         */
        static std::string GetSignature(const AuthorizationHeaderKeys &authorizationHeaderKeys, const std::string &stringToSign);

        /**
         * @brief Returns the date string in format yyyyMMdd
         *
         * Return the time in zone UTC
         *
         * @return date string.
         */
        static std::string GetDateString();

        /**
         * @brief Returns the date time string in ISO8601 format
         *
         * Return the time in zone UTC
         *
         * @return date string.
         */
        static std::string GetISODateString();
    };

    /**
     * @brief Returns the HTTP endpoint
     *
     * @param configuration current AwsMock configuration
     * @return HTTP endpoint
     */
    static inline std::string GetEndpoint() {
        int port = Core::Configuration::instance().getInt("awsmock.service.gateway.http.port", GATEWAY_DEFAULT_PORT);
        std::string hostname = Core::Configuration::instance().getString("awsmock.service.sqs.hostname", SystemUtils::GetHostName());
        return GATEWAY_DEFAULT_PROTOCOL + "://" + hostname + ":" + std::to_string(port);
    }

    /**
     * Checks whether this is a queue URL
     *
     * @param queue queue from Spring cloud
     * @return true if this is a URL
     */
    static inline bool IsSQSUrl(const std::string &queue) {
        return Core::StringUtils::StartsWith(queue, "http");
    }

    /**
     * Checks whether this is a queue ARN
     *
     * @param queue queue from Spring cloud
     * @return true if this is a URL
     */
    static inline bool IsSQSArn(const std::string &queue) {
        return Core::StringUtils::ContainsIgnoreCase(queue, "http");
    }

    /**
     * Spring cloud sends the queueName, the queueUrl, or the queueArn.
     *
     * @param queue from Spring cloud request
     * @return queue URL
     */
    static inline std::string SanitizeSQSUrl(const std::string &queue) {
        if (IsSQSUrl(queue)) {
            return queue;
        } else if (IsSQSArn(queue)) {
            return AwsUtils::ConvertSQSQueueArnToUrl(Configuration::instance(), queue);
        } else {
            return AwsUtils::CreateSQSQueueUrl(Configuration::instance(), queue);
        }
    }

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_AWS_UTILS_H
