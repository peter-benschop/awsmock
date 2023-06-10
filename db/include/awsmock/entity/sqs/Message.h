//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
#define AWSMOCK_DB_ENTITY_SQS_MESSAGE_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>
#include <Poco/MongoDB/Document.h>

// AwsMock includes
#include "MessageAttribute.h"

namespace AwsMock::Database::Entity::SQS {

    enum STATUS { INITIAL, SEND, RESEND };

    struct Message {

      /**
       * ID
       */
      long id = 0;

      /**
       * Aws region name
       */
      std::string region;

      /**
       * Queue URL
       */
      std::string queueUrl;

      /**
       * Message body
       */
      std::string body;

      /**
       * Status
       */
      int status = INITIAL;

      /**
       * Last send datetime
       */
      Poco::DateTime lastSend;

      /**
       * Send retries
       */
      int retries = 0;

      /**
       * Message ID
       */
      std::string messageId;

      /**
       * Receipt handle
       */
      std::string receiptHandle;

      /**
       * MD5 sum body
       */
      std::string md5Body;

      /**
       * MD5 sum sqs
       */
      std::string md5Attr;

      /**
       * List of sqs
       */
      MessageAttributeList attributeList;

      /**
       * Creation date
       */
      Poco::DateTime created;

      /**
       * Last modification date
       */
      Poco::DateTime modified;

      /**
       * Converts the DTO to a MongoDB document
       *
       * @return DTO as MongoDB document.
       */
      [[nodiscard]] Poco::MongoDB::Document::Ptr ToDocument() const {
          Poco::MongoDB::Document::Ptr messageDoc = new Poco::MongoDB::Document();
          messageDoc->add("region", region);
          messageDoc->add("queueUrl", queueUrl);
          messageDoc->add("body", body);
          messageDoc->add("status", status);
          messageDoc->add("retries", retries);
          messageDoc->add("messageId", messageId);
          messageDoc->add("receiptHandle", receiptHandle);
          messageDoc->add("md5Body", md5Body);
          messageDoc->add("md5Attr", md5Attr);
          for (const auto &it : attributeList) {
              messageDoc->add("attributeList", it.ToDocument());
          }
          messageDoc->add("lastSend", lastSend.timestamp());
          messageDoc->add("created", created.timestamp());
          messageDoc->add("modified", modified.timestamp());
          return messageDoc;
      };

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
      friend std::ostream &operator<<(std::ostream &os, const Message &m) {
          os << "Message={id='" + std::to_string(m.id) + "' queueUrl='" + m.queueUrl + "'body='" + m.body + "' status='" + std::to_string(m.status) + "' lastSend='" +
              Poco::DateTimeFormatter().format(m.lastSend, Poco::DateTimeFormat::HTTP_FORMAT) + "' retries='" + std::to_string(m.retries) +
              "' messageId='" + m.messageId + "' receiptHandle='" + m.receiptHandle + "' md5body='" + m.md5Body + "' md5Attr='" + m.md5Attr + "'}";
          return os;
      }

    };

    typedef struct Message Message;
    typedef std::vector<Message> MessageList;

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SQS_MESSAGE_H
