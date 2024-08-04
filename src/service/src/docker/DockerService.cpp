//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/service/docker/DockerService.h>

namespace AwsMock::Service {

    std::map<std::string, std::string> DockerService::_supportedRuntimes = {
            {"java11", "public.ecr.aws/lambda/java:11"},
            {"java17", "public.ecr.aws/lambda/java:17"},
            {"java21", "public.ecr.aws/lambda/java:21"},
            {"python3.8", "public.ecr.aws/lambda/python:3.8"},
            {"python3.9", "public.ecr.aws/lambda/python:3.9"},
            {"python3.10", "public.ecr.aws/lambda/python:3.10"},
            {"python3.11", "public.ecr.aws/lambda/python:3.11"},
            {"python3.12", "public.ecr.aws/lambda/python:3.12"},
            {"nodejs20.x", "public.ecr.aws/lambda/nodejs:20"},
            {"provided.al2", "public.ecr.aws/lambda/provided:al2"},
            {"provided.al2023", "public.ecr.aws/lambda/provided:al2023"},
            {"provided.latest", "public.ecr.aws/lambda/provided:latest"},
            {"go", "public.ecr.aws/lambda/provided:al2023"},
    };

    boost::mutex DockerService::_dockerServiceMutex;

    DockerService::DockerService() {

        // Get network mode
        Core::Configuration &_configuration = Core::Configuration::instance();
        _networkName = _configuration.getString("awsmock.docker.network.name", NETWORK_NAME);
        _containerPort = _configuration.getString("awsmock.docker.container.port", CONTAINER_PORT);
        _dockerSocketPath = _configuration.getString("awsmock.docker.socket", DOCKER_SOCKET);
        _domainSocket = std::make_shared<Core::DomainSocket>(_dockerSocketPath);
    }

