//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTESRESPONSE_H
#define AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTESRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include <Poco/JSON/Object.h>
#include "Poco/XML/XMLWriter.h"

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SQS {

  struct GetQueueAttributesResponse {

    /**
     * Attributes
     */
    std::vector<std::pair<std::string, std::string>> attributes;

    /**
     * Resource
     */
    std::string resource = "SQS";

    /**
     * Resource
     */
    std::string requestId = Poco::UUIDGenerator().createRandom().toString();

    /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
    std::string ToJson() const;

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
    friend std::ostream &operator<<(std::ostream &os, const GetQueueAttributesResponse &r);

    /**
     * Static logger
     */
    static Core::LogStream _logger;
  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTESRESPONSE_H
