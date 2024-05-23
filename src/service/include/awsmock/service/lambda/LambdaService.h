//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_SERVICE_H
#define AWSMOCK_SERVICE_LAMBDA_SERVICE_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Notification.h>
#include <Poco/NotificationQueue.h>
#include <Poco/RecursiveDirectoryIterator.h>
#include <Poco/StreamCopier.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/core/TaskPool.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/core/monitoring/MetricService.h>
#include <awsmock/dto/lambda/AccountSettingsResponse.h>
#include <awsmock/dto/lambda/CreateFunctionRequest.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>
#include <awsmock/dto/lambda/CreateTagRequest.h>
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>
#include <awsmock/dto/lambda/DeleteTagsRequest.h>
#include <awsmock/dto/lambda/GetFunctionResponse.h>
#include <awsmock/dto/lambda/ListFunctionResponse.h>
#include <awsmock/dto/lambda/ListTagsResponse.h>
#include <awsmock/dto/lambda/mapper/Mapper.h>
#include <awsmock/dto/lambda/model/Function.h>
#include <awsmock/dto/s3/model/EventNotification.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/common/DockerService.h>
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
         *
         * @param configuration module configuration
         */
        explicit LambdaService(const Core::Configuration &configuration);

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
         * @brief Invoke lambda function
         *
         * @param eventNotification S3 event eventNotification
         * @param region AWS region
         * @param user user
         */
        void InvokeEventFunction(const Dto::S3::EventNotification &eventNotification, const std::string &region, const std::string &user);

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
         * @brief Delete lambda function
         *
         * This method will also delete the corresponding container and images.
         *
         * @param request delete lambda request
         * @throws ServiceException
         */
        void DeleteFunction(Dto::Lambda::DeleteFunctionRequest &request);

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
         * @param functionName name of the function
         * @param payload payload for the function
         * @param url lambda docker image URL
         * @return output from lambda invocation call
         */
        static std::string InvokeLambdaSynchronously(const std::string &url, const std::string &payload);

        /**
         * Data directory
         */
        std::string _dataDir;

        /**
         * lambda directory
         */
        std::string _lambdaDir;

        /**
         * Temp directory
         */
        std::string _tempDir;

        /**
         * AWS region
         */
        std::string _region;

        /**
         * AWS account ID
         */
        std::string _accountId;

        /**
         * Configuration
         */
        const Core::Configuration &_configuration;

        /**
         * lambda database connection
         */
        Database::LambdaDatabase &_lambdaDatabase;

        /**
         * S3 database connection
         */
        Database::S3Database &_s3Database;

        /**
         * Docker module
         */
        std::shared_ptr<Service::DockerService> _dockerService;

        /**
         * Mutex
         */
        static Poco::Mutex _mutex;
    };

    /**
     * @brief Returns the URI for the invocation request.
     *
     * @param hostName host name of the docker instance
     * @param port lambda docker external port
     * @return URI of the invocation request
     */
    inline static std::string GetRequestUrl(const std::string &hostName, int port) {
        if (hostName.empty()) {
            return "http://localhost:" + std::to_string(port) + "/2015-03-31/functions/function/invocations";
        }
        return "http://" + hostName + ":" + std::to_string(port) + "/2015-03-31/functions/function/invocations";
    }

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_LAMBDA_SERVICE_H
