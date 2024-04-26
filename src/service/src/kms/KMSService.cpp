//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/kms/KMSService.h>

namespace AwsMock::Service {

    template<typename K>
    void CallAsyncCreateKey(K &&k) {
        Service::KMSCreator creator;
        std::thread(&KMSCreator::CreateKmsKey, &creator, k).detach();
    }

    KMSService::KMSService(Core::Configuration &configuration) : _configuration(configuration), _kmsDatabase(Database::KMSDatabase::instance()) {

        // Initialize environment
        _accountId = _configuration.getString("awsmock.account.userPoolId", DEFAULT_KMS_ACCOUNT_ID);
    }

    Dto::KMS::CreateKeyResponse KMSService::CreateKey(const Dto::KMS::CreateKeyRequest &request) {
        log_trace << "Create key request: " << request.ToString();

        try {
            // Update database
            std::string keyId = Poco::UUIDGenerator().createRandom().toString();

            std::string arn = Core::AwsUtils::CreateKMSKeyArn(request.region, _accountId, keyId);
            Database::Entity::KMS::Key key = {
                    .region = request.region,
                    .keyId = keyId,
                    .keyUsage = KeyUsageToString(request.keyUsage),
                    .keySpec = KeySpecToString(request.keySpec),
                    .arn = arn,
                    .description = request.description,
                    .tags = request.tags};

            // Store in database
            key = _kmsDatabase.CreateKey(key);
            log_trace << "KMS key created: " << key.ToString();

            // Create key asynchronously
            CallAsyncCreateKey<const char *>(keyId.c_str());
            log_debug << "KMS key creation started, keyId: " << keyId;

            Dto::KMS::KeyMetadata metadata = {
                    .keyId = key.keyId,
                    .arn = key.arn,
                    .keyState = Dto::KMS::KeyStateFromString(key.keyState),
                    .description = key.description};
            Dto::KMS::CreateKeyResponse response = {.metaData = metadata};
            return response;

        } catch (Core::DatabaseException &exc) {
            log_error << "KMS create key failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }// namespace AwsMock::Service

}// namespace AwsMock::Service
