//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_COGNITO_MAPPER_H
#define AWSMOCK_DTO_COGNITO_MAPPER_H

// AwsMock includes
#include <awsmock/dto/cognito/CreateUserPoolDomainRequest.h>
#include <awsmock/dto/cognito/ListUserPoolRequest.h>
#include <awsmock/dto/cognito/ListUserPoolResponse.h>
#include <awsmock/dto/cognito/model/UserPool.h>
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
         * @brief Maps a list of cognito user pools a list user pool response
         *
         * Some values will be pulled over from the request.
         *
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
    };

}// namespace AwsMock::Dto::Cognito

#endif// AWSMOCK_DTO_COGNITO_MAPPER_H
