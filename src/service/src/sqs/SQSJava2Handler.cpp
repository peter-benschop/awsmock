
#include "awsmock/service/SQSJava2Handler.h"

namespace AwsMock::Service {

  SQSJava2Handler::SQSJava2Handler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : AbstractHandler(), _logger(Poco::Logger::get("SQSJava2Handler")), _configuration(configuration),
                                                                                                                                         _metricService(metricService), _sqsService(configuration, condition) {
  }

  void SQSJava2Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS GET request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSJava2Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSJava2Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    //DumpRequest(request);
    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "sqs");

    std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
    std::string payload = GetBodyAsString(request);
    std::string action = GetActionFromHeader(request, payload);
    log_debug_stream(_logger) << "SQS POST request, action: " << action << " content: " << userAgent.contentType << std::endl;

    try {
      if (action == "CreateQueue") {

        Dto::SQS::CreateQueueRequest sqsRequest;
        sqsRequest.region = region;
        sqsRequest.requestId = requestId;

        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, sqsRequest.queueName);
          sqsRequest.owner = user;
          log_debug_stream(_logger) << "SQS create queue request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
          SendOkResponse(response, sqsResponse.ToJson());

        } else {

          std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueName");
          std::string queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, queueName);
          std::vector<Dto::SQS::QueueAttribute> attributes = GetQueueAttributes(payload);
          std::map<std::string, std::string> tags = GetQueueTags(payload);
          sqsRequest = {.region=region, .queueName=queueName, .queueUrl=queueUrl, .owner=user, .attributes=attributes, .tags=tags, .requestId=requestId};
          log_debug_stream(_logger) << "SQS create queue request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
        }

      } else if (action == "ListQueues") {

        log_debug_stream(_logger) << "SQS list queue request, region: " << region << std::endl;
        if (userAgent.contentType == "json") {

          Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(region);
          SendOkResponse(response, sqsResponse.ToJson());

        } else {

          Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(region);
          SendOkResponse(response, sqsResponse.ToXml());

        }

      } else if (action == "DeleteQueue") {

        Dto::SQS::DeleteQueueRequest sqsRequest;
        sqsRequest.region = region;
        sqsRequest.requestId = requestId;

        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          sqsRequest = {.queueUrl=queueUrl};
        }
        log_debug_stream(_logger) << "SQS delete queue request: " << sqsRequest.ToString() << std::endl;

        _sqsService.DeleteQueue(sqsRequest);
        SendOkResponse(response);

      } else if (action == "SendMessage") {

        Dto::SQS::SendMessageRequest sqsRequest;
        sqsRequest.region = region;
        sqsRequest.requestId = requestId;

        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;
          sqsRequest.messageId = requestId;
          log_debug_stream(_logger) << "SQS send message request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::SendMessageResponse sqsResponse = _sqsService.SendMessage(sqsRequest);
          SendOkResponse(response, sqsResponse.ToJson());

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          std::string body = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageBody");
          std::map<std::string, Dto::SQS::MessageAttribute> attributes = GetMessageAttributes(payload);
          log_debug_stream(_logger) << "SendMessage, queueUrl " << queueUrl << std::endl;

          sqsRequest = {.queueUrl=queueUrl, .body=body, .attributes=attributes, .messageId=requestId};
          sqsRequest.region=region;
          sqsRequest.requestId = requestId;
          log_debug_stream(_logger) << "SQS send message request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::SendMessageResponse sqsResponse = _sqsService.SendMessage(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
        }

      } else if (action == "GetQueueUrl") {

        Dto::SQS::GetQueueUrlRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;
          log_debug_stream(_logger) << "SQS get queue URL request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::GetQueueUrlResponse sqsResponse = _sqsService.GetQueueUrl(sqsRequest);
          SendOkResponse(response, sqsResponse.ToJson());

        } else {

          std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueName");
          sqsRequest = {.region=region, .queueName=queueName};
          log_debug_stream(_logger) << "SQS get queue URL request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::GetQueueUrlResponse sqsResponse = _sqsService.GetQueueUrl(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
        }

      } else if (action == "ReceiveMessage") {

        Dto::SQS::ReceiveMessageRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;
          log_debug_stream(_logger) << "SQS receive message request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);
          SendOkResponse(response, sqsResponse.ToJson());

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          int maxMessages = GetIntParameter(payload, "MaxNumberOfMessages", 1, 10, 3);
          int waitTimeSeconds = GetIntParameter(payload, "WaitTimeSeconds", 1, 900, 5);
          int visibility = GetIntParameter(payload, "VisibilityTimeout", 1, 900, 30);

          sqsRequest = {.region=region, .queueUrl=queueUrl, .maxMessages=maxMessages, .visibilityTimeout=visibility, .waitTimeSeconds=waitTimeSeconds, .requestId=requestId};
          log_debug_stream(_logger) << "SQS receive message request: " << sqsRequest.ToString() << std::endl;

          Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
        }

      } else if (action == "PurgeQueue") {

        Dto::SQS::PurgeQueueRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          sqsRequest = {.region=region, .queueUrl=queueUrl};

        }
        _sqsService.PurgeQueue(sqsRequest);
        SendOkResponse(response);

      } else if (action == "TagQueue") {

        Dto::SQS::TagQueueRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          std::string tagKey = Core::HttpUtils::GetQueryParameterValueByName(payload, "Tag.Key");
          std::string tagValue = Core::HttpUtils::GetQueryParameterValueByName(payload, "Tag.Key");

          std::map<std::string, std::string> tags;
          tags[tagKey] = tagValue;

          sqsRequest = {.region=region, .queueUrl=queueUrl, .tags=tags};

        }
        _sqsService.TagQueue(sqsRequest);
        SendOkResponse(response);

      } else if (action == "GetQueueAttributes") {

        if (userAgent.contentType == "json") {

          Dto::SQS::GetQueueAttributesRequest sqsRequest;
          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

          Dto::SQS::GetQueueAttributesResponse sqsResponse = _sqsService.GetQueueAttributes(sqsRequest);
          SendOkResponse(response, sqsResponse.ToJson());

        } else {

          Dto::SQS::GetQueueAttributesRequest sqsRequest;
          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          std::vector<std::string> attributeNames = Core::HttpUtils::GetQueryParametersByPrefix(payload, "Attribute");
          sqsRequest = {.region=region, .queueUrl=queueUrl, .attributeNames=attributeNames};

          Dto::SQS::GetQueueAttributesResponse sqsResponse = _sqsService.GetQueueAttributes(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
        }

      } else if (action == "SetQueueAttributes") {

        Dto::SQS::SetQueueAttributesRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "UserAttribute");
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

      } else if (action == "ChangeMessageVisibility") {

        Dto::SQS::ChangeMessageVisibilityRequest sqsRequest;

        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          int visibilityTimeout = GetIntParameter(payload, "VisibilityTimeout", 30, 12 * 3600, 60);
          std::string receiptHandle = GetStringParameter(payload, "ReceiptHandle");

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          sqsRequest = {.region=region, .queueUrl=queueUrl, .receiptHandle=receiptHandle, .visibilityTimeout=visibilityTimeout};
        }
        _sqsService.SetVisibilityTimeout(sqsRequest);
        SendOkResponse(response);

      } else if (action == "DeleteMessage") {

        Dto::SQS::DeleteMessageRequest sqsRequest;
        if (userAgent.contentType == "json") {

          sqsRequest.FromJson(payload);
          sqsRequest.region = region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(payload, "QueueUrl");
          std::string receiptHandle = GetStringParameter(payload, "ReceiptHandle");
          sqsRequest = {.region=region, .queueUrl=queueUrl, .receiptHandle=receiptHandle};
        }
        _sqsService.DeleteMessage(sqsRequest);
        SendOkResponse(response);

      } else if (action == "DeleteMessageBatch") {

        Dto::SQS::DeleteMessageBatchRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        _sqsService.DeleteMessageBatch(sqsRequest);

        SendOkResponse(response);
      }
    } catch (Core::ServiceException &exc) {
      log_error_stream(_logger) << "SQS module exception: " << exc.message() << std::endl;
      SendJsonErrorResponse("SQS", response, exc);
    }
  }

  void SQSJava2Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
    DumpResponse(response);
  }

  void SQSJava2Handler::handleOptions(Poco::Net::HTTPServerResponse &response) {

    log_debug_stream(_logger) << "SQS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void SQSJava2Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {

    log_debug_stream(_logger) << "SQS HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::string SQSJava2Handler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request, const std::string &payload) {

    std::string action;
    std::string contentType = request["Content-Type"];
    if (Core::StringUtils::ContainsIgnoreCase(contentType, "application/x-www-form-urlencoded")) {

      action = Core::HttpUtils::GetQueryParameterValueByName(payload, "Action");

    } else if (Core::StringUtils::ContainsIgnoreCase(contentType, "application/x-amz-json-1.0")) {

      std::string headerValue = request["X-Amz-Target"];
      action = Core::StringUtils::Split(headerValue, '.')[1];

    }
    return action;
  }

  std::map<std::string, Dto::SQS::MessageAttribute> SQSJava2Handler::GetMessageAttributes(const std::string &payload) {

    std::map<std::string, Dto::SQS::MessageAttribute> messageAttributes;

    int attributeCount = Core::HttpUtils::CountQueryParametersByPrefix(payload, "MessageAttribute");
    log_debug_stream(_logger) << "Got message attribute count: " << attributeCount << std::endl;

    for (int i = 1; i <= attributeCount / 3; i++) {

      std::string attributeName = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Name");
      std::string attributeType = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Value.DataType");

      std::string attributeValue;
      if (attributeType == "String" || attributeType == "Number") {
        attributeValue = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Value.StringValue");
      }
      Dto::SQS::MessageAttribute messageAttribute = {.name=attributeName, .stringValue=attributeValue, .type=Dto::SQS::MessageAttributeDataTypeFromString(attributeType), .systemAttribute=false};
      messageAttributes[attributeName] = messageAttribute;
    }
    log_debug_stream(_logger) << "Extracted message attribute count: " << messageAttributes.size() << std::endl;
    return messageAttributes;
  }

  std::vector<Dto::SQS::QueueAttribute> SQSJava2Handler::GetQueueAttributes(const std::string &payload) {

    std::vector<Dto::SQS::QueueAttribute> queueAttributes;

    int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "UserAttribute") / 2;
    log_trace_stream(_logger) << "Got attribute count, count: " << count << std::endl;

    for (int i = 1; i <= count; i++) {
      Dto::SQS::QueueAttribute attribute = {
        .attributeName=Core::HttpUtils::GetQueryParameterValueByName(payload, "UserAttribute." + std::to_string(i) + ".Name"),
        .attributeValue=Core::HttpUtils::GetQueryParameterValueByName(payload, "UserAttribute." + std::to_string(i) + ".Value")
      };
      queueAttributes.emplace_back(attribute);
    }
    return queueAttributes;
  }

  std::map<std::string, std::string> SQSJava2Handler::GetQueueTags(const std::string &payload) {

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
}
