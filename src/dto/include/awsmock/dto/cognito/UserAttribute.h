//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_COGNITO_USER_ATTRIBUTE_H
#define AWSMOCK_DTO_COGNITO_USER_ATTRIBUTE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::Cognito {

  struct UserAttribute {

    /**
     * User attribute name
     */
    std::string name;

    /**
     * MessageAttribute value
     */
    std::string value;

    /**
     * Converts the JSON string to a DTO
     *
     * @param jsonObject JSON object
     */
    void FromJson(const Poco::JSON::Object::Ptr &jsonObject);

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
    friend std::ostream &operator<<(std::ostream &os, const UserAttribute &r);

  };

  typedef std::vector<UserAttribute> UserAttributeList;

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_COGNITO_USER_ATTRIBUTE_H
