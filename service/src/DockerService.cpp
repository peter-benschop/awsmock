//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

    DockerService::DockerService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("DockerService")), _configuration(configuration) {

        // Get version
        std::string output = _curlUtils.SendRequest("GET", "/version");
        log_debug_stream(_logger) << "Docker daemon version: " << output << std::endl;
    }

    bool DockerService::ImageExists(const std::string &name, const std::string &tag) {

        std::string output = _curlUtils.SendRequest("GET", "/" + DOCKER_VERSION + "/images/json?all=true");
        log_trace_stream(_logger) << "List images request send to docker daemon, output: " << output << std::endl;

        Dto::Docker::ListImageResponse response;
        response.FromJson(output);

        // Find image
        std::string imageName = name + ":" + tag;
        bool found = find_if(response.imageList.begin(), response.imageList.end(), [&imageName](const Dto::Docker::Image &image) {
          return find_if(image.repoTags.begin(), image.repoTags.end(), [&imageName](const std::string &repoTag) {
            return repoTag == imageName;
          }) != image.repoTags.end();
        }) != response.imageList.end();
        log_debug_stream(_logger) << "Docker image found, result: " << (found ? "true" : "false") << std::endl;

        return found;
    }

    Dto::Docker::Image DockerService::GetImageByName(const std::string &name, const std::string &tag) {

        std::string output = _curlUtils.SendRequest("GET", "/" + DOCKER_VERSION + "/images/json?all=true");
        log_debug_stream(_logger) << "List container request send to docker daemon, output: " << Core::StringUtils::StripLineEndings(output) << std::endl;

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

    void DockerService::BuildImage(const std::string &codeDir,
                                   const std::string &name,
                                   const std::string &tag,
                                   const std::string &handler,
                                   long &fileSize,
                                   std::string &codeSha256) {
        log_debug_stream(_logger) << "Build image request, name: " << name << " tag: " << tag << " codeDir: " << codeDir << std::endl;

        std::string dockerFile = WriteDockerFile(codeDir, handler);

        std::string imageFile = BuildImageFile(codeDir, name);
        fileSize = Core::FileUtils::FileSize(imageFile);
        codeSha256 = Core::Crypto::GetSha256FromFile(imageFile);

        std::string output = _curlUtils.SendFileRequest("POST", "/" + DOCKER_VERSION + "/build?t=" + name + ":" + tag + "&q=true", {}, imageFile);
        log_debug_stream(_logger) << "Docker image build, image: " << name << ":" << tag << std::endl;
        log_trace_stream(_logger) << "Output: " << output << std::endl;
    }

    void DockerService::DeleteImage(const std::string &name, const std::string &tag) {
        std::string output = _curlUtils.SendRequest("DELETE", "/" + DOCKER_VERSION + "/images/" + name + ":" + tag + "?force=true");
    }

    bool DockerService::ContainerExists(const std::string &name, const std::string &tag) {

        std::string output = _curlUtils.SendRequest("GET", "/" + DOCKER_VERSION + "/containers/json?all=true");
        log_trace_stream(_logger) << "List container request send to docker daemon, output: " << output << std::endl;

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        // Find container
        std::string containerName = "/" + name;
        for (const auto &container : response.containerList) {
            for (const auto &n : container.names) {
                if (n == containerName) {
                    log_debug_stream(_logger) << "Docker container found" << std::endl;
                    return true;
                }
            }
        }
        log_debug_stream(_logger) << "Docker container not found" << std::endl;

        return false;
    }

    Dto::Docker::Container DockerService::GetContainerByName(const std::string &name, const std::string &tag) {

        std::string output = _curlUtils.SendRequest("GET", "/" + DOCKER_VERSION + "/containers/json?all=true");
        log_debug_stream(_logger) << "List container request send to docker daemon, output: " << Core::StringUtils::StripLineEndings(output) << std::endl;

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        // Find container
        std::string containerName = "/" + name;
        for (const auto &container : response.containerList) {
            for (const auto &n : container.names) {
                if (n == containerName) {
                    log_debug_stream(_logger) << "Docker container found" << std::endl;
                    return container;
                }
            }
        }
        log_debug_stream(_logger) << "Docker container not found" << std::endl;

        return {};
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &tag) {

        int hostPort = GetHostPort();
        std::string containerPort = CONTAINER_PORT;
        std::string imageName = std::string(name) + ":" + tag;
        std::string domainName = std::string(name) + NETWORK_NAME;
        std::vector<std::string> environment =
            {"AWS_ACCESS_KEY_ID=none", "AWS_SECRET_ACCESS_KEY=none", "JAVA_TOOL_OPTIONS=-Duser.timezone=Europe/Berlin -Dspring.profiles.active=localstack"};

        // Create the request
        Dto::Docker::CreateContainerRequest request = {.hostName=name, .domainName=domainName, .user="root", .image=imageName, .environment=environment,
            .containerPort=containerPort, .hostPort=std::to_string(hostPort)};

        std::string jsonBody = request.ToJson();
        std::string output = _curlUtils.SendRequest("POST", "/" + DOCKER_VERSION + "/containers/create?name=" + name, jsonBody);
        log_debug_stream(_logger) << "Create container request send to docker daemon" << std::endl;

        Dto::Docker::CreateContainerResponse response = {.hostPort=hostPort};
        response.FromJson(output);

        return response;
    }

    std::string DockerService::StartContainer(const std::string &id) {

        std::string output = _curlUtils.SendRequest("POST", "/" + DOCKER_VERSION + "/containers/" + id + "/start");
        log_debug_stream(_logger) << "Sending start container request" << std::endl;

        return output;
    }

    std::string DockerService::StartContainer(const Dto::Docker::Container &container) {
        return StartContainer(container.id);
    }

    std::string DockerService::StopContainer(const Dto::Docker::Container &container) {

        std::string output = _curlUtils.SendRequest("POST", "/" + DOCKER_VERSION + "/containers/" + container.id + "/stop");
        log_debug_stream(_logger) << "Sending stop container request" << std::endl;
        return output;
    }

    void DockerService::DeleteContainer(const Dto::Docker::Container &container) {

        std::string output = _curlUtils.SendRequest("DELETE", "/" + DOCKER_VERSION + "/containers/" + container.id + "?force=true");
        log_debug_stream(_logger) << "Sending delete container request" << std::endl;
    }

    std::string DockerService::WriteDockerFile(const std::string &codeDir, const std::string &handler) {

        std::string dockerFilename = codeDir + "Dockerfile";

        std::ofstream ofs(dockerFilename);
        ofs << "FROM public.ecr.aws/lambda/java:17" << std::endl;
        ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
        ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        log_debug_stream(_logger) << "Dockerfile written, filename: " << dockerFilename << std::endl;

        return dockerFilename;
    }

    std::string DockerService::BuildImageFile(const std::string &codeDir, const std::string &functionName) {

        std::string tarFileName = codeDir + functionName + ".tgz";
        Core::TarUtils::TarDirectory(tarFileName, codeDir);
        log_debug_stream(_logger) << "Gzip file written: " << tarFileName << std::endl;

        return tarFileName;
    }

    int DockerService::GetHostPort() {
        int port = Core::RandomUtils::NextInt(HOST_PORT_MIN, HOST_PORT_MAX);
        log_debug_stream(_logger) << "Assigned port: " << port << std::endl;
        return port;
    }
}