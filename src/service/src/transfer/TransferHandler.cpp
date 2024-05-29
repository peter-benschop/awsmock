
#include <awsmock/service/transfer/TransferHandler.h>

namespace AwsMock::Service {

    http::response<http::string_body> TransferHandler::HandlePostRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_trace << "lambda POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        try {
            std::string body = request.body();
            std::string target = GetTarget(request);

            if (target == "TransferService.CreateServer") {

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
                std::string tmp = transferResponse.ToJson();
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
            }

        } catch (Poco::Exception &exc) {
            return SendInternalServerError(request, exc.message());
        }
    }

    std::string TransferHandler::GetTarget(const http::request<http::string_body> &request) {
        return Core::HttpUtils::GetHeaderValue(request, "X-Amz-Target");
    }
}// namespace AwsMock::Service
