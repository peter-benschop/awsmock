//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDASERVICE_H
#define AWSMOCK_SERVICE_LAMBDASERVICE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/NotificationQueue.h>
#include <Poco/RecursiveDirectoryIterator.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/MetricServiceTimer.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/dto/s3/EventNotification.h>
#include <awsmock/dto/lambda/CreateFunctionRequest.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>
#include <awsmock/dto/lambda/CreateNotification.h>
#include <awsmock/dto/lambda/CreateTagRequest.h>
#include <awsmock/dto/lambda/InvocationNotification.h>
#include <awsmock/dto/lambda/ListFunctionResponse.h>
#include <awsmock/dto/lambda/ListTagsResponse.h>
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>
#include <awsmock/dto/lambda/DeleteTagsRequest.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/DockerService.h>

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
   * As the AWS lambda runtime environment (RIE) cannot handle several concurrent requests, the lambda invocation requests are queued and are send sequentially. THe incoming requests are posted to a Poco notification center. The target of the notification
   * is the LambdaExecutor (@see AwsMock::Worker::LambdaExecutor).
   *
   * @author jens.vogt@opitz-consulting.com
   */
  class LambdaService {

    public:

      /**
       * Constructor
       *
       * @param configuration module configuration
       * @param metricService aws-mock monitoring module
       * @param createQueue create notification queue
       * @param invokeQueue invoke notification queue
       */
      explicit LambdaService(const Core::Configuration &configuration, Core::MetricService &metricService, Poco::NotificationQueue &createQueue, Poco::NotificationQueue &invokeQueue);

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
       */
      Dto::Lambda::ListTagsResponse ListTags(const std::string &arn);

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
       * Logger
       */
      Core::LogStream _logger;

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
       * Monitoring
       */
      Core::MetricService &_metricService;

      /**
       * Create notification center
       */
      Poco::NotificationQueue &_createQueue;

      /**
       * Invoke notification center
       */
      Poco::NotificationQueue &_invokeQueue;

      /**
       * lambda database connection
       */
      std::shared_ptr<Database::LambdaDatabase> _lambdaDatabase;

      /**
       * S3 database connection
       */
      std::shared_ptr<Database::S3Database> _s3Database;

      /**
       * Docker module
       */
      std::shared_ptr<Service::DockerService> _dockerService;
  };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_LAMBDASERVICE_H
