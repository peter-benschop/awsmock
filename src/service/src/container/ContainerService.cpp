//
// Created by vogje01 on 06/06/2023.
//

#include <awsmock/core/DirUtils.h>
#include <awsmock/service/container/ContainerService.h>

namespace AwsMock::Service {
    std::map<std::string, std::string> ContainerService::_supportedRuntimes = {
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

    boost::mutex ContainerService::_dockerServiceMutex;

    ContainerService::ContainerService() {
        // Get network mode
        Core::Configuration &_configuration = Core::Configuration::instance();
        _networkName = _configuration.GetValueString("awsmock.docker.network-name");
        _containerPort = _configuration.GetValueString("awsmock.docker.container.port");
        _isDocker = _configuration.GetValueBool("awsmock.docker.active");
        _containerSocketPath = _isDocker ? _configuration.GetValueString("awsmock.docker.socket") : _containerSocketPath = _configuration.GetValueString("awsmock.podman.socket");
        _domainSocket = std::make_shared<Core::DomainSocket>(_containerSocketPath);
    }

    bool ContainerService::ImageExists(const std::string &name, const std::string &tag) const {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        if (_isDocker) {
            const std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + ":" + tag + "\"]}");
            if (const auto [statusCode, body] = _domainSocket->SendJson(http::verb::get, "http://localhost/images/json?all=true&filters=" + filters);
                statusCode == http::status::ok) {
                Dto::Docker::ListImageResponse response;
                response.FromJson(body);
                if (response.imageList.empty()) {
                    log_debug << "Docker image not found, name: " << name << ":" << tag;
                } else {
                    log_debug << "Docker image found, name: " << name << ":" << tag;
                }
                return !response.imageList.empty();
            }
        } else {
            if (const auto [statusCode, body] = _domainSocket->SendJson(http::verb::get, "http://localhost/v5.0.0/libpod/images/" + name + "/exists");
                statusCode == http::status::no_content) {
                log_debug << "Podman image found, name: " << name << ":" << tag;
                return true;
            }
        }
        log_error << "Image exists request failed";
        return false;
    }

