
#include <awsmock/service/CognitoJava2Handler.h>

namespace AwsMock::Service {

  CognitoJava2Handler::CognitoJava2Handler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("CognitoJava2Handler")), _configuration(configuration), _metricService(metricService),
                                                                                                                     _cognitoService(configuration) {
  }

  void CognitoJava2Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;
  }

  void CognitoJava2Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
  }

  void CognitoJava2Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      //DumpRequest(request);
      std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
      std::string payload = GetBodyAsString(request);
      std::string action = GetActionFromHeader(request);

      if (action == "CreateUserPool") {

        Dto::Cognito::CreateUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;

        log_debug_stream(_logger) << "Got list user pool request, json: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::CreateUserPoolResponse serviceResponse = _cognitoService.CreateUserPool(cognitoRequest);
        SendOkResponse(response, serviceResponse.ToJson());

      } else if (action == "ListUserPools") {

        Dto::Cognito::ListUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug_stream(_logger) << "Got list user pool request, json: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::ListUserPoolResponse serviceResponse = _cognitoService.ListUserPools(cognitoRequest);
        SendOkResponse(response, serviceResponse.ToJson());

      } else if (action == "DeleteUserPool") {

        Dto::Cognito::DeleteUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug_stream(_logger) << "Got delete user pool request, json: " << cognitoRequest.ToString() << std::endl;

        _cognitoService.DeleteUserPool(cognitoRequest);
        SendOkResponse(response);

      } else if (action == "AdminCreateUser") {

        Dto::Cognito::AdminCreateUserRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug_stream(_logger) << "Got admin create user request, json: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::AdminCreateUserResponse cognitoResponse = _cognitoService.AdminCreateUser(cognitoRequest);
        SendOkResponse(response, cognitoResponse.ToJson());

      } else if (action == "ListUsers") {

        Dto::Cognito::ListUsersRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug_stream(_logger) << "Got list users request: " << cognitoRequest.ToString() << std::endl;

        Dto::Cognito::ListUsersResponse cognitoResponse = _cognitoService.ListUsers(cognitoRequest);
        SendOkResponse(response, cognitoResponse.ToJson());

      } else if (action == "AdminDeleteUser") {

        Dto::Cognito::AdminDeleteUserRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug_stream(_logger) << "Got admin delete user request, json: " << cognitoRequest.ToString() << std::endl;

        _cognitoService.AdminDeleteUser(cognitoRequest);
        SendOkResponse(response);

      }

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("Cognito", response, exc);
    }
  }

  void CognitoJava2Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;
  }

  void CognitoJava2Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "Cognito HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;
  }

  void CognitoJava2Handler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "Cognito OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::string CognitoJava2Handler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request) {

    if (!request.has("X-Amz-Target")) {
      throw Core::ServiceException("Could not extract action");
    }

    std::string headerValue = request["X-Amz-Target"];
    return Core::StringUtils::Split(headerValue, '.')[1];
  }
}
