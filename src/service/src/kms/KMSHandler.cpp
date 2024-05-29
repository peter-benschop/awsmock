
#include <awsmock/service/kms/KMSHandler.h>

namespace AwsMock::Service {

    boost::beast::http::response<boost::beast::http::string_body> KMSHandler::HandlePostRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_trace << "KMS POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::KMSClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        switch (clientCommand.command) {

            case Dto::Common::KMSCommandType::CREATE_KEY: {

                Dto::KMS::CreateKeyRequest kmsRequest;
                kmsRequest.FromJson(clientCommand.payload);
                kmsRequest.region = clientCommand.region;

                Dto::KMS::CreateKeyResponse kmsResponse = _kmsService.CreateKey(kmsRequest);

                return SendOkResponse(request, kmsResponse.ToJson());
                log_info << "Key created, keyId: " << kmsResponse.key.keyId;

                break;
            }

            case Dto::Common::KMSCommandType::SCHEDULE_KEY_DELETION: {

                Dto::KMS::ScheduleKeyDeletionRequest kmsRequest;
                kmsRequest.FromJson(clientCommand.payload);
                kmsRequest.region = clientCommand.region;

                Dto::KMS::ScheduledKeyDeletionResponse kmsResponse = _kmsService.ScheduleKeyDeletion(kmsRequest);

                return SendOkResponse(request, kmsResponse.ToJson());
                log_info << "Key deletion scheduled, keyId: " << kmsResponse.keyId;

                break;
            }

            case Dto::Common::KMSCommandType::LIST_KEYS: {

                Dto::KMS::ListKeysRequest kmsRequest;
                kmsRequest.FromJson(clientCommand.payload);
                kmsRequest.region = clientCommand.region;

                Dto::KMS::ListKeysResponse kmsResponse = _kmsService.ListKeys(kmsRequest);

                return SendOkResponse(request, kmsResponse.ToJson());
                log_info << "List keys received, count: " << kmsResponse.keys.size();

                break;
            }

            case Dto::Common::KMSCommandType::DESCRIBE_KEY: {

                Dto::KMS::DescribeKeyRequest kmsRequest;
                kmsRequest.FromJson(clientCommand.payload);
                kmsRequest.region = clientCommand.region;

                Dto::KMS::DescribeKeyResponse kmsResponse = _kmsService.DescribeKey(kmsRequest);

                return SendOkResponse(request, kmsResponse.ToJson());
                log_info << "Describe key received, count: " << kmsResponse.key.keyId;

                break;
            }

            case Dto::Common::KMSCommandType::ENCRYPT: {

                Dto::KMS::EncryptRequest kmsRequest;
                kmsRequest.FromJson(clientCommand.payload);
                kmsRequest.region = clientCommand.region;

                Dto::KMS::EncryptResponse kmsResponse = _kmsService.Encrypt(kmsRequest);

                return SendOkResponse(request, kmsResponse.ToJson());
                log_info << "Encrypt received, size: " << kmsResponse.ciphertext.length();

                break;
            }

            case Dto::Common::KMSCommandType::DECRYPT: {

                Dto::KMS::DecryptRequest kmsRequest;
                kmsRequest.FromJson(clientCommand.payload);
                kmsRequest.region = clientCommand.region;

                Dto::KMS::DecryptResponse kmsResponse = _kmsService.Decrypt(kmsRequest);

                return SendOkResponse(request, kmsResponse.ToJson());
                log_info << "Decrypt received, size: " << kmsResponse.plaintext.length();

                break;
            }

            case Dto::Common::KMSCommandType::UNKNOWN: {
                log_error << "Unimplemented command called";
                throw Core::ServiceException("Unimplemented command called");
            }
        }
    }
}// namespace AwsMock::Service
