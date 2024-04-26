
#include <awsmock/service/kms/KMSCmdHandler.h>

namespace AwsMock::Service {

    void KMSCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::KMSClientCommand &kmsClientCommand) {
        log_trace << "KMS POST request, URI: " << request.getURI() << " region: " << kmsClientCommand.region << " user: " << kmsClientCommand.user << " command: " << Dto::Common::KMSCommandTypeToString(kmsClientCommand.command);

        std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());

        switch (kmsClientCommand.command) {

            case Dto::Common::KMSCommandType::CREATE_KEY: {

                std::string name = Core::HttpUtils::GetQueryParameterValueByName(kmsClientCommand.payload, "Name");
                log_debug << "Topic name: " << name;

                Dto::KMS::CreateKeyRequest kmsRequest = {.region = kmsClientCommand.region};
                Dto::KMS::CreateKeyResponse kmsResponse = _kmsService.CreateKey(kmsRequest);
                SendOkResponse(response, kmsResponse.ToJson());
                log_info << "Key created, name: " << name;

                break;
            }

            case Dto::Common::KMSCommandType::DELETE_KEY:
            case Dto::Common::KMSCommandType::UNKNOWN: {

                break;
            }
        }
    }
}// namespace AwsMock::Service
