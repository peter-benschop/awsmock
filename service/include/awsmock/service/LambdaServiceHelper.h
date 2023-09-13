//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_LAMBDASERVICEHELPER_H
#define AWSMOCK_SERVICE_LAMBDASERVICEHELPER_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/ActiveMethod.h"
#include "Poco/ActiveResult.h"
#include <Poco/Base64Decoder.h>
#include <Poco/StreamCopier.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/entity/lambda/Lambda.h>
#include <awsmock/repository/LambdaDatabase.h>
#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

    class LambdaServiceHelper {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit LambdaServiceHelper(const Core::Configuration &configuration);

      /**
       * Create new lambda function
       */
      Poco::ActiveMethod<void, std::pair<std::string, std::string>, LambdaServiceHelper> CreateLambdaFunction;

    private:

      /**
       * Logger
       */
      //Core::LogStream _logger;

      /**
       * Data directory
       */
      std::string _dataDir;

      /**
       * Temp directory
       */
      std::string _tempDir;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Docker service
       */
      Service::DockerService _dockerService;

      /**
       * Lambda database connection
       */
      // _lambdaDatabase;

      /**
       * Create a new lambda function.
       *
       * @param lambda pair of zip file and oid
       */
      void CreateLambdaFunctionImpl(const std::pair<std::string, std::string> &lambda);

      /**
       * Save the ZIP file and unpack it in a temporary folder
       *
       * @param zipFile Base64 encoded ZIP file
       * @param lambdaEntity lambda entity
       * @param dockerTag docker tag to use
       */
      void CreateDockerImage(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag, Core::LogStream &_logger);

      /**
       * Creates an new docker container, in case the container does not exists inside the docker daemon.
       *
       * @param entity lambda entity.
       * @param dockerTag docker tag.
       */
      void CreateDockerContainer(Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag, Core::LogStream &_logger);

      /**
       * Converts the lambda environment to a vector of string, which is needed by the docker API
       *
       * @param lambdaEnvironment lambda environment
       * @return vector of strings containing the runtime environment
       */
      std::vector<std::string> GetEnvironment(const Database::Entity::Lambda::Environment &lambdaEnvironment, Core::LogStream &_logger);

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
      std::string UnpackZipFile(const std::string &zipFile, const std::string &runtime, const std::string &fileName, Core::LogStream &_logger);

      /**
       * Returns a random host port in the range 32768 - 65536 for the host port of the docker container which is running the lambda function.
       *
       * @return random port between 32768 and 65536
       */
      int GetHostPort();

    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_LAMBDASERVICE_H
