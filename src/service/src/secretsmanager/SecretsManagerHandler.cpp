
#include <awsmock/service/secretsmanager/SecretsManagerHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> SecretsManagerHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_debug << "SecretsManager POST request, URI: " << request.target() << " region: " << region << " user: " << user;

        Dto::Common::SecretsManagerClientCommand clientCommand;
        clientCommand.FromRequest(request, region, user);

        try {

            switch (clientCommand.command) {

                case Dto::Common::SecretsManagerCommandType::CREATE_SECRET: {

                    Dto::SecretsManager::CreateSecretRequest
                            secretsManagerRequest = {.region = clientCommand.region, .requestId = Core::AwsUtils::CreateRequestId()};
                    secretsManagerRequest.FromJson(clientCommand.payload);

                    Dto::SecretsManager::CreateSecretResponse
                            secretsManagerResponse = _secretsManagerService.CreateSecret(secretsManagerRequest);
                    log_info << "Secret created, secretId: " << secretsManagerResponse.name;
                    return SendOkResponse(request, secretsManagerResponse.ToJson());

                    break;
                }

                case Dto::Common::SecretsManagerCommandType::DELETE_SECRET: {

                    Dto::SecretsManager::DeleteSecretRequest
                            secretsManagerRequest = {.region = clientCommand.region, .requestId = Core::AwsUtils::CreateRequestId()};
                    secretsManagerRequest.FromJson(clientCommand.payload);

                    Dto::SecretsManager::DeleteSecretResponse
                            secretsManagerResponse = _secretsManagerService.DeleteSecret(secretsManagerRequest);
                    log_info << "Secret deleted, secretId: " << secretsManagerResponse.name;
                    return SendOkResponse(request, secretsManagerResponse.ToJson());

                    break;
                }

                case Dto::Common::SecretsManagerCommandType::DESCRIBE_SECRET: {

                    Dto::SecretsManager::DescribeSecretRequest
                            secretsManagerRequest = {.region = clientCommand.region, .requestId = Core::AwsUtils::CreateRequestId()};
                    secretsManagerRequest.FromJson(clientCommand.payload);

                    Dto::SecretsManager::DescribeSecretResponse
                            secretsManagerResponse = _secretsManagerService.DescribeSecret(secretsManagerRequest);
                    log_info << "Secret described, secretId: " << secretsManagerResponse.name;
                    return SendOkResponse(request, secretsManagerResponse.ToJson());

                    break;
                }

                case Dto::Common::SecretsManagerCommandType::GET_SECRET_VALUE: {

                    Dto::SecretsManager::GetSecretValueRequest
                            secretsManagerRequest = {.region = clientCommand.region, .requestId = Core::AwsUtils::CreateRequestId()};
                    secretsManagerRequest.FromJson(clientCommand.payload);

                    Dto::SecretsManager::GetSecretValueResponse
                            secretsManagerResponse = _secretsManagerService.GetSecretValue(secretsManagerRequest);
                    log_info << "Secret get value, secretId: " << secretsManagerResponse.name;
                    return SendOkResponse(request, secretsManagerResponse.ToJson());

                    break;
                }

                case Dto::Common::SecretsManagerCommandType::UPDATE_SECRET: {

                    Dto::SecretsManager::UpdateSecretRequest
                            secretsManagerRequest = {.region = clientCommand.region, .requestId = Core::AwsUtils::CreateRequestId()};
                    secretsManagerRequest.FromJson(clientCommand.payload);

                    Dto::SecretsManager::UpdateSecretResponse
                            secretsManagerResponse = _secretsManagerService.UpdateSecret(secretsManagerRequest);
                    log_info << "Secret updated, secretId: " << secretsManagerResponse.name;
                    return SendOkResponse(request, secretsManagerResponse.ToJson());

                    break;
                }

                case Dto::Common::SecretsManagerCommandType::ROTATE_SECRET: {

                    Dto::SecretsManager::RotateSecretRequest secretsManagerRequest = {.region = clientCommand.region, .requestId = Core::AwsUtils::CreateRequestId()};
                    secretsManagerRequest.FromJson(clientCommand.payload);

                    Dto::SecretsManager::RotateSecretResponse
                            secretsManagerResponse = _secretsManagerService.RotateSecret(secretsManagerRequest);
                    log_info << "Secret rotated, secretId: " << secretsManagerResponse.arn;
                    return SendOkResponse(request, secretsManagerResponse.ToJson());

                    break;
                }

                case Dto::Common::SecretsManagerCommandType::LIST_SECRETS: {

                    Dto::SecretsManager::ListSecretsRequest
                            secretsManagerRequest = {.region = clientCommand.region, .requestId = Core::AwsUtils::CreateRequestId()};
                    secretsManagerRequest.FromJson(clientCommand.payload);

                    Dto::SecretsManager::ListSecretsResponse
                            secretsManagerResponse = _secretsManagerService.ListSecrets(secretsManagerRequest);
                    log_info << "Secrets listed, region: " << secretsManagerResponse.region;
                    return SendOkResponse(request, secretsManagerResponse.ToJson());

                    break;
                }
                default:
                    log_error << "Unknown method";
                    SendBadRequestError(request, "Unknown method");
            }

        } catch (Core::JsonException &exc) {
            log_error << "JsonException: " << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Core::DatabaseException &exc) {
            log_error << "DatabaseException: " << exc.message();
            return SendInternalServerError(request, exc.message());
        } catch (Core::ServiceException &exc) {
            log_error << "ServiceException: " << exc.message();
            return SendInternalServerError(request, exc.message());
        }
        log_error << "Unknown method";
        return SendBadRequestError(request, "Unknown method");
    }
}// namespace AwsMock::Service
