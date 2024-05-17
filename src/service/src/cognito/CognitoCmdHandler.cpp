
#include <awsmock/service/cognito/CognitoCmdHandler.h>

namespace AwsMock::Service {

    void CognitoCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::CognitoClientCommand &clientCommand) {
        log_debug << "Cognito POST request, URI: " << request.getURI() << " region: " << clientCommand.region << " user: " << clientCommand.user;

        try {

            //DumpRequest(request);
            std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());
            std::string payload = Core::HttpUtils::GetBodyAsString(request);
            std::string action = GetActionFromHeader(request);

            if (action == "CreateUserPool") {

                Dto::Cognito::CreateUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(payload);
                cognitoRequest.region = clientCommand.region;

                log_debug << "Got list user pool request, json: " << cognitoRequest.ToString();

                Dto::Cognito::CreateUserPoolResponse serviceResponse = _cognitoService.CreateUserPool(cognitoRequest);
                SendOkResponse(response, serviceResponse.ToJson());

            } else if (action == "ListUserPools") {

                Dto::Cognito::ListUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(payload);
                cognitoRequest.region = clientCommand.region;
                log_debug << "Got list user pool request, json: " << cognitoRequest.ToString();

                Dto::Cognito::ListUserPoolResponse serviceResponse = _cognitoService.ListUserPools(cognitoRequest);
                SendOkResponse(response, serviceResponse.ToJson());

            } else if (action == "DeleteUserPool") {

                Dto::Cognito::DeleteUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(payload);
                cognitoRequest.region = clientCommand.region;
                log_debug << "Got delete user pool request, json: " << cognitoRequest.ToString();

                _cognitoService.DeleteUserPool(cognitoRequest);
                SendOkResponse(response);

            } else if (action == "AdminCreateUser") {

                Dto::Cognito::AdminCreateUserRequest cognitoRequest{};
                cognitoRequest.FromJson(payload);
                cognitoRequest.region = clientCommand.region;
                log_debug << "Got admin create user request, json: " << cognitoRequest.ToString();

                Dto::Cognito::AdminCreateUserResponse cognitoResponse = _cognitoService.AdminCreateUser(cognitoRequest);
                SendOkResponse(response, cognitoResponse.ToJson());

            } else if (action == "ListUsers") {

                Dto::Cognito::ListUsersRequest cognitoRequest{};
                cognitoRequest.FromJson(payload);
                cognitoRequest.region = clientCommand.region;
                log_debug << "Got list users request: " << cognitoRequest.ToString();

                Dto::Cognito::ListUsersResponse cognitoResponse = _cognitoService.ListUsers(cognitoRequest);
                SendOkResponse(response, cognitoResponse.ToJson());

            } else if (action == "AdminDeleteUser") {

                Dto::Cognito::AdminDeleteUserRequest cognitoRequest{};
                cognitoRequest.FromJson(payload);
                cognitoRequest.region = clientCommand.region;
                log_debug << "Got admin delete user request, json: " << cognitoRequest.ToString();

                _cognitoService.AdminDeleteUser(cognitoRequest);
                SendOkResponse(response);
            }

        } catch (Poco::Exception &exc) {
            SendXmlErrorResponse("Cognito", response, exc);
        }
    }

    std::string CognitoCmdHandler::GetActionFromHeader(Poco::Net::HTTPServerRequest &request) {

        if (!request.has("X-Amz-Target")) {
            log_error << "Could not extract action";
            throw Core::ServiceException("Could not extract action");
        }

        std::string headerValue = request["X-Amz-Target"];
        return Core::StringUtils::Split(headerValue, '.')[1];
    }

}// namespace AwsMock::Service
