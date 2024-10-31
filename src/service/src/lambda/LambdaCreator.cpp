//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/lambda/LambdaCreator.h>

#include <utility>

namespace AwsMock::Service {

    void LambdaCreator::operator()(std::string &functionCode, std::string &functionId, std::string &instanceId) {

        log_debug << "Start creating lambda function, oid: " << functionId;

        // Make local copy
        Database::Entity::Lambda::Lambda lambdaEntity = Database::LambdaDatabase::instance().GetLambdaById(functionId);

        CreateInstance(instanceId, lambdaEntity, functionCode);

        // Update database
        lambdaEntity.lastStarted = std::chrono::system_clock::now();
        lambdaEntity.state = Database::Entity::Lambda::LambdaState::Active;
        lambdaEntity.stateReason = "Activated";
        Database::LambdaDatabase::instance().UpdateLambda(lambdaEntity);

        log_debug << "Lambda function created: " << lambdaEntity.function;
    }

    void LambdaCreator::CreateInstance(const std::string &instanceId, Database::Entity::Lambda::Lambda &lambdaEntity, std::string &functionCode) {

        // Docker tag
        std::string dockerTag = GetDockerTag(lambdaEntity);
        log_debug << "Using docker tag: " << dockerTag;

        // Build the docker image, if not existing
        if (!DockerService::instance().ImageExists(lambdaEntity.function, dockerTag)) {
            CreateDockerImage(functionCode, lambdaEntity, dockerTag);
        }

        // Create the container, if not existing. If existing get the current port from the docker container
        std::string containerName = lambdaEntity.function + "-" + instanceId;
        if (!DockerService::instance().ContainerExists(containerName, dockerTag)) {
            Database::Entity::Lambda::Instance instance;
            instance.hostPort = CreateRandomHostPort();
            instance.id = instanceId;
            instance.containerName = containerName;
            instance.status = Database::Entity::Lambda::InstanceIdle;
            CreateDockerContainer(lambdaEntity, instance, dockerTag);
            lambdaEntity.instances.emplace_back(instance);
        }

        // Get docker container
        Dto::Docker::Container container = DockerService::instance().GetFirstContainerByImageName(lambdaEntity.function, dockerTag);

        // Start docker container, in case it is not already running.
        if (container.state != "running") {
            DockerService::instance().StartDockerContainer(container.id);
            log_debug << "Lambda docker container started, containerId: " << container.id;
        }
    }

    void LambdaCreator::CreateDockerImage(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag) {

        std::string codeDir = Core::DirUtils::CreateTempDir("/tmp");
        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", "/tmp/awsmock/data");

        // Write base64 encoded zip file
        std::string encodedFile = WriteBase64File(zipFile, lambdaEntity, dockerTag, dataDir);

        // Unzip provided zip-file into a temporary directory
        codeDir = UnpackZipFile(codeDir, encodedFile, lambdaEntity.runtime);
        log_debug << "Lambda file unzipped, codeDir: " << codeDir;

        // Build the docker image using the docker module
        std::string imageFile = DockerService::instance().BuildImage(codeDir, lambdaEntity.function, dockerTag, lambdaEntity.handler, lambdaEntity.runtime, lambdaEntity.environment.variables);

        // Get the image struct
        Dto::Docker::Image image = DockerService::instance().GetImageByName(lambdaEntity.function, dockerTag);
        lambdaEntity.codeSize = image.size;
        lambdaEntity.imageId = image.id;
        lambdaEntity.codeSha256 = Core::Crypto::GetSha256FromFile(imageFile);

        // Cleanup
        Core::DirUtils::DeleteDirectory(codeDir);
        log_debug << "Docker image created, name: " << lambdaEntity.function << " size: " << lambdaEntity.codeSize;
    }

