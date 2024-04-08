//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_CREATE_SECRET_REQUEST_H
#define AWSMOCK_DTO_SECRETSMANAGER_CREATE_SECRET_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <map>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/sqs/QueueAttribute.h>
#include <awsmock/dto/sqs/SqsCommonRequest.h>

namespace AwsMock::Dto::SecretsManager {

  /**
   * Example:
   *
   * <pre>
   * {
   *   "Name": "test",
   *   "ClientRequestToken": "8b0e8777-4c9a-4621-9bd7-a6449b24c3a5"
   * }
   * </pre>
   */
  struct CreateSecretRequest {

    /**
     * AWS region
     */
    std::string region;

    /**
     * Secret name
     */
    std::string name;

    /**
     * Client request token
     */
    std::string clientRequestToken;

    /**
     * Description
     */
    std::string description;

    /**
     * Tags
     */
    std::map<std::string, std::string> tags;

    /**
     * AWS request ID
     */
    std::string requestId;

    /**
     * Converts the JSON string to DTO.
     *
     * @param jsonString JSON string
     */
    void FromJson(const std::string &jsonString);

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
    friend std::ostream &operator<<(std::ostream &os, const CreateSecretRequest &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SECRETSMANAGER_CREATE_SECRET_REQUEST_H
