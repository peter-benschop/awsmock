//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_DYNAMODB_MAPPER_H
#define AWSMOCK_DTO_DYNAMODB_MAPPER_H

// AwsMock includes
#include <awsmock/dto/dynamodb/DeleteItemRequest.h>
#include <awsmock/dto/dynamodb/PutItemRequest.h>
#include <awsmock/entity/dynamodb/AttributeValue.h>
#include <awsmock/entity/dynamodb/Item.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * @brief Maps an entity to the corresponding DTO and vice versa.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps a DynamoDB DeleteItemRequest to an entity, which can be deleted in the database.
         *
         * @param request request struct
         * @return Dynamodb entity to be deleted
         * @see Dto::DynamoDb::DeleteItemRequest
         * @see Database::Entity::DynamoDb
         */
        static Database::Entity::DynamoDb::Item map(const Dto::DynamoDb::DeleteItemRequest &request);

        /**
         * @brief Maps a DynamoDB PutItemRequest to an entity, which can be saved in the database.
         *
         * @param request request struct
         * @return Dynamodb entity to be deleted
         * @see Dto::DynamoDb::PutItemRequest
         * @see Database::Entity::DynamoDb
         */
        static Database::Entity::DynamoDb::Item map(const Dto::DynamoDb::PutItemRequest &request);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_S3_MAPPER_H
