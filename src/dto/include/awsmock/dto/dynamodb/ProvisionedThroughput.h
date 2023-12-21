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
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson();

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

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_DYNAMODB_PROVISIONED_THROUGHPUT_H
