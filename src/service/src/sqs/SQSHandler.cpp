
#include <awsmock/service/sqs/SQSHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> SQSHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_debug << "SQS POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::SQSClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {
            switch (clientCommand.command) {

                case Dto::Common::SqsCommandType::CREATE_QUEUE: {

                    if (clientCommand.contentType == "json") {

                        Dto::SQS::CreateQueueRequest sqsRequest;
                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.queueUrl = Core::CreateSQSQueueUrl(sqsRequest.queueName);
                        sqsRequest.region = clientCommand.region;
                        sqsRequest.owner = clientCommand.user;

                        Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
                        return SendOkResponse(request, sqsResponse.ToJson());
                        log_info << "Create queue, queueName: " << sqsRequest.queueName;

                    } else {

                        std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueName");
                        std::string queueUrl = Core::CreateSQSQueueUrl(queueName);
                        std::vector<Dto::SQS::QueueAttribute> attributes = GetQueueAttributes(clientCommand.payload);
                        std::map<std::string, std::string> tags = GetQueueTags(clientCommand.payload);

                        Dto::SQS::CreateQueueRequest sqsRequest = {.region = clientCommand.region, .queueName = queueName, .queueUrl = queueUrl, .owner = clientCommand.user, .attributes = attributes, .tags = tags, .requestId = Core::AwsUtils::CreateRequestId()};

                        Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
                        return SendOkResponse(request, sqsResponse.ToXml());
                        log_info << "Create queue, queueName: " << queueName;
                    }
                }

                case Dto::Common::SqsCommandType::PURGE_QUEUE: {

                    Dto::SQS::PurgeQueueRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        sqsRequest = {.region = clientCommand.region, .queueUrl = queueUrl};
                    }
                    _sqsService.PurgeQueue(sqsRequest);
                    return SendOkResponse(request);
                    log_info << "Purge queue, queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::GET_QUEUE_ATTRIBUTES: {

                    Dto::SQS::GetQueueAttributesRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        std::vector<std::string> attributeNames = GetQueueAttributeNames(clientCommand.payload);
                        sqsRequest = {.region = clientCommand.region, .queueUrl = queueUrl, .attributeNames = attributeNames};
                    }

                    Dto::SQS::GetQueueAttributesResponse sqsResponse = _sqsService.GetQueueAttributes(sqsRequest);
                    return SendOkResponse(request, clientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
                    log_info << "Get queue attributes, queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::SET_QUEUE_ATTRIBUTES: {
                    Dto::SQS::SetQueueAttributesRequest sqsRequest;

                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                        Dto::SQS::SetQueueAttributesResponse sqsResponse = _sqsService.SetQueueAttributes(sqsRequest);
                        return SendOkResponse(request, sqsResponse.ToJson());

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");

                        int count = Core::HttpUtils::CountQueryParametersByPrefix(clientCommand.payload, "Attribute") / 2;
                        log_trace << "Got attribute count, count: " << count;

                        std::map<std::string, std::string> attributes;
                        for (int i = 1; i <= count; i++) {
                            std::string attributeName = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Attribute." + std::to_string(i) + ".Name");
                            std::string attributeValue = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Attribute." + std::to_string(i) + ".Value");
                            attributes[attributeName] = attributeValue;
                        }

                        sqsRequest = {.region = clientCommand.region, .queueUrl = queueUrl, .attributes = attributes};

                        Dto::SQS::SetQueueAttributesResponse sqsResponse = _sqsService.SetQueueAttributes(sqsRequest);
                        return SendOkResponse(request, sqsResponse.ToXml());
                    }
                    log_info << "Set queue attributes, queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::GET_QUEUE_URL: {
                    Dto::SQS::GetQueueUrlRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        std::string queueName = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueName");
                        sqsRequest = {.region = clientCommand.region, .queueName = queueName};
                    }
                    Dto::SQS::GetQueueUrlResponse sqsResponse = _sqsService.GetQueueUrl(sqsRequest);
                    return SendOkResponse(request, clientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
                    log_info << "Get queue url, queueName: " << sqsRequest.queueName;
                }

                case Dto::Common::SqsCommandType::TAG_QUEUE: {
                    Dto::SQS::TagQueueRequest sqsRequest;

                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        std::string tagKey = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Tag.Key");
                        std::string tagValue = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "Tag.Key");

                        std::map<std::string, std::string> tags;
                        tags[tagKey] = tagValue;

                        sqsRequest = {.region = clientCommand.region, .queueUrl = queueUrl, .tags = tags};
                    }
                    _sqsService.TagQueue(sqsRequest);

                    return SendOkResponse(request);
                    log_info << "Tag queue, queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::LIST_QUEUES: {

                    Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(clientCommand.region);

                    if (clientCommand.contentType == "json") {

                        return SendOkResponse(request, sqsResponse.ToJson());
                        log_info << "List queues";

                    } else {

                        return SendOkResponse(request, sqsResponse.ToXml());
                        log_info << "List queues";
                    }
                }

                case Dto::Common::SqsCommandType::DELETE_QUEUE: {

                    Dto::SQS::DeleteQueueRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                        Dto::SQS::DeleteQueueResponse sqsResponse = _sqsService.DeleteQueue(sqsRequest);

                        // Empty response
                        return SendOkResponse(request);
                        log_info << "Delete queue, queueUrl: " << sqsRequest.queueUrl;

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        sqsRequest = {.queueUrl = queueUrl};
                        sqsRequest.region = clientCommand.region;
                        sqsRequest.requestId = Core::AwsUtils::CreateRequestId();

                        Dto::SQS::DeleteQueueResponse sqsResponse = _sqsService.DeleteQueue(sqsRequest);
                        return SendOkResponse(request, sqsResponse.ToXml());
                        log_info << "Delete queue, queueUrl: " << sqsRequest.queueUrl;
                    }
                }

                case Dto::Common::SqsCommandType::SEND_MESSAGE: {

                    Dto::SQS::SendMessageRequest sqsRequest;
                    sqsRequest.region = clientCommand.region;
                    sqsRequest.messageId = Core::AwsUtils::CreateRequestId();
                    sqsRequest.senderId = clientCommand.user;

                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        std::string body = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "MessageBody");
                        std::map<std::string, Dto::SQS::MessageAttribute> attributes = GetMessageAttributes(clientCommand.payload);

                        sqsRequest = {.region = clientCommand.region, .queueUrl = queueUrl, .body = body, .messageAttributes = attributes, .messageId = Core::AwsUtils::CreateRequestId()};
                    }

                    // Call service
                    Dto::SQS::SendMessageResponse sqsResponse = _sqsService.SendMessage(sqsRequest);

                    return SendOkResponse(request, clientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
                    log_info << "Send message, queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::RECEIVE_MESSAGE: {

                    Dto::SQS::ReceiveMessageRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        int maxMessages = Core::HttpUtils::GetIntParameter(clientCommand.payload, "MaxNumberOfMessages", 1, 10, 3);
                        int waitTimeSeconds = Core::HttpUtils::GetIntParameter(clientCommand.payload, "WaitTimeSeconds", 1, 900, 5);
                        int visibility = Core::HttpUtils::GetIntParameter(clientCommand.payload, "VisibilityTimeout", 1, 900, 30);
                        sqsRequest = {.region = clientCommand.region, .queueUrl = queueUrl, .maxMessages = maxMessages, .visibilityTimeout = visibility, .waitTimeSeconds = waitTimeSeconds, .requestId = Core::AwsUtils::CreateRequestId()};
                    }
                    Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);

                    // Add message attribute headers
                    //AddReceiveHeaders(request, sqsResponse);

                    // Send response
                    return SendOkResponse(request, clientCommand.contentType == "json" ? sqsResponse.ToJson() : sqsResponse.ToXml());
                    log_info << "Receive message, count: " << sqsResponse.messageList.size() << " queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::CHANGE_MESSAGE_VISIBILITY: {

                    Dto::SQS::ChangeMessageVisibilityRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        int visibilityTimeout = Core::HttpUtils::GetIntParameter(clientCommand.payload, "VisibilityTimeout", 30, 12 * 3600, 60);
                        std::string receiptHandle = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "ReceiptHandle");

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        sqsRequest = {.region = clientCommand.region, .queueUrl = queueUrl, .receiptHandle = receiptHandle, .visibilityTimeout = visibilityTimeout};
                    }

                    _sqsService.SetVisibilityTimeout(sqsRequest);
                    return SendOkResponse(request);
                    log_info << "Change visibility, queueUrl: " << sqsRequest.queueUrl << " timeout: " << sqsRequest.visibilityTimeout;
                }

                case Dto::Common::SqsCommandType::DELETE_MESSAGE: {

                    Dto::SQS::DeleteMessageRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        std::string queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");
                        std::string receiptHandle = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "ReceiptHandle");
                        sqsRequest = {
                                .region = clientCommand.region,
                                .queueUrl = queueUrl,
                                .receiptHandle = receiptHandle};
                    }

                    _sqsService.DeleteMessage(sqsRequest);
                    return SendOkResponse(request);
                    log_info << "Delete message, queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::DELETE_MESSAGE_BATCH: {

                    Dto::SQS::DeleteMessageBatchRequest sqsRequest;
                    if (clientCommand.contentType == "json") {

                        sqsRequest.FromJson(clientCommand.payload);
                        sqsRequest.region = clientCommand.region;

                    } else {

                        sqsRequest.queueUrl = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "QueueUrl");

                        // Get message count
                        int count = Core::HttpUtils::CountQueryParametersByPrefix(clientCommand.payload, "DeleteMessageBatchRequestEntry") / 2;
                        log_trace << "Got entry count, count: " << count;

                        for (int i = 1; i <= count; i++) {
                            std::string id = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "DeleteMessageBatchRequestEntry." + std::to_string(i) + ".Id");
                            std::string receiptHandle = Core::HttpUtils::GetQueryParameterValueByName(clientCommand.payload, "DeleteMessageBatchRequestEntry." + std::to_string(i) + ".ReceiptHandle");
                            Dto::SQS::DeleteMessageBatchEntry entry = {.id = id, .receiptHandle = receiptHandle};
                            sqsRequest.deleteMessageBatchEntries.emplace_back(entry);
                        }
                    }
                    _sqsService.DeleteMessageBatch(sqsRequest);
                    return SendOkResponse(request);
                    log_info << "Delete message batch, queueUrl: " << sqsRequest.queueUrl;
                }

                case Dto::Common::SqsCommandType::UNKNOWN: {
                    log_error << "Unknown method";
                    return Core::HttpUtils::BadRequest(request, "Unknown method");
                }

                default:
                    log_error << "Unknown method";
                    return Core::HttpUtils::BadRequest(request, "Unknown method");
            }

        } catch (Poco::Exception &e) {
            return Core::HttpUtils::InternalServerError(request, e.message());
        }
    }

    std::vector<Dto::SQS::QueueAttribute> SQSHandler::GetQueueAttributes(const std::string &payload) {

        std::vector<Dto::SQS::QueueAttribute> queueAttributes;

        int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "UserAttribute") / 2;
        log_trace << "Got attribute count, count: " << count;

        for (int i = 1; i <= count; i++) {
            Dto::SQS::QueueAttribute attribute = {
                    .attributeName = Core::HttpUtils::GetQueryParameterValueByName(payload, "UserAttribute." + std::to_string(i) + ".Name"),
                    .attributeValue = Core::HttpUtils::GetQueryParameterValueByName(payload, "UserAttribute." + std::to_string(i) + ".Value")};
            queueAttributes.emplace_back(attribute);
        }
        return queueAttributes;
    }

    std::map<std::string, std::string> SQSHandler::GetQueueTags(const std::string &payload) {

        std::map<std::string, std::string> queueTags;

        int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "Tag") / 2;
        log_trace << "Got tags count, count: " << count;

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

        int count = Core::HttpUtils::CountQueryParametersByPrefix(payload, "AttributeName");
        log_trace << "Got attribute names count: " << count;

        std::vector<std::string> attributeNames;
        for (int i = 1; i <= count; i++) {
            attributeNames.emplace_back(Core::HttpUtils::GetQueryParameterValueByName(payload, "AttributeName." + std::to_string(i)));
        }
        return attributeNames;
    }

    std::map<std::string, Dto::SQS::MessageAttribute> SQSHandler::GetMessageAttributes(const std::string &payload) {

        int attributeCount = Core::HttpUtils::CountQueryParametersByPrefix(payload, "MessageAttribute");
        log_debug << "Got message attribute count: " << attributeCount;

        std::map<std::string, Dto::SQS::MessageAttribute> messageAttributes;
        for (int i = 1; i <= attributeCount / 3; i++) {

            std::string attributeName = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Name");
            std::string attributeType = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Value.DataType");

            std::string attributeValue;
            if (attributeType == "String" || attributeType == "Number") {
                attributeValue = Core::HttpUtils::GetQueryParameterValueByName(payload, "MessageAttribute." + std::to_string(i) + ".Value.StringValue");
            }
            Dto::SQS::MessageAttribute messageAttribute = {.name = attributeName, .stringValue = attributeValue, .type = Dto::SQS::MessageAttributeDataTypeFromString(attributeType)};
            messageAttributes[attributeName] = messageAttribute;
        }
        log_debug << "Extracted message attribute count: " << messageAttributes.size();
        return messageAttributes;
    }

}// namespace AwsMock::Service
