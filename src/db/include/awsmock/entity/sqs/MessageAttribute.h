//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_MESSAGEATTRIBUTE_H
#define AWSMOCK_DB_ENTITY_SQS_MESSAGEATTRIBUTE_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>
#include <map>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

namespace AwsMock::Database::Entity::SQS {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  enum STATUS { INITIAL, SEND, RESEND, DELAYED };

  enum MessageAttributeType { STRING, NUMBER };
  static std::map<MessageAttributeType, std::string> MessageAttributeTypeNames{
      {MessageAttributeType::STRING, "String"},
      {MessageAttributeType::NUMBER, "Number"},
  };

  [[maybe_unused]] static std::string MessageAttributeTypeToString(MessageAttributeType messageAttributeType) {
    return MessageAttributeTypeNames[messageAttributeType];
  }

  [[maybe_unused]] static MessageAttributeType MessageAttributeTypeFromString(const std::string &messageAttributeType) {
    for (auto &it : MessageAttributeTypeNames) {
      if (it.second == messageAttributeType) {
        return it.first;
      }
    }
    return MessageAttributeType::STRING;
  }

  struct MessageAttribute {

    /**
     * Constructor.
     *
     * @param name attribute name
     * @param value attribute value
     * @param type attribute type
     */
    //MessageAttribute(std::string name, std::string value, const MessageAttributeType &type);

    /**
     * Message attribute name
     */
    std::string attributeName;

    /**
     * Message attribute value
     */
    std::string attributeValue;

    /**
     * Message attribute value
     */
    MessageAttributeType attributeType;

    /**
     * Converts the entity to a MongoDB document
     *
     * @return entity as MongoDB document.
     */
    view_or_value<view, value> ToDocument() const;

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const;

    /**
     * Stream provider.
     *
     * @param os output stream
     * @param m message attribute
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const MessageAttribute &m);

  };

  typedef struct MessageAttribute MessageAttribute;
  typedef std::vector<MessageAttribute> MessageAttributeList;

} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SQS_MESSAGEATTRIBUTE_H
