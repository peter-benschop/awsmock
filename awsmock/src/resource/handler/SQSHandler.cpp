
#include "awsmock/resource/handler/SQSHandler.h"

namespace AwsMock {

    SQSHandler::SQSHandler(Core::Configuration &configuration, Core::MetricService &metricService)
        : AbstractResource(), _logger(Poco::Logger::get("SQSHandler")), _configuration(configuration), _metricService(metricService), _sqsService(configuration) {
        Core::Logger::SetDefaultConsoleLogger("SQSHandler");
    }

    void SQSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_GET_TIMER);
        poco_debug(_logger, "SQS GET request, URI: " + request.getURI() + " region: " + region + " user: " + user);
        DumpRequest(request);
        DumpResponse(response);
    }

    void SQSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        poco_debug(_logger, "SQS PUT request, URI: " + request.getURI() + " region: " + region + " user: " + user);
        DumpRequest(request);
        DumpResponse(response);
    }

    void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        poco_debug(_logger, "SQS POST request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {
            //DumpBody(request);

            std::string endpoint = GetEndpoint(request);
            std::string payload = GetPayload(request);
            std::string action, version;

            GetActionVersion(payload, action, version);

            if (action == "CreateQueue") {

                std::string name = GetStringParameter(payload, "QueueName");

                Dto::SQS::CreateQueueRequest sqsRequest = {.region=region, .name = name, .queueUrl="http://" + endpoint + "/" + DEFAULT_USERID + "/" + name, .owner=user};
                Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "ListQueues") {

                Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(region);
                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "DeleteQueue") {

                std::string url = GetStringParameter(payload, "QueueUrl");

                Dto::SQS::DeleteQueueRequest sqsRequest = {.queueUrl=url};
                Dto::SQS::DeleteQueueResponse sqsResponse = _sqsService.DeleteQueue(sqsRequest);
                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "SendMessage") {

                std::string url = GetStringParameter(payload, "QueueUrl");
                std::string body = GetStringParameter(payload, "MessageBody");

                Dto::SQS::CreateMessageRequest sqsRequest = {.url=url, .body=body};
                Dto::SQS::CreateMessageResponse sqsResponse = _sqsService.CreateMessage(sqsRequest);
                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "ReceiveMessage") {

                std::string queueUrl = GetStringParameter(payload, "QueueUrl");
                int maxMessages = GetIntParameter(payload, "MaxNumberOfMessages", 1, 10);
                int waitTimeSeconds = GetIntParameter(payload, "WaitTimeSeconds", 1, 900);
                int visibility = GetIntParameter(payload, "VisibilityTimeout", 1, 900);

                Dto::SQS::ReceiveMessageRequest sqsRequest = {.region=region, .queueUrl=queueUrl, .maxMessages=maxMessages, .visibility=visibility,
                    .waitTimeSeconds=waitTimeSeconds};
                Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);

                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "PurgeQueue") {

                std::string queueUrl = GetStringParameter(payload, "QueueUrl");

                Dto::SQS::PurgeQueueRequest sqsRequest = {.queueUrl=queueUrl, .region=region};
                Dto::SQS::PurgeQueueResponse sqsResponse = _sqsService.PurgeQueue(sqsRequest);

                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "SetQueueAttributes") {

                std::string queueUrl = GetStringParameter(payload, "QueueUrl");

                int count = GetAttributeCount(payload, "MessageAttribute");
                poco_trace(_logger, "Got attribute count, count: " + std::to_string(count));

                AttributeList attributes;
                for(int i = 1; i <= count; i++) {
                    std::string attributeName = GetStringParameter(payload, "MessageAttribute." + std::to_string(i) + ".Name");
                    std::string attributeValue = GetStringParameter(payload, "MessageAttribute." + std::to_string(i) + ".Value");
                    attributes.emplace_back(attributeName, attributeValue);
                }

                Dto::SQS::PutQueueAttributesRequest sqsRequest = {.queueUrl=queueUrl, .attributes=attributes};
                Dto::SQS::PutQueueAttributesResponse sqsResponse = _sqsService.PutQueueAttributes(sqsRequest);

                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "DeleteMessage") {

                std::string queueUrl = GetStringParameter(payload, "QueueUrl");
                std::string receiptHandle = GetStringParameter(payload, "ReceiptHandle");

                Dto::SQS::DeleteMessageRequest sqsRequest = {.queueUrl=queueUrl, .receiptHandle=receiptHandle};
                Dto::SQS::DeleteMessageResponse sqsResponse = _sqsService.DeleteMessage(sqsRequest);

                SendOkResponse(response, sqsResponse.ToXml());
            }

        } catch (Core::ServiceException &exc) {
            poco_error(_logger, "Service exception: " + exc.message());
            SendErrorResponse("SQS", response, exc);
        }
    }

    void SQSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
        poco_debug(_logger, "SQS DELETE request, URI: " + request.getURI() + " region: " + region + " user: " + user);
        DumpRequest(request);
        DumpResponse(response);
    }

    void SQSHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        poco_debug(_logger, "SQS OPTIONS request, address: " + request.clientAddress().toString());

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void SQSHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        poco_debug(_logger, "SQS HEAD request, address: " + request.clientAddress().toString());

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void SQSHandler::GetActionVersion(const std::string &body, std::string &action, std::string &version) {
        std::vector<std::string> bodyParts = Core::StringUtils::Split(body, '&');
        for (auto &it : bodyParts) {
            std::vector<std::string> parts = Core::StringUtils::Split(it, '=');
            if (parts.size() < 2) {
                throw Core::ServiceException("Invalid request body", 400);
            }
            if (parts[0] == "Action") {
                action = parts[1];
            }
            if (parts[0] == "Version") {
                version = parts[1];
            }
        }
    }

    std::string SQSHandler::GetStringParameter(const std::string &body, const std::string &name) {
        std::string value;
        std::vector<std::string> bodyParts = Core::StringUtils::Split(body, '&');
        for (auto &it : bodyParts) {
            std::vector<std::string> parts = Core::StringUtils::Split(it, '=');
            if (parts[0] == name) {
                value = Core::StringUtils::UrlDecode(parts[1]);
            }
        }
        return value;
    }

    int SQSHandler::GetIntParameter(const std::string &body, const std::string &parameter, int min, int max) {
        int value = max;
        std::string parameterValue = GetStringParameter(body, parameter);
        if (!parameterValue.empty()) {
            value = std::stoi(parameterValue);
            value = value > min && value < max ? value : max;
        }
        return value;
    }

    int SQSHandler::GetAttributeCount(const std::string &body, const std::string &parameter) {
        int count = 0;
        std::vector<std::string> bodyParts = Core::StringUtils::Split(body, '&');
        for (auto &it : bodyParts) {
            if(it.starts_with(parameter)) {
                count++;
            }
        }
        return count;
    }

    std::string SQSHandler::GetEndpoint(Poco::Net::HTTPServerRequest &request) {
        return request.get("Host");
    }
}
