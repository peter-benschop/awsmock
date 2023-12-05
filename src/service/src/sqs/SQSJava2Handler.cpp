
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
    std::string action = GetActionFromHeader(request);

    try {
      if (action == "CreateQueue") {

        Dto::SQS::CreateQueueRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.queueUrl = Core::AwsUtils::CreateSqsQueueUrl(_configuration, sqsRequest.name);
        sqsRequest.region = region;
        sqsRequest.owner = user;

        Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
        SendOkResponse(response, sqsResponse.ToJson());

      } else if (action == "ListQueues") {

        Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(region);
        SendOkResponse(response, sqsResponse.ToJson());

      } else if (action == "DeleteQueue") {

        Dto::SQS::DeleteQueueRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        _sqsService.DeleteQueue(sqsRequest);
        SendOkResponse(response);

      } else if (action == "SendMessage") {

        Dto::SQS::SendMessageRequest sqsRequest;

        sqsRequest.FromJson(payload);
        sqsRequest.region = region;
        sqsRequest.messageId = requestId;

        Dto::SQS::SendMessageResponse sqsResponse = _sqsService.SendMessage(sqsRequest);
        SendOkResponse(response, sqsResponse.ToJson());

      } else if (action == "GetQueueUrl") {

        Dto::SQS::GetQueueUrlRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        Dto::SQS::GetQueueUrlResponse sqsResponse = _sqsService.GetQueueUrl(sqsRequest);
        SendOkResponse(response, sqsResponse.ToJson());

      } else if (action == "ReceiveMessage") {

        Dto::SQS::ReceiveMessageRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        Dto::SQS::ReceiveMessageResponse sqsResponse = _sqsService.ReceiveMessages(sqsRequest);

        // Set the message attributes
        SendOkResponse(response, sqsResponse.ToJson());

      } else if (action == "PurgeQueue") {

        Dto::SQS::PurgeQueueRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        _sqsService.PurgeQueue(sqsRequest);
        SendOkResponse(response);

      } else if (action == "GetQueueAttributes") {

        Dto::SQS::GetQueueAttributesRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        Dto::SQS::GetQueueAttributesResponse sqsResponse = _sqsService.GetQueueAttributes(sqsRequest);
        SendOkResponse(response, sqsResponse.ToJson());

      } else if (action == "SetQueueAttributes") {

        Dto::SQS::SetQueueAttributesRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        _sqsService.SetQueueAttributes(sqsRequest);

        SendOkResponse(response);

      } else if (action == "ChangeMessageVisibility") {

        Dto::SQS::ChangeMessageVisibilityRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        _sqsService.SetVisibilityTimeout(sqsRequest);
        SendOkResponse(response);

      } else if (action == "DeleteMessage") {

        Dto::SQS::DeleteMessageRequest sqsRequest;
        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

        _sqsService.DeleteMessage(sqsRequest);

        SendOkResponse(response);

      } else if (action == "DeleteMessageBatch") {

        Dto::SQS::DeleteMessageBatchRequest sqsRequest;
//        sqsRequest.FromJson(payload);
        sqsRequest.region = region;

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

  std::string SQSJava2Handler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request) {

    if (!request.has("X-Amz-Target")) {
      throw Core::ServiceException("Could not extract action");
    }

    std::string headerValue = request["X-Amz-Target"];
    return Core::StringUtils::Split(headerValue, '.')[1];
  }
}
