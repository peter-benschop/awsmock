//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_S3_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_S3_CLIENT_COMMAND_H

// C++ includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/RegularExpression.h>

// AwsMock includes
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/common/BaseClientCommand.h>
#include <awsmock/dto/common/HttpMethod.h>
#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

    enum class S3CommandType {
        CREATE_BUCKET,
        LIST_BUCKETS,
        DELETE_BUCKET,
        LIST_OBJECTS,
        PUT_OBJECT,
        GET_OBJECT,
        COPY_OBJECT,
        MOVE_OBJECT,
        DELETE_OBJECT,
        DELETE_OBJECTS,
        CREATE_MULTIPART_UPLOAD,
        UPLOAD_PART,
        COMPLETE_MULTIPART_UPLOAD,
        ABORT_MULTIPART_UPLOAD,
        LIST_OBJECT_VERSIONS,
        BUCKET_NOTIFICATION,
        PUT_BUCKET_NOTIFICATION_CONFIGURATION,
        PUT_BUCKET_ENCRYPTION,
        UNKNOWN
    };

    static std::map<S3CommandType, std::string> S3CommandTypeNames{
            {S3CommandType::CREATE_BUCKET, "CreateBucket"},
            {S3CommandType::LIST_BUCKETS, "ListBuckets"},
            {S3CommandType::DELETE_BUCKET, "DeleteBucket"},
            {S3CommandType::LIST_OBJECTS, "ListObjects"},
            {S3CommandType::PUT_OBJECT, "PutObject"},
            {S3CommandType::GET_OBJECT, "GetObject"},
            {S3CommandType::COPY_OBJECT, "CopyObject"},
            {S3CommandType::MOVE_OBJECT, "MoveObject"},
            {S3CommandType::DELETE_OBJECT, "DeleteObject"},
            {S3CommandType::DELETE_OBJECTS, "DeleteObjects"},
            {S3CommandType::CREATE_MULTIPART_UPLOAD, "CreateMultipartUpload"},
            {S3CommandType::UPLOAD_PART, "PartMultipartUpload"},
            {S3CommandType::COMPLETE_MULTIPART_UPLOAD, "CompleteMultipartUpload"},
            {S3CommandType::ABORT_MULTIPART_UPLOAD, "AbortMultipartUpload"},
            {S3CommandType::LIST_OBJECT_VERSIONS, "ListObjectVersions"},
            {S3CommandType::BUCKET_NOTIFICATION, "BucketNotification"},
            {S3CommandType::PUT_BUCKET_NOTIFICATION_CONFIGURATION, "PUT_BUCKET_NOTIFICATION_CONFIGURATION"},
            {S3CommandType::PUT_BUCKET_ENCRYPTION, "PUT_BUCKET_ENCRYPTION"},
    };

    [[maybe_unused]] static std::string S3CommandTypeToString(S3CommandType commandType) {
        return S3CommandTypeNames[commandType];
    }

    [[maybe_unused]] static S3CommandType S3CommandTypeFromString(const std::string &commandType) {
        for (auto &it: S3CommandTypeNames) {
            if (Core::StringUtils::StartsWith(commandType, it.second)) {
                return it.first;
            }
        }
        return S3CommandType::UNKNOWN;
    }

    /**
     * @brief S3 client command
     *
     * The S3 client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a
     * different way of calling the AWS REST services.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct S3ClientCommand : public BaseClientCommand {

        /**
         * Client command
         */
        S3CommandType command;

        /**
         * Bucket
         */
        std::string bucket;

        /**
         * Key
         */
        std::string key;

        /**
         * Key
         */
        std::string prefix;

        /**
         * Versioning
         */
        bool versionRequest;

        /**
         * Notification
         */
        bool notificationRequest;

        /**
         * Multipart upload/download
         */
        bool multipartRequest;

        /**
         * Multipart uploads
         */
        bool uploads;

        /**
         * Multipart part number
         */
        bool partNumber;

        /**
         * Multipart upload/download
         */
        bool copyRequest;

        /**
         * SSE encryption
         */
        bool encryptionRequest;

        /**
         * Multipart upload ID
         */
        std::string uploadId;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Gets command type from the user agent
         *
         * @param httpMethod HTTP request method
         * @param userAgent HTTP user agent
         */
        void GetCommandFromUserAgent(const HttpMethod &httpMethod, const UserAgent &userAgent);

        /**
         * Getś the value from the user-agent string
         *
         * @param method HTTP method
         * @param request HTTP server request
         * @param region AWS region
         * @param user AWS user
         */
        void FromRequest(const HttpMethod &method, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const S3ClientCommand &i);
    };

}// namespace AwsMock::Dto::Common

#endif// AWSMOCK_DTO_COMMON_S3_CLIENT_COMMAND_H
