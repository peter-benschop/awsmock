//
// Created by vogje01 on 6/2/24.
//

#include <awsmock/dto/transfer/mapper/Mapper.h>

namespace AwsMock::Dto::Transfer {

    Dto::Transfer::ListUsersResponse Mapper::map(const ListUsersRequest &request, const std::vector<Database::Entity::Transfer::User> &users) {

        Dto::Transfer::ListUsersResponse response;
        response.serverId = request.serverId;

        for (const auto &u: users) {
            Dto::Transfer::User user = {
                    .userName = u.userName,
                    .arn = u.arn,
                    .homeDirectory = u.homeDirectory,
                    .password = u.password};
            response.users.emplace_back(user);
        }
        return response;
    }

}// namespace AwsMock::Dto::Transfer
