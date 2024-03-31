//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_SQS_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_SQS_CLIENT_COMMAND_H

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
#include <awsmock/dto/common/HttpMethod.h>
#include <awsmock/dto/common/UserAgent.h>

namespace AwsMock::Dto::Common {

  enum class SqsCommandType {
    CREATE_QUEUE,
    PURGE_QUEUE,
    GET_QUEUE_ATTRIBUTES,
    LIST_QUEUES,
    DELETE_QUEUE,
    UNKNOWN
  };

  static std::map<SqsCommandType, std::string> SqsCommandTypeNames {
    {SqsCommandType::CREATE_QUEUE, "CreateQueue"},
    {SqsCommandType::PURGE_QUEUE, "PurgeQueue"},
    {SqsCommandType::GET_QUEUE_ATTRIBUTES, "GetQueueAttributes"},
    {SqsCommandType::LIST_QUEUES, "ListQueues"},
    {SqsCommandType::DELETE_QUEUE, "DeleteQueue"},
  };

  [[maybe_unused]]static std::string SqsCommandTypeToString(SqsCommandType commandType) {
    return SqsCommandTypeNames[commandType];
  }

  [[maybe_unused]]static SqsCommandType SqsCommandTypeFromString(const std::string &commandType) {
    for (auto &it : SqsCommandTypeNames) {
      if (Core::StringUtils::StartsWith(commandType, it.second)) {
        return it.first;
      }
    }
    return SqsCommandType::UNKNOWN;
  }

  /**
   * The S3 client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a different way of calling the AWS REST services.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct SQSClientCommand {

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
    SqsCommandType command;

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
    friend std::ostream &operator<<(std::ostream &os, const SQSClientCommand &i);

  };

} // namespace AwsMock::Dto::Common

#endif // AWSMOCK_DTO_COMMON_SQS_CLIENT_COMMAND_H
