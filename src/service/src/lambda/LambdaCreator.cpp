//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/lambda/LambdaCreator.h>

namespace AwsMock::Service {

    void LambdaCreator::operator()(std::string &functionCode, const std::string &functionId, const std::string &instanceId) const {

        log_debug << "Start creating lambda function, oid: " << functionId;

        // Make local copy
        Database::Entity::Lambda::Lambda lambdaEntity = Database::LambdaDatabase::instance().GetLambdaById(functionId);

        CreateInstance(instanceId, lambdaEntity, functionCode);

        // Update database
        lambdaEntity.lastStarted = system_clock::now();
        lambdaEntity.state = Database::Entity::Lambda::LambdaState::Active;
        lambdaEntity.stateReason = "Activated";
        lambdaEntity = Database::LambdaDatabase::instance().UpdateLambda(lambdaEntity);

        log_debug << "Lambda function created: " << lambdaEntity.function;
    }

    void LambdaCreator::CreateInstance(const std::string &instanceId, Database::Entity::Lambda::Lambda &lambdaEntity, std::string &functionCode) {

        // Docker tag
        std::string dockerTag = GetDockerTag(lambdaEntity);
        log_debug << "Using docker tag: " << dockerTag;

        // Build the docker image, if not existing
        if (!ContainerService::instance().ImageExists(lambdaEntity.function, dockerTag)) {
            CreateDockerImage(functionCode, lambdaEntity, dockerTag);
        }

        // Create the container, if not existing. If existing get the current port from the docker container
        std::string containerName = lambdaEntity.function + "-" + instanceId;
        if (!ContainerService::instance().ContainerExistsByName(containerName)) {
            Database::Entity::Lambda::Instance instance;
            instance.hostPort = CreateRandomHostPort();
            instance.id = instanceId;
            instance.containerName = containerName;
            instance.status = Database::Entity::Lambda::InstanceIdle;
            CreateDockerContainer(lambdaEntity, instance, dockerTag);
            lambdaEntity.instances.emplace_back(instance);
        }

        // Get docker container
        Dto::Docker::Container container = ContainerService::instance().GetContainerByName(containerName);

        // Start docker container, in case it is not already running.
        if (container.state != "running") {
            ContainerService::instance().StartDockerContainer(container.id);
            log_debug << "Lambda docker container started, containerId: " << container.id;
        }

        // Save size in entity
        lambdaEntity.containerSize = container.sizeRootFs;
    }

    void LambdaCreator::CreateDockerImage(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag) {

        std::string codeDir = Core::DirUtils::CreateTempDir("/tmp");
        const std::string dataDir = Core::Configuration::instance().GetValueString("awsmock.data-dir");

        // Write base64 encoded zip file
        const std::string encodedFile = WriteBase64File(zipFile, lambdaEntity, dockerTag, dataDir);

        // Unzip provided zip-file into a temporary directory
        codeDir = UnpackZipFile(codeDir, encodedFile, lambdaEntity.runtime);
        log_debug << "Lambda file unzipped, codeDir: " << codeDir;

        // Build the docker image using the docker module
        const std::string imageFile = ContainerService::instance().BuildImage(codeDir, lambdaEntity.function, dockerTag, lambdaEntity.handler, lambdaEntity.runtime, lambdaEntity.environment.variables);

        // Get the image struct
        const Dto::Docker::Image image = ContainerService::instance().GetImageByName(lambdaEntity.function, dockerTag);
        lambdaEntity.codeSize = static_cast<long>(zipFile.size());
        lambdaEntity.imageId = image.id;
        lambdaEntity.imageSize = image.size;
        lambdaEntity.codeSha256 = Core::Crypto::GetSha256FromFile(imageFile);

        // Cleanup
        Core::DirUtils::DeleteDirectory(codeDir);
        log_debug << "Docker image created, name: " << lambdaEntity.function << " size: " << lambdaEntity.codeSize;
    }

    void LambdaCreator::CreateDockerContainer(const Database::Entity::Lambda::Lambda &lambdaEntity, Database::Entity::Lambda::Instance &instance, const std::string &dockerTag) {

        try {

            const std::string containerName = lambdaEntity.function + "-" + instance.id;
            const std::vector<std::string> environment = GetEnvironment(lambdaEntity.environment);
            const Dto::Docker::CreateContainerResponse containerCreateResponse = ContainerService::instance().CreateContainer(lambdaEntity.function, containerName, dockerTag, environment, instance.hostPort);
            instance.containerId = containerCreateResponse.id;
            log_debug << "Lambda container created, hostPort: " << instance.hostPort << " containerId: " << instance.containerId;

        } catch (std::exception &exc) {
            log_error << exc.what();
        }
    }

