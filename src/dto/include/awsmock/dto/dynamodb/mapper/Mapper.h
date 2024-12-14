//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_DYNAMODB_MAPPER_H
#define AWSMOCK_DTO_DYNAMODB_MAPPER_H

// AwsMock includes
#include <awsmock/dto/dynamodb/DeleteItemRequest.h>
#include <awsmock/dto/dynamodb/DescribeTableResponse.h>
#include <awsmock/dto/dynamodb/PutItemRequest.h>
#include <awsmock/entity/dynamodb/AttributeValue.h>
#include <awsmock/entity/dynamodb/Item.h>
#include <awsmock/entity/dynamodb/Table.h>

namespace AwsMock::Dto::DynamoDb {

    /**
     * @brief Maps an entity to the corresponding DTO and vice versa.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps a DynamoDB table DTO to an entity
         *
         * @param response response struct
         * @return Dynamodb entity
         * @see Dto::DynamoDb::DescribeTableResponse
         * @see Database::Entity::DynamoDb::Table
         */
        static Database::Entity::DynamoDb::Table map(const DescribeTableResponse &response);

        /**
         * @brief Maps a DynamoDB DeleteItemRequest to an entity, which can be deleted in the database.
         *
         * @param request request struct
         * @return Dynamodb entity to be deleted
         * @see Dto::DynamoDb::DeleteItemRequest
         * @see Database::Entity::DynamoDb::Item
         */
        static Database::Entity::DynamoDb::Item map(const DeleteItemRequest &request);

        /**
         * @brief Maps a DynamoDB PutItemRequest to an entity, which can be saved in the database.
         *
         * @param request request struct
         * @return Dynamodb entity to be deleted
         * @see Dto::DynamoDb::PutItemRequest
         * @see Database::Entity::DynamoDb::Item
         */
        static Database::Entity::DynamoDb::Item map(const PutItemRequest &request);
    };

}// namespace AwsMock::Dto::DynamoDb

#endif// AWSMOCK_DTO_S3_MAPPER_H
