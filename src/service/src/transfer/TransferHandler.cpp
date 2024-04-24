
#include <awsmock/service/transfer/TransferHandler.h>

namespace AwsMock::Service {

    void TransferHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "lambda POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        try {
            std::string body = Core::HttpUtils::GetBodyAsString(request);

            //DumpRequest(request);

            std::string target = GetTarget(request);

            if (target == "TransferService.CreateServer") {

                Dto::Transfer::CreateServerRequest transferRequest = {.region=region};
                transferRequest.FromJson(body);
                Dto::Transfer::CreateServerResponse transferResponse = _transferService.CreateTransferServer(transferRequest);
                SendOkResponse(response, transferResponse.ToJson());

            } else if (target == "TransferService.CreateUser") {

                Dto::Transfer::CreateUserRequest transferRequest = {.region=region};
                transferRequest.FromJson(body);

                Dto::Transfer::CreateUserResponse transferResponse = _transferService.CreateUser(transferRequest);
                SendOkResponse(response, transferResponse.ToJson());

            } else if (target == "TransferService.ListServers") {

                Dto::Transfer::ListServerRequest transferRequest = {.region=region};
                transferRequest.FromJson(body);
                Dto::Transfer::ListServerResponse transferResponse = _transferService.ListServers(transferRequest);
                std::string tmp = transferResponse.ToJson();
                SendOkResponse(response, transferResponse.ToJson());

            } else if (target == "TransferService.StartServer") {

                Dto::Transfer::StartServerRequest transferRequest = {.region=region};
                transferRequest.FromJson(body);
                _transferService.StartServer(transferRequest);
                SendOkResponse(response);

            } else if (target == "TransferService.StopServer") {

                Dto::Transfer::StopServerRequest transferRequest = {.region=region};
                transferRequest.FromJson(body);
                _transferService.StopServer(transferRequest);
                SendOkResponse(response);

            } else if (target == "TransferService.DeleteServer") {

                Dto::Transfer::DeleteServerRequest transferRequest = {.region=region};
                transferRequest.FromJson(body);
                _transferService.DeleteServer(transferRequest);
                SendOkResponse(response);

            }

        } catch (Poco::Exception &exc) {
            SendXmlErrorResponse("Transfer", response, exc);
        }
    }

    std::string TransferHandler::GetTarget(const Poco::Net::HTTPServerRequest &request) {
        return request.get("X-Amz-Target");
    }
}
