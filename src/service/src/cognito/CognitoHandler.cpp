
#include "awsmock/service/cognito/CognitoHandler.h"

namespace AwsMock::Service {

  CognitoHandler::CognitoHandler(Core::Configuration &configuration) : CognitoCliHandler(configuration), CognitoJava2Handler(configuration), _configuration(configuration), _cognitoService(configuration) {}

  void CognitoHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito GET request, URI: " + request.getURI() << " region: " << region << " user: " + user;
  }

  void CognitoHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;
  }

  void CognitoHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

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
      log_error << "SQS module exception: " << exc.message();
      SendXmlErrorResponse("SQS", response, exc);
    }
  }

  void CognitoHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user;
  }

  void CognitoHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user;
  }

  void CognitoHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug << "Cognito OPTIONS request";

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
