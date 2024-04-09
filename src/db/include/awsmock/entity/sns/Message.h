//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_MESSAGE_H
#define AWSMOCK_DB_ENTITY_SNS_MESSAGE_H

// C++ includes
#include <string>
#include <sstream>
#include <vector>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>

// MongoDB includes
#include <bsoncxx/json.hpp>
#include <bsoncxx/string/to_string.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/stdx.hpp>

// AwsMock includes
#include <awsmock/entity/sns/MessageAttribute.h>

namespace AwsMock::Database::Entity::SNS {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;
  using bsoncxx::view_or_value;
  using bsoncxx::document::view;
  using bsoncxx::document::value;

  enum MessageStatus { INITIAL, SEND, RESEND };
  static std::map<MessageStatus, std::string> MessageStatusNames{
      {MessageStatus::INITIAL, "INITIAL"},
      {MessageStatus::SEND, "SEND"},
      {MessageStatus::RESEND, "RESEND"},
  };

  [[maybe_unused]] static std::string MessageStatusToString(MessageStatus messageStatus) {
    return MessageStatusNames[messageStatus];
  }

  [[maybe_unused]] static MessageStatus MessageStatusFromString(const std::string &messageStatusString) {
    for (auto &it : MessageStatusNames) {
      if (it.second == messageStatusString) {
        return it.first;
      }
    }
    return MessageStatus::INITIAL;
  }

  /**
   * SNS message entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  struct Message {

    /**
     * ID
     */
    std::string oid;

    /**
     * Aws region name
     */
    std::string region;

    /**
     * Topic ARN
     */
    std::string topicArn;

    /**
     * Target ARN
     */
    std::string targetArn;

    /**
     * Message body
     */
    std::string message;

    /**
     * Message ID
     */
    std::string messageId;

    /**
     * Message ID
     */
    MessageStatus status;

    /**
     * List of sqs
     */
    MessageAttributeList attributes;

    /**
     * Last send datetime
     */
    Poco::DateTime lastSend;

    /**
     * Creation datetime
     */
    Poco::DateTime created = Poco::DateTime();

    /**
     * Last modified datetime
     */
    Poco::DateTime modified = Poco::DateTime();

    /**
     * Converts the entity to a MongoDB document
     *
     * @return entity as MongoDB document.
     */
    [[nodiscard]] view_or_value<view, value> ToDocument() const;

    /**
     * Converts the MongoDB document to an entity
     *
     * @param mResult MongoDB document.
     */
    void FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult);

    /**
     * Converts the entity to a JSON object
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
     * @param message message entity
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Message &message);

  };

  typedef struct Message Message;
  typedef std::vector<Message> MessageList;

} // namespace AwsMock::Database::Entity::SNS

#endif // AWSMOCK_DB_ENTITY_SNS_MESSAGE_H
