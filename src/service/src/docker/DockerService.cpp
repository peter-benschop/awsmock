//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/common/DockerService.h>

namespace AwsMock::Service {

    DockerService::DockerService() : _networkMode(NETWORK_DEFAULT_MODE) {

        // Get network mode
        Core::Configuration &_configuration = Core::Configuration::instance();
        _networkMode = _configuration.getString("awsmock.docker.network.mode", NETWORK_DEFAULT_MODE);
        _networkName = _configuration.getString("awsmock.docker.network.name", NETWORK_NAME);
        _containerPort = _configuration.getString("awsmock.docker.container.port", CONTAINER_PORT);

        log_trace << "Network mode: " << _networkMode;
    }

    bool DockerService::ImageExists(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + ":" + tag + "\"]}");
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("GET", "http://localhost/images/json?all=true&filters=" + filters);
        log_trace << "List images request send to docker daemon, output: " << curlResponse.ToString();

        if (curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {

            Dto::Docker::ListImageResponse response(curlResponse.output);
            log_debug << "Docker image found, name: " << name << ":" << tag << " exists: " << (response.imageList.empty() ? "false" : "true");
            return !response.imageList.empty();
        }
        return false;
    }

    void DockerService::CreateImage(const std::string &name, const std::string &tag, const std::string &fromImage) {

        Core::CurlResponse
                curlResponse = _curlUtils.SendUnixSocketRequest("POST", "http://localhost/images/create?name=" + name + "&tag=" + tag + "&fromImage=" + fromImage);
        log_trace << "Create image request send to docker daemon, output: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "Docker image create failed, state: " << curlResponse.statusCode;
        } else {
            log_debug << "Docker image created, name: " << name << ":" << tag;
        }
        Dto::Docker::Image image = GetImageByName(name, tag);
        while (GetImageByName(name, tag).size == 0) {
            Poco::Thread::sleep(500);
        }
    }

    Dto::Docker::Image DockerService::GetImageByName(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + "\"]}");
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("GET", "http://localhost/images/json?all=true&filters=" + filters);
        log_debug << "List container request send to docker daemon, name: " << name << " tags: " << tag;
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {

            Dto::Docker::ListImageResponse response(curlResponse.output);
            if (response.imageList.empty()) {
                log_warning << "Docker image not found, name: " << name << ":" << tag;
                return {};
            }

            if (response.imageList.size() > 1) {
                log_warning << "More than one docker image found, name: " << name << ":" << tag;
                return {};
            }
            return response.imageList[0];
        }
        return {};
    }

    std::string DockerService::BuildImage(const std::string &codeDir, const std::string &name, const std::string &tag, const std::string &handler, const std::string &runtime, const std::map<std::string, std::string> &environment) {
        log_debug << "Build image request, name: " << name << " tags: " << tag << " runtime: " << runtime;

        std::string dockerFile = WriteDockerFile(codeDir, handler, runtime, environment);
        std::string imageFile = BuildImageFile(codeDir, name);

        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketFileRequest("POST", "http://localhost/build?t=" + name + ":" + tag, {}, imageFile);
        log_debug << "Docker image build, image: " << name << ":" << tag;
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "Build image failed, state: " << curlResponse.statusCode << " reason: " << curlResponse.output;
        }
        return imageFile;
    }

    std::string DockerService::BuildImage(const std::string &name, const std::string &tag, const std::string &dockerFile) {
        log_debug << "Build image request, name: " << name << " tags: " << tag;

        // Write docker file
        std::string codeDir = Core::DirUtils::CreateTempDir();
        std::string fileName = codeDir + Poco::Path::separator() + "Dockerfile";
        std::ofstream ofs(fileName);
        ofs << dockerFile;
        ofs.close();
        std::string imageFile = BuildImageFile(codeDir, name);

        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketFileRequest("POST", "http://localhost/build?t=" + name + ":" + tag /*+ "&q=true"*/, {}, imageFile);
        log_debug << "Docker image build, image: " << name << ":" << tag;
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "Build image failed, state: " << curlResponse.statusCode;
        }
        return dockerFile;
    }

    void DockerService::DeleteImage(const std::string &id) {
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("DELETE", "http://localhost/images/" + id + "?force=true");
        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "Delete image failed, state: " << curlResponse.statusCode;
        }
    }

    bool DockerService::ContainerExists(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + std::string("/") + name + "\"]}");
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("GET", "http://localhost/containers/json?all=true&filters=" + filters);
        log_debug << "List container request send to docker daemon";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_warning << "Docker container exists failed, state: " << curlResponse.statusCode;
            return false;
        }

        Dto::Docker::ListContainerResponse response(curlResponse.output);
        log_debug << "Docker image found, name: " << name << ":" << tag << " " << (response.containerList.empty() ? "true" : "false");
        return !response.containerList.empty();
    }

    Dto::Docker::Container DockerService::GetContainerByName(const std::string &name, const std::string &tag) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + std::string("/") + name + "\"]}");
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("GET", "http://localhost/containers/json?all=true&filters=" + filters);
        log_debug << "List container request send to docker daemon";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_warning << "Get docker container by name failed, state: " << curlResponse.statusCode;
            return {};
        }

        Dto::Docker::ListContainerResponse response(curlResponse.output);
        if (response.containerList.empty()) {
            log_warning << "Docker container not found, name: " << name << ":" << tag;
            return {};
        }

        if (response.containerList.size() > 1) {
            log_warning << "More than one docker container found, name: " << name << ":" << tag;
            return {};
        }

        log_debug << "Docker container found, name: " << name << ":" << tag;
        return response.containerList[0];
    }

    Dto::Docker::Container DockerService::GetContainerById(const std::string &id) {

        std::string filters = Core::StringUtils::UrlEncode(R"({"userPoolId":[")" + id + "\"]}");
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("GET", "http://localhost/containers/json?filters=" + filters);
        log_debug << "List container request send to docker daemon";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_warning << "Get docker container by ID failed, state: " << curlResponse.statusCode;
            return {};
        }

        Dto::Docker::ListContainerResponse response(curlResponse.output);

        if (response.containerList.empty()) {
            log_warning << "Docker container not found, userPoolId: " << id;
            return {};
        }

        log_debug << "Docker container found, name: " << id;
        return response.containerList[0];
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &tag, const std::vector<std::string> &environment, int hostPort) {

        // Create the request
        Dto::Docker::CreateContainerRequest request = {
                .hostName = name,
                .domainName = name + _networkName,
                .user = "root",
                .image = name + ":" + tag,
                .networkMode = _networkMode,
                .environment = environment,
                .containerPort = _containerPort,
                .hostPort = std::to_string(hostPort)};

        std::string jsonBody = request.ToJson();
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("POST", "http://localhost/containers/create?name=" + name, jsonBody);
        log_debug << "Create container request send to docker daemon";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_CREATED) {
            log_warning << "Create container failed, state: " << curlResponse.statusCode;
            return {};
        }

        Dto::Docker::CreateContainerResponse response = {.hostPort = hostPort};
        response.FromJson(curlResponse.output);

        return response;
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &tag, int hostPort, int containerPort) {

        // Create the request
        Dto::Docker::CreateContainerRequest request = {
                .hostName = name,
                .domainName = name + _networkName,
                .user = "root",
                .image = name + ":" + tag,
                .networkMode = _networkMode,
                .containerPort = std::to_string(containerPort),
                .hostPort = std::to_string(hostPort)};

        std::string jsonBody = request.ToJson();
        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("POST", "http://localhost/containers/create?name=" + name, jsonBody);
        log_debug << "Create container request send to docker daemon";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_CREATED) {
            log_warning << "Create container failed, state: " << curlResponse.statusCode;
            return {};
        }

        Dto::Docker::CreateContainerResponse response = {.hostPort = hostPort};
        response.FromJson(curlResponse.output);

        return response;
    }

    void DockerService::StartDockerContainer(const std::string &id) {

        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("POST", "http://localhost/containers/" + id + "/start");
        log_debug << "Sending StartServer container request";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_NO_CONTENT && curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_NOT_MODIFIED) {
            log_warning << "Start container failed, state: " << curlResponse.statusCode;
        }
    }

    void DockerService::StartContainer(const Dto::Docker::Container &container) {
        StartDockerContainer(container.id);
    }

    void DockerService::RestartDockerContainer(const std::string &id) {

        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("POST", "http://localhost/containers/" + id + "/restart");
        log_debug << "Sending restart container request";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_NO_CONTENT) {
            log_warning << "Restart container failed, state: " << curlResponse.statusCode;
        }
    }

    void DockerService::RestartContainer(const Dto::Docker::Container &container) {
        RestartDockerContainer(container.id);
    }

    void DockerService::StopContainer(const Dto::Docker::Container &container) {

        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("POST", "http://localhost/containers/" + container.id + "/stop");
        log_debug << "Sending stop container request";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_NO_CONTENT) {
            log_warning << "Stop container failed, state: " << curlResponse.statusCode;
        }
    }

    void DockerService::DeleteContainer(const Dto::Docker::Container &container) {

        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("DELETE", "http://localhost/containers/" + container.id + "?force=true");
        log_debug << "Sending delete container request";
        log_trace << "Response: " << curlResponse.ToString();

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_NO_CONTENT) {
            log_warning << "Delete container failed, state: " << curlResponse.statusCode;
        }
    }

    void DockerService::PruneContainers() {

        Core::CurlResponse curlResponse = _curlUtils.SendUnixSocketRequest("POST", "http://localhost/containers/prune");

        if (curlResponse.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_warning << "Prune containers failed, state: " << curlResponse.statusCode;
            return;
        }

        Dto::Docker::PruneContainerResponse response;
        response.FromJson(curlResponse.output);

        log_debug << "Prune containers, count: " << response.containersDeleted.size() << " spaceReclaimed: " << response.spaceReclaimed;
    }

    std::string DockerService::WriteDockerFile(const std::string &codeDir, const std::string &handler, const std::string &runtime, const std::map<std::string, std::string> &environment) {

        std::string dockerFilename = codeDir + Poco::Path::separator() + "Dockerfile";

        // TODO: Fix environment
        std::ofstream ofs(dockerFilename);
        if (Core::StringUtils::EqualsIgnoreCase(runtime, "java11")) {
            ofs << "FROM public.ecr.aws/lambda/java:11" << std::endl;
            for (auto &env: environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        } else if (Core::StringUtils::EqualsIgnoreCase(runtime, "java17")) {
            ofs << "FROM public.ecr.aws/lambda/java:17" << std::endl;
            for (auto &env: environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        } else if (Core::StringUtils::EqualsIgnoreCase(runtime, "java21")) {
            ofs << "FROM public.ecr.aws/lambda/java:21" << std::endl;
            for (auto &env: environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        } else if (Core::StringUtils::EqualsIgnoreCase(runtime, "provided.al2")) {
            ofs << "FROM public.ecr.aws/lambda/provided:al2" << std::endl;
            for (auto &env: environment) {
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
            for (auto &env: environment) {
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
        log_debug << "Dockerfile written, filename: " << dockerFilename;

        return dockerFilename;
    }

    std::string DockerService::BuildImageFile(const std::string &codeDir, const std::string &functionName) {

        std::string tarFileName = codeDir + Poco::Path::separator() + functionName + ".tgz";
        Core::TarUtils::TarDirectory(tarFileName, codeDir);
        log_debug << "Zipped TAR file written: " << tarFileName;

        return tarFileName;
    }
}// namespace AwsMock::Service