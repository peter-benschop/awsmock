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

    void LambdaService::InvokeEventFunction(const Dto::S3::EventNotification &notification) {
        poco_debug(_logger, "Invoke event function notification: " + notification.ToString());

        for (const auto &record : notification.records) {

            // Get the bucket notification
            Database::Entity::S3::BucketNotification
                bucketNotification = _s3Database->GetBucketNotificationByNotificationId(record.region, record.s3.bucket.name, record.s3.configurationId);
            poco_debug(_logger, "Got bucket notification: " + bucketNotification.ToString());

            // Get the lambda entity
            Database::Entity::Lambda::Lambda lambda = _lambdaDatabase->GetLambdaByArn(bucketNotification.lambdaArn);
            poco_debug(_logger, "Got lambda entity notification: " + lambda.ToString());

            SendInvokeRequest(lambda.hostPort, notification.ToJson());
        }
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

    void LambdaService::SendInvokeRequest(int port, const std::string &body) {

        Poco::URI uri("http://localhost:" + std::to_string(port) + "/2015-03-31/functions/function/invocations");
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type","application/json");
        request.setContentLength((long)body.length());
        poco_debug(_logger, "Invocation request defined, body: " + body);

        // Send request
        std::ostream& os = session.sendRequest(request);
        os << body;

        // Get the response sttaus
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            poco_error(_logger, "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: "+ response.getReason());
        }
        poco_debug(_logger, "Invocation request send, status: " + std::to_string(response.getStatus()));
    }
} // namespace AwsMock::Service
