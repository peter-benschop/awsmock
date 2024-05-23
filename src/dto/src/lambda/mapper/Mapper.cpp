//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/lambda/mapper/Mapper.h>

namespace AwsMock::Dto::Lambda {

    Dto::Lambda::CreateFunctionResponse Mapper::map(const Dto::Lambda::CreateFunctionRequest &request, const Database::Entity::Lambda::Lambda &lambdaEntity) {

        Dto::Lambda::CreateFunctionResponse response;
        response.region = request.region;
        response.user = request.user;
        response.functionArn = lambdaEntity.arn;
        response.functionName = lambdaEntity.function;
        response.runtime = lambdaEntity.runtime;
        response.role = lambdaEntity.role;
        response.handler = lambdaEntity.handler;
        response.memorySize = request.memorySize;
        response.codeSize = lambdaEntity.codeSize;
        response.timeout = lambdaEntity.timeout;
        response.codeSha256 = lambdaEntity.codeSha256;

        // Environment
        response.environment.variables = lambdaEntity.environment.variables;

        // Ephemeral storage
        response.ephemeralStorage.size = lambdaEntity.ephemeralStorage.size;

        return response;
    }

    Dto::Lambda::CreateFunctionRequest Mapper::map(const Database::Entity::Lambda::Lambda &lambdaEntity) {

        Dto::Lambda::CreateFunctionRequest request;
        request.region = request.region;
        request.user = request.user;
        request.functionName = lambdaEntity.function;
        request.runtime = lambdaEntity.runtime;
        request.role = lambdaEntity.role;
        request.handler = lambdaEntity.handler;
        request.memorySize = request.memorySize;
        request.timeout = lambdaEntity.timeout;

        // Environment
        request.environment.variables = lambdaEntity.environment.variables;

        // Ephemeral storage
        request.ephemeralStorage.size = lambdaEntity.ephemeralStorage.size;

        return request;
    }

}// namespace AwsMock::Dto::Lambda