//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/LambdaService.h>

namespace AwsMock::Service {

    using namespace Poco::Data::Keywords;

    LambdaService::LambdaService(const Core::Configuration &configuration) : _logger(Poco::Logger::get("LambdaService")), _configuration(configuration) {
        Initialize();
    }

    void LambdaService::Initialize() {

        // Set console logger
        Core::Logger::SetDefaultConsoleLogger("LambdaService");

        // Initialize environment
        _region = _configuration.getString("awsmock.region", "eu-central-1");
        _accountId = _configuration.getString("awsmock.account.id", "000000000000");
        _dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data");
        _tempDir = _dataDir + Poco::Path::separator() + "tmp";
        _lambdaDatabase = std::make_unique<Database::LambdaDatabase>(_configuration);
        _s3Database = std::make_unique<Database::S3Database>(_configuration);
        _dockerService = std::make_unique<Service::DockerService>(_configuration);

        // Create temp directory
        if (!Core::DirUtils::DirectoryExists(_tempDir)) {
            Core::DirUtils::MakeDirectory(_tempDir);
        }
        poco_information(_logger, "Lambda service initialized");
    }

    Dto::Lambda::CreateFunctionResponse LambdaService::CreateFunctionConfiguration(Dto::Lambda::CreateFunctionRequest &request) {
        poco_debug(_logger, "Create function configuration request: " + request.ToString());

        Database::Entity::Lambda::Lambda lambdaEntity = {.function=request.functionName, .runtime=request.runtime, .role=request.role, .handler=request.handler,
            .tag=IMAGE_TAG};

        // Build the docker image, if not existing
        if (!_dockerService->ImageExists(request.functionName, "latest")) {

            // Unzip provided zip-file
            std::string codeDir;
            if (!request.code.zipFile.empty()) {
                codeDir = UnpackZipFile(request.code.zipFile);
            }

            // Build the docker image
            _dockerService->BuildImage(codeDir, request.functionName, "latest", request.handler);

            // Cleanup
            Core::DirUtils::DeleteDirectory(codeDir);
        }

        // Get the image struct
        Dto::Docker::Image image = _dockerService->GetImageByName(request.functionName, "latest");
        lambdaEntity.size = image.size;
        lambdaEntity.imageId = image.id;

        // Create the container, if not existing
        if (!_dockerService->ContainerExists(request.functionName, "latest")) {
            Dto::Docker::CreateContainerResponse containerCreateResponse = _dockerService->CreateContainer(request.functionName, "latest");
            lambdaEntity.hostPort = containerCreateResponse.hostPort;
        }

        // Get the container
        Dto::Docker::Container container = _dockerService->GetContainerByName(request.functionName, "latest");
        lambdaEntity.containerId = container.id;

        // Start container
        _dockerService->StartContainer(container.id);
        lambdaEntity.lastStarted = Poco::DateTime();

        // Update database
        lambdaEntity.arn = Core::AwsUtils::CreateLambdaArn(_region, _accountId, request.functionName);
        lambdaEntity = _lambdaDatabase->CreateOrUpdateLambda(lambdaEntity);

        // Create response
        Dto::Lambda::CreateFunctionResponse
            response{.functionArn=lambdaEntity.arn, .functionName=request.functionName, .runtime=request.runtime, .role=request.role, .handler=request.handler,
            .environment=request.environment, .memorySize=request.memorySize, .dockerImageId=image.id, .dockerContainerId=container.id};

        return response;
    }

    Dto::Lambda::CreateFunctionResponse InvokeEventFunction(const Dto::S3::EventNotification &notification){

    }

    std::string LambdaService::UnpackZipFile(const std::string &zipFile) {

        std::string decodedZipFile = Core::Crypto::Base64Decode(zipFile);

        // Create directory
        std::string codeDir = _tempDir + Poco::Path::separator() + Poco::UUIDGenerator().createRandom().toString() + Poco::Path::separator();
        std::string classesDir = codeDir + "classes";
        if (Core::DirUtils::DirectoryExists(classesDir)) {
            Core::DirUtils::MakeDirectory(classesDir);
        }

        // Decompress
        std::stringstream input(decodedZipFile);
        Poco::Zip::Decompress dec(input, Poco::Path(classesDir));
        dec.decompressAllFiles();
        input.clear();

        return codeDir;
    }

} // namespace AwsMock::Service
