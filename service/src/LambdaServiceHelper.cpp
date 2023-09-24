//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/LambdaServiceHelper.h>

namespace AwsMock::Service {

    LambdaServiceHelper::LambdaServiceHelper(const Core::Configuration &configuration)
        : CreateLambdaFunction(this, &LambdaServiceHelper::CreateLambdaFunctionImpl), _configuration(configuration), _dockerService(configuration) {
    }

    void LambdaServiceHelper::CreateLambdaFunctionImpl(const std::pair<std::string, std::string> &lambda) {
        Core::LogStream logger(Poco::Logger::get("LambdaServiceHelper"));
        log_debug_stream(logger) << "Start creating lambda function, oid: " << lambda.second << std::endl;

        // Configuration
        std::shared_ptr<Database::LambdaDatabase> _lambdaDatabase = std::make_shared<Database::LambdaDatabase>(_configuration);

        // Make local copy
        Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase->GetLambdaById(lambda.second);

        // Docker tag
        std::string dockerTag = "latest";
        if (lambdaEntity.HasTag("tag")) {
            dockerTag = lambdaEntity.GetTagValue("tag");
        }
        log_debug_stream(logger) << "Using docker tag: " << dockerTag << std::endl;

        // Build the docker image, if not existing
        if (!_dockerService.ImageExists(lambdaEntity.function, dockerTag)) {
            CreateDockerImage(lambda.first, lambdaEntity, dockerTag, logger);
        }

        // Create the container, if not existing. If existing get the current port from the docker container
        if (!_dockerService.ContainerExists(lambdaEntity.function, dockerTag)) {
            lambdaEntity.hostPort = GetHostPort();
            CreateDockerContainer(lambdaEntity, dockerTag, logger);
        }

        // Get docker container
        Dto::Docker::Container container = _dockerService.GetContainerByName(lambdaEntity.function, dockerTag);
        lambdaEntity.hostPort = container.GetLambdaPort();

        // Start docker container
        _dockerService.StartDockerContainer(container.id);

        // Update database
        lambdaEntity.containerId = container.id;
        lambdaEntity.lastStarted = Poco::DateTime();
        lambdaEntity.state = Database::Entity::Lambda::LambdaState::Active;
        lambdaEntity.stateReason = "Activated";
        _lambdaDatabase->UpdateLambda(lambdaEntity);

        log_debug_stream(logger) << "Lambda function started: " << lambdaEntity.function << ":" << dockerTag << std::endl;
    }

    void LambdaServiceHelper::CreateDockerImage(const std::string &zipFile,
                                                Database::Entity::Lambda::Lambda &lambdaEntity,
                                                const std::string &dockerTag,
                                                Core::LogStream &logger) {

        if (zipFile.empty()) {
            log_error_stream(logger) << "Empty lambda zip file" << std::endl;
            return;
        }

        // Unzip provided zip-file into a temporary directory
        std::string codeDir = UnpackZipFile(zipFile, lambdaEntity.runtime, lambdaEntity.fileName, logger);

        // Build the docker image using the docker service
        std::string imageFile =
            _dockerService.BuildImage(codeDir, lambdaEntity.function, dockerTag, lambdaEntity.handler, lambdaEntity.runtime, lambdaEntity.environment.variables);

        // Get the image struct
        Dto::Docker::Image image = _dockerService.GetImageByName(lambdaEntity.function, dockerTag);
        lambdaEntity.codeSize = image.size;
        lambdaEntity.imageId = image.id;
        lambdaEntity.codeSha256 = Core::Crypto::GetSha256FromFile(imageFile);

        // Cleanup
        Core::DirUtils::DeleteDirectory(codeDir);
        log_debug_stream(logger) << "Docker image created, name: " << lambdaEntity.function << " size: " << lambdaEntity.codeSize << std::endl;
    }

    void LambdaServiceHelper::CreateDockerContainer(Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag,
                                                    Core::LogStream &logger) {

        try {
            std::vector<std::string> environment = GetEnvironment(lambdaEntity.environment, logger);
            Dto::Docker::CreateContainerResponse
                containerCreateResponse = _dockerService.CreateContainer(lambdaEntity.function, dockerTag, environment, lambdaEntity.hostPort);
            log_debug_stream(logger) << "Lambda container created, hostPort: " << lambdaEntity.hostPort << std::endl;
        } catch (std::exception &exc) {
            log_error_stream(logger) << exc.what() << std::endl;
        }
    }

    std::string LambdaServiceHelper::UnpackZipFile(const std::string &zipFile, const std::string &runtime, const std::string &fileName,
                                                   Core::LogStream &logger) {

        // If we do not have a local file already, write the Base64 encoded file to lambda dir
        if (!Core::FileUtils::FileExists(fileName)) {
            std::ofstream ofs(fileName);
            ofs << zipFile;
            ofs.flush();
            ofs.close();
        }

        std::string decodedZipFile = Core::Crypto::Base64Decode(zipFile);

        // Create directory
        std::string codeDir = Core::DirUtils::CreateTempDir();
        if (Core::StringUtils::ContainsIgnoreCase(runtime, "java")) {

            // Create classes directory
            std::string classesDir = codeDir + Poco::Path::separator() + "classes";
            if (!Core::DirUtils::DirectoryExists(classesDir)) {
                Core::DirUtils::MakeDirectory(classesDir);
            }

            // Decompress
            std::stringstream input(decodedZipFile);
            Poco::Zip::Decompress dec(input, Poco::Path(classesDir));
            dec.decompressAllFiles();
            input.clear();
            log_debug_stream(logger) << "ZIP file unpacked, dir: " << codeDir << std::endl;

        } else {

            if (!Core::DirUtils::DirectoryExists(codeDir)) {
                Core::DirUtils::MakeDirectory(codeDir);
            }

            // Write to temp file
            std::ofstream ofs(_tempDir + "/zipfile.zip");
            ofs << decodedZipFile;
            ofs.close();

            // Decompress
            Core::ExecResult result = Core::SystemUtils::Exec("unzip -o -d " + codeDir + " " + _tempDir + "/zipfile.zip");
            log_debug_stream(logger) << "ZIP file unpacked, dir: " << codeDir << " result: " << result.status << std::endl;
        }

        return codeDir;
    }

    std::vector<std::string> LambdaServiceHelper::GetEnvironment(const Database::Entity::Lambda::Environment &lambdaEnvironment,
                                                                 Core::LogStream &logger) {

        std::vector<std::string> environment;
        environment.reserve(lambdaEnvironment.variables.size());
        for (const std::pair<std::string, std::string> &variable : lambdaEnvironment.variables) {
            environment.emplace_back(variable.first + "=" + variable.second);
        }
        log_debug_stream(logger) << "Lambda runtime environment converted, size: " << environment.size() << std::endl;
        return environment;
    }

    int LambdaServiceHelper::GetHostPort() {
        return Core::RandomUtils::NextInt(HOST_PORT_MIN, HOST_PORT_MAX);
    }
} // namespace AwsMock::Service
