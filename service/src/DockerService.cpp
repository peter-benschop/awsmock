//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

    DockerService::DockerService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("DockerService")), _configuration(configuration) {
        Initialize();
    }

    void DockerService::Initialize() {

        // Set console logger
        Core::Logger::SetDefaultConsoleLogger("LambdaService");
        poco_debug(_logger, "DOcker service initialized");
    }

    bool DockerService::ImageExists(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/images/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        poco_debug(_logger, "Header: " + header);

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        poco_trace(_logger, "List images request send to docker daemon, output: " + output);

        Dto::Docker::ListImageResponse response;
        response.FromJson(output);

        // Find image
        std::string imageName = name + ":" + tag;
        bool found = find_if(response.imageList.begin(), response.imageList.end(), [&imageName](const Dto::Docker::Image &image) {
          return find_if(image.repoTags.begin(), image.repoTags.end(), [&imageName](const std::string &repoTag) {
            return repoTag == imageName;
          }) != image.repoTags.end();
        }) != response.imageList.end();
        poco_debug(_logger, "Docker image found, result: " + std::string(found ? "true" : "false"));

        return found;
    }

    Dto::Docker::Image DockerService::GetImageByName(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/images/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        poco_debug(_logger, "Header: " + header);

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        poco_debug(_logger, "List container request send to docker daemon, output: " + output);

        Dto::Docker::ListImageResponse response;
        response.FromJson(output);

        // Find image
        std::string imageName = name + ":" + tag;
        for (const auto& image : response.imageList) {
            for (const auto& repoTag : image.repoTags) {
                if (repoTag == imageName)
                    return image;
            }
        }
        return {};
    }

    void DockerService::BuildImage(const std::string &codeDir, const std::string &name, const std::string &tag, const std::string &handler) {
        poco_debug(_logger, "Build image request, name: " + name + " tag: " + tag + " codeDir: " + codeDir);

        std::string dockerFile = WriteDockerFile(codeDir, handler);

        std::string imageFile = BuildImageFile(codeDir, name);

        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/build?t=" + name + ":" + tag + "&q=true", TAR_CONTENT_TYPE,
                                                          Core::FileUtils::FileSize(imageFile));
        std::string output = Core::SystemUtils::SendFileViaDomainSocket(DOCKER_SOCKET, header, imageFile);
        poco_debug(_logger, "Docker image build, image: " + name + ":" + tag);
        poco_trace(_logger, "Output: " + output);
    }

    bool DockerService::ContainerExists(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/containers/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        poco_debug(_logger, "Header: " + header);

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        poco_trace(_logger, "List container request send to docker daemon, output: " + output);

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        // Find container
        std::string containerName = "/" + name;
        for (const auto &container : response.containerList) {
            for (const auto &n : container.names) {
                if (n == containerName) {
                    poco_debug(_logger, "Docker container found");
                    return true;
                }
            }
        }
        poco_debug(_logger, "Docker container not found");

        return false;
    }

    Dto::Docker::Container DockerService::GetContainerByName(const std::string &name, const std::string &tag) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("GET", "/" + DOCKER_VERSION + "/containers/json?all=true", JSON_CONTENT_TYPE, jsonBody.size());
        poco_debug(_logger, "Header: " + header);

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        poco_debug(_logger, "List container request send to docker daemon, output: " + output);

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        // Find container
        std::string containerName = "/" + name;
        for (const auto &container : response.containerList) {
            for (const auto &n : container.names) {
                if (n == containerName) {
                    poco_debug(_logger, "Docker container found");
                    return container;
                }
            }
        }
        poco_debug(_logger, "Docker container not found");

        return {};
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &tag) {

        Dto::Docker::CreateContainerRequest request = {.hostName=name, .domainName=name + ".dockerhost.net", .user="root", .image=name + ":" + tag};

        std::string jsonBody = request.ToJson();
        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/containers/create?name=" + name, JSON_CONTENT_TYPE, jsonBody.size());
        poco_debug(_logger, "Header: " + header);

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        poco_debug(_logger, "Create container request send to docker daemon: " + header);

        Dto::Docker::CreateContainerResponse response;
        response.FromJson(output);

        return response;
    }

    std::string DockerService::StartContainer(const std::string &id) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/containers/" + id + "/start", JSON_CONTENT_TYPE, jsonBody.size());

        return Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
    }

    std::string DockerService::StartContainer(const Dto::Docker::Container &container) {
        return StartContainer(container.id);
    }

    std::string DockerService::StopContainer(const Dto::Docker::Container &container) {

        std::string jsonBody = {};
        std::string header = Core::SystemUtils::SetHeader("POST", "/" + DOCKER_VERSION + "/containers/" + container.id + "/start", JSON_CONTENT_TYPE, jsonBody.size());

        std::string output = Core::SystemUtils::SendMessageViaDomainSocket(DOCKER_SOCKET, header, jsonBody);
        return output;
    }

    std::string DockerService::WriteDockerFile(const std::string &codeDir, const std::string &handler) {

        std::string dockerFilename = codeDir + "Dockerfile";

        std::ofstream ofs(dockerFilename);
        ofs << "FROM public.ecr.aws/lambda/java:17" << std::endl;
        ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
        ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        poco_debug(_logger, "Dockerfile written, filename: " + dockerFilename);

        return dockerFilename;
    }

    std::string DockerService::BuildImageFile(const std::string &codeDir, const std::string &functionName) {

        std::string tarFileName = codeDir + functionName + ".tgz";
        Core::TarUtils::TarDirectory(tarFileName, codeDir);
        poco_debug(_logger, "Gzip file written: " + tarFileName);

        return tarFileName;
    }

}