    bool DockerService::ImageExists(const std::string &name, const std::string &tag) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);
        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + ":" + tag + "\"]}");

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::get, "http://localhost/images/json?all=true&filters=" + filters);
        if (domainSocketResponse.statusCode == http::status::ok) {

            Dto::Docker::ListImageResponse response;
            response.FromJson(domainSocketResponse.body);
            if (response.imageList.empty()) {
                log_debug << "Docker image not found, name: " << name << ":" << tag;
            } else {
                log_debug << "Docker image found, name: " << name << ":" << tag;
            }
            return !response.imageList.empty();

        } else {

            log_error << "Image exists request failed, httpStatus: " << domainSocketResponse.statusCode;
        }
        return false;
    }

    void DockerService::CreateImage(const std::string &name, const std::string &tag, const std::string &fromImage) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::post, "http://localhost/images/create?name=" + name + "&tag=" + tag + "&fromImage=" + fromImage);
        if (domainSocketResponse.statusCode == http::status::ok) {
            log_debug << "Docker image created, name: " << name << ":" << tag;

            // Wait for image creation
            Dto::Docker::Image image = GetImageByName(name, tag);
            while (GetImageByName(name, tag).size == 0) {
                std::this_thread::sleep_for(500ms);
            }

        } else {

            log_error << "Docker image create failed, httpStatus: " << domainSocketResponse.statusCode;
        }
    }

    Dto::Docker::Image DockerService::GetImageByName(const std::string &name, const std::string &tag) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::get, "http://localhost/images/json?all=true&filters=" + filters);
        if (domainSocketResponse.statusCode == http::status::ok) {

            Dto::Docker::ListImageResponse response;
            response.FromJson(domainSocketResponse.body);
            if (response.imageList.empty()) {
                log_warning << "Docker image not found, name: " << name << ":" << tag;
                return {};
            }

            if (response.imageList.size() > 1) {
                log_warning << "More than one docker image found, name: " << name << ":" << tag;
                return {};
            }
            log_info << "Image found, name: " << name << ":" << tag;
            return response.imageList[0];

        } else {

            log_error << "Get image by name failed, httpStatus: " << domainSocketResponse.statusCode;
        }
        return {};
    }

    std::string DockerService::BuildImage(const std::string &codeDir, const std::string &name, const std::string &tag, const std::string &handler, const std::string &runtime, const std::map<std::string, std::string> &environment) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);
        log_debug << "Build image request, name: " << name << " tags: " << tag << " runtime: " << runtime;

        std::string dockerFile = WriteDockerFile(codeDir, handler, runtime, environment);
        std::string imageFile = BuildImageFile(codeDir, name);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendBinary(http::verb::post, "http://localhost/build?t=" + name + ":" + tag, imageFile);
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_error << "Build image failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
        }
        return imageFile;
    }

    std::string DockerService::BuildImage(const std::string &name, const std::string &tag, const std::string &dockerFile) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);
        log_debug << "Build image request, name: " << name << " tags: " << tag;

        // Write docker file
        std::string codeDir = Core::DirUtils::CreateTempDir();
        std::string fileName = codeDir + Poco::Path::separator() + "Dockerfile";
        std::ofstream ofs(fileName);
        ofs << dockerFile;
        ofs.close();
        std::string imageFile = BuildImageFile(codeDir, name);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendBinary(http::verb::post, "http://localhost/build?t=" + name + ":" + tag, imageFile, {});
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_error << "Build image failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
        }
        return dockerFile;
    }

    Dto::Docker::ListImageResponse DockerService::ListImages(const std::string &name) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Dto::Docker::ListImageResponse response{};
        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::get, "http://localhost/images/json?all=true&filters=" + filters);
        if (domainSocketResponse.statusCode == http::status::ok) {

            response.FromJson(domainSocketResponse.body);
            if (response.imageList.empty()) {
                log_warning << "Docker image not found, name: " << name;
                return response;
            }

            if (response.imageList.size() > 1) {
                log_warning << "More than one docker image found, name: " << name;
                return response;
            }
            log_info << "Images found, name: " << name;
            return response;

        } else {

            log_error << "Get image by name failed, httpStatus: " << domainSocketResponse.statusCode;
        }
        return response;
    }

    void DockerService::DeleteImage(const std::string &id) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::delete_, "http://localhost/images/" + id + "?force=true");
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_error << "Delete image failed, httpStatus: " << domainSocketResponse.statusCode;
        }
        log_debug << "Image deleted, id: " << id;
    }

    bool DockerService::ContainerExists(const std::string &name, const std::string &tag) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + std::string("/") + name + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::get, "http://localhost/containers/json?all=true&filters=" + filters);
        if (domainSocketResponse.statusCode == http::status::ok) {

            Dto::Docker::ListContainerResponse response(domainSocketResponse.body);
            log_debug << "Docker image found, name: " << name << ":" << tag;
            return !response.containerList.empty();

        } else {

            log_warning << "Docker container exists failed, httpStatus: " << domainSocketResponse.statusCode;
            return false;
        }
    }

    Dto::Docker::Container DockerService::GetContainerByName(const std::string &name, const std::string &tag) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + std::string("/") + name + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::get, "http://localhost/containers/json?all=true&filters=" + filters);
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_warning << "Get docker container by name failed, state: " << domainSocketResponse.statusCode;
            return {};
        }

        Dto::Docker::ListContainerResponse response(domainSocketResponse.body);
        if (response.containerList.empty()) {
            log_warning << "Docker container not found, name: " << name << ":" << tag;
            return {};
        }

        if (response.containerList.size() > 1) {
            log_warning << "More than one docker container found, name: " << name << ":" << tag;
            return {};
        }

        log_debug << "Docker container found, name: " << name << ":" << tag;
        return response.containerList.front();
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &instanceName, const std::string &tag, const std::vector<std::string> &environment, int hostPort) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        // Create the request
        std::string networkMode = Core::Configuration::instance().getString("awsmock.docker.network.mode", NETWORK_DEFAULT_MODE);
        Dto::Docker::CreateContainerRequest request = {
                .hostName = instanceName,
                .domainName = instanceName + networkMode,
                .user = "root",
                .image = name + ":" + tag,
                .networkMode = networkMode,
                .environment = environment,
                .containerPort = _containerPort,
                .hostPort = std::to_string(hostPort)};

        std::string jsonBody = request.ToJson();

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::post, "http://localhost/containers/create?name=" + instanceName, jsonBody);
        if (domainSocketResponse.statusCode != http::status::created) {
            log_warning << "Create container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return {};
        }

        Dto::Docker::CreateContainerResponse response = {.hostPort = hostPort};
        response.FromJson(domainSocketResponse.body);

        log_debug << "Docker container created, name: " << name << ":" << tag;
        return response;
    }

    Dto::Docker::CreateContainerResponse DockerService::CreateContainer(const std::string &name, const std::string &tag, int hostPort, int containerPort) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        // Create the request
        std::string networkMode = Core::Configuration::instance().getString("awsmock.docker.network.mode", NETWORK_DEFAULT_MODE);
        Dto::Docker::CreateContainerRequest request = {
                .hostName = name,
                .domainName = name + networkMode,
                .user = "root",
                .image = name + ":" + tag,
                .networkMode = networkMode,
                .containerPort = std::to_string(containerPort),
                .hostPort = std::to_string(hostPort)};
        std::string jsonBody = request.ToJson();

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::post, "http://localhost/containers/create?name=" + name, jsonBody);
        if (domainSocketResponse.statusCode != http::status::created) {
            log_warning << "Create container failed, httpStatus: " << domainSocketResponse.statusCode << " body " << domainSocketResponse.body;
            return {};
        }

        Dto::Docker::CreateContainerResponse response = {.hostPort = hostPort};
        response.FromJson(domainSocketResponse.body);

        log_debug << "Docker container created, name: " << name << ":" << tag;
        return response;
    }

    void DockerService::StartDockerContainer(const std::string &id) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::post, "http://localhost/containers/" + id + "/start");
        if (domainSocketResponse.statusCode != http::status::ok && domainSocketResponse.statusCode != http::status::no_content) {
            log_warning << "Start container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container started, id: " << id;
    }

    void DockerService::RestartDockerContainer(const std::string &id) {

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::post, "http://localhost/containers/" + id + "/restart");
        if (domainSocketResponse.statusCode != http::status::no_content) {
            log_warning << "Restart container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container restarted, id: " << id;
    }

    void DockerService::RestartContainer(const Dto::Docker::Container &container) {
        RestartDockerContainer(container.id);
    }

    void DockerService::StopContainer(const Dto::Docker::Container &container) {
        StopContainer(container.id);
    }

    void DockerService::StopContainer(const std::string &id) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::post, "http://localhost/containers/" + id + "/stop");
        if (domainSocketResponse.statusCode != http::status::no_content) {
            log_warning << "Stop container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container stopped, id: " << id;
    }

    void DockerService::DeleteContainer(const Dto::Docker::Container &container) {
        DeleteContainer(container.id);
    }

    void DockerService::DeleteContainer(const std::string &id) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::delete_, "http://localhost/containers/" + id + "?force=true");
        if (domainSocketResponse.statusCode != http::status::no_content) {
            log_warning << "Delete container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container deleted, id: " << id;
    }

    void DockerService::PruneContainers() {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(http::verb::post, "http://localhost/containers/prune");
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_warning << "Prune containers failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }

        Dto::Docker::PruneContainerResponse response;
        response.FromJson(domainSocketResponse.body);

        log_debug << "Prune containers, count: " << response.containersDeleted.size() << " spaceReclaimed: " << response.spaceReclaimed;
    }

    std::string DockerService::WriteDockerFile(const std::string &codeDir, const std::string &handler, const std::string &runtime, const std::map<std::string, std::string> &environment) {

        std::string dockerFilename = codeDir + boost::filesystem::path::preferred_separator + "Dockerfile";

        std::string supportedRuntime = _supportedRuntimes[boost::algorithm::to_lower_copy(runtime)];

        std::ofstream ofs(dockerFilename);
        if (Core::StringUtils::StartsWithIgnoringCase(runtime, "java")) {

            ofs << "FROM " << supportedRuntime << std::endl;
            for (auto &env: environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;

        } else if (Core::StringUtils::StartsWithIgnoringCase(runtime, "provided")) {

            ofs << "FROM " << supportedRuntime << std::endl;
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

        } else if (Core::StringUtils::StartsWithIgnoringCase(runtime, "python")) {

            ofs << "FROM " << supportedRuntime << std::endl;
            for (auto &env: environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY requirements.txt ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "RUN mkdir -p /root/.aws" << std::endl;
            ofs << "COPY config /root/.aws" << std::endl;
            ofs << "COPY credentials /root/.aws" << std::endl;
            ofs << "RUN pip install -r requirements.txt" << std::endl;
            ofs << "COPY lambda_function.py ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [\"" + handler + "\"]" << std::endl;

        } else if (Core::StringUtils::StartsWithIgnoringCase(runtime, "nodejs")) {

            ofs << "FROM " << supportedRuntime << std::endl;
            for (auto &env: environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY node_modules/ ${LAMBDA_TASK_ROOT}/node_modules/" << std::endl;
            ofs << "COPY index.js ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "RUN mkdir -p /root/.aws" << std::endl;
            ofs << "COPY config /root/.aws" << std::endl;
            ofs << "COPY credentials /root/.aws" << std::endl;
            ofs << "CMD [\"" + handler + "\"]" << std::endl;

        } else if (Core::StringUtils::StartsWithIgnoringCase(runtime, "go")) {

            ofs << "FROM " << supportedRuntime << std::endl;
            for (auto &env: environment) {
                ofs << "ENV " << env.first << "=\"" << env.second << "\"" << std::endl;
            }
            ofs << "COPY bootstrap ${LAMBDA_RUNTIME_DIR}" << std::endl;
            ofs << "RUN chmod 755 ${LAMBDA_RUNTIME_DIR}/bootstrap" << std::endl;
            ofs << "RUN mkdir -p /root/.aws" << std::endl;
            ofs << "COPY config /root/.aws" << std::endl;
            ofs << "COPY credentials /root/.aws" << std::endl;
            ofs << "CMD [\"" + handler + "\"]" << std::endl;
        }
        ofs.close();
        log_debug << "Dockerfile written, filename: " << dockerFilename;

        return dockerFilename;
    }

    std::string DockerService::BuildImageFile(const std::string &codeDir, const std::string &functionName) {

        std::string tarFileName = codeDir + Poco::Path::separator() + functionName + ".tgz";
        Core::TarUtils::TarDirectory(tarFileName, codeDir + "/");
        log_debug << "Zipped TAR file written: " << tarFileName;

        return tarFileName;
    }

}// namespace AwsMock::Service