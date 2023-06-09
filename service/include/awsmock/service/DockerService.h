//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_DOCKERSERVICE_H
#define AWSMOCK_SERVICE_DOCKERSERVICE_H

// C++ standard includes
#include <string>
#include <fstream>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/Logger.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/core/RandomUtils.h>
#include <awsmock/dto/docker/CreateContainerRequest.h>
#include <awsmock/dto/docker/CreateContainerResponse.h>
#include <awsmock/dto/docker/ListImageResponse.h>
#include <awsmock/dto/docker/ListContainerResponse.h>

#define DOCKER_VERSION std::string("v1.42")
#define DOCKER_SOCKET "/var/run/docker.sock"
#define TAR_CONTENT_TYPE std::string("application/x-tar")
#define JSON_CONTENT_TYPE std::string("application/json")
#define NETWORK_NAME ".dockerhost.net"
#define HOST_PORT_MIN 32768
#define HOST_PORT_MAX 65536
#define IMAGE_TAG ":latest"
#define CONTAINER_PORT "8080/tcp"

namespace AwsMock::Service {

    /**
     * Invokation:
     * <pre>
     * curl -XPOST "http://localhost:8080/2015-03-31/functions/function/invocations" -d '{}'
     * </pre>
     */
    class DockerService {

    public:

      /**
       * Constructor
       *
       * @param configuration service configuration
       */
      explicit DockerService(const Core::Configuration &configuration);

      /**
       * Checks whether a image exists.
       *
       * @param name image name
       * @param tag image tag
       * @return true if image exists, otherwise false
       */
      bool ImageExists(const std::string &name, const std::string &tag);

      /**
       * Returns a image by name/tag.
       *
       * @param name container name
       * @param tag container tag
       * @return Image
       */
      Dto::Docker::Image GetImageByName(const std::string &name, const std::string &tag);

      /**
       * Build a docker image for a lambda
       *
       * <p>Curl example:
       * <pre>
       * curl --unix-socket /var/run/docker.sock --data-binary '@docker.tar.gz' -XPOST -H "Content-Type: application/octet-stream" http://localhost/v1.42/build
       * </pre>
       * </p>
       *
       * @param codeDir code directory
       * @param name lambda function name, used as image name
       * @param tag image tag
       * @param handler lambda function handler
       * @return CreateFunctionResponse
       */
      void BuildImage(const std::string &codeDir, const std::string &name, const std::string &tag, const std::string &handler);

      /**
       * Checks whether a container exists.
       *
       * @param name container name
       * @param tag container tag
       * @return true if container exists, otherwise false
       */
      bool ContainerExists(const std::string &name, const std::string &tag);

      /**
       * List all docker images
       *
       * @return CreateFunctionResponse
       */
      // Dto::Docker::ListImageResponse ListImages();

      /**
       * Starts a container
       *
       * @param name image name
       * @param tag image tag
       * @return CreateContainerResponse
       */
      Dto::Docker::CreateContainerResponse CreateContainer(const std::string &name, const std::string &tag);

      /**
       * Returns a container by name/tag.
       *
       * @param name container name
       * @param tag container tag
       * @return Container
       */
      Dto::Docker::Container GetContainerByName(const std::string &name, const std::string &tag);

      /**
       * Start the container
       *
       * @param id container ID
       * @return output string
       */
      std::string StartContainer(const std::string &id);

      /**
       * Start the container
       *
       * @param container container
       * @return output string
       */
      std::string StartContainer(const Dto::Docker::Container &container);

      /**
       * Stops the container
       *
       * @param container container
       * @return output string
       */
      std::string StopContainer(const Dto::Docker::Container &container);

      /**
       * Invoke the lambda function
       *
       * @param container container
       * @return output string
       */
      //std::string InvokeLambda(const Dto::Lambda::InvokeLambdaRequest &container);

    private:

      /**
       * Initialize the service
       */
      void Initialize();

      /**
       * Write the docker file.
       *
       * @param codeDir code directory
       * @param handler handler function
       * @return return docker file path
       */
      std::string WriteDockerFile(const std::string &codeDir, const std::string &handler);

      /**
       * Write the compressed docker imagefile.
       *
       * @param codeDir code directory
       * @param name function name
       * @return return docker file path
       */
      std::string BuildImageFile(const std::string &codeDir, const std::string &name);

      /**
       * Returns a random host port in the range 32768 - 65536 for the host port of the docker container which is running the lambda function.
       *
       * @return random port between 32768 and 65536 as string
       */
      int GetHostPort();

      /**
       * Logger
       */
      Poco::Logger &_logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;
    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_LAMBDASERVICE_H
