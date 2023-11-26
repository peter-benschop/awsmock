
#include "awsmock/service/SQSHandler.h"

namespace AwsMock::Service {

  SQSHandler::SQSHandler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : AbstractHandler(), _logger(Poco::Logger::get("SQSServiceHandler")), _configuration(configuration),
                                                                                                                               _metricService(metricService), _sqsService(configuration, condition) {
    _accountId = _configuration.getString("awsmock.account.id", "000000000000");
    _endpoint = Core::AwsUtils::GetEndpoint(configuration);
  }

  void SQSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS GET request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SQS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "sqs");
      log_debug_stream(_logger) << "SQS POST request, userAgent: " << userAgent.ToString() << std::endl;

      std::string payload = GetPayload(request);
      std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());

      if (userAgent.clientCommand == "create-queue") {

        Dto::SQS::CreateQueueRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, sqsRequest.name);
          sqsRequest.region = region;
          sqsRequest.owner = user;

        } else {

          std::string queueName = GetQueueName(request, payload);
          std::string queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, queueName);
          std::vector<Dto::SQS::QueueAttribute> attributes = GetQueueAttributes(payload);
          std::map<std::string, std::string> tags = GetQueueTags(payload);

          sqsRequest = {.region=region, .name=queueName, .queueUrl=queueUrl, .owner=user, .attributes=attributes, .tags=tags};
        }

        Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);

        if (userAgent.contentType == "json") {
          SendOkResponse(response, sqsResponse.ToJson());
        } else {
          SendOkResponse(response, sqsResponse.ToXml());
        }

      } else if (userAgent.clientCommand == "list-queues") {

        Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(region);
        if (userAgent.contentType == "json") {
          SendOkResponse(response, sqsResponse.ToJson());
        } else {
          SendOkResponse(response, sqsResponse.ToXml());
        }

      } else if (userAgent.clientCommand == "delete-queue") {

        Dto::SQS::DeleteQueueRequest sqsRequest;
        if (userAgent.contentType == "json") {
          sqsRequest.FromJson(payload);
          sqsRequest.region = region;
        } else {
          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          sqsRequest = {.region=region, .queueUrl=queueUrl};
        }

        _sqsService.DeleteQueue(sqsRequest);
        SendOkResponse(response);

      } else if (userAgent.clientCommand == "send-message") {

        Dto::SQS::SendMessageRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = GetQueueUrl(request, payload);
          std::string queueArn = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueArn");
          std::string body = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageBody");
          std::vector<Dto::SQS::MessageAttribute> attributes = GetMessageAttributes(payload);
          log_debug_stream(_logger) << "SendMessage, queueUrl " << queueUrl << " queueArn: " << queueArn << std::endl;

          sqsRequest = {.region=region, .queueUrl=queueUrl, .queueArn=queueArn, .body=body, .messageAttributes=attributes, .requestId=requestId};
        }

        Dto::SQS::SendMessageResponse sqsResponse = _sqsService.SendMessage(sqsRequest);
        SendOkResponse(response, userAgent.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());

      } else if (userAgent.clientCommand == "get-queue-url") {

        Dto::SQS::GetQueueUrlRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueName = GetQueueName(request, payload);
          sqsRequest = {.region=region, .queueName=queueName};

        }
        Dto::SQS::GetQueueUrlResponse sqsResponse = _sqsService.GetQueueUrl(sqsRequest);
        SendOkResponse(response, userAgent.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());

      } else if (userAgent.clientCommand == "receive-message") {

        Dto::SQS::ReceiveMessageRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueName = GetQueueName(request, payload);
          int maxMessages = GetIntParameter(payload, "MaxNumberOfMessages", 1, 10, 3);
          int waitTimeSeconds = GetIntParameter(payload, "WaitTimeSeconds", 1, 900, 5);
          int visibility = GetIntParameter(payload, "VisibilityTimeout", 1, 900, 30);
          sqsRequest = {.region=region, .queueName=queueName, .maxMessages=maxMessages, .visibilityTimeout=visibility, .waitTimeSeconds=waitTimeSeconds, .requestId=requestId};

        }
        Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);

        // Set the message attributes
        SendOkResponse(response, userAgent.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());

      } else if (userAgent.clientCommand == "purge-queue") {

        Dto::SQS::PurgeQueueRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = GetQueueUrl(request, payload);
          sqsRequest = {.queueUrl=queueUrl, .region=region};

        }
        _sqsService.PurgeQueue(sqsRequest);
        SendOkResponse(response);

      } else if (userAgent.clientCommand == "get-queue-attributes") {

        Dto::SQS::GetQueueAttributesRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = GetQueueUrl(request, payload);
          std::vector<std::string> attributeNames = GetQueueAttributeNames(payload);
          sqsRequest = {.region=region, .queueUrl=queueUrl, .attributeNames=attributeNames};

        }

        Dto::SQS::GetQueueAttributesResponse sqsResponse = _sqsService.GetQueueAttributes(sqsRequest);
        SendOkResponse(response, userAgent.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());

      } else if (userAgent.clientCommand == "set-queue-attributes") {

        Dto::SQS::SetQueueAttributesRequest sqsRequest;

        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = GetQueueUrl(request, payload);

          int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "Attribute");
          log_trace_stream(_logger) << "Got attribute count, count: " << count << std::endl;

          AttributeList attributes;
          for (int i = 1; i <= count; i++) {
            std::string attributeName = Core::HttpUtils::GetQueryParameterValueByName(payload, "Attribute." + std::to_string(i) + ".Name");
            std::string attributeValue = Core::HttpUtils::GetQueryParameterValueByName(payload, "Attribute." + std::to_string(i) + ".Value");
            attributes[attributeName] = attributeValue;
          }

          sqsRequest = {.region=region, .queueUrl=queueUrl, .attributes=attributes};
        }
        _sqsService.SetQueueAttributes(sqsRequest);

        SendOkResponse(response);

      } else if (userAgent.clientCommand == "change-visibilityTimeout-timeout") {

        Dto::SQS::ChangeMessageVisibilityRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          int visibilityTimeout = GetIntParameter(payload, "VisibilityTimeout", 30, 12 * 3600, 60);
          std::string receiptHandle = GetStringParameter(payload, "ReceiptHandle");

          std::string queueUrl = GetQueueUrl(request, payload);
          sqsRequest = {.region=region, .queueUrl=queueUrl, .receiptHandle=receiptHandle, .visibilityTimeout=visibilityTimeout};

        }

        _sqsService.SetVisibilityTimeout(sqsRequest);
        SendOkResponse(response);

      } else if (userAgent.clientCommand == "DeleteMessage") {

        std::string queueUrl = GetQueueUrl(request, payload);
        std::string receiptHandle = GetStringParameter(payload, "ReceiptHandle");

        Dto::SQS::DeleteMessageRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl,
            .receiptHandle=receiptHandle
        };
        _sqsService.DeleteMessage(sqsRequest);

        SendOkResponse(response);

      } else if (userAgent.clientCommand == "DeleteMessageBatch") {

        Dto::SQS::DeleteMessageBatchRequest sqsRequest;
        sqsRequest.queueUrl = GetQueueUrl(request, payload);

        // Get message count
        int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "DeleteMessageBatchRequestEntry") / 2;
        log_trace_stream(_logger) << "Got entry count, count: " << count << std::endl;

        for (int i = 1; i <= count; i++) {
          std::string id = Core::HttpUtils::GetQueryParameterValueByName(payload, "DeleteMessageBatchRequestEntry." + std::to_string(i) + ".Id");
          std::string receiptHandle = Core::HttpUtils::GetQueryParameterValueByName(payload, "DeleteMessageBatchRequestEntry." + std::to_string(i) + ".ReceiptHandle");
          Dto::SQS::DeleteMessageBatchEntry entry = {.id=id, .receiptHandle=receiptHandle};
          sqsRequest.deleteMessageBatchEntries.emplace_back(entry);
        }
        _sqsService.DeleteMessageBatch(sqsRequest);

        SendOkResponse(response);
      }

    } catch (Core::ServiceException &exc) {
      _logger.error() << "SQS module exception: " << exc.message() << std::endl;
      SendErrorResponse("SQS", response, exc);
    }
  }

  void SQSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {

    log_debug_stream(_logger) << "SQS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void SQSHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::string SQSHandler::GetQueueName(const Poco::Net::HTTPServerRequest &request, const std::string &payload) {

    const std::string &uri = request.getURI();
    if (uri == "/") {
      return Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueName");
    } else {
      return Core::StringUtils::Split(uri, '/')[2];
    }
    /*switch (GetUserAgent(request)) {
    case UserAgentType::AWS_CLI:
    case UserAgentType::AWS_SDK_CPP:return Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueName");
    case UserAgentType::AWS_SDK_JAVA:return Core::HttpUtils::GetPathParameter(request.getURI(), 2);
    case UserAgentType::AWS_SDK_UNKNOWN:break;
    }
    return std::string{};*/
  }

  std::string SQSHandler::GetQueueUrl(const Poco::Net::HTTPServerRequest &request, const std::string &payload) {

    const std::string &uri = request.getURI();
    switch (GetUserAgent(request)) {
    case UserAgentType::AWS_CLI:
    case UserAgentType::AWS_SDK_CPP:return Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
    case UserAgentType::AWS_SDK_JAVA:return Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
    case UserAgentType::AWS_SDK_UNKNOWN:break;
    }
    return std::string{};
  }

  UserAgentType SQSHandler::GetUserAgent(const Poco::Net::HTTPServerRequest &request) {

    if (request.has("User-Agent")) {
      std::string userAgent = request["User-Agent"];
      if (Core::StringUtils::Contains(userAgent, "aws-cli")) {
        return UserAgentType::AWS_CLI;
      } else if (Core::StringUtils::Contains(userAgent, "aws-sdk-java")) {
        return UserAgentType::AWS_SDK_JAVA;
      } else if (Core::StringUtils::Contains(userAgent, "aws-sdk-cpp")) {
        return UserAgentType::AWS_SDK_CPP;
      }
    }
    throw Poco::Exception("Unknown user agent");
  }

  std::vector<Dto::SQS::QueueAttribute> SQSHandler::GetQueueAttributes(const std::string &payload) {

    std::vector<Dto::SQS::QueueAttribute> queueAttributes;

    int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "Attribute") / 2;
    log_trace_stream(_logger) << "Got attribute count, count: " << count << std::endl;

    for (int i = 1; i <= count; i++) {
      Dto::SQS::QueueAttribute attribute = {
          .attributeName=Core::HttpUtils::GetQueryParameterValueByName(payload, "Attribute." + std::to_string(i) + ".Name"),
          .attributeValue=Core::HttpUtils::GetQueryParameterValueByName(payload, "Attribute." + std::to_string(i) + ".Value")
      };
      queueAttributes.emplace_back(attribute);
    }
    return queueAttributes;
  }

  std::map<std::string, std::string> SQSHandler::GetQueueTags(const std::string &payload) {

    std::map<std::string, std::string> queueTags;

    int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "Tag") / 2;
    log_trace_stream(_logger) << "Got tags count, count: " << count << std::endl;

    for (int i = 1; i <= count; i++) {
      std::string key = Core::HttpUtils::GetQueryParameterValueByName(payload, "Tag." + std::to_string(i) + ".Key");
      std::string value = Core::HttpUtils::GetQueryParameterValueByName(payload, "Tag." + std::to_string(i) + ".Value");
      if (!key.empty() && !value.empty()) {
        queueTags[key] = value;
      }
    }
    return queueTags;
  }

  std::vector<std::string> SQSHandler::GetQueueAttributeNames(const std::string &payload) {

    int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "Attribute");
    log_trace_stream(_logger) << "Got attribute names count: " << count << std::endl;

    std::vector<std::string> attributeNames;
    for (int i = 1; i <= count; i++) {
      attributeNames.emplace_back(Core::HttpUtils::GetQueryParameterValueByName(payload, "AttributeName." + std::to_string(i)));
    }
    return attributeNames;
  }

  std::vector<Dto::SQS::MessageAttribute> SQSHandler::GetMessageAttributes(const std::string &payload) {

    std::vector<Dto::SQS::MessageAttribute> messageAttributes;

    int attributeCount = Core::HttpUtils::CountQueryParametersByPrefix(payload, "MessageAttribute");
    log_debug_stream(_logger) << "Got message attribute count: " << attributeCount << std::endl;

    for (int i = 1; i <= attributeCount / 3; i++) {

      std::string attributeName = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Name");
      std::string attributeType = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Value.DataType");

      std::string attributeValue;
      if (attributeType == "String" || attributeType == "Number") {
        attributeValue = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Value.StringValue");
      }
      Dto::SQS::MessageAttribute messageAttribute = {.attributeName=attributeName, .attributeValue=attributeValue, .type=attributeType};
      messageAttributes.emplace_back(messageAttribute);
    }
    log_debug_stream(_logger) << "Extracted message attribute count: " << messageAttributes.size() << std::endl;
    return messageAttributes;
  }
}
