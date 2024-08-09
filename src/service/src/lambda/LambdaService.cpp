//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/lambda/LambdaService.h>

namespace AwsMock::Service {

    Poco::Mutex LambdaService::_mutex;

    Dto::Lambda::CreateFunctionResponse LambdaService::CreateFunction(Dto::Lambda::CreateFunctionRequest &request) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "create_function");
        log_debug << "Create function request, name: " << request.functionName;

        std::string accountId = Core::Configuration::instance().getString("awsmock.account.id", "000000000000");

        // Save to file
        Database::Entity::Lambda::Lambda lambdaEntity;
        std::string lambdaArn = Core::AwsUtils::CreateLambdaArn(request.region, accountId, request.functionName);

        std::string zippedCode;
        if (_lambdaDatabase.LambdaExists(request.region, request.functionName, request.runtime)) {

            // Get the existing entity
            lambdaEntity = _lambdaDatabase.GetLambdaByArn(lambdaArn);

        } else {

            Database::Entity::Lambda::Environment environment = {.variables = request.environment.variables};
            lambdaEntity = Dto::Lambda::Mapper::map(request);
            lambdaEntity.arn = lambdaArn;

            // Remove code
            if (!request.code.zipFile.empty()) {
                zippedCode = std::move(request.code.zipFile);
                lambdaEntity.code.zipFile.clear();
            }
        }

        // Update database
        lambdaEntity.state = Database::Entity::Lambda::LambdaState::Pending;
        lambdaEntity.stateReason = "Initializing";
        lambdaEntity.stateReasonCode = Database::Entity::Lambda::LambdaStateReasonCode::Creating;
        lambdaEntity = _lambdaDatabase.CreateOrUpdateLambda(lambdaEntity);

        // Create lambda function asynchronously
        std::string instanceId = Core::StringUtils::GenerateRandomHexString(8);
        LambdaCreator lambdaCreator;
        boost::thread t(boost::ref(lambdaCreator), zippedCode, lambdaEntity.oid, instanceId);
        t.detach();
        log_debug << "Lambda create started, function: " << lambdaEntity.function;

        // Create response
        Dto::Lambda::CreateFunctionResponse response = Dto::Lambda::Mapper::map(request, lambdaEntity);
        log_info << "Function created, name: " << request.functionName;

        return response;
    }

    Dto::Lambda::ListFunctionResponse LambdaService::ListFunctions(const std::string &region) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "list_functions");
        log_debug << "List functions request, region: " << region;

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
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "get_function");
        log_debug << "Get function request, region: " << region << " name: " << name;

        try {

            Database::Entity::Lambda::Lambda lambda = _lambdaDatabase.GetLambdaByName(region, name);

            Dto::Lambda::Configuration configuration = {.functionName = lambda.function, .handler = lambda.handler, .runtime = lambda.runtime, .state = LambdaStateToString(lambda.state), .stateReason = lambda.stateReason, .stateReasonCode = LambdaStateReasonCodeToString(lambda.stateReasonCode)};
            Dto::Lambda::GetFunctionResponse response = {.region = lambda.region, .configuration = configuration, .tags = lambda.tags};

            log_info << "Lambda function: " + response.ToJson();
            return response;

        } catch (Poco::Exception &ex) {
            log_error << "Lambda list request failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    std::string LambdaService::InvokeLambdaFunction(const std::string &functionName, const std::string &payload, const std::string &region, const std::string &user, const std::string &logType) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "invoke_lambda_function");
        Poco::ScopedLock lock(_mutex);
        log_debug << "Invocation lambda function, functionName: " << functionName;

        std::string accountId = Core::Configuration::instance().getString("awsmock.account.id", "000000000000");
        std::string lambdaArn = Core::AwsUtils::CreateLambdaArn(region, accountId, functionName);

        // Get the lambda entity
        Database::Entity::Lambda::Lambda lambda = _lambdaDatabase.GetLambdaByArn(lambdaArn);
        log_debug << "Got lambda entity, name: " << lambda.function;

        // Find an idle instance
        std::string instanceId = FindIdleInstance(lambda);
        if (instanceId.empty()) {

            // Create instance
            instanceId = Core::StringUtils::GenerateRandomHexString(8);
            LambdaCreator lambdaCreator;
            boost::thread t(boost::ref(lambdaCreator), lambda.code.zipFile, lambda.oid, instanceId);
            t.join();

            // Replace lambda
            lambda = _lambdaDatabase.GetLambdaByArn(lambdaArn);
        }

        Database::Entity::Lambda::Instance instance = lambda.GetInstance(instanceId);

        // Send invocation request
        std::string output;
        if (!logType.empty() && Core::StringUtils::EqualsIgnoreCase(logType, "Tail")) {

            // Synchronous execution
            output = InvokeLambdaSynchronously("localhost", lambda.hostPort, payload);

        } else {

            LambdaExecutor lambdaExecutor;
            boost::thread t(boost::ref(lambdaExecutor), lambda.function, instance.containerId, "localHost", instance.hostPort, payload);
            t.detach();
        }
        log_debug << "Lambda executor notification send, name: " << lambda.function;

        // Update database
        lambda.lastInvocation = std::chrono::system_clock::now();
        lambda.state = Database::Entity::Lambda::Active;
        lambda = _lambdaDatabase.UpdateLambda(lambda);
        log_debug << "Lambda entity invoked, name: " << lambda.function;
        return output;
    }

    void LambdaService::CreateTag(const Dto::Lambda::CreateTagRequest &request) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "create_tag");
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
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "list_tags");
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
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "get_account_settings");
        log_debug << "Get account settings";

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

    Dto::Lambda::CreateEventSourceMappingsResponse LambdaService::CreateEventSourceMappings(const Dto::Lambda::CreateEventSourceMappingsRequest &request) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "create_event_source_mapping");
        log_debug << "Create event source mapping, arn: " << request.functionName << " sourceArn: " << request.eventSourceArn;

        if (!_lambdaDatabase.LambdaExists(request.functionName)) {
            log_warning << "Lambda function does not exist, function: " << request.functionName;
            throw Core::NotFoundException("Lambda function does not exist");
        }

        // Get the existing entity
        Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase.GetLambdaByName(request.region, request.functionName);

        // Map request to entity
        Database::Entity::Lambda::EventSourceMapping eventSourceMapping = Dto::Lambda::Mapper::map(request);
        eventSourceMapping.uuid = Core::StringUtils::CreateRandomUuid();

        // Check existence
        if (lambdaEntity.HasEventSource(request.eventSourceArn)) {
            log_warning << "Event source exists already, function: " << request.functionName << " sourceArn: " << request.eventSourceArn;
            throw Core::BadRequestException("Event source exists already");
        }

        // Update database
        lambdaEntity.eventSources.emplace_back(eventSourceMapping);
        lambdaEntity = _lambdaDatabase.UpdateLambda(lambdaEntity);
        log_debug << "Lambda function updated, function: " << lambdaEntity.function;

        // Create response (which is actually the request)
        Dto::Lambda::CreateEventSourceMappingsResponse response;
        response.functionName = request.functionName;
        response.eventSourceArn = request.eventSourceArn;
        response.batchSize = request.batchSize;
        response.maximumBatchingWindowInSeconds = request.maximumBatchingWindowInSeconds;
        response.enabled = request.enabled;
        response.uuid = eventSourceMapping.uuid;

        log_trace << "Response: " << response.ToJson();
        log_debug << "Event source mapping created, function: " << response.functionName << " sourceArn: " << response.eventSourceArn;
        return response;
    }

    Dto::Lambda::ListEventSourceMappingsResponse LambdaService::ListEventSourceMappings(const Dto::Lambda::ListEventSourceMappingsRequest &request) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "list_event_source_mapping");
        log_debug << "List event source mappings, functionName: " << request.functionName << " sourceArn: " << request.eventSourceArn;

        if (!_lambdaDatabase.LambdaExists(request.functionName)) {
            log_warning << "Lambda function does not exist, function: " << request.functionName;
            throw Core::NotFoundException("Lambda function does not exist");
        }

        // Get the existing entity
        Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase.GetLambdaByName(request.region, request.functionName);

        return Dto::Lambda::Mapper::map(lambdaEntity.arn, lambdaEntity.eventSources);
    }

    void LambdaService::DeleteFunction(Dto::Lambda::DeleteFunctionRequest &request) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "delete_function");
        log_debug << "Delete function: " + request.ToString();

        DockerService &dockerService = DockerService::instance();

        if (!_lambdaDatabase.LambdaExists(request.functionName)) {
            log_error << "Lambda function does not exist, function: " + request.functionName;
            throw Core::ServiceException("Lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Delete the container, if existing
        if (dockerService.ContainerExists(request.functionName, request.qualifier)) {
            Dto::Docker::Container container = dockerService.GetContainerByName(request.functionName, request.qualifier);
            dockerService.DeleteContainer(container);
            log_debug << "Docker container deleted, function: " + request.functionName;
        }

        // Delete the image, if existing
        if (dockerService.ImageExists(request.functionName, request.qualifier)) {
            Dto::Docker::Image image = dockerService.GetImageByName(request.functionName, request.qualifier);
            dockerService.DeleteImage(image.id);
            log_debug << "Docker image deleted, function: " + request.functionName;
        }

        _lambdaDatabase.DeleteLambda(request.functionName);
        log_info << "Lambda function deleted, function: " + request.functionName;
    }

    void LambdaService::DeleteTags(Dto::Lambda::DeleteTagsRequest &request) {
        Core::MetricServiceTimer measure(LAMBDA_SERVICE_TIMER, "method", "delete_tags");
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

    std::string LambdaService::InvokeLambdaSynchronously(const std::string &host, int port, const std::string &payload) {
        Core::MetricServiceTimer measure(LAMBDA_INVOCATION_TIMER);
        Core::MetricService::instance().IncrementCounter(LAMBDA_INVOCATION_COUNT);
        log_debug << "Sending lambda invocation request, endpoint: " << host << ":" << port;

        Core::HttpSocketResponse response = Core::HttpSocket::SendJson(http::verb::post, host, port, "/", payload, {});
        if (response.statusCode != http::status::ok) {
            log_debug << "HTTP error, httpStatus: " << response.statusCode << " body: " << response.body;
        }
        log_debug << "Lambda invocation finished send, status: " << response.statusCode;
        log_info << "Lambda output: " << response.body;
        return response.body.substr(0, MAX_OUTPUT_LENGTH);
    }

    std::string LambdaService::FindIdleInstance(Database::Entity::Lambda::Lambda &lambda) {
        if (lambda.instances.empty()) {
            return {};
        }
        for (const auto &instance: lambda.instances) {
            if (instance.status == Database::Entity::Lambda::InstanceIdle) {
                return instance.id;
            }
        }
        return {};
    }
}// namespace AwsMock::Service
