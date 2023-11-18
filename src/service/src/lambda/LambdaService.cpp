//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/LambdaService.h>

namespace AwsMock::Service {

  LambdaService::LambdaService(const Core::Configuration &configuration, Core::MetricService &metricService, Poco::NotificationQueue &createQueue, Poco::NotificationQueue &invokeQueue) :
    _logger(Poco::Logger::get("LambdaService")), _configuration(configuration), _metricService(metricService), _createQueue(createQueue), _invokeQueue(invokeQueue) {

    // Initialize environment
    _accountId = _configuration.getString("awsmock.account.id", "000000000000");
    _dataDir = _configuration.getString("awsmock.data.dir", "/home/awsmock/data");
    _tempDir = _dataDir + Poco::Path::separator() + "tmp";
    _lambdaDir = _dataDir + Poco::Path::separator() + "lambda";
    _lambdaDatabase = std::make_shared<Database::LambdaDatabase>(_configuration);
    _s3Database = std::make_shared<Database::S3Database>(_configuration);
    _dockerService = std::make_shared<Service::DockerService>(_configuration);

    // Create temp directory
    Core::DirUtils::EnsureDirectory(_tempDir);
    log_trace_stream(_logger) << "lambda module initialized" << std::endl;
  }

  Dto::Lambda::CreateFunctionResponse LambdaService::CreateFunction(Dto::Lambda::CreateFunctionRequest &request) {
    log_debug_stream(_logger) << "Create function request, name: " + request.functionName << std::endl;

    // Save to file
    Database::Entity::Lambda::Lambda lambdaEntity;
    std::string lambdaArn = Core::AwsUtils::CreateLambdaArn(request.region, _accountId, request.functionName);

    if (_lambdaDatabase->LambdaExists(request.region, request.functionName, request.runtime)) {

      // Get the existing entity
      lambdaEntity = _lambdaDatabase->GetLambdaByArn(lambdaArn);

    } else {

      std::string codeFileName = _lambdaDir + Poco::Path::separator() + request.functionName + "-" + "latest" + ".zip";
      Database::Entity::Lambda::Environment environment = {
          .variables=request.environmentVariables.variables
      };
      lambdaEntity = {
          .region=request.region,
          .user=request.user,
          .function=request.functionName,
          .runtime=request.runtime,
          .role=request.role,
          .handler=request.handler,
          .tags=request.tags,
          .arn=lambdaArn,
          .timeout=request.timeout,
          .environment=environment,
          .state=Database::Entity::Lambda::LambdaState::Pending,
          .stateReasonCode=Database::Entity::Lambda::LambdaStateReasonCode::Creating,
          .fileName=codeFileName,
      };
    }

    // Update database
    lambdaEntity.state = Database::Entity::Lambda::LambdaState::Pending;
    lambdaEntity.stateReason = "Initializing";
    lambdaEntity.stateReasonCode = Database::Entity::Lambda::LambdaStateReasonCode::Idle;
    lambdaEntity = _lambdaDatabase->CreateOrUpdateLambda(lambdaEntity);

    // Create lambda function asynchronously
    // Send create notification
    _createQueue.enqueueNotification(new Dto::Lambda::CreateNotification(request.code.zipFile, lambdaEntity.oid));
    log_debug_stream(_logger) << "lambda create notification send, function: " + lambdaEntity.function << std::endl;

    // Create response
    Dto::Lambda::CreateFunctionResponse response{
        .functionArn=lambdaEntity.arn,
        .functionName=request.functionName,
        .runtime=request.runtime,
        .role=request.role,
        .handler=request.handler,
        .environment=request.environmentVariables,
        .memorySize=request.memorySize,
        .codeSize=lambdaEntity.codeSize,
        .codeSha256=lambdaEntity.codeSha256,
        .ephemeralStorage=request.ephemeralStorage,
    };

    log_info_stream(_logger) << "Function created, name: " + request.functionName << std::endl;

    return response;
  }

  Dto::Lambda::ListFunctionResponse LambdaService::ListFunctions(const std::string &region) {

    try {
      std::vector<Database::Entity::Lambda::Lambda> lambdas = _lambdaDatabase->ListLambdas(region);

      auto response = Dto::Lambda::ListFunctionResponse(lambdas);
      log_trace_stream(_logger) << "lambda list outcome: " + response.ToJson() << std::endl;
      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "lambda list request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500);
    }
  }

  void LambdaService::InvokeEventFunction(const Dto::S3::EventNotification &eventNotification, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Invocation event function eventNotification: " + eventNotification.ToString() << std::endl;

    for (const auto &record : eventNotification.records) {

      // Get the bucket eventNotification
      Database::Entity::S3::Bucket bucket = _s3Database->GetBucketByRegionName(record.region, record.s3.bucket.name);
      if (bucket.HasNotification(record.eventName)) {

        Database::Entity::S3::BucketNotification notification = bucket.GetNotification(record.eventName);
        log_debug_stream(_logger) << "Got bucket eventNotification: " << notification.ToString() << std::endl;

        // Get the lambda entity
        Database::Entity::Lambda::Lambda lambda = _lambdaDatabase->GetLambdaByArn(notification.lambdaArn);
        log_debug_stream(_logger) << "Got lambda entity eventNotification: " + lambda.ToString() << std::endl;

        // Send invocation request
        _invokeQueue.enqueueNotification(new Dto::Lambda::InvocationNotification(lambda.function, eventNotification.ToJson(), region, user, "localhost", lambda.hostPort));
        log_debug_stream(_logger) << "lambda executor notification send, name: " + lambda.function << std::endl;
      }
    }
  }

