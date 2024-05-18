//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/cognito/mapper/Mapper.h>

namespace AwsMock::Dto::Cognito {

    Dto::Cognito::ListUserPoolResponse Mapper::map(const ListUserPoolRequest &request, const std::vector<Database::Entity::Cognito::UserPool> &userPoolList) {

        Dto::Cognito::ListUserPoolResponse response;

        for (const auto &userPool: userPoolList) {
            UserPool userPoolDto = {
                    .region = userPool.region,
                    .name = userPool.name,
                    .userPoolId = userPool.userPoolId,
                    .created = userPool.created,
                    .lastModified = userPool.modified};
            response.userPools.emplace_back(userPool);
        }
        return response;
    }

}// namespace AwsMock::Dto::Cognito