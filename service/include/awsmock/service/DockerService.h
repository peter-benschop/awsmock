//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_DOCKERSERVICE_H
#define AWSMOCK_SERVICE_DOCKERSERVICE_H

// C++ standard includes
#include <string>
#include <curl/curl.h>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/dto/docker/ListImageResponse.h>

#define DOCKER_VERSION "1.42"

namespace AwsMock::Service {

    struct buffer {
      char *data;
      size_t size;
    };

    struct docker {
      CURL *curl;
      char *version;
      struct buffer *buffer;
    };

    typedef struct docker DOCKER;

    class DockerService {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit DockerService(const Core::Configuration &configuration);

      /**
       * List all docker images
       *
       * @return CreateFunctionResponse
       */
      Dto::Docker::ListImageResponse ListImages();

      /**
       * List all docker images
       *
       * @param tarFile tar file
       * @param tag image tag
       * @return CreateFunctionResponse
       */
      long BuildImage(const std::string &tarFile, const std::string &tag);

    private:

      /**
       * Initialize the service
       */
      void Initialize();

      /**
       * @param url URL to send to
       * @param httpStatus HTTP status
       * @return curl status code
       */
      CURLcode SendRequest(char *url, long *httpStatus);

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      DOCKER *client;
    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_LAMBDASERVICE_H
