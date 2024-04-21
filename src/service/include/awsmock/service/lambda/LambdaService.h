//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDA_SERVICE_H
#define AWSMOCK_SERVICE_LAMBDA_SERVICE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/NotificationQueue.h>
#include <Poco/Notification.h>
#include <Poco/RecursiveDirectoryIterator.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/dto/s3/EventNotification.h>
#include <awsmock/dto/lambda/CreateFunctionRequest.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>
#include <awsmock/dto/lambda/CreateTagRequest.h>
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>
#include <awsmock/dto/lambda/DeleteTagsRequest.h>
#include <awsmock/dto/lambda/Function.h>
#include <awsmock/dto/lambda/GetFunctionResponse.h>
#include <awsmock/dto/lambda/ListFunctionResponse.h>
#include <awsmock/dto/lambda/ListTagsResponse.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/common/DockerService.h>
#include <awsmock/service/lambda/LambdaCreator.h>
#include <awsmock/service/lambda/LambdaExecutor.h>

namespace AwsMock::Service {

  /**
   * AWS lambda module. Handles all lambda related requests:
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
   * @author jens.vogt@opitz-consulting.com
   */
  class LambdaService {

  public:

    /**
     * Constructor
     *
     * @param configuration module configuration
     */
    explicit LambdaService(Core::Configuration &configuration);

    /**
     * Create lambda function
     *
     * @param request create lambda request
     * @return CreateFunctionResponse
     */
    Dto::Lambda::CreateFunctionResponse CreateFunction(Dto::Lambda::CreateFunctionRequest &request);

    /**
     * List lambda functions
     *
     * @param region AWS region name
     * @return CreateFunctionResponse
     */
    Dto::Lambda::ListFunctionResponse ListFunctions(const std::string &region);

    /**
     * Invoke lambda function
     *
     * @param eventNotification S3 event eventNotification
     * @param region AWS region
     * @param user user
     */
    void InvokeEventFunction(const Dto::S3::EventNotification &eventNotification, const std::string &region, const std::string &user);

    /**
     * Invoke SQS function.
     *
     * @param functionName lambda function name
     * @param payload SQS message
     * @param region AWS region
     * @param user user
     */
    void InvokeLambdaFunction(const std::string &functionName, const std::string &payload, const std::string &region, const std::string &user);

    /**
     * Create a new tag for a lambda functions.
     *
     * @param request lambda create tag request
     */
    void CreateTag(const Dto::Lambda::CreateTagRequest &request);

    /**
     * Returns a list of tags for a ARN.
     *
     * @param arn lambda function ARN
     * @return ListTagsResponse
     * @see AwsMock::Dto::Lambda::ListTagsResponse
     */
    Dto::Lambda::ListTagsResponse ListTags(const std::string &arn);

    /**
     * Gets a single lambda function
     *
     * @param region AWS region
     * @param name function name
     * @return GetFunctionResponse
     * @throws ServiceException
     * @see AwsMock::Dto::Lambda::GetFunctionResponse
     */
    Dto::Lambda::GetFunctionResponse GetFunction(const std::string &region, const std::string &name);

    /**
     * Delete lambda function
     *
     * <p>This method will also delete the corresponding container and images.
     *
     * @param request delete lambda request
     * @throws ServiceException
     */
    void DeleteFunction(Dto::Lambda::DeleteFunctionRequest &request);

    /**
     * Delete lambda function tags
     *
     * @param request delete tags request
     * @throws ServiceException
     */
    void DeleteTags(Dto::Lambda::DeleteTagsRequest &request);

  private:

    /**
     * Returns the URI for the invocation request.
     *
     * @param hostName host name of the docker instance
     * @param port lambda docker external port
     * @return URI of the invocation request
     */
    static std::string GetRequestUrl(const std::string &hostName, int port);

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
    Core::Configuration &_configuration;

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

} // namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_LAMBDA_SERVICE_H
