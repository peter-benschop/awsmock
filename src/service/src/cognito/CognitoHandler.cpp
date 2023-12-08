
#include <awsmock/service/CognitoHandler.h>

namespace AwsMock::Service {

  CognitoHandler::CognitoHandler(Core::Configuration &configuration, Core::MetricService &metricService) : CognitoCliHandler(configuration, metricService), CognitoJava2Handler(configuration, metricService), _logger(Poco::Logger::get("CognitoHandler")),
                                                                                                           _configuration(configuration), _metricService(metricService), _cognitoService(configuration) {}

  void CognitoHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;
  }

  void CognitoHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
  }

  void CognitoHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "cognito");

      switch (userAgent.type) {
      case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:
      case Dto::Common::UserAgentType::AWS_CLI: return CognitoCliHandler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_JAVA1: break;
      case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return CognitoJava2Handler::handlePost(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_CPP: return CognitoJava2Handler::handlePost(request, response, region, user);

      }

    } catch (Core::ServiceException &exc) {
      _logger.error() << "SQS module exception: " << exc.message() << std::endl;
      SendXmlErrorResponse("SQS", response, exc);
    }
  }

  void CognitoHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;
  }

  void CognitoHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
  }

  void CognitoHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "Cognito OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