    void ContainerService::CreateImage(const std::string &name, const std::string &tag, const std::string &fromImage) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        auto [statusCode, body] = _domainSocket->SendJson(http::verb::post, "http://localhost/images/create?name=" + name + "&tag=" + tag + "&fromImage=" + fromImage);
        if (statusCode == http::status::ok) {
            log_debug << "Docker image created, name: " << name << ":" << tag;

            // Wait for image creation
            Dto::Docker::Image image = GetImageByName(name, tag, true);
            while (GetImageByName(name, tag, true).size == 0) {
                std::this_thread::sleep_for(500ms);
            }
        } else {
            log_error << "Docker image create failed, httpStatus: " << statusCode;
        }
    }

    Dto::Docker::Image ContainerService::GetImageByName(const std::string &name, const std::string &tag, bool locked) {
        if (!locked) {
            boost::mutex::scoped_lock lock(_dockerServiceMutex);
        }

        std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::get,
                "http://localhost/images/json?all=true&filters=" + filters);
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

    std::string ContainerService::BuildImage(const std::string &codeDir,
                                             const std::string &name,
                                             const std::string &tag,
                                             const std::string &handler,
                                             const std::string &runtime,
                                             const std::map<std::string, std::string> &environment) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);
        log_debug << "Build image request, name: " << name << " tags: " << tag << " runtime: " << runtime;

        std::string dockerFile = WriteDockerFile(codeDir, handler, runtime, environment);
        std::string imageFile = BuildImageFile(codeDir, name);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendBinary(
                http::verb::post,
                "http://localhost/build?t=" + name + ":" + tag,
                imageFile);
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_error << "Build image failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
        }
        return imageFile;
    }

    std::string ContainerService::BuildImage(const std::string &name,
                                             const std::string &tag,
                                             const std::string &dockerFile) const {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);
        log_debug << "Build image request, name: " << name << " tags: " << tag;

        // Write docker file
        std::string codeDir = Core::DirUtils::CreateTempDir();
        std::string fileName = codeDir + Poco::Path::separator() + "Dockerfile";
        std::ofstream ofs(fileName);
        ofs << dockerFile;
        ofs.close();
        std::string imageFile = BuildImageFile(codeDir, name);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendBinary(
                http::verb::post,
                "http://localhost/build?t=" + name + ":" + tag,
                imageFile,
                {});
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_error << "Build image failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
        }
        return dockerFile;
    }

    Dto::Docker::ListImageResponse ContainerService::ListImages(const std::string &name) const {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Dto::Docker::ListImageResponse response{};
        const std::string filters = Core::StringUtils::UrlEncode(R"({"reference":[")" + name + "\"]}");
        if (auto [statusCode, body] = _domainSocket->SendJson(http::verb::get,
                                                              "http://localhost/images/json?all=true&filters=" +
                                                                      filters);
            statusCode == http::status::ok) {
            response.FromJson(body);
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
            log_error << "Get image by name failed, httpStatus: " << statusCode;
        }
        return response;
    }

    void ContainerService::DeleteImage(const std::string &id) const {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        if (auto [statusCode, body] = _domainSocket->SendJson(http::verb::delete_,
                                                              "http://localhost/images/" + id + "?force=true");
            statusCode != http::status::ok) {
            log_error << "Delete image failed, httpStatus: " << statusCode;
        }
        log_debug << "Image deleted, id: " << id;
    }

    bool ContainerService::ContainerExists(const std::string &id) const {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        if (_isDocker) {
            const std::string filters = Core::StringUtils::UrlEncode(R"({"id":[")" + id + "\"]}");
            auto [statusCode, body] = _domainSocket->SendJson(http::verb::get,
                                                              "http://localhost/containers/json?all=true&filters=" +
                                                                      filters);
            if (statusCode == http::status::ok) {
                Dto::Docker::ListContainerResponse response(body);
                log_debug << "Docker container found, id: " << id;
                return !response.containerList.empty();
            } else {
                log_warning << "Docker container exists failed, httpStatus: " << statusCode;
                return false;
            }
        } else {
            auto [statusCode, body] = _domainSocket->SendJson(http::verb::get,
                                                              "http://localhost/v5.0.0/libpod/containers/" + id +
                                                                      "/exists");
            if (statusCode == http::status::ok) {
                Dto::Docker::ListContainerResponse response(body);
                log_debug << "Docker container found, id: " << id;
                return !response.containerList.empty();
            } else {
                log_warning << "Docker container exists failed, httpStatus: " << statusCode;
                return false;
            }
        }
    }

    bool ContainerService::ContainerExists(const std::string &name, const std::string &tag) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        if (_isDocker) {
            const std::string filters = Core::StringUtils::UrlEncode(R"({"ancestor":[")" + name + ":" + tag + "\"]}");
            auto [statusCode, body] = _domainSocket->SendJson(http::verb::get,
                                                              "http://localhost/containers/json?all=true&filters=" +
                                                                      filters);
            if (statusCode == http::status::ok) {
                Dto::Docker::ListContainerResponse response(body);
                log_debug << "Docker container found, name: " << name << ":" << tag;
                return !response.containerList.empty();
            } else {
                log_warning << "Docker container exists failed, httpStatus: " << statusCode;
                return false;
            }
        } else {
            Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                    http::verb::get,
                    "http://localhost/v5.0.0/libpod/images/" + name + "/exists");
            if (domainSocketResponse.statusCode == http::status::no_content) {
                log_debug << "Podman container found, name: " << name << ":" << tag;
                return true;
            } else if (domainSocketResponse.statusCode == http::status::not_found) {
                log_info << "Podman container not found";
            } else {
                log_error << "Podman container exists request failed, httpStatus: " << domainSocketResponse.statusCode;
            }
        }
        return false;
    }

    Dto::Docker::Container
    ContainerService::GetFirstContainerByImageName(const std::string &name, const std::string &tag) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        std::string filters = Core::StringUtils::UrlEncode(R"({"ancestor":[")" + name + ":" + tag + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::get,
                "http://localhost/containers/json?all=true&size=true&filters=" + filters);
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
            log_warning << "More than one docker container found, name: " << name << ":" << tag << " count: " << response.containerList.size();
        }

        log_debug << "Docker container found, name: " << name << ":" << tag;
        return response.containerList.front();
    }

    Dto::Docker::Container ContainerService::GetContainerById(const std::string &containerId) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        std::string filters = Core::StringUtils::UrlEncode(R"({"id":[")" + containerId + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::get,
                "http://localhost/containers/json?all=true&filters=" + filters);
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_warning << "Get docker container by name failed, state: " << domainSocketResponse.statusCode;
            return {};
        }

        Dto::Docker::ListContainerResponse response(domainSocketResponse.body);
        if (response.containerList.empty()) {
            log_warning << "Docker container not found, id: " << containerId;
            return {};
        }

        if (response.containerList.size() > 1) {
            log_warning << "More than one docker container found, id: " << containerId << " count: " << response.containerList.size();
        }

        log_debug << "Docker container found, id: " << containerId;
        return response.containerList.front();
    }

    Dto::Docker::Container ContainerService::GetContainerByName(const std::string &name) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + name + "\"]}");
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::get,
                "http://localhost/containers/json?all=true&size=true&filters=" + filters);
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_warning << "Get container by name failed, state: " << domainSocketResponse.statusCode;
            return {};
        }

        Dto::Docker::ListContainerResponse response(domainSocketResponse.body);
        if (response.containerList.empty()) {
            log_warning << "Container not found, name: " << name;
            return {};
        }

        if (response.containerList.size() > 1) {
            log_warning << "More than one container found, name: " << name << " count: " << response.containerList.size();
        }

        log_debug << "Container found, name: " << name;
        return response.containerList.front();
    }

    std::vector<Dto::Docker::Container> ContainerService::ListContainerByImageName(
            const std::string &name,
            const std::string &tag) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        if (_isDocker) {
            std::string filters = Core::StringUtils::UrlEncode(R"({"ancestor":[")" + name + ":" + tag + "\"]}");
            Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                    http::verb::get,
                    "http://localhost/containers/json?all=true&filters=" + filters);
            if (domainSocketResponse.statusCode != http::status::ok) {
                log_warning << "Get docker container by name failed, state: " << domainSocketResponse.statusCode;
                return {};
            }

            Dto::Docker::ListContainerResponse response(domainSocketResponse.body);
            if (response.containerList.empty()) {
                log_warning << "Docker container not found, name: " << name << ":" << tag;
                return {};
            }
            log_debug << "Docker container found, name: " << name << ":" << tag << " count: " << response.containerList.size();
            return response.containerList;
        } else {
            std::string filters = Core::StringUtils::UrlEncode(R"({"ancestor":[")" + name + ":" + tag + "\"]}");
            Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                    http::verb::get,
                    "http://localhost/containers/json?all=true&filters=" + filters);
            if (domainSocketResponse.statusCode != http::status::ok) {
                log_warning << "Get docker container by name failed, state: " << domainSocketResponse.statusCode;
                return {};
            }

            Dto::Docker::ListContainerResponse response(domainSocketResponse.body);
            if (response.containerList.empty()) {
                log_warning << "Docker container not found, name: " << name << ":" << tag;
                return {};
            }
            log_debug << "Docker container found, name: " << name << ":" << tag << " count: " << response.containerList.size();
            return response.containerList;
        }
    }

    Dto::Docker::CreateContainerResponse ContainerService::CreateContainer(const std::string &imageName,
                                                                           const std::string &instanceName,
                                                                           const std::string &tag,
                                                                           const std::vector<std::string> &environment,
                                                                           int hostPort) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        // Create the request
        Dto::Docker::CreateContainerRequest request = {
                .hostName = instanceName,
                .user = "root",
                .image = imageName + ":" + tag,
                .networkMode = GetNetworkName(),
                .environment = environment,
                .containerPort = _containerPort,
                .hostPort = std::to_string(hostPort)};

        std::string jsonBody = request.ToJson();
        log_debug << "Docker container configuration, json: " << jsonBody;

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::post,
                "http://localhost/containers/create?name=" + instanceName,
                jsonBody);
        if (domainSocketResponse.statusCode != http::status::created) {
            log_warning << "Create container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return {};
        }

        Dto::Docker::CreateContainerResponse response = {.hostPort = hostPort};
        response.FromJson(domainSocketResponse.body);

        log_debug << "Docker container created, name: " << imageName << ":" << tag << " id: " << response.id;
        return response;
    }

    Dto::Docker::CreateContainerResponse ContainerService::CreateContainer(const std::string &imageName,
                                                                           const std::string &tag,
                                                                           int hostPort,
                                                                           int containerPort) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        // Check container name
        std::string containerName = imageName;
        if (Core::StringUtils::Contains(imageName, "/")) {
            containerName = Core::StringUtils::SubStringAfter(containerName, "/");
        }

        // Create the request
        Dto::Docker::CreateContainerRequest request = {
                .hostName = imageName,
                .user = "root",
                .image = imageName + ":" + tag,
                .networkMode = GetNetworkName(),
                .containerPort = std::to_string(containerPort),
                .hostPort = std::to_string(hostPort)};
        std::string jsonBody = request.ToJson();

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::post,
                "http://localhost/containers/create?name=" + containerName,
                jsonBody);
        if (domainSocketResponse.statusCode != http::status::created) {
            log_warning << "Create container failed, httpStatus: " << domainSocketResponse.statusCode << " body " << domainSocketResponse.body;
            return {};
        }

        Dto::Docker::CreateContainerResponse response = {.hostPort = hostPort};
        response.FromJson(domainSocketResponse.body);

        log_debug << "Docker container created, name: " << imageName << ":" << tag;
        return response;
    }

    bool ContainerService::NetworkExists(const std::string &name) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);
        std::string filters = Core::StringUtils::UrlEncode(R"({"name":[")" + name + "\"]}");

        if (_isDocker) {
            Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                    http::verb::get,
                    "http://localhost/networks/?filters=" + filters);
            if (domainSocketResponse.statusCode == http::status::ok) {
                Dto::Docker::ListNetworkResponse response;
                response.FromJson(domainSocketResponse.body);
                if (response.networkList.empty()) {
                    log_debug << "Docker network not found, name: " << name;
                } else {
                    log_debug << "Docker network found, name: " << name;
                }
                return !response.networkList.empty();
            } else {
                log_error << "Network exists request failed, httpStatus: " << domainSocketResponse.statusCode;
            }
        } else {
            Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                    http::verb::get,
                    "http://localhost/v5.0.0/libpod/network/" + name + "/exists");
            if (domainSocketResponse.statusCode == http::status::no_content) {
                log_debug << "Podman network found, name: " << name;
                return true;
            } else if (domainSocketResponse.statusCode == http::status::not_found) {
                log_info << "Podman network not found";
            } else {
                log_error << "Podman network exists request failed, httpStatus: " << domainSocketResponse.statusCode;
            }
        }
        return false;
    }

    Dto::Docker::CreateNetworkResponse ContainerService::CreateNetwork(const Dto::Docker::CreateNetworkRequest &request) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Dto::Docker::CreateNetworkResponse response;
        if (_isDocker) {
            Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                    http::verb::post,
                    "http://localhost/networks/create",
                    request.ToJson());
            if (domainSocketResponse.statusCode == http::status::ok) {
                log_debug << "Docker network created, name: " << request.name << " driver: " << request.driver;
            } else {
                log_error << "Docker network create failed, httpStatus: " << domainSocketResponse.statusCode;
            }
            response.FromJson(domainSocketResponse.body);
        } else {
            Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                    http::verb::post,
                    "http://localhost/networks/create",
                    request.ToJson());
            if (domainSocketResponse.statusCode == http::status::ok) {
                log_debug << "Podman network created, name: " << request.name << " driver: " << request.driver;
            } else {
                log_error << "Podman network create failed, httpStatus: " << domainSocketResponse.statusCode;
            }
            response.FromJson(domainSocketResponse.body);
        }
        return response;
    }

    void ContainerService::StartDockerContainer(const std::string &id) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::post,
                "http://localhost/containers/" + id + "/start");
        if (domainSocketResponse.statusCode != http::status::ok && domainSocketResponse.statusCode !=
                                                                           http::status::no_content) {
            log_warning << "Start container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container started, id: " << id;
    }

    void ContainerService::RestartContainer(const Dto::Docker::Container &container) {
        RestartDockerContainer(container.id);
    }

    void ContainerService::RestartDockerContainer(const std::string &id) {
        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::post,
                "http://localhost/containers/" + id + "/restart");
        if (domainSocketResponse.statusCode != http::status::no_content) {
            log_warning << "Restart container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container restarted, id: " << id;
    }

    void ContainerService::StopContainer(const Dto::Docker::Container &container) {
        StopContainer(container.id);
    }

    void ContainerService::StopContainer(const std::string &id) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::post,
                "http://localhost/containers/" + id + "/stop");
        if (domainSocketResponse.statusCode != http::status::no_content) {
            log_warning << "Stop container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container stopped, id: " << id;
    }

    void ContainerService::DeleteContainer(const Dto::Docker::Container &container) {
        DeleteContainer(container.id);
    }

    void ContainerService::DeleteContainer(const std::string &id) {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::delete_,
                "http://localhost/containers/" + id + "?force=true");
        if (domainSocketResponse.statusCode != http::status::no_content) {
            log_warning << "Delete container failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }
        log_debug << "Docker container deleted, id: " << id;
    }

    void ContainerService::PruneContainers() {
        boost::mutex::scoped_lock lock(_dockerServiceMutex);

        Core::DomainSocketResult domainSocketResponse = _domainSocket->SendJson(
                http::verb::post,
                "http://localhost/containers/prune");
        if (domainSocketResponse.statusCode != http::status::ok) {
            log_warning << "Prune containers failed, httpStatus: " << domainSocketResponse.statusCode << " body: " << domainSocketResponse.body;
            return;
        }

        Dto::Docker::PruneContainerResponse response;
        response.FromJson(domainSocketResponse.body);

        log_debug << "Prune containers, count: " << response.containersDeleted.size() << " spaceReclaimed: " << response.spaceReclaimed;
    }

    std::string ContainerService::WriteDockerFile(const std::string &codeDir, const std::string &handler, const std::string &runtime, const std::map<std::string, std::string> &environment) {
        std::string dockerFilename = codeDir + boost::filesystem::path::preferred_separator + "Dockerfile";

        std::string supportedRuntime = _supportedRuntimes[boost::algorithm::to_lower_copy(runtime)];

        std::ofstream ofs(dockerFilename);
        if (Core::StringUtils::StartsWithIgnoringCase(runtime, "java")) {
            ofs << "FROM " << supportedRuntime << std::endl;
            for (const auto &[fst, snd]: environment) {
                ofs << "ENV " << fst << "=\"" << snd << "\"" << std::endl;
            }
            ofs << "COPY classes ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        } else if (Core::StringUtils::StartsWithIgnoringCase(runtime, "provided")) {
            ofs << "FROM " << supportedRuntime << std::endl;
            for (const auto &[fst, snd]: environment) {
                ofs << "ENV " << fst << "=\"" << snd << "\"" << std::endl;
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
            for (const auto &[fst, snd]: environment) {
                ofs << "ENV " << fst << "=\"" << snd << "\"" << std::endl;
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
            for (const auto &[fst, snd]: environment) {
                ofs << "ENV " << fst << "=\"" << snd << "\"" << std::endl;
            }
            ofs << "COPY node_modules/ ${LAMBDA_TASK_ROOT}/node_modules/" << std::endl;
            ofs << "COPY index.js ${LAMBDA_TASK_ROOT}" << std::endl;
            ofs << "RUN mkdir -p /root/.aws" << std::endl;
            ofs << "COPY config /root/.aws" << std::endl;
            ofs << "COPY credentials /root/.aws" << std::endl;
            ofs << "CMD [\"" + handler + "\"]" << std::endl;
        } else if (Core::StringUtils::StartsWithIgnoringCase(runtime, "go")) {
            ofs << "FROM " << supportedRuntime << std::endl;
            for (const auto &[fst, snd]: environment) {
                ofs << "ENV " << fst << "=\"" << snd << "\"" << std::endl;
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

    std::string ContainerService::BuildImageFile(const std::string &codeDir, const std::string &functionName) {
        std::string tarFileName = codeDir + Poco::Path::separator() + functionName + ".tgz";
        Core::TarUtils::TarDirectory(tarFileName, codeDir + "/");
        log_debug << "Zipped TAR file written: " << tarFileName;

        return tarFileName;
    }

    std::string ContainerService::GetNetworkName() {
        if (Core::Configuration::instance().GetValueBool("awsmock.docker.active")) {
            return Core::Configuration::instance().GetValueString("awsmock.docker.network.mode");
        } else {
            return Core::Configuration::instance().GetValueString("awsmock.podman.network.mode");
        }
    }
}// namespace AwsMock::Service
