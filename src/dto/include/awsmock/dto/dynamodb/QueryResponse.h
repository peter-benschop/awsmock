//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_QUERY_RESPONSE_H
#define AWSMOCK_DTO_DYNAMODB_QUERY_RESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>
#include <utility>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/dynamodb/TableStatus.h>

namespace AwsMock::Dto::DynamoDb {

  /**
   * Example:
   * <pre>
   * {
   *   "ConsumedCapacity":
   *     {
   *       "TableName":"test-table",
   *       "CapacityUnits":1.0
   *     }
   * }
   * </pre>
   */
  struct QueryResponse {

    /**
     * Region
     */
    std::string region;

    /**
     * Table name
     */
    std::string tableName;

    /**
     * Original HTTP response body
     */
    std::string body;

    /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson();

    /**
     * Parse a JSON stream
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
    friend std::ostream &operator<<(std::ostream &os, const QueryResponse &r);

  };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_DYNAMODB_QUERY_RESPONSE_H
