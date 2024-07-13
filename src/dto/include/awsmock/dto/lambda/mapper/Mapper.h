//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_LAMBDA_MAPPER_H
#define AWSMOCK_DTO_LAMBDA_MAPPER_H

// AwsMock includes
#include <awsmock/dto/lambda/CreateEventSourceMappingsRequest.h>
#include <awsmock/dto/lambda/CreateFunctionRequest.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>
#include <awsmock/entity/lambda/Lambda.h>

namespace AwsMock::Dto::Lambda {

    /**
     * @brief Maps an entity to the corresponding DTO
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps a lambda entity to a create function response
         *
         * Some values will be pulled over from the request.
         *
         * @param lambdaEntity lambda entity
         * @param request lambda create function request struct
         * @return CreateFunctionResponse
         * @see CreateFunctionResponse
         */
        static Dto::Lambda::CreateFunctionResponse map(const Dto::Lambda::CreateFunctionRequest &request, const Database::Entity::Lambda::Lambda &lambdaEntity);

        /**
         * @brief Maps a lambda entity to a create function request.
         *
         * Some values will be pulled over from the request. This is needed, as the server starts all lambdas during startup and needs to convert the lambda entities
         * stored in the database to an CreateLambdaRequest, which ís send to the lambda service.
         *
         * @param lambdaEntity lambda entity
         * @return CreateFunctionRequest
         * @see CreateFunctionRequest
         */
        static Dto::Lambda::CreateFunctionRequest map(const Database::Entity::Lambda::Lambda &lambdaEntity);

        /**
         * @brief Maps a lambda create request to a lambda entity
         *
         * @param request create lambda request
         * @return lambda entity
         * @see CreateFunctionRequest
         */
        static Database::Entity::Lambda::Lambda map(const Dto::Lambda::CreateFunctionRequest &request);

        /**
         * @brief Maps a lambda create eventsource mappings request request to a lambda event source mapping
         *
         * @param request create lambda request
         * @return lambda event source mapping
         * @see CreateEventSourceMappingsRequest
         * @see EventSourceMapping
         */
        static Database::Entity::Lambda::EventSourceMapping map(const Dto::Lambda::CreateEventSourceMappingsRequest &request);
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_MAPPER_H
