
#include <awsmock/service/CognitoHandler.h>

namespace AwsMock::Service {

  CognitoHandler::CognitoHandler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("CognitoHandler")), _configuration(configuration), _metricService(metricService),
                                                                                                           _cognitoService(configuration) {
  }

  void CognitoHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;
  }

  void CognitoHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
  }

  void CognitoHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      //DumpRequest(request);
      //DumpBody(request);

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "cognito-idp");

      if (userAgent.clientCommand == "create-user-pool") {

        std::string payload = GetPayload(request);
        Dto::Cognito::CreateUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;

        log_debug_stream(_logger) << "Got list user pool request, json: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::CreateUserPoolResponse serviceResponse = _cognitoService.CreateUserPool(cognitoRequest);
        SendOkResponse(response, serviceResponse.ToJson());

      } else if (userAgent.clientCommand == "list-user-pools") {

        std::string payload = GetPayload(request);
        Dto::Cognito::ListUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug_stream(_logger) << "Got list user pool request, json: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::ListUserPoolResponse serviceResponse = _cognitoService.ListUserPools(cognitoRequest);
        SendOkResponse(response, serviceResponse.ToJson());

      } else if (userAgent.clientCommand == "delete-user-pool") {

        std::string payload = GetPayload(request);
        Dto::Cognito::DeleteUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        log_debug_stream(_logger) << "Got delete user pool request, json: " << cognitoRequest.ToString() << std::endl;

        _cognitoService.DeleteUserPool(cognitoRequest);
        SendOkResponse(response);

      }

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("Cognito", response, exc);
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
