
#include <awsmock/service/transfer/TransferHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> TransferHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_trace << "lambda POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        try {
            std::string body = Core::HttpUtils::GetBodyAsString(request);

            if (std::string target = GetTarget(request); target == "TransferService.CreateServer") {

                Dto::Transfer::CreateServerRequest transferRequest = {.region = region};
                transferRequest.FromJson(body);
                Dto::Transfer::CreateServerResponse transferResponse = _transferService.CreateTransferServer(transferRequest);
                return SendOkResponse(request, transferResponse.ToJson());

            } else if (target == "TransferService.CreateUser") {

                Dto::Transfer::CreateUserRequest transferRequest = {.region = region};
                transferRequest.FromJson(body);

                Dto::Transfer::CreateUserResponse transferResponse = _transferService.CreateUser(transferRequest);
                return SendOkResponse(request, transferResponse.ToJson());

            } else if (target == "TransferService.ListServers") {

                Dto::Transfer::ListServerRequest transferRequest = {.region = region};
                transferRequest.FromJson(body);
                Dto::Transfer::ListServerResponse transferResponse = _transferService.ListServers(transferRequest);
                return SendOkResponse(request, transferResponse.ToJson());

            } else if (target == "TransferService.ListUsers") {

                std::string serverId;
                Dto::Transfer::ListUsersRequest transferRequest = {.region = region};
                transferRequest.FromJson(body);
                Dto::Transfer::ListUsersResponse transferResponse = _transferService.ListUsers(transferRequest);
                return SendOkResponse(request, transferResponse.ToJson());

            } else if (target == "TransferService.StartServer") {

                Dto::Transfer::StartServerRequest transferRequest = {.region = region};
                transferRequest.FromJson(body);
                _transferService.StartServer(transferRequest);
                return SendOkResponse(request);

            } else if (target == "TransferService.StopServer") {

                Dto::Transfer::StopServerRequest transferRequest = {.region = region};
                transferRequest.FromJson(body);
                _transferService.StopServer(transferRequest);
                return SendOkResponse(request);

            } else if (target == "TransferService.DeleteServer") {

                Dto::Transfer::DeleteServerRequest transferRequest = {.region = region};
                transferRequest.FromJson(body);
                _transferService.DeleteServer(transferRequest);
                return SendOkResponse(request);

            } else {

                log_error << "Unknown method";
                return SendBadRequestError(request, "Unknown method");
            }


        } catch (std::exception &exc) {
            return SendInternalServerError(request, exc.what());
        }
    }

    std::string TransferHandler::GetTarget(const http::request<http::dynamic_body> &request) {
        return Core::HttpUtils::GetHeaderValue(request, "X-Amz-Target");
    }
}// namespace AwsMock::Service
