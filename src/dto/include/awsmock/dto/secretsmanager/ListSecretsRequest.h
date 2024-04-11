//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SECRETSMANAGER_LIST_SECRETS_REQUEST_H
#define AWSMOCK_DTO_SECRETSMANAGER_LIST_SECRETS_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include <awsmock/core/JsonUtils.h>
#include "awsmock/core/JsonException.h"
#include "awsmock/dto/secretsmanager/Filter.h"

namespace AwsMock::Dto::SecretsManager {

  /**
   * List secrets request.
   *
   * Example:
   * <pre>
   * {
   *   "Filters": [
   *      {
   *         "Key": "string",
   *         "Values": [ "string" ]
   *      }
   *   ],
   *   "IncludePlannedDeletion": boolean,
   *   "MaxResults": number,
   *   "NextToken": "string",
   *   "SortOrder": "string"
   * }
   */
  struct ListSecretsRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Next token
     */
    std::string nextToken;

    /**
     * Sort order
     */
    std::string sortOrder;

    /**
     * Maximal number of results
     */
    int maxResults;

    /**
     * Include deletion flag
     */
    bool includePlannedDeletion = false;

    /**
     * Selection filters
     */
    std::vector<Filter> filters;

    /**
     * AWS request ID
     */
    std::string requestId;

    /**
     * Converts the DTO to a JSON representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToJson() const;

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
    friend std::ostream &operator<<(std::ostream &os, const ListSecretsRequest &r);

  };

} // namespace AwsMock::Dto::SecretsManager

#endif // AWSMOCK_DTO_SECRETSMANAGER_LIST_SECRETS_REQUEST_H
