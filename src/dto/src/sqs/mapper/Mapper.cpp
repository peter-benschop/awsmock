//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/sqs/mapper/Mapper.h>

namespace AwsMock::Dto::SQS {

    Database::Entity::SQS::Message Mapper::map(const SendMessageRequest &request) {

        Database::Entity::SQS::Message messageEntity;
        messageEntity.body = request.body,
        messageEntity.size = static_cast<long>(request.body.length()),
        messageEntity.contentType = request.contentType;

        for (const auto &[fst, snd]: request.messageAttributes) {
            Database::Entity::SQS::MessageAttribute attribute = {.attributeName = fst, .attributeValue = snd.stringValue, .attributeType = Database::Entity::SQS::MessageAttributeTypeFromString(MessageAttributeDataTypeToString(snd.type))};
            messageEntity.messageAttributes.emplace_back(attribute);
        }
        return messageEntity;
    }

    Dto::SQS::SendMessageResponse Mapper::map(const SendMessageRequest &request, const Database::Entity::SQS::Message &messageEntity) {

        SendMessageResponse response;
        response.queueUrl = request.queueUrl,
        response.messageId = messageEntity.messageId,
        response.receiptHandle = messageEntity.receiptHandle,
        response.md5Body = messageEntity.md5Body,
        response.md5UserAttr = messageEntity.md5UserAttr,
        response.md5SystemAttr = messageEntity.md5SystemAttr,
        response.requestId = request.requestId;
        return response;
    }

}// namespace AwsMock::Dto::SQS