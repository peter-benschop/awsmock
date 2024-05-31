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
            response.userPools.emplace_back(userPoolDto);
        }
        return response;
    }

    Database::Entity::Cognito::UserPoolDomain Mapper::map(const Dto::Cognito::CreateUserPoolDomainRequest &request) {

        Database::Entity::Cognito::UserPoolDomain userPoolDomain;
        userPoolDomain.domain = request.domain;
        return userPoolDomain;
    }

    Database::Entity::Cognito::Group Mapper::map(const Dto::Cognito::CreateGroupRequest &request) {
        Database::Entity::Cognito::Group group = {
                .region = request.region,
                .userPoolId = request.userPoolId,
                .groupName = request.groupName,
                .description = request.description,
                .precedence = request.precedence};
        return group;
    }

    Dto::Cognito::CreateGroupResponse Mapper::map(const CreateGroupRequest &request, const Database::Entity::Cognito::Group &group) {
        Dto::Cognito::Group groupDto = {group.groupName, group.userPoolId, group.description, group.roleArn, group.precedence, group.created, group.modified};
        Dto::Cognito::CreateGroupResponse response = {{.requestId = request.requestId, .region = group.region, .user = request.user}, groupDto};
        return response;
    }

    Dto::Cognito::ListGroupsResponse Mapper::map(const ListGroupsRequest &request, const std::vector<Database::Entity::Cognito::Group> &groupList) {

        Dto::Cognito::ListGroupsResponse response{{.requestId = request.requestId, .region = request.region, .user = request.user}};

        for (const auto &group: groupList) {
            Group groupDto = {group.groupName, group.userPoolId, group.description, group.roleArn, group.precedence, group.created, group.modified};
            response.groups.emplace_back(groupDto);
        }
        return response;
    }

}// namespace AwsMock::Dto::Cognito