//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H
#define AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

// AwsMock includes
#include <awsmock/dto/common/Common.h>

namespace AwsMock::Dto::SQS {

    struct PurgeQueueRequest {

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * AWS region
       */
      std::string region;

      /**
       * Resource
       */
      std::string resource = "Unknown resource";

      /**
       * Resource
       */
      std::string requestId = Poco::UUIDGenerator().createRandom().toString();

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
      friend std::ostream &operator<<(std::ostream &os, const PurgeQueueRequest &r);

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H
