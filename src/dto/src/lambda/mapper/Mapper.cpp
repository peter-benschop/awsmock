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
        request.region = lambdaEntity.region;
        request.user = lambdaEntity.user;
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

        // Core
        request.code.zipFile = lambdaEntity.code.zipFile;
        request.code.s3Bucket = lambdaEntity.code.s3Bucket;
        request.code.s3Key = lambdaEntity.code.s3Key;
        request.code.s3ObjectVersion = lambdaEntity.code.s3ObjectVersion;

        return request;
    }

    Database::Entity::Lambda::Lambda Mapper::map(const Dto::Lambda::CreateFunctionRequest &request) {
        Database::Entity::Lambda::Lambda lambda;
        lambda.region = request.region;
        lambda.user = request.user;
        lambda.function = request.functionName;
        lambda.handler = request.handler;
        lambda.role = request.role;
        lambda.environment.variables = request.environment.variables;
        lambda.runtime = request.runtime;
        lambda.code.zipFile = request.code.zipFile;
        lambda.code.s3Bucket = request.code.s3Bucket;
        lambda.code.s3Key = request.code.s3Key;
        lambda.code.s3ObjectVersion = request.code.s3ObjectVersion;
        return lambda;
    }

    Database::Entity::Lambda::EventSourceMapping Mapper::map(const Dto::Lambda::CreateEventSourceMappingsRequest &request) {
        Database::Entity::Lambda::EventSourceMapping eventSourceMapping;
        eventSourceMapping.eventSourceArn = request.eventSourceArn;
        eventSourceMapping.batchSize = request.batchSize;
        eventSourceMapping.maximumBatchingWindowInSeconds = request.maximumBatchingWindowInSeconds;
        eventSourceMapping.enabled = request.enabled;
        return eventSourceMapping;
    }

}// namespace AwsMock::Dto::Lambda