//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_PUTQUEUEATTRIBUTESRESPONSE_H
#define AWSMOCK_DTO_SQS_PUTQUEUEATTRIBUTESRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::SQS {

    struct SetQueueAttributesResponse {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Resource
       */
      std::string resource = "SQS";

      /**
       * Resource
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
      friend std::ostream &operator<<(std::ostream &os, const SetQueueAttributesResponse &r);

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_PUTQUEUEATTRIBUTESRESPONSE_H
