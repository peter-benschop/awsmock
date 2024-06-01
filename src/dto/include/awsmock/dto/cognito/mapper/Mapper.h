//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_COGNITO_MAPPER_H
#define AWSMOCK_DTO_COGNITO_MAPPER_H

// AwsMock includes
#include <awsmock/core/StringUtils.h>
#include <awsmock/dto/cognito/CreateGroupRequest.h>
#include <awsmock/dto/cognito/CreateGroupResponse.h>
#include <awsmock/dto/cognito/CreateUserPoolClientRequest.h>
#include <awsmock/dto/cognito/CreateUserPoolDomainRequest.h>
#include <awsmock/dto/cognito/DescribeUserPoolRequest.h>
#include <awsmock/dto/cognito/DescribeUserPoolResponse.h>
#include <awsmock/dto/cognito/ListGroupsRequest.h>
#include <awsmock/dto/cognito/ListGroupsResponse.h>
#include <awsmock/dto/cognito/ListUserPoolRequest.h>
#include <awsmock/dto/cognito/ListUserPoolResponse.h>
#include <awsmock/dto/cognito/ListUsersInGroupRequest.h>
#include <awsmock/dto/cognito/ListUsersInGroupResponse.h>
#include <awsmock/dto/cognito/model/User.h>
#include <awsmock/dto/cognito/model/UserPool.h>
#include <awsmock/entity/cognito/Group.h>
#include <awsmock/entity/cognito/User.h>
#include <awsmock/entity/cognito/UserPool.h>

namespace AwsMock::Dto::Cognito {

    /**
     * @brief Maps an entity to the corresponding DTO
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps a user pool entity to a user pool DTO
         *
         * @param userPoolEntity user pool entity
         * @return UserPool DTO
         */
        static Dto::Cognito::UserPool map(const Database::Entity::Cognito::UserPool &userPoolEntity);

        /**
         * @brief Maps a user entity to a user DTO
         *
         * @param userEntity user entity
         * @return User DTO
         */
        static Dto::Cognito::User map(const Database::Entity::Cognito::User &userEntity);

        /**
         * @brief Maps a group entity to a group DTO
         *
         * @param groupEntity group entity
         * @return Group DTO
         */
        static Dto::Cognito::Group map(const Database::Entity::Cognito::Group &groupEntity);

        /**
         * @brief Maps a list of cognito user pools a list user pool response
         *
         * Some values will be pulled over from the request.
         *
         * @param request original request
         * @param userPoolList cognito user pool entity list
         * @param request request struct
         * @return ListUserPoolResponse
         * @see ListUserPoolResponse
         */
        static Dto::Cognito::ListUserPoolResponse map(const ListUserPoolRequest &request, const std::vector<Database::Entity::Cognito::UserPool> &userPoolList);

        /**
         * @brief Maps a user pool domain DTO to an entity
         *
         * @param request CreateUserPoolDomain request struct
         * @return UserPoolDomain
         * @see CreateUserPoolDomainRequest
         */
        static Database::Entity::Cognito::UserPoolDomain map(const CreateUserPoolDomainRequest &request);

        /**
         * @brief Maps a user pool client DTO to an entity
         *
         * @param request CreateUserPoolClientRequest request struct
         * @return UserPoolClient
         * @see CreateUserPoolClientRequest
         */
        static Database::Entity::Cognito::UserPoolClient map(const Dto::Cognito::CreateUserPoolClientRequest &request);

        /**
         * @brief Maps a create group DTO request to an entity
         *
         * @param request CreateGroupRequest struct
         * @return Group entity
         * @see CreateGroupRequest
         */
        static Database::Entity::Cognito::Group map(const CreateGroupRequest &request);

        /**
         * @brief Maps a group entity to a CreateGroupResponse
         *
         * @param request original request
         * @param group group entity
         * @return CreateGroupResponse
         * @see CreateGroupResponse
         */
        static Dto::Cognito::CreateGroupResponse map(const CreateGroupRequest &request, const Database::Entity::Cognito::Group &group);

        /**
         * @brief Maps a list of cognito groups to a list group response
         *
         * Some values will be pulled over from the request.
         *
         * @param request original request
         * @param groupList cognito user group entity list
         * @return ListGroupResponse
         * @see ListGroupResponse
         */
        static Dto::Cognito::ListGroupsResponse map(const ListGroupsRequest &request, const std::vector<Database::Entity::Cognito::Group> &groupList);

        /**
         * @brief Maps a list of cognito users in a group to a list user in group response
         *
         * Some values will be pulled over from the request.
         *
         * @param request original request
         * @param userList cognito user entity list
         * @return ListUsersInGroupResponse
         * @see ListUsersInGroupResponse
         */
        static Dto::Cognito::ListUsersInGroupResponse map(const ListUsersInGroupRequest &request, const std::vector<Database::Entity::Cognito::User> &userList);

        /**
         * @brief Maps a user pool to a describe user pool response
         *
         * Some values will be pulled over from the request.
         *
         * @param request original request
         * @param userPool cognito user pool entity
         * @param request request struct
         * @return DescribeUserPoolResponse
         * @see DescribeUserPoolResponse
         */
        static Dto::Cognito::DescribeUserPoolResponse map(const DescribeUserPoolRequest &request, const Database::Entity::Cognito::UserPool &userPool);
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_MAPPER_H
