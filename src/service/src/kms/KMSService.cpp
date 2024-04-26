//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/kms/KMSService.h>

namespace AwsMock::Service {

    KMSService::KMSService(Core::Configuration &configuration) : _configuration(configuration), _kmsDatabase(Database::KMSDatabase::instance()) {

        // Initialize environment
        _accountId = _configuration.getString("awsmock.account.userPoolId", DEFAULT_KMS_ACCOUNT_ID);
    }

    Dto::KMS::CreateKeyResponse KMSService::CreateKey(const Dto::KMS::CreateKeyRequest &request) {
        log_trace << "Create key request: " << request.ToString();

        // Check existence
        if (_kmsDatabase.KeyExists(request.region, request.description)) {

            log_warning << "KMS key '" + request.description + "' exists already";
            Database::Entity::KMS::Key key = _kmsDatabase.GetKeyById(request.region);

            return {
                    .region = key.region,
                    .arn = key.arn};
        }

        try {
            // Update database
            std::string arn = Core::AwsUtils::CreateKMSKeyArn(request.region, _accountId, "CreateKMSKeyArn");
            Database::Entity::KMS::Key key = _kmsDatabase.CreateKey({.region = request.region, .arn = arn});
            log_trace << "KMS key created: " << key.ToString();

            return {.region = key.region, .arn = key.arn};

        } catch (Core::DatabaseException &exc) {
            log_error << "KMS create key failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

}// namespace AwsMock::Service
