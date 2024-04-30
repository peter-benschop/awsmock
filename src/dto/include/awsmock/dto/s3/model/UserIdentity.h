//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_DTO_S3_USER_IDENTITY_H
#define AWSMOCK_DTO_S3_USER_IDENTITY_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include "awsmock/core/JsonException.h"
#include "awsmock/core/JsonUtils.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/core/XmlUtils.h"

namespace AwsMock::Dto::S3 {

    struct UserIdentity {

        /**
         * AWS principal ID
         */
        std::string principalId;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const UserIdentity &r);
    };
}// namespace AwsMock::Dto::S3
#endif// AWSMOCK_DTO_S3_USER_IDENTITY_H
