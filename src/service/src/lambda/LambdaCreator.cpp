//
// Created by vogje01 on 30/05/2023.
//

#include "awsmock/service/lambda/LambdaCreator.h"

namespace AwsMock::Service {

    [[maybe_unused]] LambdaCreator::LambdaCreator(Core::Configuration &configuration) : _configuration(configuration), _lambdaDatabase(Database::LambdaDatabase::instance()), _dockerService(configuration) {

        // Configuration
        _dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data");
        _tempDir = _dataDir + Poco::Path::separator() + "tmp";
    }

    void LambdaCreator::CreateLambdaFunction(const std::string &functionCode, const std::string &functionId) {

        log_debug << "Start creating lambda function, oid: " << functionId;

        // Make local copy
        Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase.GetLambdaById(functionId);

        // Docker tag
        std::string dockerTag = GetDockerTag(lambdaEntity);
        log_debug << "Using docker tag: " << dockerTag;

        // Build the docker image, if not existing
        if (!_dockerService.ImageExists(lambdaEntity.function, dockerTag)) {
            CreateDockerImage(functionCode, lambdaEntity, dockerTag);
        }

        // Create the container, if not existing. If existing get the current port from the docker container
        if (!_dockerService.ContainerExists(lambdaEntity.function, dockerTag)) {
            lambdaEntity.hostPort = GetHostPort();
            CreateDockerContainer(lambdaEntity, dockerTag);
        }

        // Get docker container
        Dto::Docker::Container container = _dockerService.GetContainerByName(lambdaEntity.function, dockerTag);

        // Start docker container, in case it is not already running.
        if (container.state != "running") {
            _dockerService.StartDockerContainer(container.id);
        } else {
            lambdaEntity.hostPort = container.GetLambdaPort();
        }

        // Update database
        lambdaEntity.containerId = container.id;
        lambdaEntity.lastStarted = Poco::DateTime();
        lambdaEntity.state = Database::Entity::Lambda::LambdaState::Active;
        lambdaEntity.stateReason = "Activated";
        _lambdaDatabase.UpdateLambda(lambdaEntity);

        log_debug << "Lambda function started: " << lambdaEntity.function << ":" << dockerTag;
    }

    void LambdaCreator::CreateDockerImage(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag) {

        if (zipFile.empty()) {
            log_error << "Empty lambda zip file";
            return;
        }

        // Unzip provided zip-file into a temporary directory
        std::string codeDir = UnpackZipFile(zipFile, lambdaEntity.runtime, lambdaEntity.fileName);
        log_debug << "Lambda file unzipped, codeDir: " << codeDir;

        // Build the docker image using the docker module
        std::string imageFile = _dockerService.BuildImage(codeDir, lambdaEntity.function, dockerTag, lambdaEntity.handler, lambdaEntity.runtime, lambdaEntity.environment.variables);

        // Get the image struct
        Dto::Docker::Image image = _dockerService.GetImageByName(lambdaEntity.function, dockerTag);
        lambdaEntity.codeSize = image.size;
        lambdaEntity.imageId = image.id;
        lambdaEntity.codeSha256 = Core::Crypto::GetSha256FromFile(imageFile);
        lambdaEntity.hostPort = GetHostPort();

        // Cleanup
        Core::DirUtils::DeleteDirectory(codeDir);
        log_debug << "Docker image created, name: " << lambdaEntity.function << " size: " << lambdaEntity.codeSize;
        log_debug << "Using port: " << lambdaEntity.hostPort;
    }

    void LambdaCreator::CreateDockerContainer(Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag) {

        try {
            std::vector<std::string> environment = GetEnvironment(lambdaEntity.environment);
            Dto::Docker::CreateContainerResponse
                    containerCreateResponse = _dockerService.CreateContainer(lambdaEntity.function, dockerTag, environment, lambdaEntity.hostPort);
            log_debug << "Lambda container created, hostPort: " << lambdaEntity.hostPort;
        } catch (std::exception &exc) {
            log_error << exc.what();
        }
    }

    std::string LambdaCreator::UnpackZipFile(const std::string &zipFile, const std::string &runtime, const std::string &fileName) {

        // If we do not have a local file already, write the Base64 encoded file to lambda dir
        if (!Core::FileUtils::FileExists(fileName)) {
            std::ofstream ofs(fileName);
            ofs << zipFile;
            ofs.flush();
            ofs.close();
        }

        std::string decodedZipFile = Core::Crypto::Base64Decode(zipFile);

        // Create directory
        try {
            std::string codeDir = Core::DirUtils::CreateTempDir("/tmp");
            if (Core::StringUtils::ContainsIgnoreCase(runtime, "java")) {

                // Create classes directory
                std::string classesDir = codeDir + Poco::Path::separator() + "classes";
                Core::DirUtils::EnsureDirectory(classesDir);

                // Decompress
                std::stringstream input(decodedZipFile);
                Poco::Zip::Decompress dec(input, Poco::Path(classesDir));
                dec.decompressAllFiles();
                input.clear();
                log_debug << "ZIP file unpacked, dir: " << codeDir;

            } else {

                // Create directory
                Core::DirUtils::EnsureDirectory(codeDir);

                // Write to temp file
                std::ofstream ofs(_tempDir + "/zipfile.zip");
                ofs << decodedZipFile;
                ofs.close();

                // Decompress
                Core::ExecResult result = Core::SystemUtils::Exec("unzip -o -d " + codeDir + " " + _tempDir + "/zipfile.zip");
                log_debug << "ZIP file unpacked, dir: " << codeDir << " result: " << result.status;
            }
            return codeDir;

        } catch (Poco::Exception &exc) {
            log_error << "Could not unzip lambda code, error: " << exc.message();
        }
        return {};
    }

    std::vector<std::string> LambdaCreator::GetEnvironment(const Database::Entity::Lambda::Environment &lambdaEnvironment) {

        std::vector<std::string> environment;
        environment.reserve(lambdaEnvironment.variables.size());
        for (const auto &variable: lambdaEnvironment.variables) {
            environment.emplace_back(variable.first + "=" + variable.second);
        }
        log_debug << "lambda runtime environment converted, size: " << environment.size();
        return environment;
    }

    int LambdaCreator::GetHostPort() {
        return Core::RandomUtils::NextInt(HOST_PORT_MIN, HOST_PORT_MAX);
    }

    std::string LambdaCreator::GetDockerTag(const Database::Entity::Lambda::Lambda &lambda) {
        if (lambda.HasTag("version")) {
            return lambda.GetTagValue("version");
        }
        if (lambda.HasTag("dockerTag")) {
            return lambda.GetTagValue("dockerTag");
        }
        if (lambda.HasTag("tag")) {
            return lambda.GetTagValue("tag");
        }
        return "latest";
    }
}// namespace AwsMock::Service