    void LambdaCreator::CreateDockerContainer(Database::Entity::Lambda::Lambda &lambdaEntity, Database::Entity::Lambda::Instance &instance, const std::string &dockerTag) {

        try {

            std::string containerName = lambdaEntity.function + "-" + instance.id;
            std::vector<std::string> environment = GetEnvironment(lambdaEntity.environment);
            Dto::Docker::CreateContainerResponse containerCreateResponse = DockerService::instance().CreateContainer(lambdaEntity.function, containerName, dockerTag, environment, instance.hostPort);
            instance.containerId = containerCreateResponse.id;
            log_debug << "Lambda container created, hostPort: " << instance.hostPort << " containerId: " << instance.containerId;

        } catch (std::exception &exc) {
            log_error << exc.what();
        }
    }

    std::string LambdaCreator::UnpackZipFile(const std::string &codeDir, const std::string &zipFile, const std::string &runtime) {

        std::string dataDir = Core::Configuration::instance().getString("awsmock.data.dir", "/tmp/awsmock/data");
        std::string tempDir = dataDir + Poco::Path::separator() + "tmp";

        // Decode Base64 file
        std::stringstream stringStream;
        std::ifstream ifs(zipFile);
        stringStream << ifs.rdbuf();
        ifs.close();

        std::string decoded = Core::Crypto::Base64Decode(stringStream.str());

        try {

            // Save zip file
            if (Core::StringUtils::ContainsIgnoreCase(runtime, "java")) {

                // Create classes directory
                std::string classesDir = codeDir + Poco::Path::separator() + "classes";
                Core::DirUtils::EnsureDirectory(classesDir);

                // Decompress
                std::stringstream input(decoded);
                Poco::Zip::Decompress dec(input, Poco::Path(classesDir));
                dec.decompressAllFiles();
                input.clear();
                log_debug << "ZIP file unpacked, dir: " << codeDir;

            } else {

                // Write to temp file
                std::ofstream ofs(tempDir + "/zipfile.zip");
                ofs << decoded;
                ofs.close();

                // Decompress
                Core::ExecResult result = Core::SystemUtils::Exec("unzip -o -d " + codeDir + " " + tempDir + "/zipfile.zip");
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

    int LambdaCreator::CreateRandomHostPort() {
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

    template<typename Out>
    Out load_file(std::string const &filename, Out out) {
        std::ifstream ifs(filename, std::ios::binary);
        ifs.exceptions(std::ios::failbit | std::ios::badbit);// we prefer exceptions
        return std::copy(std::istreambuf_iterator<char>(ifs), {}, out);
    }

    std::string LambdaCreator::WriteBase64File(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag, const std::string &dataDir) {

        std::string s3DataDir = dataDir + Poco::Path::separator() + "s3";
        std::string lambdaDir = dataDir + Poco::Path::separator() + "lambda";

        std::string base64Path = lambdaDir + Poco::Path::separator();
        std::string base64File = lambdaEntity.function + "-" + dockerTag + ".zip";
        std::string base64FullFile = base64Path + base64File;

        // Write Base64 ZIP file
        if (!Core::FileUtils::FileExists(base64FullFile)) {

            // Write base64 zip file, either from S3 bucket/key or from supplied string
            if (zipFile.empty()) {

                // Get internal name of S3 object
                Database::Entity::S3::Object s3Object = Database::S3Database::instance().GetObject(lambdaEntity.region, lambdaEntity.code.s3Bucket, lambdaEntity.code.s3Key);
                std::string s3CodeFile = s3DataDir + Poco::Path::separator() + s3Object.internalName;

                // Load file
                std::vector<char> input;
                load_file(s3CodeFile, back_inserter(input));

                // Allocate "enough" space, using an upperbound prediction:
                std::string encoded(boost::beast::detail::base64::encoded_size(input.size()), '\0');

                // Encode returns the actual encoded_size
                auto encoded_size = boost::beast::detail::base64::encode(encoded.data(), input.data(), input.size());
                encoded.resize(encoded_size);
                std::ofstream(base64FullFile) << encoded;

            } else {

                // If we do not have a local file already, write the Base64 encoded file to lambda dir
                std::ofstream ofs(base64FullFile);
                ofs << zipFile;
                ofs.close();
            }
        }
        lambdaEntity.code.zipFile = base64File;
        return base64FullFile;
    }
}// namespace AwsMock::Service
