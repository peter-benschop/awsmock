//
// Created by vogje01 on 12/21/23.
//

#ifndef AWSMOCK_DTO_DYNAMODB_ATTRIBUTEVALUE_H
#define AWSMOCK_DTO_DYNAMODB_ATTRIBUTEVALUE_H

// C++ includes
#include <string>
#include <map>

// Poco includes
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>

// AwsMock include
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::DynamoDb {

  struct AttributeValue {

    /**
     * Type
     */
    std::string type;

    /**
     * Value
     */
    std::string value;

    /**
     * String value
     */
    std::string stringValue;

    /**
     * String set value
     */
    std::vector<std::string> stringSetValue;

    /**
     * Number value
     */
    std::string numberValue;

    /**
     * Number set value
     */
    std::vector<std::string> numberSetValue;

    /**
     * Boolean value
     */
    bool boolValue;

    /**
     * Null value
     */
    bool nullValue;

    /**
     * Convert to JSON value
     *
     * @return JSON object
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

    /**
     * Convert from JSON object.
     *
     * @param jsonObject JSON object
     */
    void FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject);

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
    friend std::ostream &operator<<(std::ostream &os, const AttributeValue &r);

  };
} // namespace AwsMock::Dto::DynampDb

#endif // AWSMOCK_DTO_DYNAMODB_ATTRIBUTEVALUE_H
