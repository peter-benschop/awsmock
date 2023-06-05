//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_RECEIVEMESSAGEREQUEST_H
#define AWSMOCK_DTO_SQS_RECEIVEMESSAGEREQUEST_H

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

// AwsMock includes
#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Dto::SQS {

    struct ReceiveMessageRequest {

      /**
       * AWS region
       */
      std::string region;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Maximal number of messages
       */
      int maxMessages = 10;

      /**
       * Visibility
       */
      int visibility = 15;

      /**
       * Wait time in seconds
       */
      int waitTimeSeconds = 1;

      /**
       * MessageAttribute names
       */
      std::vector<std::string> AttributeName = {"All"};

      /**
       * Resource
       */
      std::string resource = "SQS";

      /**
       * Resource
       */
      std::string requestId = Poco::UUIDGenerator().createRandom().toString();

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const ReceiveMessageRequest &r) {
          os << "ReceiveMessageRequest={region='" + r.region + "' queueUrl='" + r.queueUrl + "' maxMessages='" + std::to_string(r.maxMessages) +
              "' visibility='" + std::to_string(r.visibility) + "' waitTimeSeconds='" + std::to_string(r.waitTimeSeconds) + "' resource='" + r.resource +
              "' requestId: '" + r.requestId + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_RECEIVEMESSAGERESPONSE_H
