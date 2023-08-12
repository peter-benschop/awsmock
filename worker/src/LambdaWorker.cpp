//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/LambdaWorker.h>

namespace AwsMock::Worker {

    [[maybe_unused]] LambdaWorker::LambdaWorker(const Core::Configuration &configuration)
        : _logger(Poco::Logger::get("LambdaWorker")), _configuration(configuration), _running(false) {

        Initialize();
    }

    void LambdaWorker::Initialize() {

        _dataDir = _configuration.getString("awsmock.data.dir") + Poco::Path::separator() + "lambda";
        _logger.debug() << "Lambda directory: " << _dataDir << std::endl;

        // Sleeping period
        _period = _configuration.getInt("awsmock.worker.lambda.period", 10000);
        log_debug_stream(_logger) << "Lambda worker period: " << _period << std::endl;

        // Create lambda directory
        if (!Core::DirUtils::DirectoryExists(_dataDir)) {
            Core::DirUtils::MakeDirectory(_dataDir);
        }

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _clientId = _configuration.getString("awsmock.client.id", "00000000");
        _user = _configuration.getString("awsmock.user", "none");
        _s3Service = std::make_unique<Service::S3Service>(_configuration);
        _lambdaDatabase = std::make_unique<Database::LambdaDatabase>(_configuration);

        // Lambda service connection
        _lambdaServiceHost = _configuration.getString("awsmock.service.lambda.host", "localhost");
        _lambdaServicePort = _configuration.getInt("awsmock.service.lambda.port", 9503);
        log_debug_stream(_logger) << "Lambda service endpoint: http://" << _lambdaServiceHost << ":" << _lambdaServicePort << std::endl;

        log_debug_stream(_logger) << "LambdaWorker initialized" << std::endl;
    }

    void LambdaWorker::StartLambdaFunctions() {

        log_debug_stream(_logger) << "Starting lambdas" << std::endl;
        std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase->ListLambdas(_region);

        for(auto &lambda : lambdas){

            // Create create function request
            Dto::Lambda::CreateFunctionRequest request = {.region=lambda.region, .functionName=lambda.function, .runtime=lambda.runtime};
            SendCreateFunctionRequest(request, "application/json");
            log_debug_stream(_logger) << "Lambda started, name:" << lambda.function <<std::endl;
        }
    }

    void LambdaWorker::run() {

        log_info_stream(_logger) << "Lambda worker started" << std::endl;

        // Check service active
        /*if (!_serviceDatabase->IsActive("Lambda")) {
            return;
        }*/

        // Start all lambda functions
        StartLambdaFunctions();

        _running = true;
        while (_running) {
            log_debug_stream(_logger) << "LambdaWorker processing started" << std::endl;
            Poco::Thread::sleep(_period);
        }
    }

    void LambdaWorker::SendCreateFunctionRequest(Dto::Lambda::CreateFunctionRequest &lambdaRequest, const std::string &contentType) {

        Poco::URI uri("http://" + _lambdaServiceHost + ":" + std::to_string(_lambdaServicePort) + "/2015-03-31/functions");
        std::string path(uri.getPathAndQuery());

        // Get the body
        std::string body = lambdaRequest.ToJson();

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "Lambda create function request created, name: " + lambdaRequest.functionName << std::endl;

        // Send request
        std::ostream &os = session.sendRequest(request);
        os << body;

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "Lambda create function request send, status: " << response.getStatus() << std::endl;
    }

    void LambdaWorker::AddAuthorization(Poco::Net::HTTPRequest &request) {
        request.add("Authorization",
                    "AWS4-HMAC-SHA256 Credential=" + _user + "/" + _clientId + "/" + _region
                        + "/s3/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840");

    }

} // namespace AwsMock::Worker
