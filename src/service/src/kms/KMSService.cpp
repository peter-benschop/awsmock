//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/kms/KMSService.h>

namespace AwsMock::Service {

    template<typename K>
    void CallAsyncCreateKey(K &&k) {
        Service::KMSCreator creator;
        std::thread(&KMSCreator::CreateKmsKey, k).detach();
    }

    KMSService::KMSService(Core::Configuration &configuration) : _configuration(configuration), _kmsDatabase(Database::KMSDatabase::instance()) {

        // Initialize environment
        _accountId = _configuration.getString("awsmock.account.userPoolId", DEFAULT_KMS_ACCOUNT_ID);
    }

    Dto::KMS::ListKeysResponse KMSService::ListKeys(const Dto::KMS::ListKeysRequest &request) {
        log_trace << "List keys request: " << request.ToString();

        try {

            Database::Entity::KMS::KeyList keyList = _kmsDatabase.ListKeys();
            Dto::KMS::ListKeysResponse listKeysResponse;
            for (const auto &k: keyList) {
                Dto::KMS::ListKey key = {.keyId = k.keyId, .keyArn = k.arn};
                listKeysResponse.keys.emplace_back(key);
            }
            log_debug << "List all keys, size: " << keyList.size();

            return listKeysResponse;

        } catch (Poco::Exception &ex) {
            log_error << "S3 Create Bucket failed, message: " << ex.message();
            throw Core::ServiceException(ex.message());
        }
    }

    Dto::KMS::CreateKeyResponse KMSService::CreateKey(const Dto::KMS::CreateKeyRequest &request) {
        log_trace << "Create key request: " << request.ToString();

        try {
            // Update database
            std::string keyId = Poco::UUIDGenerator().createRandom().toString();

            std::string arn = Core::AwsUtils::CreateKMSKeyArn(request.region, _accountId, keyId);
            Database::Entity::KMS::Key keyEntity = {
                    .region = request.region,
                    .keyId = keyId,
                    .keyUsage = KeyUsageToString(request.keyUsage),
                    .keySpec = KeySpecToString(request.keySpec),
                    .arn = arn,
                    .description = request.description,
                    .tags = request.tags};

            // Store in database
            keyEntity = _kmsDatabase.CreateKey(keyEntity);
            log_trace << "KMS keyEntity created: " << keyEntity.ToString();

            // Create keyEntity material asynchronously
            CallAsyncCreateKey<std::string &>(keyId);
            log_debug << "KMS keyEntity creation started, keyId: " << keyId;

            Dto::KMS::Key key = {
                    .keyId = keyEntity.keyId,
                    .arn = keyEntity.arn,
                    .keyState = Dto::KMS::KeyStateFromString(keyEntity.keyState),
                    .description = keyEntity.description};
            Dto::KMS::CreateKeyResponse response = {.key = key};
            return response;

        } catch (Core::DatabaseException &exc) {
            log_error << "KMS create key failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    Dto::KMS::ScheduledKeyDeletionResponse KMSService::ScheduleKeyDeletion(const Dto::KMS::ScheduleKeyDeletionRequest &request) {
        log_trace << "Schedule key deletion request: " << request.ToString();

        if (!_kmsDatabase.KeyExists(request.keyId)) {
            log_error << "Key not found, keyId: " << request.keyId;
            throw Core::ServiceException("Key not found, keyId: " + request.keyId);
        }

        try {

            // Get the key
            Database::Entity::KMS::Key key = _kmsDatabase.GetKeyByKeyId(request.keyId);

            key.pendingWindowInDays = request.pendingWindowInDays;
            key.scheduledDeletion = Poco::DateTime(Poco::DateTime().timestamp() + Poco::Timespan(request.pendingWindowInDays * 24 * 60 * 60, 0));
            key.keyState = Dto::KMS::KeyStateToString(Dto::KMS::KeyState::PENDING_DELETION);

            // Store in database
            key = _kmsDatabase.UpdateKey(key);
            log_trace << "KMS key updated: " << key.ToString();

            return {
                    .keyId = request.keyId,
                    .keyState = key.keyState,
                    .deletionDate = key.scheduledDeletion.timestamp().epochMicroseconds() / 1000,
                    .pendingWindowInDays = request.pendingWindowInDays,
            };

        } catch (Core::DatabaseException &exc) {
            log_error << "KMS create key failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }
}// namespace AwsMock::Service