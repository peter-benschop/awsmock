//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_PUBLISH_RESPONSE_H
#define AWSMOCK_DTO_SNS_PUBLISH_RESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>
#include <utility>

// Poco includes
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/RandomUtils.h>
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Dto::SNS {

    struct PublishResponse {

        /**
         * Message ID
         */
        std::string messageId;

        /**
         * Request ID
         */
        std::string requestId = Poco::UUIDGenerator().createRandom().toString();

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
        friend std::ostream &operator<<(std::ostream &os, const PublishResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_PUBLISH_RESPONSE_H
