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
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/HttpUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/dto/common/HttpMethod.h>
#include <awsmock/dto/common/UserAgent.h>


namespace AwsMock::Dto::Common {

  enum class SqsCommandType {
    CREATE_QUEUE,
    PURGE_QUEUE,
    GET_QUEUE_ATTRIBUTES,
    SET_QUEUE_ATTRIBUTES,
    GET_QUEUE_URL,
    TAG_QUEUE,
    LIST_QUEUES,
    DELETE_QUEUE,
    SEND_MESSAGE,
    RECEIVE_MESSAGE,
    CHANGE_MESSAGE_VISIBILITY,
    DELETE_MESSAGE,
    DELETE_MESSAGE_BATCH,
    UNKNOWN
  };

  static std::map<SqsCommandType, std::string> SqsCommandTypeNames{
    {SqsCommandType::CREATE_QUEUE, "create-queue"},
    {SqsCommandType::PURGE_QUEUE, "purge-queue"},
    {SqsCommandType::GET_QUEUE_ATTRIBUTES, "get-queue-attributes"},
    {SqsCommandType::SET_QUEUE_ATTRIBUTES, "set-queue-attributes"},
    {SqsCommandType::GET_QUEUE_URL, "get-queue-url"},
    {SqsCommandType::TAG_QUEUE, "tag-queue"},
    {SqsCommandType::LIST_QUEUES, "list-queues"},
    {SqsCommandType::DELETE_QUEUE, "delete-queue"},
    {SqsCommandType::SEND_MESSAGE, "send-message"},
    {SqsCommandType::RECEIVE_MESSAGE, "receive-message"},
    {SqsCommandType::CHANGE_MESSAGE_VISIBILITY, "change-message-visibility"},
    {SqsCommandType::DELETE_MESSAGE, "delete-message"},
    {SqsCommandType::DELETE_MESSAGE_BATCH, "delete-message-batch"},
  };

  [[maybe_unused]]static std::string SqsCommandTypeToString(SqsCommandType commandType) {
    return SqsCommandTypeNames[commandType];
  }

  [[maybe_unused]]static SqsCommandType SqsCommandTypeFromString(const std::string &commandType) {
    for (auto &it : SqsCommandTypeNames) {
      if (Core::StringUtils::EqualsIgnoreCase(commandType, it.second)) {
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
     * Content type
     */
    std::string contentType;

    /**
     * Message body
     */
    std::string payload;

    /**
     * Returns the message body as string.
     *
     * @param request HTTP request
     * @return message body as string
     */
    static std::string GetBodyAsString(Poco::Net::HTTPServerRequest &request);

    /**
     * Returns the command from HTTP header
     *
     * @param request HTTP request
     * @return command string
     */
    std::string GetCommandFromHeader(Poco::Net::HTTPServerRequest &request) const;

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
     * Convert to a JSON string
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const;

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
