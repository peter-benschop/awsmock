
#include <awsmock/service/cognito/CognitoHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> CognitoHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_debug << "Cognito POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::CognitoClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {

            std::string action = GetActionFromHeader(request);

            if (action == "CreateUserPool") {

                Dto::Cognito::CreateUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got create user pool request, json: " << cognitoRequest.ToString();

                Dto::Cognito::CreateUserPoolResponse serviceResponse = _cognitoService.CreateUserPool(cognitoRequest);
                log_info << "User pool created, userPoolId: " << serviceResponse.userPoolId;

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "CreateUserPoolDomain") {

                Dto::Cognito::CreateUserPoolDomainRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got create user pool domain request, json: " << cognitoRequest.ToString();

                Dto::Cognito::CreateUserPoolDomainResponse serviceResponse = _cognitoService.CreateUserPoolDomain(cognitoRequest);
                log_info << "User pool domain created, domain: " << serviceResponse.cloudFrontDomain;

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "UpdateUserPoolDomain") {

                Dto::Cognito::UpdateUserPoolDomainRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got update user pool domain request, json: " << cognitoRequest.ToString();

                Dto::Cognito::UpdateUserPoolDomainResponse cognitoResponse = _cognitoService.UpdateUserPoolDomain(cognitoRequest);
                log_info << "User pool domain updated, domain: " << cognitoResponse.cloudFrontDomain;

                return SendOkResponse(request, cognitoResponse.ToJson());

            } else if (action == "CreateUserPoolClient") {

                Dto::Cognito::CreateUserPoolClientRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got create user pool client request, json: " << cognitoRequest.ToString();

                Dto::Cognito::CreateUserPoolClientResponse serviceResponse = _cognitoService.CreateUserPoolClient(cognitoRequest);
                log_info << "User pool client created, userPoolId: " << serviceResponse.userGroupClient.userPoolId << " clientId: " << serviceResponse.userGroupClient.clientId;

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "ListUserPools") {

                Dto::Cognito::ListUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got list user pool request, json: " << cognitoRequest.ToString();

                Dto::Cognito::ListUserPoolResponse serviceResponse = _cognitoService.ListUserPools(cognitoRequest);
                log_info << "User pools listed, count: " << serviceResponse.userPools.size();

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "UpdateUserPool") {

                Dto::Cognito::UpdateUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got update user pool request, json: " << cognitoRequest.ToString();

                _cognitoService.UpdateUserPool(cognitoRequest);
                log_info << "User pool updated, userPoolId: " << cognitoRequest.userPoolId;

                return SendOkResponse(request);

            } else if (action == "ListUserPoolClients") {

                Dto::Cognito::ListUserPoolClientsRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got list user pool clients request, json: " << cognitoRequest.ToString();

                Dto::Cognito::ListUserPoolClientsResponse serviceResponse = _cognitoService.ListUserPoolClients(cognitoRequest);
                log_info << "User pool clients listed, userPoolId: " << serviceResponse.userPoolsClients.size();

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "DescribeUserPoolClient") {

                Dto::Cognito::DescribeUserPoolClientRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got describe user pool client request, json: " << cognitoRequest.ToString();

                Dto::Cognito::DescribeUserPoolClientResponse cognitoResponse = _cognitoService.DescribeUserPoolClient(cognitoRequest);
                log_info << "Describe user pool client, userPoolId: " << cognitoResponse.userPoolClient.userPoolId << " clientId: " << cognitoResponse.userPoolClient.clientId;

                return SendOkResponse(request, cognitoResponse.ToJson());

            } else if (action == "UpdateUserPoolClient") {

                Dto::Cognito::UpdateUserPoolClientRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got update user pool client request, json: " << cognitoRequest.ToString();

                _cognitoService.UpdateUserPoolClient(cognitoRequest);
                log_info << "User pool client updated, userPoolId: " << cognitoRequest.userPoolId << " clientId: " << cognitoRequest.clientId;

                return SendOkResponse(request);

            } else if (action == "DeleteUserPoolClient") {

                Dto::Cognito::DeleteUserPoolClientRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got delete user pool client request, json: " << cognitoRequest.ToString();

                _cognitoService.DeleteUserPoolClient(cognitoRequest);
                log_info << "User pool client deleted, userPoolId: " << cognitoRequest.userPoolId << " clientId: " << cognitoRequest.clientId;

                return SendOkResponse(request);

            } else if (action == "DescribeUserPool") {

                Dto::Cognito::DescribeUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Describe user pool request, json: " << cognitoRequest.ToString();

                Dto::Cognito::DescribeUserPoolResponse serviceResponse = _cognitoService.DescribeUserPool(cognitoRequest);
                log_info << "Describe user pool, userPoolId: " << cognitoRequest.userPoolId;

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "DeleteUserPool") {

                Dto::Cognito::DeleteUserPoolRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got delete user pool request, json: " << cognitoRequest.ToString();

                _cognitoService.DeleteUserPool(cognitoRequest);
                log_info << "User pool deleted, userPoolId: " << cognitoRequest.userPoolId;

                return SendOkResponse(request);

            } else if (action == "AdminCreateUser") {

                Dto::Cognito::AdminCreateUserRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got admin create user request, json: " << cognitoRequest.ToString();

                Dto::Cognito::AdminCreateUserResponse cognitoResponse = _cognitoService.AdminCreateUser(cognitoRequest);
                log_info << "User created, userPoolId: " << cognitoRequest.userPoolId;

                return SendOkResponse(request, cognitoResponse.ToJson());

            } else if (action == "ListUsers") {

                Dto::Cognito::ListUsersRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got list users request: " << cognitoRequest.ToString();

                Dto::Cognito::ListUsersResponse cognitoResponse = _cognitoService.ListUsers(cognitoRequest);
                log_info << "Users listed, userPoolId: " << cognitoRequest.userPoolId << " count: " << cognitoResponse.users.size();

                return SendOkResponse(request, cognitoResponse.ToJson());

            } else if (action == "AdminDeleteUser") {

                Dto::Cognito::AdminDeleteUserRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got admin delete user request, json: " << cognitoRequest.ToString();

                _cognitoService.AdminDeleteUser(cognitoRequest);
                log_info << "User deleted, userPoolId: " << cognitoRequest.userPoolId << " user: " << cognitoRequest.user;

                return SendOkResponse(request);

            } else if (action == "CreateGroup") {

                Dto::Cognito::CreateGroupRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got create group request, json: " << cognitoRequest.ToString();

                Dto::Cognito::CreateGroupResponse serviceResponse = _cognitoService.CreateGroup(cognitoRequest);
                log_info << "Group created, group: " << serviceResponse.group;

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "ListGroups") {

                Dto::Cognito::ListGroupsRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got list groups request, json: " << cognitoRequest.ToString();

                Dto::Cognito::ListGroupsResponse serviceResponse = _cognitoService.ListGroups(cognitoRequest);
                log_info << "Groups listed, userPoolId: " << cognitoRequest.userPoolId << " count: " << serviceResponse.groups.size();

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "AdminAddUserToGroup") {

                Dto::Cognito::AdminAddUserToGroupRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Add user to group request, json: " << cognitoRequest.ToString();

                _cognitoService.AdminAddUserToGroup(cognitoRequest);
                log_info << "Add user to group, userPoolId: " << cognitoRequest.userPoolId;

                return SendOkResponse(request);

            } else if (action == "ListUsersInGroup") {

                Dto::Cognito::ListUsersInGroupRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "List users in group request, json: " << cognitoRequest.ToString();

                Dto::Cognito::ListUsersInGroupResponse serviceResponse = _cognitoService.ListUsersInGroup(cognitoRequest);
                log_info << "Users in group listed, userPoolId: " << cognitoRequest.userPoolId;

                return SendOkResponse(request, serviceResponse.ToJson());

            } else if (action == "DeleteGroup") {

                Dto::Cognito::DeleteGroupRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got delete group request, json: " << cognitoRequest.ToString();

                _cognitoService.DeleteGroup(cognitoRequest);
                log_info << "Group deleted, userPoolId: " << cognitoRequest.userPoolId << " group: " << cognitoRequest.groupName;

                return SendOkResponse(request);

            } else if (action == "SignUp") {

                Dto::Cognito::SignUpRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got sign up request, json: " << cognitoRequest.ToString();

                Dto::Cognito::SignUpResponse cognitoResponse = _cognitoService.SignUp(cognitoRequest);
                log_info << "Sign up user, user: " << cognitoRequest.user << " clientId: " << cognitoRequest.clientId;

                return SendOkResponse(request, cognitoResponse.ToJson());

            } else if (action == "AdminConfirmSignUp") {

                Dto::Cognito::AdminConfirmUserRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got sign up request, json: " << cognitoRequest.ToString();

                _cognitoService.ConfirmUser(cognitoRequest);
                log_info << "User confirmed, userPoolId: " << cognitoRequest.userPoolId << " userName: " << cognitoRequest.userName;

                return SendOkResponse(request);

            } else {

                return SendBadRequestError(request, "Unknown function");
            }

        } catch (Poco::Exception &exc) {
            return SendInternalServerError(request, exc.message());
        }
    }

    std::string CognitoHandler::GetActionFromHeader(const http::request<http::dynamic_body> &request) {

        if (!Core::HttpUtils::HasHeader(request, "X-Amz-Target")) {
            log_error << "Could not extract action";
            throw Core::BadRequestException("Could not extract action");
        }

        std::string headerValue = request["X-Amz-Target"];
        return Core::StringUtils::Split(headerValue, '.')[1];
    }

}// namespace AwsMock::Service
