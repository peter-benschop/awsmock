//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_S3_DELETEOBJECTSRESPONSE_H
#define AWSMOCK_DTO_S3_DELETEOBJECTSRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/NodeList.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::S3 {

  struct DeleteObjectsResponse {

    /**
     * Keys
     */
    std::vector<std::string> keys;

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

#endif // AWSMOCK_DTO_S3_DELETEOBJECTSRESPONSE_H
