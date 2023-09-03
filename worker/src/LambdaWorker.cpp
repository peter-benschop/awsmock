//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/LambdaWorker.h>

namespace AwsMock::Worker {

    [[maybe_unused]] LambdaWorker::LambdaWorker(const Core::Configuration &configuration)
        : AbstractWorker(configuration), _logger(Poco::Logger::get("LambdaWorker")), _configuration(configuration), _running(false) {

        _dataDir = _configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "lambda";
        _logger.debug() << "Lambda directory: " << _dataDir << std::endl;

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
        log_debug_stream(_logger) << "Lambda worker period: " << _period << std::endl;

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _lambdaDatabase = std::make_unique<Database::LambdaDatabase>(_configuration);

        // Lambda service connection
        _lambdaServiceHost = _configuration.getString("awsmock.service.lambda.host", "localhost");
        _lambdaServicePort = _configuration.getInt("awsmock.service.lambda.port", 9503);
        log_debug_stream(_logger) << "Lambda service endpoint: http://" << _lambdaServiceHost << ":" << _lambdaServicePort << std::endl;

        // Create lambda directory
        if (!Core::DirUtils::DirectoryExists(_dataDir)) {
            Core::DirUtils::MakeDirectory(_dataDir);
        }

        log_debug_stream(_logger) << "LambdaWorker initialized" << std::endl;
    }

    void LambdaWorker::StartLambdaFunctions() {

        log_debug_stream(_logger) << "Starting lambdas" << std::endl;
        std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase->ListLambdas(_region);

        for (auto &lambda : lambdas) {

            Dto::Lambda::Code code = GetCode(lambda);

            Dto::Lambda::Tags tags = {
                .tags=lambda.tags.tags
            };

            // Create create function request
            Dto::Lambda::CreateFunctionRequest request = {
                .region=lambda.region,
                .functionName=lambda.function,
                .runtime=lambda.runtime,
                .code=code,
                .tags=tags
            };
            SendCreateFunctionRequest(request, "application/json");
            log_debug_stream(_logger) << "Lambda started, name:" << lambda.function << std::endl;
        }
    }

    Dto::Lambda::Code LambdaWorker::GetCode(const Database::Entity::Lambda::Lambda &lambda) {

        Dto::Lambda::Code code;
        if (Core::FileUtils::FileExists(lambda.fileName)) {
            std::stringstream ss;
            std::ifstream ifs(lambda.fileName);
            ss << ifs.rdbuf();
            ifs.close();

            code = {
                .zipFile=ss.str()
            };
            log_debug_stream(_logger) << "Loaded lambda from file:" << lambda.fileName << " size: " << Core::FileUtils::FileSize(lambda.fileName) << std::endl;
        }
        return code;
    }

    void LambdaWorker::run() {

        log_info_stream(_logger) << "Lambda worker started" << std::endl;

        // Check service active
        /*if (!_serviceDatabase->IsActive("Lambda")) {
            return;
        }*/

        // Start all lambda functions
        Poco::Thread::sleep(5000);
        StartLambdaFunctions();

        _running = true;
        while (_running) {
            log_debug_stream(_logger) << "LambdaWorker processing started" << std::endl;
            Poco::Thread::sleep(_period);
        }
    }

    void LambdaWorker::SendCreateFunctionRequest(Dto::Lambda::CreateFunctionRequest &lambdaRequest, const std::string &contentType) {

        std::string url = "http://" + _lambdaServiceHost + ":" + std::to_string(_lambdaServicePort) + "/2015-03-31/functions";
        std::string body = lambdaRequest.ToJson();
        SendPostRequest(url, body, contentType);
        log_debug_stream(_logger) << "Lambda create function request send" << std::endl;
    }

} // namespace AwsMock::Worker
