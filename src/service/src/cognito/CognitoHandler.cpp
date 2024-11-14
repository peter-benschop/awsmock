#include <awsmock/service/cognito/CognitoHandler.h>

namespace AwsMock::Service {

    const std::map<std::string, std::string> CognitoHandler::headers = CognitoHandler::CreateHeaderMap();

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
                log_info << "User pool client created, userPoolId: " << cognitoRequest.userPoolId << " clientName: " << cognitoRequest.clientName;

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

            } else if (action == "ListUserPoolCounters") {

                Dto::Cognito::ListUserPoolCountersRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got list user pool counters request, json: " << cognitoRequest.ToString();

                Dto::Cognito::ListUserPoolCountersResponse serviceResponse = _cognitoService.ListUserPoolCounters(cognitoRequest);
                log_info << "User pools counters listed, count: " << serviceResponse.userPools.size();

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

            } else if (action == "ListUserCounters") {

                Dto::Cognito::ListUserCountersRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got list user counters request: " << cognitoRequest.ToString();

                Dto::Cognito::ListUserCountersResponse cognitoResponse = _cognitoService.ListUserCounters(cognitoRequest);
                log_info << "User counters listed, userPoolId: " << cognitoRequest.userPoolId << " count: " << cognitoResponse.users.size();

                return SendOkResponse(request, cognitoResponse.ToJson());

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

            } else if (action == "AdminRemoveUserFromGroup") {

                Dto::Cognito::AdminRemoveUserFromGroupRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Remove user from group request, json: " << cognitoRequest.ToString();

                _cognitoService.AdminRemoveUserFromGroup(cognitoRequest);
                log_info << "Remove user from group, userPoolId: " << cognitoRequest.userPoolId;

                return SendOkResponse(request);
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

                log_debug << "Got confirm sign up request, json: " << cognitoRequest.ToString();

                _cognitoService.ConfirmUser(cognitoRequest);
                log_info << "User confirmed, userPoolId: " << cognitoRequest.userPoolId << " userName: " << cognitoRequest.userName;

                return SendOkResponse(request);

            } else if (action == "InitiateAuth") {

                Dto::Cognito::InitiateAuthRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got initiate auth request, json: " << cognitoRequest.ToString();

                Dto::Cognito::InitiateAuthResponse cognitoResponse = _cognitoService.InitiateAuth(cognitoRequest);
                log_info << "User authorization initiated, userName: " << cognitoRequest.GetUserId();

                return SendOkResponse(request, cognitoResponse.ToJson(), headers);

            } else if (action == "RespondToAuthChallenge") {

                Dto::Cognito::RespondToAuthChallengeRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got response to auth challenge request, json: " << cognitoRequest.ToString();

                Dto::Cognito::RespondToAuthChallengeResponse cognitoResponse = _cognitoService.RespondToAuthChallenge(cognitoRequest);
                log_info << "Respond to auth challenge, clientId: " << cognitoRequest.clientId << " json: " << cognitoResponse.ToJson();

                return SendOkResponse(request, cognitoResponse.ToJson(), headers);

            } else if (action == "GlobalSignOut") {

                Dto::Cognito::GlobalSignOutRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;

                log_debug << "Got global sign out request, json: " << cognitoRequest.ToString();

                _cognitoService.GlobalSignOut(cognitoRequest);
                log_info << "Global sign out, accessToken: " << cognitoRequest.accessToken;

                return SendOkResponse(request, {}, headers);

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

            } else if (action == "AdminGetUser") {

                Dto::Cognito::AdminGetUserRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got admin get user request, json: " << cognitoRequest.ToString();

                Dto::Cognito::AdminGetUserResponse cognitoResponse = _cognitoService.AdminGetUser(cognitoRequest);
                log_info << "User returned, userPoolId: " << cognitoRequest.userPoolId << " username: " << cognitoRequest.user;

                return SendOkResponse(request, cognitoResponse.ToJson());

            } else if (action == "AdminEnableUser") {

                Dto::Cognito::AdminEnableUserRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got admin enable user request, json: " << cognitoRequest.ToString();

                _cognitoService.AdminEnableUser(cognitoRequest);
                log_info << "User enabled, userPoolId: " << cognitoRequest.userPoolId << " user: " << cognitoRequest.user;

                return SendOkResponse(request);

            } else if (action == "AdminDisableUser") {

                Dto::Cognito::AdminDisableUserRequest cognitoRequest{};
                cognitoRequest.FromJson(clientCommand.payload);
                cognitoRequest.region = clientCommand.region;
                cognitoRequest.requestId = clientCommand.requestId;
                cognitoRequest.user = clientCommand.user;
                log_debug << "Got admin disable user request, json: " << cognitoRequest.ToString();

                _cognitoService.AdminDisableUser(cognitoRequest);
                log_info << "User disabled, userPoolId: " << cognitoRequest.userPoolId << " user: " << cognitoRequest.user;

                return SendOkResponse(request);

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

            } else {

                return SendBadRequestError(request, "Unknown action");
            }

        } catch (Poco::Exception &exc) {
            return SendInternalServerError(request, exc.message());
        }
    }

    std::string CognitoHandler::GetActionFromHeader(const http::request<http::dynamic_body> &request) {

        if (Core::HttpUtils::HasHeader(request, "x-awsmock-action")) {
            return Core::HttpUtils::GetHeaderValue(request, "x-awsmock-action");
        }

        if (!Core::HttpUtils::HasHeader(request, "X-Amz-Target")) {
            log_error << "Could not extract action";
            throw Core::BadRequestException("Could not extract action");
        }

        std::string headerValue = request["X-Amz-Target"];
        return Core::StringUtils::Split(headerValue, '.')[1];
    }

}// namespace AwsMock::Service
