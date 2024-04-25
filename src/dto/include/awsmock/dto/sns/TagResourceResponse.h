//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_TAG_RESOURCE_RESPONSE_H
#define AWSMOCK_DTO_SNS_TAG_RESOURCE_RESPONSE_H

// C++ standard includes
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/XML/XMLWriter.h>

namespace AwsMock::Dto::SNS {

    struct TagResourceResponse {

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
        friend std::ostream &operator<<(std::ostream &os, const TagResourceResponse &r);
    };

    typedef std::map<std::string, std::string> TagList;

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_TAG_RESOURCE_RESPONSE_H
