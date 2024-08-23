//
// Created by vogje01 on 5/10/24.
//

#ifndef AWSMOCK_DTO_SSM_MAPPER_H
#define AWSMOCK_DTO_SSM_MAPPER_H

// AwsMock includes
#include <awsmock/dto/ssm/GetParameterRequest.h>
#include <awsmock/dto/ssm/GetParameterResponse.h>
#include <awsmock/dto/ssm/model/ParameterType.h>
#include <awsmock/entity/ssm/Parameter.h>

namespace AwsMock::Dto::SSM {

    /**
     * @brief Maps an entity to the corresponding DTO
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class Mapper {

      public:

        /**
         * @brief Maps a single parameter
         *
         * @param parameterEntity parameter entity
         * @return parameter DTO
         */
        static Dto::SSM::Parameter map(const Database::Entity::SSM::Parameter &parameterEntity);

        /**
         * @brief Maps a SSM parameter entity to a parameter response
         *
         * @par
         * Some values will be pulled over from the request.
         *
         * @param parameter SSM parameter
         * @param request request struct
         * @return GetParameterResponse
         * @see GetParameterResponse
         */
        static Dto::SSM::GetParameterResponse map(const GetParameterRequest &request, const Database::Entity::SSM::Parameter &parameter);

        /**
         * @brief Maps a SSM parameter entity list to a parameter response
         *
         * Some values will be pulled over from the request.
         *
         * @param objectList S3 object entity list
         * @param request request struct
         * @return ListObjectVersionsResponse
         * @see ListObjectVersionsResponse
         */
        static Dto::SSM::GetParameterResponse map(const GetParameterRequest &request, const std::vector<Database::Entity::SSM::Parameter> &parameterList);
    };

}// namespace AwsMock::Dto::SSM

#endif// AWSMOCK_DTO_S3_MAPPER_H
