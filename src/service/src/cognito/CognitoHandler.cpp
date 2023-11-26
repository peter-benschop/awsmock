
#include <awsmock/service/CognitoHandler.h>

namespace AwsMock::Service {

  CognitoHandler::CognitoHandler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("CognitoHandler")), _configuration(configuration),
                                                                                                           _metricService(metricService), _cognitoService(configuration) {

    std::string host = _configuration.getString("awsmock.service.cognito.host", "localhost");
    std::string port = _configuration.getString("awsmock.service.cognito.port", "4566");
  }

  void CognitoHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    try {

      // Strange behaviour of the S3CRT client
      std::string uri = request.getURI();

    } catch (Poco::Exception &exc) {
      SendErrorResponse("Cognito", response, exc);
    }
  }

  void CognitoHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      //DumpRequest(request);

      // Strange behaviour of the S3CRT client
      std::string uri = request.getURI();

    } catch (Poco::Exception &exc) {
      SendErrorResponse("Cognito", response, exc);
    }
  }

  void CognitoHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      //DumpRequest(request);
      //DumpBody(request);
      std::string action = GetAction(request);

      if (action == "create-user-pool") {

        std::string payload = GetPayload(request);
        Dto::Cognito::CreateUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;

        log_debug_stream(_logger) << "Got list user pool request, json: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::CreateUserPoolResponse serviceResponse = _cognitoService.CreateUserPool(cognitoRequest);
        SendOkResponse(response, serviceResponse.ToJson());

      } else if (action == "list-user-pools") {

        std::string payload = GetPayload(request);
        Dto::Cognito::ListUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        log_debug_stream(_logger) << "Got list user pool request, json: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::ListUserPoolResponse serviceResponse = _cognitoService.ListUserPools(cognitoRequest);
        std::string tmp = serviceResponse.ToJson();
        SendOkResponse(response, serviceResponse.ToJson());

      }

    } catch (Poco::Exception &exc) {
      SendErrorResponse("Cognito", response, exc);
    }
  }

  void CognitoHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      // Strange behaviour of the S3CRT client
      std::string uri = request.getURI();

    } catch (Core::ServiceException &exc) {
      SendErrorResponse("Cognito", response, exc);
    }
  }

  void CognitoHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "Cognito HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      // Strange behaviour of the S3CRT client
      std::string uri = request.getURI();

    } catch (Poco::Exception &exc) {
      log_warning_stream(_logger) << exc.message() << std::endl;
      SendErrorResponse("Cognito", response, exc);
    } catch (std::exception &exc) {
      log_error_stream(_logger) << exc.what() << std::endl;
    }
  }

  std::string CognitoHandler::GetAction(const Poco::Net::HTTPServerRequest &request) {

    std::string userAgent = request["User-Agent"];
    Poco::RegularExpression::MatchVec posVec;
    Poco::RegularExpression pattern(R"(^([A-Za-z0-9_\-\/\.]+)\ ([A-Za-z0-9_\-\/\.]+)\ ([A-Za-z0-9_\-\/\.]+)\ ([A-Za-z0-9_\-\/\.]+)+\ ([A-Za-z0-9_\-\/\.]+)\ command\/cognito\-idp\.(.*)$)");
    if (!pattern.match(userAgent, 0, posVec)) {
      log_error_stream(_logger) << "Could not extract action, userAgent: " << userAgent << std::endl;
      throw Core::ResourceNotFoundException("Could not extract action");
    }

    std::string action = userAgent.substr(posVec[6].offset, posVec[6].length);

    log_debug_stream(_logger) << "Found action: " << action << std::endl;

    return action;
  }

  void CognitoHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "Cognito OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
