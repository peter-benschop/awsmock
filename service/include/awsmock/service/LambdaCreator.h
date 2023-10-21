//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDACREATOR_H
#define AWSMOCK_SERVICE_LAMBDACREATOR_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"
#include <Poco/Base64Decoder.h>
#include <Poco/NotificationQueue.h>
#include <Poco/StreamCopier.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/MetricService.h>
#include <awsmock/dto/lambda/CreateNotification.h>
#include <awsmock/entity/lambda/Lambda.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

  class LambdaCreator : public Poco::Runnable {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       * @param metricService monitoring service
       * @param createQueue lambda create notification queue
       */
      explicit LambdaCreator(Core::Configuration &configuration, Core::MetricService &metricService, Poco::NotificationQueue &createQueue);

      /**
       * Listens for invocation requests and send the invocation to the right port.
       */
      void run() override;

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      Core::Configuration &_configuration;

      /**
       * Metric service
       */
      Core::MetricService &_metricService;

      /**
       * Database connection
       */
      std::shared_ptr<Database::LambdaDatabase> _lambdaDatabase;

      /**
       * Data directory
       */
      std::string _dataDir;

      /**
       * Temp directory
       */
      std::string _tempDir;

      /**
       * Docker service
       */
      Service::DockerService _dockerService;

      /**
       * Lambda create notification queue
       */
      Poco::NotificationQueue &_createQueue;

      /**
       * Create new lambda function
       *
       * @param functionCode zipped and BASE64 encoded function code
       * @param functionId lambda function OID
       */
      void CreateLambdaFunction(const std::string &functionCode, const std::string &functionId);

      /**
       * Save the ZIP file and unpack it in a temporary folder
       *
       * @param zipFile Base64 encoded ZIP file
       * @param lambdaEntity lambda entity
       * @param dockerTag docker tag to use
       */
      void CreateDockerImage(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag);

      /**
       * Creates an new docker container, in case the container does not exists inside the docker daemon.
       *
       * @param entity lambda entity.
       * @param dockerTag docker tag.
       */
      void CreateDockerContainer(Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag);

      /**
       * Converts the lambda environment to a vector of string, which is needed by the docker API
       *
       * @param lambdaEnvironment lambda environment
       * @return vector of strings containing the runtime environment
       */
      std::vector<std::string> GetEnvironment(const Database::Entity::Lambda::Environment &lambdaEnvironment);

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
       * Returns a random host port in the range 32768 - 65536 for the host port of the docker container which is running the lambda function.
       *
       * @return random port between 32768 and 65536
       */
      static int GetHostPort();

  };

} //namespace AwsMock::Service

#endif // AWSMOCK_SERVICE_LAMBDACREATOR_H
