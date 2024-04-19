//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_DELETE_OBJECTS_RESPONSE_H
#define AWSMOCK_DTO_S3_DELETE_OBJECTS_RESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Dto::S3 {

  struct DeleteObjectsResponse {

    /**
     * Keys
     */
    std::vector<std::string> keys;

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const;

    /**
     * Convert to XML representation
     *
     * @return XML string
     */
    [[nodiscard]] std::string ToXml() const;

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
    friend std::ostream &operator<<(std::ostream &os, const DeleteObjectsResponse &r);

  };

} // namespace AwsMock::Dto

#endif // AWSMOCK_DTO_S3_DELETE_OBJECTS_RESPONSE_H
