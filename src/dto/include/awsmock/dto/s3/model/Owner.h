//
// Created by vogje01 on 12/18/23.
//

#ifndef AWSMOCK_DTO_S3_OWNER_H
#define AWSMOCK_DTO_S3_OWNER_H

// C++ includes
#include <sstream>
#include <string>

// AwsMock includes
#include "awsmock/core/JsonException.h"
#include "awsmock/core/JsonUtils.h"
#include "awsmock/core/LogStream.h"
#include "awsmock/core/XmlUtils.h"

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
         * Convert to a XML element
         *
         * @param pDoc XML document
         * @return XML element
         */
        [[nodiscard]] Poco::XML::AutoPtr<Poco::XML::Element> ToXmlElement(Poco::XML::AutoPtr<Poco::XML::Document> pDoc) const;

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
        friend std::ostream &operator<<(std::ostream &os, const Owner &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_OWNER_H
