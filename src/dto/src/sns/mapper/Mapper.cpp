//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/sns/mapper/Mapper.h>

namespace AwsMock::Dto::SNS {

    ListMessagesResponse Mapper::map(const ListMessagesRequest &request, const std::vector<Database::Entity::SNS::Message> &messageEntities) {

        ListMessagesResponse response;
        for (const auto &entity: messageEntities) {
            Message message;
            message.region = entity.region;
            message.topicArn = entity.topicArn;
            message.messageId = entity.messageId;
            message.created = entity.created;
            message.modified = entity.modified;
            response.messageList.emplace_back(entity);
        }
        return response;
    }

    ListMessageCountersResponse Mapper::map(const std::vector<Database::Entity::SNS::Message> &messageEntities) {

        ListMessageCountersResponse response;
        for (const auto &entity: messageEntities) {
            Message message;
            message.region = entity.region;
            message.topicArn = entity.topicArn;
            message.messageId = entity.messageId;
            message.message = entity.message;
            message.created = entity.created;
            message.modified = entity.modified;
            response.messages.emplace_back(message);
        }
        return response;
    }
}// namespace AwsMock::Dto::SNS