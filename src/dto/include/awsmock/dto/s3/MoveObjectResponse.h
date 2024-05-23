//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_MOVEOBJECTSRESPONSE_H
#define AWSMOCK_DTO_S3_MOVEOBJECTSRESPONSE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/NodeList.h>
#include <Poco/DOM/Text.h>
#include <Poco/XML/XMLWriter.h>

namespace AwsMock::Dto::S3 {

    struct MoveObjectResponse {

        /**
         * Etag
         */
        std::string eTag;

        /**
         * Last modified
         */
        std::string lastModified;

        /**
         * Convert to XML representation
         *
         * @return XML string
         */
        std::string ToXml() const;

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
        friend std::ostream &operator<<(std::ostream &os, const MoveObjectResponse &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_MOVEOBJECTSRESPONSE_H
