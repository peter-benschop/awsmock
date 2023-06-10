//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_MESSAGEATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SQS_MESSAGEATTRIBUTE_H

// C++ includes
#include <string>
#include <vector>

// Poco includes
#include <Poco/DateTime.h>

namespace AwsMock::Database::Entity::SQS {

    struct MessageAttribute {

      /**
       * ID
       */
      long id = 0;

      /**
       * MessageAttribute name
       */
      std::string name;

      /**
       * MessageAttribute value
       */
      std::string value;

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
          Poco::MongoDB::Document::Ptr attributeDoc = new Poco::MongoDB::Document();
          attributeDoc->add("name", name);
          attributeDoc->add("value", value);
          attributeDoc->add("created", created.timestamp());
          attributeDoc->add("modified", modified.timestamp());
          return attributeDoc;
      }

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
      friend std::ostream &operator<<(std::ostream &os, const MessageAttribute &m) {
          os << "MessageAttribute={id='" + std::to_string(m.id) + "' name='" + m.name + "'value='" + m.value +
              "' created='" + Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT) +
              "' modified='" + Poco::DateTimeFormatter().format(m.created, Poco::DateTimeFormat::HTTP_FORMAT) + "'}";
          return os;
      }

    };

    typedef struct MessageAttribute MessageAttribute;
    typedef std::vector<MessageAttribute> MessageAttributeList;

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SQS_MESSAGEATTRIBUTE_H
