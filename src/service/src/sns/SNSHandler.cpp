
#include <awsmock/service/SNSHandler.h>

namespace AwsMock::Service {

  SNSHandler::SNSHandler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : SNSCliHandler(configuration, metricService, condition), SNSJava2Handler(configuration, metricService, condition),
                                                                                                                               SNSCppHandler(configuration, metricService, condition), _logger(Poco::Logger::get("SNSHandler")),
                                                                                                                               _configuration(configuration), _metricService(metricService), _snsService(configuration, condition) {
  }

  void SNSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
  }

  void SNSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    DumpRequest(request);
  }

  void SNSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "SNS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << " length: " << response.getContentLength() << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "sqs");

      switch (userAgent.type) {
      case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:
      case Dto::Common::UserAgentType::AWS_CLI: return SNSCliHandler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_JAVA1: break;
      case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return SNSJava2Handler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_CPP: return SNSCppHandler::handlePost(request, response, region, user);

      }

    } catch (Core::ServiceException &exc) {
      _logger.error() << "SQS module exception: " << exc.message() << std::endl;
      SendXmlErrorResponse("SQS", response, exc);
    }
  }

  void SNSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
    log_debug_stream(_logger) << "SNS DELETE request, URI: " << response.getContentLength() << std::endl;
    DumpRequest(request);
  }

  void SNSHandler::handleHead([[maybe_unused]]Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SNS HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void SNSHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "SNS OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
