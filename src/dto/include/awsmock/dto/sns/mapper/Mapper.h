//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_SNS_MAPPER_H
#define AWSMOCK_DTO_SNS_MAPPER_H

// AwsMock includes
#include <awsmock/dto/sns/ListMessageCountersResponse.h>
#include <awsmock/dto/sns/ListMessagesRequest.h>
#include <awsmock/dto/sns/ListMessagesResponse.h>
#include <awsmock/dto/sns/model/Message.h>
#include <awsmock/entity/sns/Message.h>

namespace AwsMock::Dto::SNS {

    /**
     * @brief Maps an entity to the corresponding DTO
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps an SNS message entity list to a list messages response
         *
         * Some values will be pulled over from the request.
         *
         * @param request request struct
         * @param messageEntities SNS message entity list
         * @return ListMessagesResponse
         * @see ListMessagesResponse
         * @see ListMessagesRequest
         */
        static ListMessagesResponse map(const ListMessagesRequest &request, const std::vector<Database::Entity::SNS::Message> &messageEntities);
        /**
         * @brief Maps an SNS message entity list to a list messages response
         *
         * Some values will be pulled over from the request.
         *
         * @param messageEntities SNS message entity list
         * @return ListMessagesResponse
         * @see ListMessagesResponse
         * @see ListMessagesRequest
         */
        static ListMessageCountersResponse map(const std::vector<Database::Entity::SNS::Message> &messageEntities);
    };

}// namespace AwsMock::Dto::SNS

#endif// AWSMOCK_DTO_SNS_MAPPER_H
