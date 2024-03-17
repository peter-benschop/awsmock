//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_PROVISIONED_THROUGHPUT_H
#define AWSMOCK_DTO_DYNAMODB_PROVISIONED_THROUGHPUT_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::DynamoDb {

  struct ProvisionedThroughput {

    /**
     * Read capacity units
     */
    int readCapacityUnits;

    /**
     * Write capacity units
     */
    int writeCapacityUnits;

    /**
     * Last decrease time
     */
    long lastDecreaseDateTime;

    /**
     * Last increase time
     */
    long lastIncreaseDateTime;

    /**
     * NUmber of decreases
     */
    long numberOfDecreasesToday;

    /**
     * Converts the entity to a JSON object
     *
     * @return JSON object
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

    /**
     * Parse a JSON stream
     *
     * @param jsonBody JSON string
     */
    void FromJson(const std::string &jsonBody);

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
    friend std::ostream &operator<<(std::ostream &os, const ProvisionedThroughput &r);

  };

} // namespace AwsMock::Dto::DynamoDb

#endif // AWSMOCK_DTO_DYNAMODB_PROVISIONED_THROUGHPUT_H
