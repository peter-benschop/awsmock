//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_DOCKERSERVICE_H
#define AWSMOCK_SERVICE_DOCKERSERVICE_H

// C++ standard includes
#include <string>
#include <fstream>
#include <iostream>

// Poco includes
#include <Poco/Logger.h>
#include <Poco/Net/HTTPResponse.h>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/Logger.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StreamFilter.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/core/RandomUtils.h>
#include <awsmock/core/StreamFilter.h>
#include <awsmock/core/CurlUtils.h>
#include <awsmock/dto/docker/CreateContainerRequest.h>
#include <awsmock/dto/docker/CreateContainerResponse.h>
#include <awsmock/dto/docker/ListImageResponse.h>
#include <awsmock/dto/docker/ListContainerResponse.h>
#include <awsmock/dto/docker/PruneContainerResponse.h>
#include <awsmock/dto/docker/VersionResponse.h>

#define DOCKER_SOCKET "/var/run/docker.sock"
#define NETWORK_NAME ".dockerhost.net"
#define HOST_PORT_MIN 32768
#define HOST_PORT_MAX 65536
#define CONTAINER_PORT "8080/tcp"
#define NETWORK_DEFAULT_MODE "bridge"

namespace AwsMock::Service {

    /**
     * The DockerService controls the connection to the docker daemon.
     *
     * <p>All docker related commands will be executed by the different methods.</p>
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
       * Creates a simple image
       *
       * @param name image name
       * @param tag image tags
       * @param imageCode code of the image
       */
      void CreateImage(const std::string &name, const std::string &tag, const std::string &imageCode);

      /**
       * Checks whether a image exists.
       *
       * @param name image name
       * @param tag image tags
       * @return true if image exists, otherwise false
       */
      bool ImageExists(const std::string &name, const std::string &tag);

      /**
       * Returns a image by name/tags.
       *
       * @param name container name
       * @param tag container tags
       * @return Image
       */
      Dto::Docker::Image GetImageByName(const std::string &name, const std::string &tag);

      /**
       * Build a docker image for a lambda
       *
       * @param codeDir code directory
       * @param name lambda function name, used as image name
       * @param tag image tags
       * @param handler lambda function handler
       * @param runtime lambda AWS runtime
       * @param fileSize size of the image file in bytes
       * @param codeSha256 SHA256 of the image file
       * @param environment runtime environment
       * @return CreateFunctionResponse
       */
      void BuildImage(const std::string &codeDir,
                      const std::string &name,
                      const std::string &tag,
                      const std::string &handler,
                      const std::string &runtime,
                      long &fileSize,
                      std::string &codeSha256,
                      const std::vector<std::pair<std::string, std::string>> &environment);

      /**
       * Delete an image by name/tags.
       *
       * @param name container name
       * @param tag container tags
       */
      void DeleteImage(const std::string &name, const std::string &tag);

      /**
       * Checks whether a container exists.
       *
       * @param name container name
       * @param tag container tags
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
       * Creates a container
       *
       * @param name image name
       * @param tag image tags
       * @param environment runtime environment variables
       * @param hostPort external port of the lambda
       * @return CreateContainerResponse
       */
      Dto::Docker::CreateContainerResponse CreateContainer(const std::string &name, const std::string &tag, const std::vector<std::string> &environment, int hostPort);

      /**
       * Returns a container by name/tags.
       *
       * @param name container name
       * @param tag container tags
       * @return Container
       */
      Dto::Docker::Container GetContainerByName(const std::string &name, const std::string &tag);

      /**
       * Returns a container by name/tags.
       *
       * @param id container ID
       * @return Container
       */
      Dto::Docker::Container GetContainerById(const std::string &id);

      /**
       * Start the container
       *
       * @param id container ID
       */
      void StartDockerContainer(const std::string &id);

      /**
       * Start the container
       *
       * @param container container
       */
      void StartContainer(const Dto::Docker::Container &container);

      /**
       * Restart the container
       *
       * @param id container ID
       */
      void RestartDockerContainer(const std::string &id);

      /**
       * Restart the container
       *
       * @param container container
       */
      void RestartContainer(const Dto::Docker::Container &container);

      /**
       * Stops the container
       *
       * @param container container
       */
      void StopContainer(const Dto::Docker::Container &container);

      /**
       * Deletes the container
       *
       * @param container container DTO
       */
      void DeleteContainer(const Dto::Docker::Container &container);

      /**
       * Deletes all stopped containers.
       */
      void PruneContainers();

    private:

      /**
       * Write the docker file.
       *
       * @param codeDir code directory
       * @param handler handler function
       * @param runtime docker image runtime
       * @param environment runtime environment
       * @return return docker file path
       */
      std::string WriteDockerFile(const std::string &codeDir, const std::string &handler, const std::string &runtime,
                                  const std::vector<std::pair<std::string, std::string>> &environment);

      /**
       * Write the compressed docker imagefile.
       *
       * @param codeDir code directory
       * @param name function name
       * @return return docker file path
       */
      std::string BuildImageFile(const std::string &codeDir, const std::string &name);

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Configuration
       */
      const Core::Configuration &_configuration;

      /**
       * Curl utilities
       */
      Core::CurlUtils _curlUtils;

      /**
       * Docker version
       */
      std::string _dockerVersion;

      /**
       * Docker network mode, bridge or host
       */
      std::string _networkMode;

      /**
       * Docker internal network name
       */
      std::string _networkName;

      /**
       * Docker internal network name
       */
      std::string _containerPort;
    };

} //namespace AwsMock::Service

#endif //AWSMOCK_SERVICE_LAMBDASERVICE_H
