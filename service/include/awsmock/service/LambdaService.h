//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDASERVICE_H
#define AWSMOCK_SERVICE_LAMBDASERVICE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/RecursiveDirectoryIterator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/dto/s3/EventNotification.h>
#include <awsmock/dto/lambda/CreateFunctionRequest.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>
#include <awsmock/dto/lambda/CreateTagRequest.h>
#include <awsmock/dto/lambda/ListFunctionResponse.h>
#include <awsmock/dto/lambda/ListTagsResponse.h>
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>
#include <awsmock/dto/lambda/DeleteTagsRequest.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/repository/S3Database.h>
#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

    class LambdaService {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit LambdaService(const Core::Configuration &configuration);

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
       */
      void InvokeEventFunction(const Dto::S3::EventNotification &eventNotification);

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
       * Creates an new image, in case the image does not exists inside the docker daemon.
       *
       * <p>It uses the docker service to actually create the image. The image size and the SHA256 are returned
       * by the docker service.<p>
       *
       * @param request create function request.
       * @param entity lambda entity.
       * @param dockerTag docker tag to use
       */
      void CreateDockerImage(const Dto::Lambda::CreateFunctionRequest &request, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag);

      /**
       * Creates an new docker container, in case the container does not exists inside the docker daemon.
       *
       * @param request create function request.
       * @param entity lambda entity.
       * @param dockerTag docker tag.
       */
      void CreateDockerContainer(const Dto::Lambda::CreateFunctionRequest &request, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag);

      /**
       * Unpack the provided ZIP file.
       *
       * <p>Needed only when the Lambda function is provided as zipped request body.</p>
       *
       * @param zipFile Base64 encoded zip file.
       * @param runtime AWS lambda runtime name
       * @param fileName filename of the Base64 encoded and zipped code file
       * @return code directory
       */
      std::string UnpackZipFile(const std::string &zipFile, const std::string &runtime, const std::string &fileName);

      /**
       * Converts the lambda environment to a vector of string, which is needed by the docker API
       *
       * @param lambdaEnvironment lambda environment
       * @return vector of strings containing the runtime environment
       */
      std::vector<std::string> GetEnvironment(const Database::Entity::Lambda::Environment &lambdaEnvironment);

      /**
       * Start the lambda docker container.
       *
       * @param lambdaEntity lambda entity.
       */
      void CreateSwarm(Database::Entity::Lambda::Lambda &lambdaEntity);

      /**
       * Send the invocation request via HTTP to the lambda function.
       *
       * @param port host port of the docker image, running the lambda function.
       * @param body message body containing the S3 event in JSON representation.
       */
      void SendInvocationRequest(int port, const std::string &body);

      /**
       * Returns a random host port in the range 32768 - 65536 for the host port of the docker container which is running the lambda function.
       *
       * @return random port between 32768 and 65536
       */
      int GetHostPort();

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Data directory
       */
      std::string _dataDir;

      /**
       * Lambda directory
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
       * Lambda database connection
       */
      std::shared_ptr<Database::LambdaDatabase> _lambdaDatabase;

      /**
       * S3 database connection
       */
      std::shared_ptr<Database::S3Database> _s3Database;

      /**
       * Database connection
       */
      std::shared_ptr<Service::DockerService> _dockerService;
    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_LAMBDASERVICE_H
