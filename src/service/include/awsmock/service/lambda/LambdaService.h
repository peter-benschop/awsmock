//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_SERVICE_H
#define AWSMOCK_SERVICE_LAMBDA_SERVICE_H

// C++ standard includes
#include <sstream>
#include <string>

// Boost includes
#include <boost/thread.hpp>

// AwsMock includes
#include "awsmock/service/docker/DockerService.h"
#include "awsmock/service/monitoring/MetricService.h"
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/core/exception/BadRequestException.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/lambda/AccountSettingsResponse.h>
#include <awsmock/dto/lambda/CreateEventSourceMappingsRequest.h>
#include <awsmock/dto/lambda/CreateEventSourceMappingsResponse.h>
#include <awsmock/dto/lambda/CreateFunctionRequest.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>
#include <awsmock/dto/lambda/CreateTagRequest.h>
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>
#include <awsmock/dto/lambda/DeleteTagsRequest.h>
#include <awsmock/dto/lambda/GetFunctionResponse.h>
#include <awsmock/dto/lambda/ListEventSourceMappingsRequest.h>
#include <awsmock/dto/lambda/ListEventSourceMappingsResponse.h>
#include <awsmock/dto/lambda/ListFunctionResponse.h>
#include <awsmock/dto/lambda/ListTagsResponse.h>
#include <awsmock/dto/lambda/mapper/Mapper.h>
#include <awsmock/dto/lambda/model/Function.h>
#include <awsmock/dto/s3/model/EventNotification.h>
#include <awsmock/dto/sqs/model/EventNotification.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/lambda/LambdaCreator.h>
#include <awsmock/service/lambda/LambdaExecutor.h>

// Maximal output length for a synchronous invocation call
#define MAX_OUTPUT_LENGTH (4 * 1024)

namespace AwsMock::Service {

    /**
     * @brief Lambda service module. Handles all lambda related requests:
     *
     * <ul>
     * <li>Create lambda function.</li>
     * <li>Delete lambda function.</li>
     * <li>List lambda function.</li>
     * <li>Create lambda function tags.</li>
     * <li>List lambda function tags.</li>
     * <li>Delete lambda function tags.</li>
     * <li>Invoke lambda function with AWS S3 notification payload.</li>
     * <li>Invoke lambda function with AWS SQS notification payload.</li>
     * </ul>
     *
     * <p>
     * As the AWS lambda runtime environment (RIE) cannot handle several concurrent requests, the lambda invocation requests are queued and are send sequentially to the lambda function
     * running as docker container. The incoming requests are posted to a Poco notification center. The target of the notification is the LambdaExecutor (@see AwsMock::Worker::LambdaExecutor).
     * </p>
     * <p>
     * The execution command are send via HTTP to the docker image. RIE is using port 8080 for the REST invocation requests. This port is mapped to the docker host on a randomly chosen port,
     * between 32768 and 65536.
     * </p>
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class LambdaService {

      public:

        /**
         * @brief Constructor
         */
        explicit LambdaService() : _lambdaDatabase(Database::LambdaDatabase::instance()) {};

        /**
         * @brief Create lambda function
         *
         * @param request create lambda request
         * @return CreateFunctionResponse
         */
        Dto::Lambda::CreateFunctionResponse CreateFunction(Dto::Lambda::CreateFunctionRequest &request);

        /**
         * @brief List lambda functions
         *
         * @param region AWS region name
         * @return CreateFunctionResponse
         */
        Dto::Lambda::ListFunctionResponse ListFunctions(const std::string &region);

        /**
         * @brief Invoke SQS function.
         *
         * If the logType is set and is equal to 'Tail', the function will be invoked synchronously and the output will be appended to the response.
         *
         * @param functionName lambda function name
         * @param payload SQS message
         * @param region AWS region
         * @param user user
         * @param logType logging type
         * @return output string (limited to 4kb) in case logType = 'Tail' and an synchronous invocation.
         */
        std::string InvokeLambdaFunction(const std::string &functionName, const std::string &payload, const std::string &region, const std::string &user, const std::string &logType = {});

        /**
         * @brief Create a new tag for a lambda functions.
         *
         * @param request lambda create tag request
         */
        void CreateTag(const Dto::Lambda::CreateTagRequest &request);

        /**
         * @brief Returns a list of tags for a ARN.
         *
         * @param arn lambda function ARN
         * @return ListTagsResponse
         * @see AwsMock::Dto::Lambda::ListTagsResponse
         */
        Dto::Lambda::ListTagsResponse ListTags(const std::string &arn);

        /**
         * @brief Gets a single lambda function
         *
         * @param region AWS region
         * @param name function name
         * @return GetFunctionResponse
         * @throws ServiceException
         * @see AwsMock::Dto::Lambda::GetFunctionResponse
         */
        Dto::Lambda::GetFunctionResponse GetFunction(const std::string &region, const std::string &name);

        /**
         * @brief Returns the account settings
         *
         * @return AccountSettingsResponse
         * @throws ServiceException
         * @see AwsMock::Dto::Lambda::AccountSettingsResponse
         */
        Dto::Lambda::AccountSettingsResponse GetAccountSettings();

        /**
         * @brief Creates a event source mapping.
         *
         * @par
         * The event source mapping is created in the SQS/SNS entities and executes whenever a SQS/SNS message is created.
         *
         * @param request create event source mappings request
         * @return create event source mappings response
         * @throws ServiceException
         * @see AwsMock::Dto::Lambda::CreateEventSourceMappingsRequest
         * @see AwsMock::Dto::Lambda::CreateEventSourceMappingsResponse
         */
        Dto::Lambda::CreateEventSourceMappingsResponse CreateEventSourceMappings(const Dto::Lambda::CreateEventSourceMappingsRequest &request);

        /**
         * @brief List a event source mappings
         *
         * @param request list event source mappings request
         * @return list event source mappings response
         * @throws ServiceException
         * @see AwsMock::Dto::Lambda::ListEventSourceMappingsRequest
         * @see AwsMock::Dto::Lambda::ListEventSourceMappingsResponse
         */
        Dto::Lambda::ListEventSourceMappingsResponse ListEventSourceMappings(const Dto::Lambda::ListEventSourceMappingsRequest &request);

        /**
         * @brief Delete lambda function
         *
         * This method will also delete the corresponding container and images.
         *
         * @param request delete lambda request
         * @throws ServiceException
         */
        void DeleteFunction(const Dto::Lambda::DeleteFunctionRequest &request);

        /**
         * @brief Delete lambda function tags
         *
         * @param request delete tags request
         * @throws ServiceException
         */
        void DeleteTags(Dto::Lambda::DeleteTagsRequest &request);

      private:

        /**
         * @brief Invoke the lambda function synchronously.
         *
         * The output will be returned to the calling method.
         *
         * @param host lambda docker container host
         * @param port lambda docker container port
         * @param payload payload for the function
         * @return output from lambda invocation call
         */
        static std::string InvokeLambdaSynchronously(const std::string &host, int port, const std::string &payload);

        /**
         * @brief Tries to find an idle instance
         *
         * @param lambda lambda entity to check
         * @return containerId of the idle instance
         */
        static std::string FindIdleInstance(Database::Entity::Lambda::Lambda &lambda);

        /**
         * lambda database connection
         */
        Database::LambdaDatabase &_lambdaDatabase;

        /**
         * Mutex
         */
        static Poco::Mutex _mutex;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_LAMBDA_SERVICE_H
