
#include "awsmock/service/cognito/CognitoJava2Handler.h"

namespace AwsMock::Service {

  CognitoJava2Handler::CognitoJava2Handler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _configuration(configuration), _metricService(metricService), _cognitoService(configuration) {
  }

  void CognitoJava2Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito GET request, URI: " + request.getURI() << " region: " << region << " user: " + user;
  }

  void CognitoJava2Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;
  }

  void CognitoJava2Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

    try {

      //DumpRequest(request);
      std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
      std::string payload = Core::HttpUtils::GetBodyAsString(request);
      std::string action = GetActionFromHeader(request);

      if (action == "CreateUserPool") {

        Dto::Cognito::CreateUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;

        log_debug << "Got list user pool request, json: " << cognitoRequest.ToString();

        Dto::Cognito::CreateUserPoolResponse serviceResponse = _cognitoService.CreateUserPool(cognitoRequest);
        SendOkResponse(response, serviceResponse.ToJson());

      } else if (action == "ListUserPools") {

        Dto::Cognito::ListUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug << "Got list user pool request, json: " << cognitoRequest.ToString();

        Dto::Cognito::ListUserPoolResponse serviceResponse = _cognitoService.ListUserPools(cognitoRequest);
        SendOkResponse(response, serviceResponse.ToJson());

      } else if (action == "DeleteUserPool") {

        Dto::Cognito::DeleteUserPoolRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug << "Got delete user pool request, json: " << cognitoRequest.ToString();

        _cognitoService.DeleteUserPool(cognitoRequest);
        SendOkResponse(response);

      } else if (action == "AdminCreateUser") {

        Dto::Cognito::AdminCreateUserRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug << "Got admin create user request, json: " << cognitoRequest.ToString();

        Dto::Cognito::AdminCreateUserResponse cognitoResponse = _cognitoService.AdminCreateUser(cognitoRequest);
        SendOkResponse(response, cognitoResponse.ToJson());

      } else if (action == "ListUsers") {

        Dto::Cognito::ListUsersRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug << "Got list users request: " << cognitoRequest.ToString();

        Dto::Cognito::ListUsersResponse cognitoResponse = _cognitoService.ListUsers(cognitoRequest);
        SendOkResponse(response, cognitoResponse.ToJson());

      } else if (action == "AdminDeleteUser") {

        Dto::Cognito::AdminDeleteUserRequest cognitoRequest{};
        cognitoRequest.FromJson(payload);
        cognitoRequest.region = region;
        log_debug << "Got admin delete user request, json: " << cognitoRequest.ToString();

        _cognitoService.AdminDeleteUser(cognitoRequest);
        SendOkResponse(response);

      }

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("Cognito", response, exc);
    }
  }

  void CognitoJava2Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user;
  }

  void CognitoJava2Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug << "Cognito HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user;
  }

  void CognitoJava2Handler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug << "Cognito OPTIONS request";

    response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  std::string CognitoJava2Handler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request) {

    if (!request.has("X-Amz-Target")) {
      log_error << "Could not extract action";
      throw Core::ServiceException("Could not extract action");
    }

    std::string headerValue = request["X-Amz-Target"];
    return Core::StringUtils::Split(headerValue, '.')[1];
  }
}
