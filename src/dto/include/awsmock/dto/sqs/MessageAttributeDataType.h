//
// Created by vogje01 on 12/2/23.
//

#ifndef AWSMOCK_DTO_SQS_MESSAGE_ATTRIBUTE_DATA_TYPE_H
#define AWSMOCK_DTO_SQS_MESSAGE_ATTRIBUTE_DATA_TYPE_H

namespace AwsMock::Dto::SQS {

    enum MessageAttributeDataType {
        STRING,
        NUMBER,
        BINARY
    };

    static std::map<MessageAttributeDataType, std::string> MessageAttributeDataTypeNames{
            {MessageAttributeDataType::STRING, "String"},
            {MessageAttributeDataType::NUMBER, "Number"},
            {MessageAttributeDataType::BINARY, "Binary"},
    };

    [[maybe_unused]] static std::string MessageAttributeDataTypeToString(MessageAttributeDataType messageAttributeDataType) {
        return MessageAttributeDataTypeNames[messageAttributeDataType];
    }

    [[maybe_unused]] static MessageAttributeDataType MessageAttributeDataTypeFromString(const std::string &messageAttributeDataType) {
        for (auto &it: MessageAttributeDataTypeNames) {
            if (it.second == messageAttributeDataType) {
                return it.first;
            }
        }
        return MessageAttributeDataType::STRING;
    }

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_MESSAGE_ATTRIBUTE_DATA_TYPE_H
