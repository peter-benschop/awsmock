
#include <awsmock/service/secretsmanager/SecretsManagerCmdHandler.h>

namespace AwsMock::Service {

  SecretsManagerCmdHandler::SecretsManagerCmdHandler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _configuration(configuration),
        _metricService(metricService), _secretsManagerService(configuration) {
  }

  void SecretsManagerCmdHandler::handlePost(Poco::Net::HTTPServerRequest &request,
                                            Poco::Net::HTTPServerResponse &response,
                                            const Dto::Common::SecretsManagerClientCommand &secretsManagerClientCommand) {
    log_debug << "SecretsManager POST request, URI: " << request.getURI() << " region: "
                              << secretsManagerClientCommand.region << " user: " << secretsManagerClientCommand.user
                              << " command: "
                              << Dto::Common::SecretsManagerCommandTypeToString(secretsManagerClientCommand.command)
                             ;

    std::string requestId = GetHeaderValue(request, "RequestId", Poco::UUIDGenerator().createRandom().toString());

    try {

      switch (secretsManagerClientCommand.command) {

      case Dto::Common::SecretsManagerCommandType::CREATE_SECRET: {

        Dto::SecretsManager::CreateSecretRequest
            secretsManagerRequest = {.region=secretsManagerClientCommand.region, .requestId=requestId};
        secretsManagerRequest.FromJson(secretsManagerClientCommand.payload);

        Dto::SecretsManager::CreateSecretResponse
            secretsManagerResponse = _secretsManagerService.CreateSecret(secretsManagerRequest);
        log_info << "Secret created, secretId: " << secretsManagerResponse.name;
        SendOkResponse(response, secretsManagerResponse.ToJson());

        break;
      }

      case Dto::Common::SecretsManagerCommandType::DELETE_SECRET: {

        Dto::SecretsManager::DeleteSecretRequest
            secretsManagerRequest = {.region=secretsManagerClientCommand.region, .requestId=requestId};
        secretsManagerRequest.FromJson(secretsManagerClientCommand.payload);

        Dto::SecretsManager::DeleteSecretResponse
            secretsManagerResponse = _secretsManagerService.DeleteSecret(secretsManagerRequest);
        log_info << "Secret deleted, secretId: " << secretsManagerResponse.name;
        SendOkResponse(response, secretsManagerResponse.ToJson());

        break;
      }

      case Dto::Common::SecretsManagerCommandType::DESCRIBE_SECRET:{

        Dto::SecretsManager::DescribeSecretRequest
            secretsManagerRequest = {.region=secretsManagerClientCommand.region, .requestId=requestId};
        secretsManagerRequest.FromJson(secretsManagerClientCommand.payload);

        Dto::SecretsManager::DescribeSecretResponse
            secretsManagerResponse = _secretsManagerService.DescribeSecret(secretsManagerRequest);
        log_info << "Secret described, secretId: " << secretsManagerResponse.name;
        SendOkResponse(response, secretsManagerResponse.ToJson());

        break;
      }

      case Dto::Common::SecretsManagerCommandType::GET_SECRET_VALUE:{

        Dto::SecretsManager::GetSecretValueRequest
          secretsManagerRequest = {.region=secretsManagerClientCommand.region, .requestId=requestId};
        secretsManagerRequest.FromJson(secretsManagerClientCommand.payload);

        Dto::SecretsManager::GetSecretValueResponse
          secretsManagerResponse = _secretsManagerService.GetSecretValue(secretsManagerRequest);
        log_info << "Secret get value, secretId: " << secretsManagerResponse.name;
        SendOkResponse(response, secretsManagerResponse.ToJson());

        break;
      }

      case Dto::Common::SecretsManagerCommandType::UPDATE_SECRET:{

        Dto::SecretsManager::UpdateSecretRequest
          secretsManagerRequest = {.region=secretsManagerClientCommand.region, .requestId=requestId};
        secretsManagerRequest.FromJson(secretsManagerClientCommand.payload);

        Dto::SecretsManager::UpdateSecretResponse
          secretsManagerResponse = _secretsManagerService.UpdateSecret(secretsManagerRequest);
        log_info << "Secret updated, secretId: " << secretsManagerResponse.name;
        SendOkResponse(response, secretsManagerResponse.ToJson());

        break;
      }

      case Dto::Common::SecretsManagerCommandType::ROTATE_SECRET:{

        Dto::SecretsManager::RotateSecretRequest
          secretsManagerRequest = {.region=secretsManagerClientCommand.region, .requestId=requestId};
        secretsManagerRequest.FromJson(secretsManagerClientCommand.payload);

        Dto::SecretsManager::RotateSecretResponse
          secretsManagerResponse = _secretsManagerService.RotateSecret(secretsManagerRequest);
        log_info << "Secret rotated, secretId: " << secretsManagerResponse.arn;
        SendOkResponse(response, secretsManagerResponse.ToJson());

        break;
      }

      case Dto::Common::SecretsManagerCommandType::LIST_SECRETS:{

        Dto::SecretsManager::ListSecretsRequest
          secretsManagerRequest = {.region=secretsManagerClientCommand.region, .requestId=requestId};
        secretsManagerRequest.FromJson(secretsManagerClientCommand.payload);

        Dto::SecretsManager::ListSecretsResponse
          secretsManagerResponse = _secretsManagerService.ListSecrets(secretsManagerRequest);
        log_info << "Secrets listed, region: " << secretsManagerResponse.region;
        SendOkResponse(response, secretsManagerResponse.ToJson());

        break;
      }

      case Dto::Common::SecretsManagerCommandType::UNKNOWN: {
        log_error << "Bad request, method: POST clientCommand: "
                                  << Dto::Common::SecretsManagerCommandTypeToString(secretsManagerClientCommand.command)
                                 ;
        throw Core::ServiceException("Bad request, method: POST clientCommand: "
                                         + Dto::Common::SecretsManagerCommandTypeToString(secretsManagerClientCommand.command));
      }

      }

    } catch (Core::JsonException &exc) {
      log_error << "JsonException: " << exc.message();
      SendJsonErrorResponse("SecretsManager", response, exc);
    } catch (Core::DatabaseException &exc) {
      log_error << "DatabaseException: " << exc.message();
      SendJsonErrorResponse("SecretsManager", response, exc);
    } catch (Core::ServiceException &exc) {
      log_error << "ServiceException: " << exc.message();
      SendJsonErrorResponse("SecretsManager", response, exc);
    }
  }
}
