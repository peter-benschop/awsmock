//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_CORE_DTO_DESCRIBE_SECRET_REQUEST_H
#define AWSMOCK_CORE_DTO_DESCRIBE_SECRET_REQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMoc includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SecretsManager {

  struct DescribeSecretRequest {

    /**
     * Region
     */
    std::string region;

    /**
     * Secret name
     */
    std::string name;

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
    friend std::ostream &operator<<(std::ostream &os, const DescribeSecretRequest &r);

  };

} // namespace AwsMock::Dto::S3

#endif // AWSMOCK_CORE_DTO_DESCRIBE_SECRET_REQUEST_H
