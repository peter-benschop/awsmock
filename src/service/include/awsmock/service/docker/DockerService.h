//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_SERVICE_DOCKER_SERVICE_H
#define AWSMOCK_SERVICE_DOCKER_SERVICE_H

// C++ standard includes
#include <fstream>
#include <iostream>
#include <string>

// Boost includes
#include <boost/filesystem/path.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

// AwsMock includes
#include <awsmock/core/AwsUtils.h>
#include <awsmock/core/CryptoUtils.h>
#include <awsmock/core/DomainSocket.h>
#include <awsmock/core/DomainSocketResult.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/RandomUtils.h>
#include <awsmock/core/StreamFilter.h>
#include <awsmock/core/SystemUtils.h>
#include <awsmock/core/TarUtils.h>
#include <awsmock/core/config/Configuration.h>
#include <awsmock/core/exception/ServiceException.h>
#include <awsmock/dto/docker/CreateContainerRequest.h>
#include <awsmock/dto/docker/CreateContainerResponse.h>
#include <awsmock/dto/docker/ListContainerResponse.h>
#include <awsmock/dto/docker/ListImageResponse.h>
#include <awsmock/dto/docker/PruneContainerResponse.h>
#include <awsmock/dto/docker/VersionResponse.h>

#define DOCKER_SOCKET "/var/run/docker.sock"
#define NETWORK_NAME ".dockerhost.net"
#define HOST_PORT_MIN 32768
#define HOST_PORT_MAX 65536
#define CONTAINER_PORT "8080/tcp"
#define NETWORK_DEFAULT_MODE "bridge"

namespace AwsMock::Service {

    namespace http = boost::beast::http;
    using namespace std::chrono_literals;

    /**
     * @brief Controls the connection to the docker daemon using a UNIX Domain socket.
     *
     * All docker related commands will be executed by the different methods. This means create, delete, starting, stopping the docker images for DynamoDB, Lambdas etc.
     *
     * @par Linux
     * On Linux the service is using the docker REST API available at the UNIX domain socket. Depending on your Linux distribution the docker socket is located under
     * different directory normally its: <i>/var/run/docker.sock</i> (Debian, Ubuntu). If you lLinux distribution is using another location set the full path to the
     * docker socket in the awsmock configuration file.
     *
     * @par Windows
     * On Windows the HTTP port will be used to communicate with the docker daemon. Usually `http://localhost:2375`, if the port is not accessible make the port accessible
     * in Docker Desktop for Windows.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class DockerService {

      public:

        /**
         * @brief Constructor
         */
        explicit DockerService();

        /**
         * @brief Singleton instance
         */
        static DockerService &instance() {
            static DockerService dockerService;
            return dockerService;
        }

        /**
         * @brief Creates a simple image
         *
         * @param name image name
         * @param tag image tags
         * @param imageCode code of the image
         */
        void CreateImage(const std::string &name, const std::string &tag, const std::string &imageCode);

        /**
         * @brief Checks whether a image exists.
         *
         * @param name image name
         * @param tag image tags
         * @return true if image exists, otherwise false
         */
        bool ImageExists(const std::string &name, const std::string &tag);

        /**
         * @brief Returns a image by name/tags.
         *
         * @param name container name
         * @param tag container tags
         * @param locked if true is already locked
         * @return Image
         */
        Dto::Docker::Image GetImageByName(const std::string &name, const std::string &tag, bool locked = false);

        /**
         * @brief Build a docker image for a lambda
         *
         * @param codeDir code directory
         * @param name lambda function name, used as image name
         * @param tag image tags
         * @param handler lambda function handler
         * @param runtime lambda AWS runtime
         * @param environment runtime environment
         * @return file size in bytes
         */
        std::string BuildImage(const std::string &codeDir, const std::string &name, const std::string &tag, const std::string &handler, const std::string &runtime, const std::map<std::string, std::string> &environment);

        /**
         * @brief Build a docker image from a docker file
         *
         * @param name lambda function name, used as image name
         * @param tag image tags
         * @param dockerFile docker file
         * @return file size in bytes
         */
        std::string BuildImage(const std::string &name, const std::string &tag, const std::string &dockerFile);