    std::string LambdaCreator::UnpackZipFile(const std::string &codeDir, const std::string &zipFile, const std::string &runtime) {

        std::string dataDir = Core::Configuration::instance().GetValueString("awsmock.data-dir");
        std::string tempDir = dataDir + Core::FileUtils::separator() + "tmp";

        // Decode Base64 file
        std::stringstream stringStream;
        std::ifstream ifs(zipFile);
        stringStream << ifs.rdbuf();
        ifs.close();

        std::string decoded = Core::Crypto::Base64Decode(stringStream.str());

        try {

            // Write to temp file
            std::ofstream ofs(tempDir + "/zipfile.zip");
            ofs << decoded;
            ofs.close();

            // Save zip file
            if (Core::StringUtils::ContainsIgnoreCase(runtime, "java")) {

                // Create classes directory
                std::string classesDir = codeDir + Core::FileUtils::separator() + "classes";
                Core::DirUtils::EnsureDirectory(classesDir);

                // Decompress
                Core::TarUtils::Unzip(tempDir + "/zipfile.zip", classesDir);

            } else {

                // Decompress
                std::string extractDir = Core::DirUtils::CreateTempDir("/tmp");
                Core::TarUtils::Unzip(tempDir + "/zipfile.zip", extractDir);
            }
            log_debug << "ZIP file unpacked, dir: " << codeDir;
            return codeDir;

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::vector<std::string> LambdaCreator::GetEnvironment(const Database::Entity::Lambda::Environment &lambdaEnvironment) {

        std::vector<std::string> environment;
        environment.reserve(lambdaEnvironment.variables.size());
        for (const auto &[fst, snd]: lambdaEnvironment.variables) {
            environment.emplace_back(fst + "=" + snd);
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
        return std::copy(std::istreambuf_iterator(ifs), {}, out);
    }

    std::string LambdaCreator::WriteBase64File(const std::string &zipFile, Database::Entity::Lambda::Lambda &lambdaEntity, const std::string &dockerTag, const std::string &dataDir) {

        std::string s3DataDir = dataDir + Core::FileUtils::separator() + "s3";
        std::string lambdaDir = dataDir + Core::FileUtils::separator() + "lambda";

        std::string base64Path = lambdaDir + Core::FileUtils::separator();
        std::string base64File = lambdaEntity.function + "-" + dockerTag + ".zip";
        std::string base64FullFile = base64Path + base64File;

        std::string base64EncodedCodeString = zipFile;

        // Write base64 string, either from S3 bucket/key or from supplied string
        if (zipFile.empty()) {

            // Get internal name of S3 object
            Database::Entity::S3::Object s3Object = Database::S3Database::instance().GetObject(lambdaEntity.region, lambdaEntity.code.s3Bucket, lambdaEntity.code.s3Key);
            std::string s3CodeFile = s3DataDir + Core::FileUtils::separator() + s3Object.internalName;

            // Load file
            std::vector<char> input;
            load_file(s3CodeFile, back_inserter(input));

            // Allocate "enough" space, using an upperbound prediction:
            std::string encoded(boost::beast::detail::base64::encoded_size(input.size()), '\0');

            // Encode returns the actual encoded_size
            auto encoded_size = boost::beast::detail::base64::encode(encoded.data(), input.data(), input.size());
            encoded.resize(encoded_size);

            base64EncodedCodeString = encoded;
        }

        // If we do not have a local file already or the MD5 sum changed, write the Base64 encoded file to lambda dir
        if (!Core::FileUtils::FileExists(base64FullFile)) {

            std::ofstream ofs(base64FullFile);
            ofs << base64EncodedCodeString;
            ofs.close();

        } else {

            std::string md5sumFile = Core::Crypto::GetMd5FromFile(base64FullFile);
            if (std::string md5sumString = Core::Crypto::GetMd5FromString(base64EncodedCodeString); md5sumFile != md5sumString) {
                std::ofstream ofs(base64FullFile);
                ofs << base64EncodedCodeString;
                ofs.close();
            }
        }

        lambdaEntity.code.zipFile = base64File;
        return base64FullFile;
    }
}// namespace AwsMock::Service
