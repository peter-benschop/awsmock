//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SQS_MESSAGESTATUS_H
#define AWSMOCK_DB_ENTITY_SQS_MESSAGESTATUS_H

// C++ includes
#include <string>
#include <map>

namespace AwsMock::Database::Entity::SQS {

  enum class MessageStatus {
      INITIAL,
      DELAYED,
      INVISIBLE,
      UNKNOWN
  };

  static std::map<MessageStatus, std::string> MessageStatusNames{
      {MessageStatus::INITIAL, "INITIAL"},
      {MessageStatus::DELAYED, "DELAYED"},
      {MessageStatus::INVISIBLE, "INVISIBLE"},
  };

  [[maybe_unused]]static std::string MessageStatusToString(MessageStatus messageStatus) {
    return MessageStatusNames[messageStatus];
  }

  [[maybe_unused]]static MessageStatus MessageStatusFromString(const std::string &messageStatus) {
    for (auto &it : MessageStatusNames) {
      if (it.second == messageStatus) {
        return it.first;
      }
    }
    return MessageStatus::UNKNOWN;
  }
} // namespace AwsMock::Database::Entity::S3

#endif // AWSMOCK_DB_ENTITY_SQS_MESSAGESTATUS_H
