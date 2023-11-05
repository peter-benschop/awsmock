//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETEQUEUERESPONSE_H
#define AWSMOCK_DTO_SQS_DELETEQUEUERESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <utility>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/XML/XMLWriter.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/entity/sqs/Queue.h>

namespace AwsMock::Dto::SQS {

  class DeleteQueueResponse {

    public:

      /**
       * Queue entity
       */
      Database::Entity::SQS::Queue _queue;

      /**
       * Constructor
       */
      explicit DeleteQueueResponse() = default;

      /**
       * Constructor
       *
       * @param queue queue entity.
       */
      explicit DeleteQueueResponse(Database::Entity::SQS::Queue queue);

      /**
       * Convert to XML representation
       *
       * @return XML string
       */
      std::string ToXml();

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
      friend std::ostream &operator<<(std::ostream &os, const DeleteQueueResponse &r);

      /**
       * Static logger
       */
      static Core::LogStream _logger;
  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_DELETEQUEUERESPONSE_H
