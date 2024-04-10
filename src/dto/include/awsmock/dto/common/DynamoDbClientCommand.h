//
// Created by vogje01 on 11/26/23.
//

#ifndef AWSMOCK_DTO_COMMON_DYNAMODB_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_DYNAMODB_CLIENT_COMMAND_H

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
#include "awsmock/dto/common/UserAgent.h"

namespace AwsMock::Dto::Common {

  enum class DynamoDbCommandType {
    CREATE_TABLE,
    LIST_TABLES,
    DESCRIBE_TABLE,
    DELETE_TABLE,
    GET_ITEM,
    PUT_ITEM,
    QUERY,
    SCAN,
    UNKNOWN
  };

  static std::map<DynamoDbCommandType, std::string> DynamoDbCommandTypeNames {
    {DynamoDbCommandType::CREATE_TABLE, "CreateTable"},
    {DynamoDbCommandType::LIST_TABLES, "ListTables"},
    {DynamoDbCommandType::DESCRIBE_TABLE, "DescribeTable"},
    {DynamoDbCommandType::DELETE_TABLE, "DeleteTable"},
    {DynamoDbCommandType::GET_ITEM, "GetItem"},
    {DynamoDbCommandType::PUT_ITEM, "PutItem"},
    {DynamoDbCommandType::QUERY, "Query"},
    {DynamoDbCommandType::SCAN, "Scan"},
    {DynamoDbCommandType::UNKNOWN, "Unknown"},
  };

  [[maybe_unused]]static std::string DynamoDbCommandTypeToString(DynamoDbCommandType commandType) {
    return DynamoDbCommandTypeNames[commandType];
  }

  [[maybe_unused]]static DynamoDbCommandType DynamoDbCommandTypeFromString(const std::string &commandType) {
    for (auto &it : DynamoDbCommandTypeNames) {
      if (Core::StringUtils::StartsWith(commandType, it.second)) {
        return it.first;
      }
    }
    return DynamoDbCommandType::UNKNOWN;
  }

  /**
   * The DynamoDB client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a different way of calling the AWS REST services.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct DynamoDbClientCommand {

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
    DynamoDbCommandType command;

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
    friend std::ostream &operator<<(std::ostream &os, const DynamoDbClientCommand &i);

  };

} // namespace AwsMock::Dto::Common

#endif // AWSMOCK_DTO_COMMON_DYNAMODB_CLIENT_COMMAND_H
