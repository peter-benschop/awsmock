//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

    DockerService::DockerService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("DockerService")), _configuration(configuration) {

        // Set console logger
        Core::Logger::SetDefaultConsoleLogger("DockerService");
        _logger.debug() << "Docker service initialized" << std::endl;
    }

    bool DockerService::ImageExists(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/images/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        _logger.debug() << "Header: " << Core::StringUtils::StripLineEndings(header) << std::endl;

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        _logger.trace() << "List images request send to docker daemon, output: " << output << std::endl;

        Dto::Docker::ListImageResponse response;
        response.FromJson(output);

        // Find image
        std::string imageName = name + ":" + tag;
        bool found = find_if(response.imageList.begin(), response.imageList.end(), [&imageName](const Dto::Docker::Image &image) {
          return find_if(image.repoTags.begin(), image.repoTags.end(), [&imageName](const std::string &repoTag) {
            return repoTag == imageName;
          }) != image.repoTags.end();
        }) != response.imageList.end();
        _logger.debug() << "Docker image found, result: " << (found ? "true" : "false") << std::endl;

        return found;
    }

    Dto::Docker::Image DockerService::GetImageByName(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/images/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        _logger.debug() << "Header: " << Core::StringUtils::StripLineEndings(header) << std::endl;

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        _logger.debug() << "List container request send to docker daemon, output: " << Core::StringUtils::StripLineEndings(output) << std::endl;

        Dto::Docker::ListImageResponse response;
        response.FromJson(output);

        // Find image
        std::string imageName = name + ":" + tag;
        for (const auto &image : response.imageList) {
            for (const auto &repoTag : image.repoTags) {
                if (repoTag == imageName)
                    return image;
            }
        }
        return {};
    }

    void DockerService::BuildImage(const std::string &codeDir, const std::string &name, const std::string &tag, const std::string &handler) {
        _logger.debug() << "Build image request, name: " << name << " tag: " << tag << " codeDir: " << codeDir << std::endl;

        std::string dockerFile = WriteDockerFile(codeDir, handler);

        std::string imageFile = BuildImageFile(codeDir, name);

        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/build?t=" + name + ":" + tag + "&q=true", TAR_CONTENT_TYPE,
                                                          Core::FileUtils::FileSize(imageFile));
        std::string output = Core::SystemUtils::SendFileViaDomainSocket(DOCKER_SOCKET, header, imageFile);
        _logger.debug() << "Docker image build, image: " << name << ":" << tag << std::endl;
        _logger.trace() << "Output: " << output << std::endl;
    }

    void DockerService::DeleteImage(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string
            header = Core::SystemUtils::SetHeader("DELETE", "/" + DOCKER_VERSION + "/images/" + name + ":" + tag + "?force=true", JSON_CONTENT_TYPE, jsonBody.size());

        _logger.debug() << "Sending delete image request" << std::endl;

        Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
    }

    bool DockerService::ContainerExists(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/containers/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        _logger.debug() << "Header: " << Core::StringUtils::StripLineEndings(header) << std::endl;

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        _logger.trace() << "List container request send to docker daemon, output: " << output << std::endl;

        // Remove unwanted characters
        std::stringstream sin, sout;
        sin << output << std::endl;
        Core::StreamFilter::XmlCharacterStreamFilter(sin, sout);

        std::string tmp = sout.str();

        Dto::Docker::ListContainerResponse response;
        response.FromJson(sout.str());

        // Find container
        std::string containerName = "/" + name;
        for (const auto &container : response.containerList) {
            for (const auto &n : container.names) {
                if (n == containerName) {
                    _logger.debug() << "Docker container found" << std::endl;
                    return true;
                }
            }
        }
        _logger.debug() << "Docker container not found" << std::endl;

        return false;
    }

    Dto::Docker::Container DockerService::GetContainerByName(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/containers/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        _logger.debug() << "Header: " << Core::StringUtils::StripLineEndings(header) << std::endl;

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        _logger.debug() << "List container request send to docker daemon, output: " << Core::StringUtils::StripLineEndings(output) << std::endl;

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        // Find container
        std::string containerName = "/" + name;
        for (const auto &container : response.containerList) {
            for (const auto &n : container.names) {
                if (n == containerName) {
                    _logger.debug() << "Docker container found" << std::endl;
                    return container;
                }
            }
        }
        _logger.debug() << "Docker container not found" << std::endl;

        return {};
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &tag) {

        int hostPort = GetHostPort();
        std::string containerPort = CONTAINER_PORT;
        std::string imageName = std::string(name) + IMAGE_TAG;
        std::string domainName = std::string(name) + NETWORK_NAME;
        std::vector<std::string> environment =
            {"AWS_ACCESS_KEY_ID=none", "AWS_SECRET_ACCESS_KEY=none", "JAVA_TOOL_OPTIONS=-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localstack"};

        // Create the request
        Dto::Docker::CreateContainerRequest request = {.hostName=name, .domainName=domainName, .user="root", .image=imageName, .environment=environment,
            .containerPort=containerPort, .hostPort=std::to_string(hostPort)};

        std::string jsonBody = request.ToJson();
        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/containers/create?name=" + name, JSON_CONTENT_TYPE, jsonBody.size());
        _logger.debug() << "Header: " << Core::StringUtils::StripLineEndings(header) << std::endl;

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        _logger.debug() << "Create container request send to docker daemon: " << Core::StringUtils::StripLineEndings(header) << std::endl;

        Dto::Docker::CreateContainerResponse response = {.hostPort=hostPort};
        response.FromJson(output);

        return response;
    }

    std::string DockerService::StartContainer(const std::string &id) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/containers/" + id + "/start", JSON_CONTENT_TYPE, jsonBody.size());

        _logger.debug() << "Sending start container request" << std::endl;

        return Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
    }

    std::string DockerService::StartContainer(const Dto::Docker::Container &container) {
        return StartContainer(container.id);
    }

    std::string DockerService::StopContainer(const Dto::Docker::Container &container) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/containers/" + container.id + "/start", JSON_CONTENT_TYPE, jsonBody.size());

        _logger.debug() << "Sending stop container request, payload: " << jsonBody << std::endl;

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        return output;
    }

    void DockerService::DeleteContainer(const Dto::Docker::Container &container) {

        std::string jsonBody = {};
        std::string
            header = Core::SystemUtils::SetHeader("DELETE", "/" + DOCKER_VERSION + "/containers/" + container.id + "?force=true", JSON_CONTENT_TYPE, jsonBody.size());

        _logger.debug() << "Sending delete container request" << std::endl;

        Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
    }

    std::string DockerService::WriteDockerFile(const std::string &codeDir, const std::string &handler) {

        std::string dockerFilename = codeDir + "Dockerfile";

        std::ofstream ofs(dockerFilename);
        ofs << "FROM public.ecr.aws/lambda/java:17" << std::endl;
        ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
        ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        _logger.debug() << "Dockerfile written, filename: " << dockerFilename << std::endl;

        return dockerFilename;
    }

    std::string DockerService::BuildImageFile(const std::string &codeDir, const std::string &functionName) {

        std::string tarFileName = codeDir + functionName + ".tgz";
        Core::TarUtils::TarDirectory(tarFileName, codeDir);
        _logger.debug() << "Gzip file written: " << tarFileName << std::endl;

        return tarFileName;
    }

    int DockerService::GetHostPort() {
        int port = Core::RandomUtils::NextInt(HOST_PORT_MIN, HOST_PORT_MAX);
        _logger.debug() << "Assigned port: " << port << std::endl;
        return port;
    }
}