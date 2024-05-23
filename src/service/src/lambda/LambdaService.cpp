//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/lambda/LambdaService.h>

namespace AwsMock::Service {

    Poco::Mutex LambdaService::_mutex;

    LambdaService::LambdaService(const Core::Configuration &configuration) : _configuration(configuration), _lambdaDatabase(Database::LambdaDatabase::instance()), _s3Database(Database::S3Database::instance()) {

        // Initialize environment
        _accountId = _configuration.getString("awsmock.account.userPoolId", "000000000000");
        _dataDir = _configuration.getString("awsmock.data.dir", "/home/awsmock/data");
        _tempDir = _dataDir + Poco::Path::separator() + "tmp";
        _lambdaDir = _dataDir + Poco::Path::separator() + "lambda";
        _dockerService = std::make_shared<Service::DockerService>();

        // Create temp directory
        Core::DirUtils::EnsureDirectory(_tempDir);
        log_trace << "Lambda module initialized";
    }

    Dto::Lambda::CreateFunctionResponse LambdaService::CreateFunction(Dto::Lambda::CreateFunctionRequest &request) {
        log_debug << "Create function request, name: " << request.functionName;

        // Save to file
        Database::Entity::Lambda::Lambda lambdaEntity;
        std::string lambdaArn = Core::AwsUtils::CreateLambdaArn(request.region, _accountId, request.functionName);

        if (_lambdaDatabase.LambdaExists(request.region, request.functionName, request.runtime)) {

            // Get the existing entity
            lambdaEntity = _lambdaDatabase.GetLambdaByArn(lambdaArn);

        } else {

            std::string codeFileName = _lambdaDir + Poco::Path::separator() + request.functionName + "-" + "latest" + ".zip";
            Database::Entity::Lambda::Environment environment = {
                    .variables = request.environment.variables};
            lambdaEntity = {
                    .region = request.region,
                    .user = request.user,
                    .function = request.functionName,
                    .runtime = request.runtime,
                    .role = request.role,
                    .handler = request.handler,
                    .tags = request.tags,
                    .arn = lambdaArn,
                    .timeout = request.timeout,
                    .environment = environment,
                    .state = Database::Entity::Lambda::LambdaState::Pending,
                    .stateReasonCode = Database::Entity::Lambda::LambdaStateReasonCode::Creating,
                    .fileName = codeFileName,
            };
        }

        // Update database
        lambdaEntity.state = Database::Entity::Lambda::LambdaState::Pending;
        lambdaEntity.stateReason = "Initializing";
        lambdaEntity.stateReasonCode = Database::Entity::Lambda::LambdaStateReasonCode::Idle;
        lambdaEntity = _lambdaDatabase.CreateOrUpdateLambda(lambdaEntity);

        // Create lambda function asynchronously
        Core::TaskPool::instance().Add<std::string, LambdaCreator>("lambda-creator", LambdaCreator(request.code.zipFile, lambdaEntity.oid));
        log_debug << "Lambda create started, function: " << lambdaEntity.function;

        // Create response
        Dto::Lambda::CreateFunctionResponse response = Dto::Lambda::Mapper::map(request, lambdaEntity);
        log_info << "Function created, name: " << request.functionName;

        return response;
    }

    Dto::Lambda::ListFunctionResponse LambdaService::ListFunctions(const std::string &region) {

        try {
            std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase.ListLambdas(region);

            auto response = Dto::Lambda::ListFunctionResponse(lambdas);
            log_trace << "Lambda list outcome: " << response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "Lambda list request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message(), 500);
        }
    }