        /**
         * @brief Delete an image by name/tags.
         *
         * @param id image ID
         */
        void DeleteImage(const std::string &id);

        /**
         * @brief Checks whether a container exists.
         *
         * @param name container name
         * @param tag container tags
         * @return true if container exists, otherwise false
         */
        bool ContainerExists(const std::string &name, const std::string &tag);

        /**
         * @brief List all docker images, with the given name and different tags.
         *
         * @param name name of the image
         * @return ListImageResponse
         */
        Dto::Docker::ListImageResponse ListImages(const std::string &name);

        /**
         * @brief Creates a container
         *
         * @param name image name
         * @param instanceName name of the instance
         * @param tag image tags
         * @param environment runtime environment variables
         * @param hostPort external port of the lambda
         * @return CreateContainerResponse
         */
        Dto::Docker::CreateContainerResponse CreateContainer(const std::string &name, const std::string &instanceName, const std::string &tag, const std::vector<std::string> &environment, int hostPort);

        /**
         * @brief Creates a container for a predefined image.
         *
         * @param name image name
         * @param tag image tags
         * @param hostPort external port of the container
         * @param containerPort internal port of the container
         * @return CreateContainerResponse
         */
        Dto::Docker::CreateContainerResponse CreateContainer(const std::string &name, const std::string &tag, int hostPort, int containerPort);

        /**
         * @brief Returns a container by name/tags.
         *
         * @param name container name
         * @param tag container tags
         * @return Container
         */
        Dto::Docker::Container GetFirstContainerByImageName(const std::string &name, const std::string &tag);

        /**
         * @brief Returns a container by ID.
         *
         * @param containerId container ID
         * @return Container
         */
        Dto::Docker::Container GetContainerById(const std::string &containerId);

        /**
         * @brief Start the container
         *
         * @param id container ID
         */
        void StartDockerContainer(const std::string &id);

        /**
         * @brief Restart the container
         *
         * @param id container ID
         */
        void RestartDockerContainer(const std::string &id);

        /**
         * @brief Restart the container
         *
         * @param container container
         */
        void RestartContainer(const Dto::Docker::Container &container);

        /**
         * @brief Stops the container
         *
         * @param container container
         */
        void StopContainer(const Dto::Docker::Container &container);

        /**
         * @brief Stops the container by ID
         *
         * @param id container ID
         */
        void StopContainer(const std::string &id);

        /**
         * @brief Deletes the container
         *
         * @param container container DTO
         */
        void DeleteContainer(const Dto::Docker::Container &container);

        /**
         * @brief Deletes the container by ID
         *
         * @param id container ID
         */
        void DeleteContainer(const std::string &id);

        /**
         * @brief Deletes all stopped containers.
         */
        void PruneContainers();

      private:

        /**
         * @brief Write the docker file.
         *
         * @param codeDir code directory
         * @param handler handler function
         * @param runtime docker image runtime
         * @param environment runtime environment
         * @return return docker file path
         */
        static std::string WriteDockerFile(const std::string &codeDir, const std::string &handler, const std::string &runtime, const std::map<std::string, std::string> &environment);

        /**
         * @brief Write the compressed docker image file.
         *
         * @param codeDir code directory
         * @param name function name
         * @return return docker file path
         */
        static std::string BuildImageFile(const std::string &codeDir, const std::string &name);

        /**
         * Docker version
         */
        std::string _dockerVersion;

        /**
         * Docker internal network name
         */
        std::string _networkName;

        /**
         * Docker internal network name
         */
        std::string _containerPort;

        /**
         * Docker listening socket
         */
        std::string _dockerSocketPath;

        /**
         * Docker listening socket
         */
        std::shared_ptr<Core::DomainSocket> _domainSocket;

        /**
         * Supported runtimes
         */
        static std::map<std::string, std::string> _supportedRuntimes;

        /**
         * Mutex
         */
        static boost::mutex _dockerServiceMutex;
    };

}// namespace AwsMock::Service

#endif// AWSMOCK_SERVICE_DOCKER_SERVICE_H
