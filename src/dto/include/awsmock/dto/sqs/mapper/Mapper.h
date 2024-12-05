//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_SQS_MAPPER_H
#define AWSMOCK_DTO_SQS_MAPPER_H

// AwsMock includes
#include <awsmock/dto/sqs/SendMessageRequest.h>
#include <awsmock/dto/sqs/SendMessageResponse.h>
#include <awsmock/dto/sqs/model/Message.h>
#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Dto::SQS {

    /**
     * @brief Maps an entity to the corresponding DTO
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps a SQS message DTO list to a SQS message entity
         *
         * Some values will be pulled over from the request.
         *
         * @param request request struct
         * @return ListObjectVersionsResponse
         * @see ListObjectVersionsResponse
         */
        static Database::Entity::SQS::Message map(const SendMessageRequest &request);

        /**
         * @brief Maps a SQS message entity to a SQS send message response DTO
         *
         * Some values will be pulled over from the request.
         *
         * @param request request struct
         * @param messageEntity message entity
         * @return ListObjectVersionsResponse
         * @see ListObjectVersionsResponse
         */
        static SendMessageResponse map(const SendMessageRequest &request, const Database::Entity::SQS::Message &messageEntity);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_MAPPER_H
