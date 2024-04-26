
#include <awsmock/service/kms/KMSCmdHandler.h>

namespace AwsMock::Service {

    void KMSCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::KMSClientCommand &kmsClientCommand) {
        log_trace << "KMS POST request, URI: " << request.getURI() << " region: " << kmsClientCommand.region << " user: " << kmsClientCommand.user << " command: " << Dto::Common::KMSCommandTypeToString(kmsClientCommand.command);

        std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());

        switch (kmsClientCommand.command) {

            case Dto::Common::KMSCommandType::CREATE_KEY: {

                Dto::KMS::CreateKeyRequest kmsRequest;
                kmsRequest.FromJson(kmsClientCommand.payload);
                kmsRequest.region = kmsClientCommand.region;

                Dto::KMS::CreateKeyResponse kmsResponse = _kmsService.CreateKey(kmsRequest);
                SendOkResponse(response, kmsResponse.ToJson());
                log_info << "Key created, keyId: " << kmsResponse.key.keyId;

                break;
            }

            case Dto::Common::KMSCommandType::SCHEDULE_KEY_DELETION: {

                Dto::KMS::ScheduleKeyDeletionRequest kmsRequest;
                kmsRequest.FromJson(kmsClientCommand.payload);
                kmsRequest.region = kmsClientCommand.region;

                Dto::KMS::ScheduledKeyDeletionResponse kmsResponse = _kmsService.ScheduleKeyDeletion(kmsRequest);
                SendOkResponse(response, kmsResponse.ToJson());
                log_info << "Key deletion scheduled, keyId: " << kmsResponse.keyId;

                break;
            }

            case Dto::Common::KMSCommandType::LIST_KEYS: {

                Dto::KMS::ListKeysRequest kmsRequest;
                kmsRequest.FromJson(kmsClientCommand.payload);
                kmsRequest.region = kmsClientCommand.region;

                Dto::KMS::ListKeysResponse kmsResponse = _kmsService.ListKeys(kmsRequest);
                SendOkResponse(response, kmsResponse.ToJson());
                log_info << "List keys received, count: " << kmsResponse.keys.size();

                break;
            }

            case Dto::Common::KMSCommandType::DESCRIBE_KEY:
            case Dto::Common::KMSCommandType::UNKNOWN: {

                break;
            }
        }
    }
}// namespace AwsMock::Service
