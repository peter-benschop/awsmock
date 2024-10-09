//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/sns/mapper/Mapper.h>

namespace AwsMock::Dto::SNS {

    Dto::SNS::ListMessagesResponse Mapper::map(const ListMessagesRequest &request, const std::vector<Database::Entity::SNS::Message> &messageEntities) {

        ListMessagesResponse response;
        for (const auto &entity: messageEntities) {
            response.messageList.emplace_back(entity);
        }
        return response;
    }
}// namespace AwsMock::Dto::SNS