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
        _database = std::make_unique<Database::LambdaDatabase>(_configuration);

        // Create temp directory
        if (!Core::DirUtils::DirectoryExists(_tempDir)) {
            Core::DirUtils::MakeDirectory(_tempDir);
        }
        poco_information(_logger, "Lambda service initialized");
    }

    Dto::Lambda::CreateFunctionResponse LambdaService::CreateFunction(Dto::Lambda::CreateFunctionRequest &request) {
        poco_debug(_logger, "Create function request: " + request.ToString());

        std::string codeDir;
        if (!request.code.zipFile.empty()) {
            codeDir = UnpackZipFile(request.code.zipFile);
        }

        // Build the docker image
        BuildDockerImage(codeDir, request.functionName, request.handler);

        // Create ARN
        std::string arn = Core::AwsUtils::CreateLambdaArn(_region, _accountId, request.functionName);

        // Create response
        Dto::Lambda::CreateFunctionResponse
            response{.functionArn=arn, .functionName=request.functionName, .runtime=request.runtime, .role=request.role, .handler=request.handler,
            .environment=request.environment, .memorySize=request.memorySize};
        return response;
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

    std::string LambdaService::BuildDockerImage(const std::string &codeDir, const std::string &name, const std::string &handler) {

        std::string dockerFile = WriteDockerFile(codeDir, handler);

        std::string output;
        std::string cmd = "docker build -t " + name + ":latest -f " + dockerFile + " " + codeDir;
        poco_debug(_logger, "Executing command, cmd: " + cmd);

        Core::ExecResult result = Core::SystemUtils::Exec(cmd);
        poco_debug(_logger, "Build docker image exit code: " + std::to_string(result.status) + " output: " + result.output);

        return result.output;
    }

    std::string LambdaService::WriteDockerFile(const std::string &codeDir, const std::string &handler) {

        std::string dockerFilename=codeDir + "Dockerfile";

        std::ofstream ofs(dockerFilename);
        ofs << "FROM public.ecr.aws/lambda/java:17" << std::endl;
        ofs << "COPY classes/* ${LAMBDA_TASK_ROOT}/lib/" << std::endl;
        ofs << "CMD [ \"" + handler + "::handleRequest\" ]" << std::endl;
        poco_debug(_logger, "Dockerfile written, filename: " + dockerFilename);

        return dockerFilename;
    }


} // namespace AwsMock::Service
