//
// Created by vogje01 on 12/2/23.
//

#ifndef AWSMOCK_DTO_COGNITO_MESSAGE_ACTION_H
#define AWSMOCK_DTO_COGNITO_MESSAGE_ACTION_H

// Poco includes
#include <Poco/JSON/JSON.h>

namespace AwsMock::Dto::Cognito {

  enum MessageAction {
    RESEND,
    SUPPRESS
  };

  static std::map<MessageAction, std::string> MessageActionNames{
      {MessageAction::RESEND, "RESEND"},
      {MessageAction::SUPPRESS, "SUPPRESS"}
  };

  [[maybe_unused]] static std::string MessageActionToString(MessageAction messageAction) {
    return MessageActionNames[messageAction];
  }

  [[maybe_unused]] static MessageAction MessageActionFromString(const std::string &messageActionName) {
    for (auto &it : MessageActionNames) {
      if (it.second == messageActionName) {
        return it.first;
      }
    }
    return MessageAction::SUPPRESS;
  }

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_COGNITO_MESSAGE_ACTION_H
