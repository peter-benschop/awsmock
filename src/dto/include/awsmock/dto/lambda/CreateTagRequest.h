//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_CREATETAREQUEST_H
#define AWSMOCK_DTO_LAMBDA_CREATETAREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <utility>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/dto/lambda/Environment.h>
#include <awsmock/dto/lambda/EphemeralStorage.h>

namespace AwsMock::Dto::Lambda {

  struct CreateTagRequest {

    /**
     * ARN
     */
    std::string arn;

    /**
     * Tags
     */
    std::map<std::string, std::string> tags;

    /**
     * Convert from a JSON object.
     *
     * @param jsonObject json object
     */
    void FromJson(const std::string &body);

    /**
     * Creates a JSON string from the object.
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const;

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
    friend std::ostream &operator<<(std::ostream &os, const CreateTagRequest &r);

  };

} // namespace AwsMock::Dto::lambda

#endif // AWSMOCK_DTO_LAMBDA_CREATETAREQUEST_H
