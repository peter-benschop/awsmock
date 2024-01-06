//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/SQSService.h>

namespace AwsMock::Service {

  SQSService::SQSService(Core::Configuration &configuration, Poco::Condition &condition)
    : _logger(Poco::Logger::get("SQSService")), _configuration(configuration), _condition(condition) {

    // Initialize environment
    _accountId = _configuration.getString("awsmock.account.id", DEFAULT_ACCOUNT_ID);

    // Database connection
    _database = std::make_unique<Database::SQSDatabase>(_configuration);
  }

  Dto::SQS::CreateQueueResponse SQSService::CreateQueue(const Dto::SQS::CreateQueueRequest &request) {

    // Check existence
    if (_database->QueueExists(request.region, request.name)) {
      throw Core::ServiceException("SQS queue '" + request.queueUrl + "' exists already", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }

    try {
      // Get queue ARN
      std::string queueArn = Core::AwsUtils::CreateSqsQueueArn(_configuration, request.name);

      Database::Entity::SQS::QueueAttribute attributes;
      for (auto &a : request.attributes) {
        if (a.attributeName == "VisibilityTimeout") {
          attributes.visibilityTimeout = std::stoi(a.attributeValue);
        }
      }

      // Update database
      Database::Entity::SQS::Queue queue = _database->CreateQueue({
                                                                    .region=request.region,
                                                                    .name=request.name,
                                                                    .owner=request.owner,
                                                                    .queueUrl=request.queueUrl,
                                                                    .queueArn=queueArn,
                                                                    .attributes=attributes,
                                                                    .tags=request.tags
                                                                  });
      log_trace_stream(_logger) << "SQS queue created: " << queue.ToString() << std::endl;

      return {
        .region=queue.region,
        .name=queue.name,
        .owner=queue.owner,
        .queueUrl=queue.queueUrl,
        .queueArn=queue.queueArn
      };

    } catch (Core::DatabaseException &exc) {
      log_error_stream(_logger) << "SQS create queue failed, message: " << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), 400);
    }
  }

  Dto::SQS::ListQueueResponse SQSService::ListQueues(const std::string &region) {
    log_trace_stream(_logger) << "List all queues request, region: " << region << std::endl;

    try {

      Database::Entity::SQS::QueueList queueList = _database->ListQueues(region);
      auto listQueueResponse = Dto::SQS::ListQueueResponse(queueList);
      log_trace_stream(_logger) << "SQS create queue list response: " << listQueueResponse.ToXml() << std::endl;

      return listQueueResponse;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS list queues failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), 500, "SQS", Poco::UUIDGenerator().createRandom().toString().c_str());
    }
  }

  void SQSService::PurgeQueue(const Dto::SQS::PurgeQueueRequest &request) {
    log_trace_stream(_logger) << "Purge queue request, region: " << request.region << " queueUrl: " << request.queueUrl << std::endl;

    // Check existence
    if (!_database->QueueUrlExists(request.region, request.queueUrl)) {
      throw Core::ServiceException("SQS queue '" + request.queueUrl + "' does not exists", Poco::Net::HTTPResponse::HTTP_NOT_FOUND, request.resource.c_str(), request.requestId.c_str());
    }

    try {

      _database->PurgeQueue(request.region, request.queueUrl);
      log_trace_stream(_logger) << "SQS queue purged, region: " << request.region << " queueUrl: " << request.queueUrl << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS purge queue failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR, request.resource.c_str(), request.requestId.c_str());
    }
  }

  Dto::SQS::GetQueueUrlResponse SQSService::GetQueueUrl(const Dto::SQS::GetQueueUrlRequest &request) {
    log_trace_stream(_logger) << "Get queue URL request, region: " << request.region << " name: " << request.queueName << std::endl;

    try {

      // Get queue
      Database::Entity::SQS::Queue queue = _database->GetQueueByName(request.region, request.queueName);
      log_info_stream(_logger) << "SQS get queue URL, region: " << request.region << " name: " << queue.queueUrl << std::endl;
      return {.queueUrl=queue.queueUrl};

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS get queue failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_NOT_FOUND, request.region.c_str(), request.queueName.c_str());
    }
  }

  Dto::SQS::GetQueueAttributesResponse SQSService::GetQueueAttributes(const Dto::SQS::GetQueueAttributesRequest &request) {
    log_trace_stream(_logger) << "Get queue userAttributes request, request: " << request.ToString() << std::endl;

    // Check existence
    if (!_database->QueueUrlExists(request.region, request.queueUrl)) {
      throw Core::ServiceException("SQS queue '" + request.queueUrl + "' does not exists",
                                   Poco::Net::HTTPResponse::HTTP_NOT_FOUND,
                                   request.resource.c_str(),
                                   request.requestId.c_str());
    }

    Database::Entity::SQS::Queue queue = _database->GetQueueByUrl(request.region, request.queueUrl);
    log_debug_stream(_logger) << "Got queue: " << queue.queueUrl << std::endl;

    Dto::SQS::GetQueueAttributesResponse response;
    if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "All") != request.attributeNames.end()) {
      response.attributes.emplace_back("ApproximateNumberOfMessages", std::to_string(queue.attributes.approximateNumberOfMessages));
      response.attributes.emplace_back("ApproximateNumberOfMessagesDelayed", std::to_string(queue.attributes.approximateNumberOfMessagesDelayed));
      response.attributes.emplace_back("ApproximateNumberOfMessagesNotVisible", std::to_string(queue.attributes.approximateNumberOfMessagesNotVisible));
      response.attributes.emplace_back("CreatedTimestamp", std::to_string(queue.created.timestamp().epochTime()));
      response.attributes.emplace_back("DelaySeconds", std::to_string(queue.attributes.delaySeconds));
      response.attributes.emplace_back("LastModifiedTimestamp", std::to_string(queue.modified.timestamp().epochTime()));
      response.attributes.emplace_back("MaximumMessageSize", std::to_string(queue.attributes.maxMessageSize));
      response.attributes.emplace_back("MessageRetentionPeriod", std::to_string(queue.attributes.messageRetentionPeriod));
      response.attributes.emplace_back("Policy", queue.attributes.policy);
      response.attributes.emplace_back("QueueArn", queue.queueArn);
      response.attributes.emplace_back("ReceiveMessageWaitTimeSeconds", std::to_string(queue.attributes.receiveMessageWaitTime));
      response.attributes.emplace_back("VisibilityTimeout", std::to_string(queue.attributes.visibilityTimeout));
    } else {
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "VisibilityTimeout") != request.attributeNames.end()) {
        response.attributes.emplace_back("Policy", queue.attributes.policy);
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "VisibilityTimeout") != request.attributeNames.end()) {
        response.attributes.emplace_back("VisibilityTimeout", std::to_string(queue.attributes.visibilityTimeout));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "MaximumMessageSize") != request.attributeNames.end()) {
        response.attributes.emplace_back("MaximumMessageSize", std::to_string(queue.attributes.maxMessageSize));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "MessageRetentionPeriod") != request.attributeNames.end()) {
        response.attributes.emplace_back("MessageRetentionPeriod", std::to_string(queue.attributes.messageRetentionPeriod));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "ApproximateNumberOfMessages") != request.attributeNames.end()) {
        response.attributes.emplace_back("ApproximateNumberOfMessages", std::to_string(queue.attributes.approximateNumberOfMessages));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "ApproximateNumberOfMessagesNotVisible") != request.attributeNames.end()) {
        response.attributes.emplace_back("ApproximateNumberOfMessagesNotVisible", std::to_string(queue.attributes.approximateNumberOfMessagesNotVisible));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "CreatedTimestamp") != request.attributeNames.end()) {
        response.attributes.emplace_back("CreatedTimestamp", Poco::DateTimeFormatter::format(queue.created, Poco::DateTimeFormat::HTTP_FORMAT));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "LastModifiedTimestamp") != request.attributeNames.end()) {
        response.attributes.emplace_back("LastModifiedTimestamp", Poco::DateTimeFormatter::format(queue.modified, Poco::DateTimeFormat::HTTP_FORMAT));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "ApproximateNumberOfMessagesDelayed") != request.attributeNames.end()) {
        response.attributes.emplace_back("ApproximateNumberOfMessagesNotVisible", std::to_string(queue.attributes.approximateNumberOfMessagesDelayed));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "DelaySeconds") != request.attributeNames.end()) {
        response.attributes.emplace_back("DelaySeconds", std::to_string(queue.attributes.delaySeconds));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "ReceiveMessageWaitTimeSeconds") != request.attributeNames.end()) {
        response.attributes.emplace_back("ReceiveMessageWaitTimeSeconds", std::to_string(queue.attributes.receiveMessageWaitTime));
      }
      if (std::find(request.attributeNames.begin(), request.attributeNames.end(), "RedrivePolicy") != request.attributeNames.end()) {
        response.attributes.emplace_back("RedrivePolicy", queue.attributes.redrivePolicy.ToJson());
      }
    }
    log_debug_stream(_logger) << response.ToString() << std::endl;
    return response;
  }

  void SQSService::SetQueueAttributes(Dto::SQS::SetQueueAttributesRequest &request) {
    log_trace_stream(_logger) << "Put queue sqs request, queue: " << request.queueUrl << std::endl;

    // Check existence
    if (!_database->QueueUrlExists(request.region, request.queueUrl)) {
      throw Core::ServiceException("SQS queue '" + request.queueUrl + "' does not exists", Poco::Net::HTTPResponse::HTTP_NOT_FOUND, request.resource.c_str(), request.requestId.c_str());
    }

    try {

      // Get the queue
      Database::Entity::SQS::Queue queue = _database->GetQueueByUrl(request.region, request.queueUrl);
      log_trace_stream(_logger) << "Got queue: " << queue.ToString() << std::endl;

      // Reset all userAttributes
      if (!request.attributes["Policy"].empty()) {
        queue.attributes.policy = request.attributes["Policy"];
      }
      if (!request.attributes["RedrivePolicy"].empty()) {
        queue.attributes.redrivePolicy.FromJson(request.attributes["RedrivePolicy"]);
      }
      if (!request.attributes["RedriveAllowPolicy"].empty()) {
        queue.attributes.redriveAllowPolicy = request.attributes["RedriveAllowPolicy"];
      }
      if (!request.attributes["MessageRetentionPeriod"].empty()) {
        queue.attributes.messageRetentionPeriod = std::stoi(request.attributes["MessageRetentionPeriod"]);
      }
      if (!request.attributes["VisibilityTimeout"].empty()) {
        queue.attributes.visibilityTimeout = std::stoi(request.attributes["VisibilityTimeout"]);
      }
      if (!request.attributes["QueueArn"].empty()) {
        queue.attributes.queueArn = request.attributes["QueueArn"];
      }

      // Update database
      queue = _database->UpdateQueue(queue);
      log_trace_stream(_logger) << "Queue updated: " << queue.ToString() << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS delete queue failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void SQSService::SetVisibilityTimeout(Dto::SQS::ChangeMessageVisibilityRequest &request) {
    log_trace_stream(_logger) << "Change message visibilityTimeout request, queue: " << request.queueUrl << std::endl;

    // Check existence
    if (!_database->MessageExists(request.receiptHandle)) {
      log_warning_stream(_logger) << "SQS message does not exist, receiptHandle: " << request.receiptHandle << std::endl;
      throw Core::ServiceException("SQS message with receipt handle '" + request.receiptHandle + "' does not exists", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    try {

      // Get the message
      Database::Entity::SQS::Message message = _database->GetMessageByReceiptHandle(request.receiptHandle);
      log_trace_stream(_logger) << "Got message: " << message.ToString() << std::endl;

      // Reset all userAttributes
      Database::Entity::SQS::MessageAttribute attribute = {.attributeName="VisibilityTimeout", .attributeValue=std::to_string(request.visibilityTimeout), .attributeType=Database::Entity::SQS::MessageAttributeType::NUMBER};
      message.attributes.push_back(attribute);

      // Update database
      message = _database->UpdateMessage(message);
      log_trace_stream(_logger) << "Message updated: " << message.ToString() << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS change message visibilityTimeout timeout request failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void SQSService::TagQueue(const Dto::SQS::TagQueueRequest &request) {

    try {

      // Check existence
      if (!_database->QueueUrlExists(request.region, request.queueUrl)) {
        throw Core::ServiceException("SQS queue topic does not exists", Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
      }

      // Get the topic
      Database::Entity::SQS::Queue queue = _database->GetQueueByUrl(request.region, request.queueUrl);

      // Set tags and update database
      for(const auto &tag:request.tags) {
        queue.tags[tag.first] = tag.second;
      }

      queue = _database->UpdateQueue(queue);
      log_info_stream(_logger) << "SQS queue tags updated, count: " << request.tags.size() << std::endl;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS set queue tags failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }


  void SQSService::DeleteQueue(const Dto::SQS::DeleteQueueRequest &request) {
    log_trace_stream(_logger) << "Delete queue request, request: " << request.ToString() << std::endl;

    // Check existence
    if (!_database->QueueUrlExists(request.region, request.queueUrl)) {
      throw Core::ServiceException("SQS queue '" + request.queueUrl + "' does not exists", Poco::Net::HTTPResponse::HTTP_NOT_FOUND, request.resource.c_str(), request.requestId.c_str());
    }

    try {

      // Delete all messages in queue
      _database->DeleteMessages(request.queueUrl);

      // Update database
      _database->DeleteQueue({.region=request.region, .queueUrl=request.queueUrl});

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS delete queue failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  Dto::SQS::SendMessageResponse SQSService::SendMessage(const Dto::SQS::SendMessageRequest &request) {

    if (!request.queueUrl.empty() && !_database->QueueUrlExists(request.region, request.queueUrl)) {
      throw Core::ServiceException("SQS queue '" + request.queueUrl + "' does not exists", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
    }

    try {
      // Sanitize message body
      // TODO: FIx iconv on alpine linux
      //std::string messageBody = Core::StringUtils::SanitizeUtf8(request.body);

      // Get queue by URL
      Database::Entity::SQS::Queue queue;
      if (!request.queueUrl.empty()) {
        queue = _database->GetQueueByUrl(request.region, request.queueUrl);
      }

      // Set userAttributes
      Database::Entity::SQS::MessageAttributeList attributes;
      attributes.push_back({.attributeName="SentTimestamp", .attributeValue=std::to_string(Poco::Timestamp().epochMicroseconds() / 1000), .attributeType=Database::Entity::SQS::MessageAttributeType::NUMBER});
      attributes.push_back({.attributeName="ApproximateFirstReceivedTimestamp", .attributeValue=std::to_string(Poco::Timestamp().epochMicroseconds() / 1000), .attributeType=Database::Entity::SQS::MessageAttributeType::NUMBER});
      attributes.push_back({.attributeName="ApproximateReceivedCount", .attributeValue=std::to_string(0), .attributeType=Database::Entity::SQS::MessageAttributeType::NUMBER});
      attributes.push_back({.attributeName="SenderId", .attributeValue=request.region, .attributeType=Database::Entity::SQS::MessageAttributeType::STRING});
      for (const auto &attribute : request.messageAttributes) {
        attributes.push_back({.attributeName=attribute.name, .attributeValue=attribute.stringValue, .attributeType=Database::Entity::SQS::MessageAttributeTypeFromString(Dto::SQS::MessageAttributeDataTypeToString(attribute.type))});
      }

      // Set delay
      Poco::DateTime reset;
      Database::Entity::SQS::MessageStatus messageStatus = Database::Entity::SQS::MessageStatus::INITIAL;
      if (queue.attributes.delaySeconds > 0) {
        messageStatus = Database::Entity::SQS::MessageStatus::DELAYED;
        reset += Poco::Timespan(queue.attributes.delaySeconds, 0);
      }

      // Set parameters
      std::string messageId = Core::AwsUtils::CreateMessageId();
      std::string receiptHandle = Core::AwsUtils::CreateSqsReceiptHandler();
      std::string md5Body = Core::Crypto::GetMd5FromString(messageBody);
      std::string md5Attr = Dto::SQS::MessageAttribute::GetMd5Attributes(request.messageAttributes);

      // Update database
      Database::Entity::SQS::Message message = _database->CreateMessage(
        {
          .region= request.region,
          .queueUrl=queue.queueUrl,
          .body=messageBody,
          .status=messageStatus,
          .reset=reset,
          .messageId=messageId,
          .receiptHandle=receiptHandle,
          .md5Body=md5Body,
          .md5Attr=md5Attr,
          .attributes=attributes,
        });
      log_info_stream(_logger) << "Message send, messageId: " << request.messageId << " md5Body: " << md5Body << std::endl;

      return {
        .queueUrl=message.queueUrl,
        .messageId=message.messageId,
        .receiptHandle=message.receiptHandle,
        .md5Body=md5Body,
        .md5Attr=md5Attr,
        .requestId=request.requestId
      };

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS create message failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  Dto::SQS::ReceiveMessageResponse SQSService::ReceiveMessages(const Dto::SQS::ReceiveMessageRequest &request) {
    log_trace_stream(_logger) << "Receive message request: " << request.ToString() << std::endl;

    try {
      Database::Entity::SQS::MessageList messageList;
      Database::Entity::SQS::Queue queue = _database->GetQueueByUrl(request.region, request.queueUrl);

      long elapsed = 0;
      auto begin = std::chrono::high_resolution_clock::now();
      while (elapsed < request.waitTimeSeconds * 1000) {

        _database->ReceiveMessages(queue.region, queue.queueUrl, queue.attributes.visibilityTimeout, request.maxMessages, messageList);
        log_trace_stream(_logger) << "Messages in database, url: " << queue.queueUrl << " count: " << messageList.size() << std::endl;

        if (!messageList.empty()) {
          break;
        }

        auto end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

        // Wait for timeout or condition
        _mutex.lock();
        if (_condition.tryWait(_mutex, 500)) {
          return {};
        }
        _mutex.unlock();
      }

      Dto::SQS::ReceiveMessageResponse response;
      if (!messageList.empty()) {
        response.messageList = messageList;
        response.requestId = request.requestId;
        log_info_stream(_logger) << "Messages received, count: " << messageList.size() << " requestId: " << request.requestId << std::endl;
      }
      log_trace_stream(_logger) << "Messages in response: " << messageList.size() << std::endl;

      return response;

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS create message failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void SQSService::DeleteMessage(const Dto::SQS::DeleteMessageRequest &request) {
    log_trace_stream(_logger) << "Delete message request, url: " << request.receiptHandle << std::endl;

    try {
      // TODO: Check existence
      if (!_database->MessageExists(request.receiptHandle)) {
        throw Core::ServiceException("Queue does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
      }

      // Delete from database
      _database->DeleteMessage({.queueUrl=request.queueUrl, .receiptHandle=request.receiptHandle});

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS delete message failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void SQSService::DeleteMessageBatch(const Dto::SQS::DeleteMessageBatchRequest &request) {
    log_trace_stream(_logger) << "Delete message batch request, size: " << request.deleteMessageBatchEntries.size() << std::endl;

    try {

      for (const auto &entry : request.deleteMessageBatchEntries) {

        // TODO: Check existence
        if (!_database->MessageExists(entry.receiptHandle)) {
          throw Core::ServiceException("Queue does not exist", Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        }

        // Delete from database
        _database->DeleteMessage({.queueUrl=request.queueUrl, .receiptHandle=entry.receiptHandle});
      }

    } catch (Poco::Exception &ex) {
      log_error_stream(_logger) << "SQS delete message failed, message: " << ex.message() << std::endl;
      throw Core::ServiceException(ex.message(), Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

} // namespace AwsMock::Service
