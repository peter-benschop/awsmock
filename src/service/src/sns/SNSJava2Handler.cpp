
#include <awsmock/service/SNSJava2Handler.h>

namespace AwsMock::Service {

  SNSJava2Handler::SNSJava2Handler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition)
    : AbstractHandler(), _logger(Poco::Logger::get("SNSJava2Handler")), _configuration(configuration), _metricService(metricService), _snsService(configuration, condition) {
  }

  void SNSJava2Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
  }

  void SNSJava2Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
  }

  void SNSJava2Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "SNS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << " length: " << response.getContentLength() << std::endl;

    try {

      std::string payload = GetPayload(request);
      std::string action, version;
      GetActionVersion(payload, action, version);
      log_debug_stream(_logger) << "Action: " << action << std::endl;

      if (action == "CreateTopic") {

        std::string name = GetStringParameter(payload, "Name");
        log_debug_stream(_logger) << "Topic name: " << name << std::endl;

        Dto::SNS::CreateTopicResponse snsResponse = _snsService.CreateTopic({.region=region, .topicName = name, .owner=user});
        SendOkResponse(response, snsResponse.ToXml());

      } else if (action == "ListTopics") {

        Dto::SNS::ListTopicsResponse snsResponse = _snsService.ListTopics(region);
        SendOkResponse(response, snsResponse.ToXml());

      } else if (action == "Publish") {

        std::string topicArn = GetStringParameter(payload, "TopicArn");
        std::string targetArn = GetStringParameter(payload, "TargetArn");
        std::string message = GetStringParameter(payload, "Message");
        log_debug_stream(_logger) << "Topic ARN: " << topicArn << " targetArn:" << targetArn << " message: " << message << std::endl;

        Dto::SNS::PublishResponse snsResponse = _snsService.Publish({.region=region, .topicArn=topicArn, .targetArn=targetArn, .message=message});
        SendOkResponse(response, snsResponse.ToXml());

      } else if (action == "Subscribe") {

        std::string topicArn = GetStringParameter(payload, "TopicArn");
        std::string protocol = GetStringParameter(payload, "Protocol");
        std::string endpoint = GetStringParameter(payload, "Endpoint");
        log_debug_stream(_logger) << "Topic ARN: " << topicArn << " protocol:" << protocol << " endpoint: " << endpoint << std::endl;

        Dto::SNS::SubscribeResponse snsResponse = _snsService.Subscribe({.region=region, .topicArn=topicArn, .protocol=protocol, .endpoint=endpoint, .owner=user});
        SendOkResponse(response, snsResponse.ToXml());

      } else if (action == "Unsubscribe") {

        std::string subscriptionArn = GetStringParameter(payload, "SubscriptionArn");
        log_debug_stream(_logger) << "Subscription ARN: " << subscriptionArn << std::endl;

        Dto::SNS::UnsubscribeResponse snsResponse = _snsService.Unsubscribe({.region=region, .subscriptionArn=subscriptionArn});
        SendOkResponse(response, snsResponse.ToXml());

      } else if (action == "GetTopicAttributes") {

        std::string topicArn = GetStringParameter(payload, "TopicArn");
        log_debug_stream(_logger) << "Topic ARN: " << topicArn << std::endl;

        Dto::SNS::GetTopicAttributesResponse snsResponse = _snsService.GetTopicAttributes({.region=region, .topicArn=topicArn});
        SendOkResponse(response, snsResponse.ToXml());

      } else if (action == "ListSubscriptionsByTopic") {

        std::string topicArn = GetStringParameter(payload, "TopicArn");
        log_debug_stream(_logger) << "Topic ARN: " << topicArn << std::endl;

        Dto::SNS::ListSubscriptionsByTopicResponse snsResponse = _snsService.ListSubscriptionsByTopic({.region=region, .topicArn=topicArn});
        SendOkResponse(response, snsResponse.ToXml());

      } else if (action == "DeleteTopic") {

        std::string topicArn = GetStringParameter(payload, "TopicArn");
        log_debug_stream(_logger) << "Topic ARN: " << topicArn << std::endl;

        Dto::SNS::DeleteTopicResponse snsResponse = _snsService.DeleteTopic(region, topicArn);
        SendOkResponse(response, snsResponse.ToXml());
      }

    } catch (Core::ServiceException &exc) {
      log_error_stream(_logger) << "Service exception: " << exc.message() << std::endl;
      SendXmlErrorResponse("SNS", response, exc);
    }
  }

  void SNSJava2Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    log_debug_stream(_logger) << "SNS DELETE request, URI: " << response.getContentLength() << std::endl;
    DumpRequest(request);
  }

  void SNSJava2Handler::handleHead([[maybe_unused]]Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void SNSJava2Handler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "SNS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS, HEAD");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
