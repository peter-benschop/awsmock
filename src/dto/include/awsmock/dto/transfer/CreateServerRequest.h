//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_TRANSFER_CREATE_TRANSFER_REQUEST_H
#define AWSMOCK_DTO_TRANSFER_CREATE_TRANSFER_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/dto/transfer/IdentityProviderDetails.h>
#include <awsmock/dto/transfer/Tag.h>

namespace AwsMock::Dto::Transfer {

    struct CreateServerRequest {

        /**
         * Region
         */
        std::string region;

        /**
         * Domain
         */
        std::string domain;

        /**
         * Protocols
         */
        std::vector<std::string> protocols;

        /**
         * Tags
         */
        TagList tags;

        /**
         * Identity provider details
         */
        IdentityProviderDetails identityProviderDetails;

        /**
         * Parse a JSON stream
         *
         * @param body json input stream
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
        friend std::ostream &operator<<(std::ostream &os, const CreateServerRequest &r);
    };

}// namespace AwsMock::Dto::Transfer

#endif// AWSMOCK_DTO_TRANSFER_CREATE_TRANSFER_REQUEST_H
