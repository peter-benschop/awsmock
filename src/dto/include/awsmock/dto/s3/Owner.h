//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_S3_OWNER_H
#define AWSMOCK_DTO_S3_OWNER_H

// C++ includes
#include <string>
#include <sstream>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Dto::S3 {

  struct Owner {

    /**
     * ID
     */
    std::string id;

    /**
     * Display name
     */
    std::string displayName;

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson() const;

    /**
     * Convert to a JSON object
     *
     * @return JSON object
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    std::string ToString() const;

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Owner &r);

  };

} // namespace AwsMock::Dto::S3
#endif // AWSMOCK_DTO_S3_OWNER_H
