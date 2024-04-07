//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_DYNAMODB_LIST_TABLE_RESPONSE_H
#define AWSMOCK_DTO_DYNAMODB_LIST_TABLE_RESPONSE_H

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
#include <awsmock/dto/dynamodb/ProvisionedThroughput.h>

namespace AwsMock::Dto::DynamoDb {

  struct ListTableResponse {

    /**
     * Region
     */
    std::string region;

    /**
     * Table names
     */
    std::vector<std::string> tableNames;

    /**
     * Last evaluated table name
     */
    std::string lastEvaluatedTableName;

    /**
     * HTTP response body
     */
    std::string body;

    /**
     * HTTP headers
     */
    std::map<std::string, std::string> headers;

    /**
     * HTTP status from docker image
     */
    Poco::Net::HTTPResponse::HTTPStatus status;

    /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson();

    /**
     * Parse a JSON stream
     *
     * @param body JSON body
     * @param headers HTTP headers
     */
    void FromJson(const std::string &body, const std::map<std::string, std::string> &headers);

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
    friend std::ostream &operator<<(std::ostream &os, const ListTableResponse &r);

  };

} // namespace AwsMock::Dto::DynamoDb

#endif // AWSMOCK_DTO_DYNAMODB_LIST_TABLE_RESPONSE_H
