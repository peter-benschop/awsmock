//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_S3_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_S3_CLIENT_COMMAND_H

// C++ includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/RegularExpression.h>
#include <Poco/Net/HTTPServerRequest.h>

// AwsMock includes
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include "awsmock/dto/common/UserAgent.h"

namespace AwsMock::Dto::Common {

  enum class HttpMethod {
    GET,
    PUT,
    POST,
    DELETE,
    UNKNOWN
  };

  static std::map<HttpMethod, std::string> HttpMethodNames {
    {HttpMethod::GET, "GET"},
    {HttpMethod::PUT, "PUT"},
    {HttpMethod::POST, "POST"},
    {HttpMethod::DELETE, "DELETE"},
  };

  [[maybe_unused]]static std::string HttpMethodToString(HttpMethod requestType) {
    return HttpMethodNames[requestType];
  }

  [[maybe_unused]]static HttpMethod HttpMethodFromString(const std::string &requestType) {
    for (auto &it : HttpMethodNames) {
      if (Core::StringUtils::StartsWith(requestType, it.second)) {
        return it.first;
      }
    }
    return HttpMethod::UNKNOWN;
  }

  enum class CommandType {
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
    UNKNOWN
  };

  static std::map<CommandType, std::string> CommandTypeNames {
    {CommandType::CREATE_BUCKET, "CreateBucket"},
    {CommandType::LIST_BUCKETS, "ListBuckets"},
    {CommandType::DELETE_BUCKET, "DeleteBucket"},
    {CommandType::LIST_OBJECTS, "ListObjects"},
    {CommandType::PUT_OBJECT, "PutObject"},
    {CommandType::GET_OBJECT, "GetObject"},
    {CommandType::COPY_OBJECT, "CopyObject"},
    {CommandType::MOVE_OBJECT, "MoveObject"},
    {CommandType::DELETE_OBJECT, "DeleteObject"},
    {CommandType::DELETE_OBJECTS, "DeleteObjects"},
    {CommandType::CREATE_MULTIPART_UPLOAD, "CreateMultipartUpload"},
    {CommandType::UPLOAD_PART, "PartMultipartUpload"},
    {CommandType::COMPLETE_MULTIPART_UPLOAD, "CompleteMultipartUpload"},
  };

  [[maybe_unused]]static std::string CommandTypeToString(CommandType commandType) {
    return CommandTypeNames[commandType];
  }

  [[maybe_unused]]static CommandType CommandTypeFromString(const std::string &commandType) {
    for (auto &it : CommandTypeNames) {
      if (Core::StringUtils::StartsWith(commandType, it.second)) {
        return it.first;
      }
    }
    return CommandType::UNKNOWN;
  }

  /**
   * The S3 client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a different way of calling the AWS REST services.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct S3ClientCommand {

    /**
     * HTTP request type
     */
    HttpMethod method;

    /**
     * Client region
     */
    std::string region;

    /**
     * Client user
     */
    std::string user;

    /**
     * Client command
     */
    CommandType command;

    /**
     * Bucket
     */
    std::string bucket;

    /**
     * Key
     */
    std::string key;

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
     * Multipart upload/download
     */
    bool copyRequest;

    /**
     * Multipart upload ID
     */
    std::string uploadId;

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
     * @param request HTTP server request
     * @param region AWS region
     * @param user AWS user
     */
    void FromRequest(const HttpMethod &requestType, Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user);

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

}
#endif // AWSMOCK_DTO_COMMON_S3_CLIENT_COMMAND_H
