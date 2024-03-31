
#include <awsmock/service/SNSHandler.h>

namespace AwsMock::Service {

  SNSHandler::SNSHandler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : SNSCmdHandler(configuration, metricService, condition), _logger(Poco::Logger::get("SNSHandler")),
                                                                                                                               _configuration(configuration), _metricService(metricService), _snsService(configuration, condition) {
  }

  void SNSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "SNS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << " length: " << response.getContentLength() << std::endl;


    Dto::Common::SNSClientCommand clientCommand;
    clientCommand.FromRequest(Dto::Common::HttpMethod::GET, request, region, user);

    SNSCmdHandler::handlePost(request, response, clientCommand);

    /*try {

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
    }*/
  }
}
