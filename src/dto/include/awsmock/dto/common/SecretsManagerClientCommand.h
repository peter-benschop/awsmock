//
// Created by vogje01 on 07/04/2024.
//

#ifndef AWSMOCK_DTO_COMMON_SECRETSMANAGER_CLIENT_COMMAND_H
#define AWSMOCK_DTO_COMMON_SECRETSMANAGER_CLIENT_COMMAND_H

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

  enum class SecretsManagerCommandType {
    CREATE_SECRET,
    DELETE_SECRET,
    UNKNOWN
  };

  static std::map<SecretsManagerCommandType, std::string> SecretsManagerCommandTypeNames {
    {SecretsManagerCommandType::CREATE_SECRET, "CreateSecret"},
    {SecretsManagerCommandType::DELETE_SECRET, "DeleteSecret"},
    {SecretsManagerCommandType::UNKNOWN, "Unknown"},
  };

  [[maybe_unused]]static std::string SecretsManagerCommandTypeToString(SecretsManagerCommandType commandType) {
    return SecretsManagerCommandTypeNames[commandType];
  }

  [[maybe_unused]]static SecretsManagerCommandType SecretsManagerCommandTypeFromString(const std::string &commandType) {
    for (auto &it : SecretsManagerCommandTypeNames) {
      if (Core::StringUtils::StartsWith(commandType, it.second)) {
        return it.first;
      }
    }
    return SecretsManagerCommandType::UNKNOWN;
  }

  /**
   * The SecretsManager client command is used as a standardized way of interpreting the different ways the clients are calling the REST services. Each client type is using a different way of calling the AWS REST services.
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct SecretsManagerClientCommand {

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
    SecretsManagerCommandType command;

    /**
     * HTTP body
     */
    std::string payload;

    /**
     * Returns the message body as string.
     *
     * @param request HTTP request
     * @return message body as string
     */
    std::string GetBodyAsString(Poco::Net::HTTPServerRequest &request);

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
    friend std::ostream &operator<<(std::ostream &os, const SecretsManagerClientCommand &i);

  };

} // namespace AwsMock::Dto::Common

#endif // AWSMOCK_DTO_COMMON_SECRETSMANAGER_CLIENT_COMMAND_H
