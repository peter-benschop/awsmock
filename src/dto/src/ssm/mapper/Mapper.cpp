//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/ssm/mapper/Mapper.h>

namespace AwsMock::Dto::SSM {

    Dto::SSM::Parameter Mapper::map(const Database::Entity::SSM::Parameter &parameterEntity) {

        Dto::SSM::Parameter responseDto;
        responseDto.region = parameterEntity.region;
        responseDto.name = parameterEntity.parameterName;
        responseDto.value = parameterEntity.parameterValue;
        responseDto.description = parameterEntity.description;
        responseDto.arn = parameterEntity.arn;
        responseDto.tier = parameterEntity.tier;
        responseDto.type = ParameterTypeFromString(parameterEntity.type);
        for (const auto &tag: parameterEntity.tags) {
            responseDto.tags[tag.first] = tag.second;
        }
        return responseDto;
    }

    Dto::SSM::GetParameterResponse Mapper::map(const GetParameterRequest &request, const Database::Entity::SSM::Parameter &parameterEntity) {

        Dto::SSM::GetParameterResponse response;
        response.region = request.region;
        response.parameter = map(parameterEntity);
        return response;
    }

}// namespace AwsMock::Dto::SSM