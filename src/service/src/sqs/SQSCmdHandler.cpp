
#include "awsmock/service/SQSCmdHandler.h"

namespace AwsMock::Service {

  SQSCmdHandler::SQSCmdHandler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : AbstractHandler(), _logger(Poco::Logger::get("SQSCmdHandler")), _configuration(configuration),
                                                                                                                                     _metricService(metricService), _sqsService(configuration, condition) {
  }

  void SQSCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::SQSClientCommand &sqsClientCommand) {
    log_debug_stream(_logger) << "SQS POST request, URI: " << request.getURI() << " region: " << sqsClientCommand.region << " user: " << sqsClientCommand.user << " command: " << Dto::Common::SqsCommandTypeToString(sqsClientCommand.command) << std::endl;

    std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());

    switch (sqsClientCommand.command) {

      case Dto::Common::SqsCommandType::CREATE_QUEUE: {

        if (sqsClientCommand.contentType == "json") {

          Dto::SQS::CreateQueueRequest sqsRequest;
          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, sqsRequest.queueName);
          sqsRequest.region = sqsClientCommand.region;
          sqsRequest.owner = sqsClientCommand.user;

          Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
          SendOkResponse(response, sqsResponse.ToJson());
          log_info_stream(_logger) << "Create queue, queueName: " << sqsRequest.queueName << std::endl;

        } else {

          std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueName");
          std::string queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, queueName);
          std::vector<Dto::SQS::QueueAttribute> attributes = GetQueueAttributes(sqsClientCommand.payload);
          std::map<std::string, std::string> tags = GetQueueTags(sqsClientCommand.payload);

          Dto::SQS::CreateQueueRequest sqsRequest = {.region=sqsClientCommand.region, .queueName=queueName, .queueUrl=queueUrl, .owner=sqsClientCommand.user, .attributes=attributes, .tags=tags, .requestId=requestId};

          Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
          log_info_stream(_logger) << "Create queue, queueName: " << queueName << std::endl;
        }
        break;
      }

      case Dto::Common::SqsCommandType::PURGE_QUEUE: {

        Dto::SQS::PurgeQueueRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          sqsRequest = {.region=sqsClientCommand.region, .queueUrl=queueUrl};

        }
        _sqsService.PurgeQueue(sqsRequest);
        SendOkResponse(response);
        log_info_stream(_logger) << "Purge queue, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::GET_QUEUE_ATTRIBUTES: {

        Dto::SQS::GetQueueAttributesRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          std::vector<std::string> attributeNames = GetQueueAttributeNames(sqsClientCommand.payload);
          sqsRequest = {.region=sqsClientCommand.region, .queueUrl=queueUrl, .attributeNames=attributeNames};

        }

        Dto::SQS::GetQueueAttributesResponse sqsResponse = _sqsService.GetQueueAttributes(sqsRequest);
        SendOkResponse(response, sqsClientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
        log_info_stream(_logger) << "Get queue attributes, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::SET_QUEUE_ATTRIBUTES: {
        Dto::SQS::SetQueueAttributesRequest sqsRequest;

        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

          Dto::SQS::SetQueueAttributesResponse sqsResponse = _sqsService.SetQueueAttributes(sqsRequest);
          SendOkResponse(response, sqsResponse.ToJson());

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");

          int count = Core::HttpUtils::CountQueryParametersByPrefix(sqsClientCommand.payload, "Attribute")/2;
          log_trace_stream(_logger) << "Got attribute count, count: " << count << std::endl;

          AttributeList attributes;
          for (int i = 1; i <= count; i++) {
            std::string attributeName = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "Attribute." + std::to_string(i) + ".Name");
            std::string attributeValue = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "Attribute." + std::to_string(i) + ".Value");
            attributes[attributeName] = attributeValue;
          }

          sqsRequest = {.region=sqsClientCommand.region, .queueUrl=queueUrl, .attributes=attributes};

          Dto::SQS::SetQueueAttributesResponse sqsResponse = _sqsService.SetQueueAttributes(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
        }
        log_info_stream(_logger) << "Set queue attributes, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::GET_QUEUE_URL: {
        Dto::SQS::GetQueueUrlRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueName");
          sqsRequest = {.region=sqsClientCommand.region, .queueName=queueName};

        }
        Dto::SQS::GetQueueUrlResponse sqsResponse = _sqsService.GetQueueUrl(sqsRequest);
        SendOkResponse(response, sqsClientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
        log_info_stream(_logger) << "Get queue url, queueName: " << sqsRequest.queueName << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::TAG_QUEUE: {
        Dto::SQS::TagQueueRequest sqsRequest;

        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          std::string tagKey = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "Tag.Key");
          std::string tagValue = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "Tag.Key");

          std::map<std::string, std::string> tags;
          tags[tagKey] = tagValue;

          sqsRequest = {.region=sqsClientCommand.region, .queueUrl=queueUrl, .tags=tags};
        }
        _sqsService.TagQueue(sqsRequest);

        SendOkResponse(response);
        log_info_stream(_logger) << "Tag queue, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::LIST_QUEUES: {

        Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(sqsClientCommand.region);

        if (sqsClientCommand.contentType == "json") {

          SendOkResponse(response, sqsResponse.ToJson());
          log_info_stream(_logger) << "List queues" << std::endl;

        } else {

          SendOkResponse(response, sqsResponse.ToXml());
          log_info_stream(_logger) << "List queues" << std::endl;
        }
        break;
      }

      case Dto::Common::SqsCommandType::DELETE_QUEUE: {

        Dto::SQS::DeleteQueueRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

          Dto::SQS::DeleteQueueResponse sqsResponse = _sqsService.DeleteQueue(sqsRequest);

          // Empty response
          SendOkResponse(response);
          log_info_stream(_logger) << "Delete queue, queueUrl: " << sqsRequest.queueUrl << std::endl;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          sqsRequest = {.queueUrl=queueUrl};
          sqsRequest.region = sqsClientCommand.region;
          sqsRequest.requestId = requestId;

          Dto::SQS::DeleteQueueResponse sqsResponse = _sqsService.DeleteQueue(sqsRequest);
          SendOkResponse(response, sqsResponse.ToXml());
          log_info_stream(_logger) << "Delete queue, queueUrl: " << sqsRequest.queueUrl << std::endl;

        }
        break;
      }

      case Dto::Common::SqsCommandType::SEND_MESSAGE: {

        Dto::SQS::SendMessageRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;
          sqsRequest.messageId = requestId;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          std::string body = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "MessageBody");
          std::map<std::string, Dto::SQS::MessageAttribute> attributes = GetMessageAttributes(sqsClientCommand.payload);
          log_debug_stream(_logger) << "SendMessage, queueUrl " << queueUrl << std::endl;

          sqsRequest = {.queueUrl=queueUrl, .body=body, .attributes=attributes, .messageId=requestId};
          sqsRequest.region = sqsClientCommand.region;
          sqsRequest.requestId = requestId;
        }

        Dto::SQS::SendMessageResponse sqsResponse = _sqsService.SendMessage(sqsRequest);
        SendOkResponse(response, sqsClientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
        log_info_stream(_logger) << "Send message, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::RECEIVE_MESSAGE: {

        Dto::SQS::ReceiveMessageRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          int maxMessages = GetIntParameter(sqsClientCommand.payload, "MaxNumberOfMessages", 1, 10, 3);
          int waitTimeSeconds = GetIntParameter(sqsClientCommand.payload, "WaitTimeSeconds", 1, 900, 5);
          int visibility = GetIntParameter(sqsClientCommand.payload, "VisibilityTimeout", 1, 900, 30);
          sqsRequest = {.region=sqsClientCommand.region, .queueUrl=queueUrl, .maxMessages=maxMessages, .visibilityTimeout=visibility, .waitTimeSeconds=waitTimeSeconds, .requestId=requestId};

        }
        Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);

        // Set the message userAttributes
        SendOkResponse(response, sqsClientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
        log_info_stream(_logger) << "Receive message, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::CHANGE_MESSAGE_VISIBILITY: {

        Dto::SQS::ChangeMessageVisibilityRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          int visibilityTimeout = GetIntParameter(sqsClientCommand.payload, "VisibilityTimeout", 30, 12 * 3600, 60);
          std::string receiptHandle = GetStringParameter(sqsClientCommand.payload, "ReceiptHandle");

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          sqsRequest = {.region=sqsClientCommand.region, .queueUrl=queueUrl, .receiptHandle=receiptHandle, .visibilityTimeout=visibilityTimeout};

        }

        _sqsService.SetVisibilityTimeout(sqsRequest);
        SendOkResponse(response);
        log_info_stream(_logger) << "Change visibility, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::DELETE_MESSAGE: {

        Dto::SQS::DeleteMessageRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");
          std::string receiptHandle = GetStringParameter(sqsClientCommand.payload, "ReceiptHandle");
          sqsRequest = {
            .region=sqsClientCommand.region,
            .queueUrl=queueUrl,
            .receiptHandle=receiptHandle
          };
        }

        _sqsService.DeleteMessage(sqsRequest);
        SendOkResponse(response);
        log_info_stream(_logger) << "Delete message, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::DELETE_MESSAGE_BATCH: {

        Dto::SQS::DeleteMessageBatchRequest sqsRequest;
        if (sqsClientCommand.contentType == "json") {

          sqsRequest.FromJson(sqsClientCommand.payload);
          sqsRequest.region = sqsClientCommand.region;

        } else {

          sqsRequest.queueUrl = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "QueueUrl");

          // Get message count
          int count = Core::HttpUtils::CountQueryParametersByPrefix(sqsClientCommand.payload, "DeleteMessageBatchRequestEntry") / 2;
          log_trace_stream(_logger) << "Got entry count, count: " << count << std::endl;

          for (int i = 1; i <= count; i++) {
            std::string id = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "DeleteMessageBatchRequestEntry." + std::to_string(i) + ".Id");
            std::string receiptHandle = Core::HttpUtils::GetQueryParameterValueByName(sqsClientCommand.payload, "DeleteMessageBatchRequestEntry." + std::to_string(i) + ".ReceiptHandle");
            Dto::SQS::DeleteMessageBatchEntry entry = {.id=id, .receiptHandle=receiptHandle};
            sqsRequest.deleteMessageBatchEntries.emplace_back(entry);
          }
        }
        _sqsService.DeleteMessageBatch(sqsRequest);
        SendOkResponse(response);
        log_info_stream(_logger) << "Delete message batch, queueUrl: " << sqsRequest.queueUrl << std::endl;

        break;
      }

      case Dto::Common::SqsCommandType::UNKNOWN: {
        log_error_stream(_logger) << "Bad request, method: POST clientCommand: " << Dto::Common::SqsCommandTypeToString(sqsClientCommand.command) << std::endl;
        throw Core::ServiceException("Bad request, method: POST clientCommand: " + Dto::Common::SqsCommandTypeToString(sqsClientCommand.command));
      }
    }
  }

  std::vector<Dto::SQS::QueueAttribute> SQSCmdHandler::GetQueueAttributes(const std::string &payload) {

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

  std::map<std::string, std::string> SQSCmdHandler::GetQueueTags(const std::string &payload) {

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

  std::vector<std::string> SQSCmdHandler::GetQueueAttributeNames(const std::string &payload) {

    int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "AttributeName");
    log_trace_stream(_logger) << "Got attribute names count: " << count << std::endl;

    std::vector<std::string> attributeNames;
    for (int i = 1; i <= count; i++) {
      attributeNames.emplace_back(Core::HttpUtils::GetQueryParameterValueByName(payload, "AttributeName." + std::to_string(i)));
    }
    return attributeNames;
  }

  std::map<std::string, Dto::SQS::MessageAttribute> SQSCmdHandler::GetMessageAttributes(const std::string &payload) {

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
      Dto::SQS::MessageAttribute messageAttribute = {.name=attributeName, .stringValue=attributeValue, .type=Dto::SQS::MessageAttributeDataTypeFromString(attributeType)};
      messageAttributes[attributeName] = messageAttribute;
    }
    log_debug_stream(_logger) << "Extracted message attribute count: " << messageAttributes.size() << std::endl;
    return messageAttributes;
  }
}
