//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDASERVICE_H
#define AWSMOCK_SERVICE_LAMBDASERVICE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/RecursiveDirectoryIterator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/db/LambdaDatabase.h>
#include <awsmock/db/S3Database.h>
#include <awsmock/dto/s3/EventNotification.h>
#include <awsmock/dto/lambda/CreateFunctionResponse.h>
#include <awsmock/dto/lambda/CreateFunctionRequest.h>
#include <awsmock/dto/lambda/DeleteFunctionRequest.h>
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
      Dto::Lambda::CreateFunctionResponse CreateFunctionConfiguration(Dto::Lambda::CreateFunctionRequest &request);

      /**
       * Invoke lambda function
       *
       * @param eventNotification S3 event eventNotification
       */
      void InvokeEventFunction(const Dto::S3::EventNotification &eventNotification);

      /**
       * Delete lambda function
       *
       * <p>This method will also delete the corresponding container and images.
       *
       * @param request create lambda request
       * @return CreateFunctionResponse
       * @throws ServiceException
       */
      void DeleteFunction(Dto::Lambda::DeleteFunctionRequest &request);

    private:

      /**
       * Initialize the service
       */
      void Initialize();

      /**
       * Unpack the provided ZIP file.
       *
       * <p>Needed only when the Lambda function is provided as zipped request body.</p>
       *
       * @param zipFile Base64 encoded zip file.
       * @return code directory
       */
      std::string UnpackZipFile(const std::string &zipFile);

      /**
       * Send the invocation request via HTTP to the lambda function.
       *
       * @param port host port of the docker image, running the lambda function.
       * @param body message body containing the S3 event in JSON representation.
       */
      void SendInvocationRequest(int port, const std::string &body);

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Data directory
       */
      std::string _dataDir;

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
      std::unique_ptr<Database::LambdaDatabase> _lambdaDatabase;

      /**
       * S3 database connection
       */
      std::unique_ptr<Database::S3Database> _s3Database;

      /**
       * Database connection
       */
      std::unique_ptr<Service::DockerService> _dockerService;
    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_LAMBDASERVICE_H
