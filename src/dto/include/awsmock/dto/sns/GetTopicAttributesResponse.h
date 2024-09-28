//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SNS_GET_TOPIC_ATTRIBUTES_RESPONSE_H
#define AWSMOCK_DTO_SNS_GET_TOPIC_ATTRIBUTES_RESPONSE_H

// C++ standard includes
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

// AwsMock includes
#include <awsmock/core/XmlUtils.h>

namespace AwsMock::Dto::SNS {

    struct GetTopicAttributesResponse {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Name
         */
        std::string topicName;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * Owner
         */
        std::string owner;

        /**
         * Display name
         */
        std::string displayName;

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
        friend std::ostream &operator<<(std::ostream &os, const GetTopicAttributesResponse &r);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_GET_TOPIC_ATTRIBUTES_RESPONSE_H
