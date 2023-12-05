
#include "awsmock/service/SQSCppHandler.h"

namespace AwsMock::Service {

  SQSCppHandler::SQSCppHandler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : AbstractHandler(), _logger(Poco::Logger::get("SQSCppHandler")), _configuration(configuration),
                                                                                                                                     _metricService(metricService), _sqsService(configuration, condition) {
  }

  void SQSCppHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS GET request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSCppHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSCppHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    try {

      std::string payload = GetPayload(request);
      std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
      std::string action = Core::HttpUtils::GetQueryParameterValueByName(payload, "Action");
      std::string version = Core::HttpUtils::GetQueryParameterValueByName(payload, "Version");
      log_debug_stream(_logger) << "SQS POST request, action: " << action << " version: " << version << std::endl;

      if (action == "CreateQueu") {

        std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueName");
        std::string queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, queueName);

        std::vector<Dto::SQS::QueueAttribute> attributes = GetQueueAttributes(payload);
        std::map<std::string, std::string> tags = GetQueueTags(payload);

        Dto::SQS::CreateQueueRequest sqsRequest = {
            .region=region,
            .name=queueName,
            .queueUrl=queueUrl,
            .owner=user,
            .attributes=attributes,
            .tags=tags
        };
        Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
        SendOkResponse(response, sqsResponse.ToXml());

      } else if (action == "ListQueues") {

        Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(region);
        SendOkResponse(response, sqsResponse.ToXml());

      } else if (action == "DeleteQueue") {

        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");

        Dto::SQS::DeleteQueueRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl
        };
        _sqsService.DeleteQueue(sqsRequest);
        SendOkResponse(response);

      } else if (action == "SendMessage") {

        std::string messageId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
        std::string body = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageBody");
        std::vector<Dto::SQS::MessageAttribute> attributes = GetMessageAttributes(payload);
        log_debug_stream(_logger) << "SendMessage, queueUrl " << queueUrl << std::endl;

        Dto::SQS::SendMessageRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl,
            .body=body,
            .messageAttributes=attributes,
            .requestId=requestId,
            .messageId=messageId
        };
        Dto::SQS::SendMessageResponse sqsResponse = _sqsService.SendMessage(sqsRequest);
        SendOkResponse(response, sqsResponse.ToXml());

      } else if (action == "GetQueueUrl") {

        std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueName");

        Dto::SQS::GetQueueUrlRequest sqsRequest = {
            .region=region,
            .queueName=queueName
        };
        Dto::SQS::GetQueueUrlResponse sqsResponse = _sqsService.GetQueueUrl(sqsRequest);
        SendOkResponse(response, sqsResponse.ToXml());

      } else if (action == "ReceiveMessage") {

        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");

        int maxMessages = GetIntParameter(payload, "MaxNumberOfMessages", 1, 10, 3);
        int waitTimeSeconds = GetIntParameter(payload, "WaitTimeSeconds", 1, 900, 5);
        int visibility = GetIntParameter(payload, "VisibilityTimeout", 1, 900, 30);

        Dto::SQS::ReceiveMessageRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl,
            .maxMessages=maxMessages,
            .visibilityTimeout=visibility,
            .waitTimeSeconds=waitTimeSeconds,
            .requestId=requestId
        };
        Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);

        // Set the message attributes
        std::map<std::string, std::string> extraHeader = {{"contentType", "application/xml"}};
        log_debug_stream(_logger) << "ReceiveMessage, queueUrl " << queueUrl << " count: " << sqsResponse.messageList.size() << std::endl;
        SendOkResponse(response, sqsResponse.ToXml(), extraHeader);

      } else if (action == "PurgeQueue") {

        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");

        Dto::SQS::PurgeQueueRequest sqsRequest = {
            .queueUrl=queueUrl,
            .region=region
        };
        _sqsService.PurgeQueue(sqsRequest);

        SendOkResponse(response);

      } else if (action == "GetQueueAttributes") {

        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
        std::vector<std::string> attributeNames = GetQueueAttributeNames(payload);

        Dto::SQS::GetQueueAttributesRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl,
            .attributeNames=attributeNames
        };
        Dto::SQS::GetQueueAttributesResponse sqsResponse = _sqsService.GetQueueAttributes(sqsRequest);

        SendOkResponse(response, sqsResponse.ToXml());

      } else if (action == "SetQueueAttributes") {

        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");

        int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "Attribute");
        log_trace_stream(_logger) << "Got attribute count, count: " << count << std::endl;

        AttributeList attributes;
        for (int i = 1; i <= count; i++) {
          std::string attributeName = Core::HttpUtils::GetQueryParameterValueByName(payload, "Attribute." + std::to_string(i) + ".Name");
          std::string attributeValue = Core::HttpUtils::GetQueryParameterValueByName(payload, "Attribute." + std::to_string(i) + ".Value");
          attributes[attributeName] = attributeValue;
        }

        Dto::SQS::SetQueueAttributesRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl,
            .attributes=attributes
        };
        _sqsService.SetQueueAttributes(sqsRequest);

        SendOkResponse(response);

      } else if (action == "ChangeMessageVisibility") {

        //DumpRequestHeaders(request);
        //DumpPayload(payload);

        int visibilityTimeout = GetIntParameter(payload, "VisibilityTimeout", 30, 12 * 3600, 60);
        std::string receiptHandle = GetStringParameter(payload, "ReceiptHandle");

        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");

        Dto::SQS::ChangeMessageVisibilityRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl,
            .receiptHandle=receiptHandle,
            .visibilityTimeout=visibilityTimeout
        };

        SendOkResponse(response);

      } else if (action == "DeleteMessage") {

        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
        std::string receiptHandle = GetStringParameter(payload, "ReceiptHandle");

        Dto::SQS::DeleteMessageRequest sqsRequest = {
            .region=region,
            .queueUrl=queueUrl,
            .receiptHandle=receiptHandle
        };
        _sqsService.DeleteMessage(sqsRequest);

        SendOkResponse(response);

      } else if (action == "DeleteMessageBatch") {

        Dto::SQS::DeleteMessageBatchRequest sqsRequest;
        sqsRequest.queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");

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
      SendXmlErrorResponse("SQS", response, exc);
    }
  }

  void SQSCppHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSCppHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {

    log_debug_stream(_logger) << "SQS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void SQSCppHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::vector<Dto::SQS::QueueAttribute> SQSCppHandler::GetQueueAttributes(const std::string &payload) {

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

  std::map<std::string, std::string> SQSCppHandler::GetQueueTags(const std::string &payload) {

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

  std::vector<std::string> SQSCppHandler::GetQueueAttributeNames(const std::string &payload) {

    int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "Attribute");
    log_trace_stream(_logger) << "Got attribute names count: " << count << std::endl;

    std::vector<std::string> attributeNames;
    for (int i = 1; i <= count; i++) {
      attributeNames.emplace_back(Core::HttpUtils::GetQueryParameterValueByName(payload, "AttributeName." + std::to_string(i)));
    }
    return attributeNames;
  }

  std::vector<Dto::SQS::MessageAttribute> SQSCppHandler::GetMessageAttributes(const std::string &payload) {

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
      Dto::SQS::MessageAttribute messageAttribute = {.name=attributeName, .stringValue=attributeValue, .type=Dto::SQS::MessageAttributeDataTypeFromString(attributeType)};
      messageAttributes.emplace_back(messageAttribute);
    }
    log_debug_stream(_logger) << "Extracted message attribute count: " << messageAttributes.size() << std::endl;
    return messageAttributes;
  }
}
