//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DB_ENTITY_SNS_MESSAGESTATUS_H
#define AWSMOCK_DB_ENTITY_SNS_MESSAGESTATUS_H

// C++ includes
#include <string>
#include <map>

namespace AwsMock::Database::Entity::SNS {

  /**
   * SNS message attribute entity
   *
   * @author jens.vogt@opitz-consulting.com
   */
  enum MessageStatus {
    INITIAL, SEND, RESEND
  };
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

} // namespace AwsMock::Database::Entity::SNS

#endif // AWSMOCK_DB_ENTITY_SNS_MESSAGESTATUS_H