    Dto::Lambda::GetFunctionResponse LambdaService::GetFunction(const std::string &region, const std::string &name) {

        try {

            Database::Entity::Lambda::Lambda lambda = _lambdaDatabase.GetLambdaByName(region, name);

            Dto::Lambda::GetFunctionResponse response = {.region = lambda.region, .functionName = lambda.function};
            log_trace << "Lambda function: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "Lambda list request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    void LambdaService::InvokeEventFunction(const Dto::S3::EventNotification &eventNotification, const std::string &region, const std::string &user) {
        log_debug << "Invocation event function eventNotification: " + eventNotification.ToString();

        for (const auto &record: eventNotification.records) {

            // Get the bucket eventNotification
            Database::Entity::S3::Bucket bucket = _s3Database.GetBucketByRegionName(record.region, record.s3.bucket.name);
            if (bucket.HasNotification(record.eventName)) {

                Database::Entity::S3::BucketNotification notification = bucket.GetNotification(record.eventName);
                log_debug << "Got bucket eventNotification: " << notification.ToString();

                // Get the lambda entity
                Database::Entity::Lambda::Lambda lambda = _lambdaDatabase.GetLambdaByArn(notification.lambdaArn);
                log_debug << "Got lambda entity eventNotification: " + lambda.ToString();

                // Send invocation request
                //_invokeQueue.enqueueNotification(new Dto::Lambda::InvocationNotification(lambda.function, eventNotification.ToJson(), region, user, "localhost", lambda.hostPort));
                log_debug << "Lambda executor notification send, name: " + lambda.function;
            }
        }
    }

    std::string LambdaService::InvokeLambdaFunction(const std::string &functionName, const std::string &payload, const std::string &region, const std::string &user, const std::string &logType) {
        Poco::ScopedLock lock(_mutex);
        log_debug << "Invocation lambda function, functionName: " << functionName;

        std::string lambdaArn = Core::AwsUtils::CreateLambdaArn(region, _accountId, functionName);

        // Get the lambda entity
        Database::Entity::Lambda::Lambda lambda = _lambdaDatabase.GetLambdaByArn(lambdaArn);
        log_debug << "Got lambda entity, name: " << lambda.function;

        // Send invocation request
        std::string output;
        std::string url = GetRequestUrl("localhost", lambda.hostPort);
        if (!logType.empty() && Core::StringUtils::EqualsIgnoreCase(logType, "Tail")) {

            // Synchronous execution
            output = InvokeLambdaSynchronously(url, payload);

        } else {

            // Asynchronous execution
            Core::TaskPool::instance().Add<std::string, LambdaExecutor>("lambda-creator", LambdaExecutor(url, payload));
        }
        log_debug << "Lambda executor notification send, name: " << lambda.function;

        // Update database
        lambda.lastInvocation = Poco::DateTime();
        lambda.state = Database::Entity::Lambda::Active;
        lambda = _lambdaDatabase.UpdateLambda(lambda);
        log_debug << "Lambda entity invoked, name: " << lambda.function;
        return output;
    }

    void LambdaService::CreateTag(const Dto::Lambda::CreateTagRequest &request) {
        log_debug << "Create tag request, arn: " << request.arn;

        if (!_lambdaDatabase.LambdaExistsByArn(request.arn)) {
            log_warning << "Lambda function does not exist, arn: " << request.arn;
            throw Core::ServiceException("Lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Get the existing entity
        Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase.GetLambdaByArn(request.arn);
        for (const auto &it: request.tags) {
            lambdaEntity.tags.emplace(it.first, it.second);
        }
        lambdaEntity = _lambdaDatabase.UpdateLambda(lambdaEntity);
        log_debug << "Create tag request succeeded, arn: " + request.arn << " size: " << lambdaEntity.tags.size();
    }

    Dto::Lambda::ListTagsResponse LambdaService::ListTags(const std::string &arn) {
        log_debug << "List tags request, arn: " << arn;

        if (!_lambdaDatabase.LambdaExistsByArn(arn)) {
            log_warning << "Lambda function does not exist, arn: " << arn;
            throw Core::ServiceException("Lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Get the existing entity
        Dto::Lambda::ListTagsResponse response;
        Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase.GetLambdaByArn(arn);
        for (const auto &it: lambdaEntity.tags) {
            response.tags.emplace(it.first, it.second);
        }
        log_debug << "List tag request succeeded, arn: " + arn << " size: " << lambdaEntity.tags.size();

        return response;
    }

    Dto::Lambda::AccountSettingsResponse LambdaService::GetAccountSettings() {

        Dto::Lambda::AccountSettingsResponse response;

        // 50 MB
        response.accountLimit.codeSizeUnzipped = 50 * 1024 * 1024L;
        response.accountLimit.codeSizeZipped = 50 * 1024 * 1024L;

        // 1000 concurrent executions (which is irrelevant in AwsMock environment)
        response.accountLimit.concurrentExecutions = 1000;

        // 75 GB
        response.accountLimit.totalCodeSize = 75 * 1024 * 1024 * 1024L;
        log_debug << "List account limits: " << response.ToJson();

        // 75 GB
        response.accountUsage.totalCodeSize = 10 * 1024 * 1024L;
        response.accountUsage.functionCount = _lambdaDatabase.LambdaCount();

        return response;
    }

    void LambdaService::DeleteFunction(Dto::Lambda::DeleteFunctionRequest &request) {
        log_debug << "Delete function: " + request.ToString();

        if (!_lambdaDatabase.LambdaExists(request.functionName)) {
            log_error << "Lambda function does not exist, function: " + request.functionName;
            throw Core::ServiceException("Lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Delete the container, if existing
        if (_dockerService->ContainerExists(request.functionName, "latest")) {
            Dto::Docker::Container container = _dockerService->GetContainerByName(request.functionName, "latest");
            _dockerService->DeleteContainer(container);
            log_debug << "Docker container deleted, function: " + request.functionName;
        }

        // Delete the image, if existing
        if (_dockerService->ImageExists(request.functionName, "latest")) {
            Dto::Docker::Image image = _dockerService->GetImageByName(request.functionName, "latest");
            _dockerService->DeleteImage(image.id);
            log_debug << "Docker image deleted, function: " + request.functionName;
        }

        _lambdaDatabase.DeleteLambda(request.functionName);
        log_info << "Lambda function deleted, function: " + request.functionName;
    }

    void LambdaService::DeleteTags(Dto::Lambda::DeleteTagsRequest &request) {
        log_trace << "Delete tags: " + request.ToString();

        if (!_lambdaDatabase.LambdaExistsByArn(request.arn)) {
            log_error << "Lambda function does not exist, arn: " + request.arn;
            throw Core::ServiceException("Lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Get the existing entity
        Dto::Lambda::ListTagsResponse response;
        Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase.GetLambdaByArn(request.arn);
        for (const auto &it: request.tags) {
            if (lambdaEntity.HasTag(it)) {
                auto key = lambdaEntity.tags.find(it);
                lambdaEntity.tags.erase(it);
            }
        }
        lambdaEntity = _lambdaDatabase.UpdateLambda(lambdaEntity);
        log_debug << "Delete tag request succeeded, arn: " + request.arn << " size: " << lambdaEntity.tags.size();
    }

    std::string LambdaService::InvokeLambdaSynchronously(const std::string &url, const std::string &payload) {

        Core::MetricServiceTimer measure(LAMBDA_INVOCATION_TIMER);
        Core::MetricService::instance().IncrementCounter(LAMBDA_INVOCATION_COUNT);
        log_debug << "Sending lambda invocation request, endpoint: " << url;

        Core::CurlUtils _curlUtils;
        Core::CurlResponse response = _curlUtils.SendHttpRequest("POST", url, {}, payload);
        if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            log_debug << "HTTP error, status: " << response.statusCode << " reason: " << response.output;
        }
        log_debug << "Lambda invocation finished send, status: " << response.statusCode;
        log_info << "Lambda output: " << response.output;
        return response.output.substr(0, MAX_OUTPUT_LENGTH);
    }

    std::string LambdaService::GetRequestUrl(const std::string &hostName, int port) {
        if (hostName.empty()) {
            return "http://localhost:" + std::to_string(port) + "/2015-03-31/functions/function/invocations";
        }
        return "http://" + hostName + ":" + std::to_string(port) + "/2015-03-31/functions/function/invocations";
    }

}// namespace AwsMock::Service