  void LambdaService::InvokeLambdaFunction(const std::string &functionName, const std::string &payload, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Invocation lambda function, functionName: " + functionName << std::endl;

    std::string lambdaArn = Core::AwsUtils::CreateLambdaArn(region, _accountId, functionName);

    // Get the lambda entity
    Database::Entity::Lambda::Lambda lambda = _lambdaDatabase->GetLambdaByArn(lambdaArn);
    log_debug_stream(_logger) << "Got lambda entity, name: " + lambda.function << std::endl;

    // Send invocation request
    _invokeQueue.enqueueNotification(new Dto::Lambda::InvocationNotification(functionName, payload, region, user, "localhost", lambda.hostPort));
    log_debug_stream(_logger) << "lambda executor notification send, name: " + lambda.function << std::endl;

    // Update database
    lambda.lastInvocation = Poco::DateTime();
    lambda.state = Database::Entity::Lambda::Active;
    lambda = _lambdaDatabase->UpdateLambda(lambda);
    log_debug_stream(_logger) << "lambda entity invoked, name: " + lambda.function << std::endl;
  }

  void LambdaService::CreateTag(const Dto::Lambda::CreateTagRequest &request) {
    log_debug_stream(_logger) << "Create tag request, arn: " << request.arn << std::endl;

    if (!_lambdaDatabase->LambdaExistsByArn(request.arn)) {
      throw Core::ServiceException("lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Get the existing entity
    Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase->GetLambdaByArn(request.arn);
    for (const auto &it : request.tags) {
      lambdaEntity.tags.emplace(it.first, it.second);
    }
    lambdaEntity = _lambdaDatabase->UpdateLambda(lambdaEntity);
    log_debug_stream(_logger) << "Create tag request succeeded, arn: " + request.arn << " size: " << lambdaEntity.tags.size() << std::endl;
  }

  Dto::Lambda::ListTagsResponse LambdaService::ListTags(const std::string &arn) {
    log_debug_stream(_logger) << "List tags request, arn: " << arn << std::endl;

    if (!_lambdaDatabase->LambdaExistsByArn(arn)) {
      throw Core::ServiceException("lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Get the existing entity
    Dto::Lambda::ListTagsResponse response;
    Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase->GetLambdaByArn(arn);
    for (const auto &it : lambdaEntity.tags) {
      response.tags.emplace(it.first, it.second);
    }
    log_debug_stream(_logger) << "List tag request succeeded, arn: " + arn << " size: " << lambdaEntity.tags.size() << std::endl;

    return response;
  }

  void LambdaService::DeleteFunction(Dto::Lambda::DeleteFunctionRequest &request) {
    log_debug_stream(_logger) << "Delete function: " + request.ToString() << std::endl;

    if (!_lambdaDatabase->LambdaExists(request.functionName)) {
      log_error_stream(_logger) << "lambda function does not exist, function: " + request.functionName << std::endl;
      throw Core::ServiceException("lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Delete the container, if existing
    if (_dockerService->ContainerExists(request.functionName, "latest")) {
      Dto::Docker::Container container = _dockerService->GetContainerByName(request.functionName, "latest");
      _dockerService->DeleteContainer(container);
      log_debug_stream(_logger) << "Docker container deleted, function: " + request.functionName << std::endl;
    }

    // Delete the image, if existing
    if (_dockerService->ImageExists(request.functionName, "latest")) {
      Dto::Docker::Image image = _dockerService->GetImageByName(request.functionName, "latest");
      _dockerService->DeleteImage(image.id);
      log_debug_stream(_logger) << "Docker image deleted, function: " + request.functionName << std::endl;
    }

    _lambdaDatabase->DeleteLambda(request.functionName);
    _logger.information() << "lambda function deleted, function: " + request.functionName << std::endl;
  }

  void LambdaService::DeleteTags(Dto::Lambda::DeleteTagsRequest &request) {
    log_trace_stream(_logger) << "Delete tags: " + request.ToString() << std::endl;

    if (!_lambdaDatabase->LambdaExistsByArn(request.arn)) {
      log_error_stream(_logger) << "lambda function does not exist, arn: " + request.arn << std::endl;
      throw Core::ServiceException("lambda function does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    // Get the existing entity
    Dto::Lambda::ListTagsResponse response;
    Database::Entity::Lambda::Lambda lambdaEntity = _lambdaDatabase->GetLambdaByArn(request.arn);
    for (const auto &it : request.tags) {
      if (lambdaEntity.HasTag(it)) {
        auto key = lambdaEntity.tags.find(it);
        lambdaEntity.tags.erase(it);
      }
    }
    lambdaEntity = _lambdaDatabase->UpdateLambda(lambdaEntity);
    log_debug_stream(_logger) << "Delete tag request succeeded, arn: " + request.arn << " size: " << lambdaEntity.tags.size() << std::endl;
  }
} // namespace AwsMock::Service
