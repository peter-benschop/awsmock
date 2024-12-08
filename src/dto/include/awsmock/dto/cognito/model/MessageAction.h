//
// Created by vogje01 on 12/2/23.
//

#ifndef AWSMOCK_DTO_COGNITO_MESSAGE_ACTION_H
#define AWSMOCK_DTO_COGNITO_MESSAGE_ACTION_H

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/entity/cognito/User.h>

namespace AwsMock::Dto::Cognito {

    enum MessageAction {
        RESEND,
        SUPPRESS
    };

    static std::map<MessageAction, std::string> MessageActionNames{
            {RESEND, "RESEND"},
            {SUPPRESS, "SUPPRESS"}};

    [[maybe_unused]] static std::string MessageActionToString(MessageAction messageAction) {
        return MessageActionNames[messageAction];
    }

    [[maybe_unused]] static MessageAction MessageActionFromString(const std::string &messageActionName) {
        for (auto &[fst, snd]: MessageActionNames) {
            if (snd == messageActionName) {
                return fst;
            }
        }
        return SUPPRESS;
    }

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_MESSAGE_ACTION_H
