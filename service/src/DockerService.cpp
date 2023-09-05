//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/DockerService.h>

namespace AwsMock::Service {

    DockerService::DockerService(const Core::Configuration &configuration)
        : _logger(Poco::Logger::get("DockerService")), _configuration(configuration), _networkMode(NETWORK_DEFAULT_MODE) {

        // Get network mode
        _networkMode = _configuration.getString("awsmock.docker.network.mode", NETWORK_DEFAULT_MODE);
        log_debug_stream(_logger) << "Network mode: " << _networkMode << std::endl;
    }

    bool DockerService::ImageExists(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + "\"]}");
        std::string output = _curlUtils.SendRequest("GET", "http://localhost/images/json?filters=" + filters);
        log_trace_stream(_logger) << "List images request send to docker daemon, output: " << output << std::endl;

        Dto::Docker::ListImageResponse response;
        response.FromJson(output);

        if (response.imageList.empty()) {
            log_warning_stream(_logger) << "Docker image not found, name: " << name << ":" << tag << std::endl;
            return false;
        }

        log_debug_stream(_logger) << "Docker image found, name: " << name << ":" << tag << std::endl;
        return true;
    }

    Dto::Docker::Image DockerService::CreateImage(const std::string &name, const std::string &tag, const std::string &fromImage) {

        std::string queryString = Core::StringUtils::UrlEncode("name=" + name + "&tag=" + tag + "&fromImage=" + fromImage);
        std::string output = _curlUtils.SendRequest("POST", "http://localhost/images/create?" + queryString);
        log_trace_stream(_logger) << "Create image request send to docker daemon, output: " << output << std::endl;

        Dto::Docker::Image image;
        image.FromJson(output);

        log_debug_stream(_logger) << "Docker image created, name: " << name << ":" << tag << std::endl;
        return image;
    }

    Dto::Docker::Image DockerService::GetImageByName(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + "\"]}");
        std::string output = _curlUtils.SendRequest("GET", "http://localhost/images/json?filters=" + filters);
        log_debug_stream(_logger) << "List container request send to docker daemon, name: " << name << " tags: " << tag << std::endl;
        log_trace_stream(_logger) << "Response: " << Core::StringUtils::StripLineEndings(output) << std::endl;

        Dto::Docker::ListImageResponse response;
        response.FromJson(output);

        if (response.imageList.empty()) {
            log_warning_stream(_logger) << "Docker image not found, name: " << name << ":" << tag << std::endl;
            return {};
        }

        if (response.imageList.size() > 1) {
            log_warning_stream(_logger) << "More than one docker image found, name: " << name << ":" << tag << std::endl;
            return {};
        }
        return response.imageList[0];
    }

    void DockerService::BuildImage(const std::string &codeDir,
                                   const std::string &name,
                                   const std::string &tag,
                                   const std::string &handler,
                                   const std::string &runtime,
                                   long &fileSize,
                                   std::string &codeSha256,
                                   const std::vector<std::pair<std::string, std::string>> &environment) {
        log_debug_stream(_logger) << "Build image request, name: " << name << " tags: " << tag << " runtime: " << runtime << std::endl;

        std::string dockerFile = WriteDockerFile(codeDir, handler, runtime, environment);

        std::string imageFile = BuildImageFile(codeDir, name);
        fileSize = Core::FileUtils::FileSize(imageFile);
        codeSha256 = Core::Crypto::GetSha256FromFile(imageFile);

        std::string output = _curlUtils.SendFileRequest("POST", "http://localhost/build?t=" + name + ":" + tag + "&q=true", {}, imageFile);
        log_debug_stream(_logger) << "Docker image build, image: " << name << ":" << tag << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;
    }

    void DockerService::DeleteImage(const std::string &name, const std::string &tag) {
        std::string output = _curlUtils.SendRequest("DELETE", "/images/" + name + ":" + tag + "?force=true");
    }

    bool DockerService::ContainerExists(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + name + "\"]}");
        std::string output = _curlUtils.SendRequest("GET", "http://localhost/containers/json?filters=" + filters);
        log_debug_stream(_logger) << "List container request send to docker daemon" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        if (response.containerList.empty()) {
            log_warning_stream(_logger) << "Docker container not found, name: " << name << ":" << tag << std::endl;
            return false;
        }

        log_debug_stream(_logger) << "Docker container found, name: " << name << ":" << tag << std::endl;
        return true;
    }

    Dto::Docker::Container DockerService::GetContainerByName(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + std::string("/")+name + "\"]}");
        std::string output = _curlUtils.SendRequest("GET", "http://localhost/containers/json?all=true&filters=" + filters);
        log_debug_stream(_logger) << "List container request send to docker daemon" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        if (response.containerList.empty()) {
            log_warning_stream(_logger) << "Docker container not found, name: " << name << ":" << tag << std::endl;
            return {};
        }

        if (response.containerList.size() > 1) {
            log_warning_stream(_logger) << "More than one docker container found, name: " << name << ":" << tag << std::endl;
            return {};
        }

        log_debug_stream(_logger) << "Docker container found, name: " << name << ":" << tag << std::endl;
        return response.containerList[0];
    }

    Dto::Docker::Container DockerService::GetContainerById(const std::string &id) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"id":[")" + id +"\"]}");
        std::string output = _curlUtils.SendRequest("GET", "http://localhost/containers/json?filters=" + filters);
        log_debug_stream(_logger) << "List container request send to docker daemon" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;

        Dto::Docker::ListContainerResponse response;
        response.FromJson(output);

        if (response.containerList.empty()) {
            log_warning_stream(_logger) << "Docker container not found, id: " << id << std::endl;
            return {};
        }

        log_debug_stream(_logger) << "Docker container found, name: " << id << std::endl;
        return response.containerList[0];
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &tag, const std::vector<std::string> &environment) {

        int hostPort = GetHostPort();
        std::string containerPort = CONTAINER_PORT;
        std::string imageName = std::string(name) + ":" + tag;
        std::string domainName = std::string(name) + NETWORK_NAME;
        std::string networkMode = _networkMode;

        // Create the request
        Dto::Docker::CreateContainerRequest request = {
            .hostName=name,
            .domainName=domainName,
            .user="root",
            .image=imageName,
            .networkMode=networkMode,
            .environment=environment,
            .containerPort=containerPort,
            .hostPort=std::to_string(hostPort)
        };

        std::string jsonBody = request.ToJson();
        std::string output = _curlUtils.SendRequest("POST", "http://localhost/containers/create?name=" + name, jsonBody);
        log_debug_stream(_logger) << "Create container request send to docker daemon" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;

        Dto::Docker::CreateContainerResponse response = {.hostPort=hostPort};
        response.FromJson(output);

        return response;
    }

    std::string DockerService::StartDockerContainer(const std::string &id) {

        std::string output = _curlUtils.SendRequest("POST", "http://localhost/containers/" + id + "/start");
        log_debug_stream(_logger) << "Sending start container request" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;

        return output;
    }

    std::string DockerService::StartContainer(const Dto::Docker::Container &container) {
        return StartDockerContainer(container.id);
    }

    std::string DockerService::RestartDockerContainer(const std::string &id) {

        std::string output = _curlUtils.SendRequest("POST", "http://localhost/containers/" + id + "/restart");
        log_debug_stream(_logger) << "Sending restart container request" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;

        return output;
    }

    std::string DockerService::RestartContainer(const Dto::Docker::Container &container) {
        return RestartDockerContainer(container.id);
    }

    std::string DockerService::StopContainer(const Dto::Docker::Container &container) {

        std::string output = _curlUtils.SendRequest("POST", "http://localhost/containers/" + container.id + "/stop");
        log_debug_stream(_logger) << "Sending stop container request" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;

        return output;
    }

    void DockerService::DeleteContainer(const Dto::Docker::Container &container) {

        std::string output = _curlUtils.SendRequest("DELETE", "http://localhost/containers/" + container.id + "?force=true");
        log_debug_stream(_logger) << "Sending delete container request" << std::endl;
        log_trace_stream(_logger) << "Response: " << output << std::endl;
    }

    void DockerService::PruneContainers() {

        std::string output = _curlUtils.SendRequest("POST", "http://localhost/containers/prune");

        Dto::Docker::PruneContainerResponse response;
        response.FromJson(output);

        log_debug_stream(_logger) << "Prune containers, count: " << response.containersDeleted.size() << " spaceReclaimed: " << response.spaceReclaimed << std::endl;
    }

    std::string DockerService::WriteDockerFile(const std::string &codeDir, const std::string &handler, const std::string &runtime,
                                               const std::vector<std::pair<std::string, std::string>> &environment) {

        std::string dockerFilename = codeDir + "Dockerfile";

        // TODO: Fix environment
        std::ofstream ofs(dockerFilename);
        if (Core::StringUtils::EqualsIgnoreCase(runtime, "java11")) {
            ofs << "FROM public.ecr.aws/lambda/java:11" << std::endl;
            for (auto &env : environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        } else if (Core::StringUtils::EqualsIgnoreCase(runtime, "java17")) {
            ofs << "FROM public.ecr.aws/lambda/java:latest" << std::endl;
            for (auto &env : environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        } else if (Core::StringUtils::EqualsIgnoreCase(runtime, "provided.al2")) {
            ofs << "FROM public.ecr.aws/lambda/provided:al2" << std::endl;
            for (auto &env : environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY bootstrap ${LAMBDA_RUNTIME_DIR}" << std::endl;
            ofs << "RUN chmod 755 ${LAMBDA_RUNTIME_DIR}/bootstrap" << std::endl;
            ofs << "RUN mkdir -p ${LAMBDA_TASK_ROOT}/lib" << std::endl;
            ofs << "RUN mkdir -p ${LAMBDA_TASK_ROOT}/bin" << std::endl;
            ofs << "COPY bin/* ${LAMBDA_TASK_ROOT}/bin/" << std::endl;
            ofs << "COPY lib/* ${LAMBDA_TASK_ROOT}/lib/" << std::endl;
            ofs << "RUN chmod 755 ${LAMBDA_TASK_ROOT}/lib/ld-linux-x86-64.so.2" << std::endl;
            ofs << "CMD [ \"" + handler + "\" ]" << std::endl;
        } else if (Core::StringUtils::EqualsIgnoreCase(runtime, "provided.latest")) {
            ofs << "FROM public.ecr.aws/lambda/provided:latest" << std::endl;
            for (auto &env : environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY bootstrap ${LAMBDA_RUNTIME_DIR}" << std::endl;
            ofs << "RUN chmod 755 ${LAMBDA_RUNTIME_DIR}/bootstrap" << std::endl;
            ofs << "RUN mkdir -p ${LAMBDA_TASK_ROOT}/lib" << std::endl;
            ofs << "RUN mkdir -p ${LAMBDA_TASK_ROOT}/bin" << std::endl;
            ofs << "COPY bin/* ${LAMBDA_TASK_ROOT}/bin/" << std::endl;
            ofs << "COPY lib/* ${LAMBDA_TASK_ROOT}/lib/" << std::endl;
            ofs << "RUN chmod 755 ${LAMBDA_TASK_ROOT}/lib/ld-linux-x86-64.so.2" << std::endl;
            ofs << "CMD [ \"" + handler + "\" ]" << std::endl;
        }
        ofs.close();
        log_debug_stream(_logger) << "Dockerfile written, filename: " << dockerFilename << std::endl;

        return dockerFilename;
    }

    std::string DockerService::BuildImageFile(const std::string &codeDir, const std::string &functionName) {

        std::string tarFileName = codeDir + functionName + ".tgz";
        Core::TarUtils::TarDirectory(tarFileName, codeDir);
        log_debug_stream(_logger) << "Zipped TAR file written: " << tarFileName << std::endl;

        return tarFileName;
    }

    int DockerService::GetHostPort() {
        int port = Core::RandomUtils::NextInt(HOST_PORT_MIN, HOST_PORT_MAX);
        log_debug_stream(_logger) << "Assigned port: " << port << std::endl;
        return port;
    }
}