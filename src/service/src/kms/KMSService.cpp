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
                    .keySpec = Dto::KMS::KeySpecFromString(keyEntity.keySpec),
                    .keyUsage = Dto::KMS::KeyUsageFromString(keyEntity.keyUsage),
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

    Dto::KMS::DescribeKeyResponse KMSService::DescribeKey(const Dto::KMS::DescribeKeyRequest &request) {
        log_trace << "Create key request: " << request.ToString();

        if (!_kmsDatabase.KeyExists(request.keyId)) {
            log_error << "Key not found, keyId: " << request.keyId;
            throw Core::ServiceException("Key not found, keyId: " + request.keyId);
        }

        try {

            Database::Entity::KMS::Key keyEntity = _kmsDatabase.GetKeyByKeyId(request.keyId);
            log_trace << "KMS key entity received: " << keyEntity.ToString();

            Dto::KMS::Key key = {
                    .keyId = keyEntity.keyId,
                    .arn = keyEntity.arn,
                    .keySpec = Dto::KMS::KeySpecFromString(keyEntity.keySpec),
                    .keyUsage = Dto::KMS::KeyUsageFromString(keyEntity.keyUsage),
                    .keyState = Dto::KMS::KeyStateFromString(keyEntity.keyState),
                    .description = keyEntity.description,
                    .creationDate = keyEntity.created.timestamp().epochTime(),
                    .deletionDate = keyEntity.scheduledDeletion.timestamp().epochTime(),
                    .enabled = Core::StringUtils::Equals(keyEntity.keyState, Dto::KMS::KeyStateToString(Dto::KMS::KeyState::ENABLED))};
            Dto::KMS::DescribeKeyResponse response = {.key = key};
            return response;

        } catch (Core::DatabaseException &exc) {
            log_error << "KMS describe key failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    Dto::KMS::EncryptResponse KMSService::Encrypt(const Dto::KMS::EncryptRequest &request) {
        log_trace << "Encrypt plaintext request: " << request.ToString();

        if (!_kmsDatabase.KeyExists(request.keyId)) {
            log_error << "Key not found, keyId: " << request.keyId;
            throw Core::ServiceException("Key not found, keyId: " + request.keyId);
        }

        try {

            Database::Entity::KMS::Key keyEntity = _kmsDatabase.GetKeyByKeyId(request.keyId);
            log_trace << "KMS key entity received: " << keyEntity.ToString();

            std::string cipherText = EncryptPlaintext(keyEntity, request.plainText);

            Dto::KMS::EncryptResponse response = {.region = request.region, .keyId = keyEntity.keyId, .encryptionAlgorithm = request.encryptionAlgorithm, .ciphertext = cipherText};
            return response;

        } catch (Core::DatabaseException &exc) {
            log_error << "KMS encrypt failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    Dto::KMS::DecryptResponse KMSService::Decrypt(const Dto::KMS::DecryptRequest &request) {
        log_trace << "Decrypt plaintext request: " << request.ToString();

        if (!_kmsDatabase.KeyExists(request.keyId)) {
            log_error << "Key not found, keyId: " << request.keyId;
            throw Core::ServiceException("Key not found, keyId: " + request.keyId);
        }

        try {

            Database::Entity::KMS::Key keyEntity = _kmsDatabase.GetKeyByKeyId(request.keyId);
            log_trace << "KMS key entity received: " << keyEntity.ToString();

            std::string plainText = DecryptPlaintext(keyEntity, request.ciphertext);

            Dto::KMS::DecryptResponse response = {.region = request.region, .keyId = keyEntity.keyId, .encryptionAlgorithm = request.encryptionAlgorithm, .plaintext = plainText};
            return response;

        } catch (Core::DatabaseException &exc) {
            log_error << "KMS decrypt failed, message: " << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string KMSService::EncryptPlaintext(const Database::Entity::KMS::Key &key, const std::string &plainText) {

        switch (Dto::KMS::KeySpecFromString(key.keySpec)) {

            case Dto::KMS::KeySpec::SYMMETRIC_DEFAULT: {

                // Preparation
                std::string rawKey = Core::Crypto::HexDecode(key.aes256Key);
                unsigned char *rawCiphertext = nullptr;
                std::string rawPlaintext = Core::Crypto::Base64Decode(plainText);
                int plaintextLen = static_cast<int>(rawPlaintext.length());

                // Encryption
                rawCiphertext = Core::Crypto::Aes256EncryptString((unsigned char *) rawPlaintext.c_str(), &plaintextLen, (unsigned char *) rawKey.c_str());
                log_debug << "Encrypted plaintext, length: " << rawPlaintext;
                return Core::Crypto::Base64Encode({(char *) rawCiphertext, static_cast<size_t>(plaintextLen)});
            }

            case Dto::KMS::KeySpec::RSA_2048:
            case Dto::KMS::KeySpec::RSA_3072:
            case Dto::KMS::KeySpec::RSA_4096: {

                // Preparation
                std::string rawPlaintext = Core::Crypto::Base64Decode(plainText);
                EVP_PKEY *publicKey = Core::Crypto::ReadRsaPublicKey(key.rsaPublicKey);

                // Encryption
                std::string cipherText = Core::Crypto::RsaEncrypt(publicKey, rawPlaintext);
                log_debug << "Encrypted plaintext, length: " << rawPlaintext.length();
                return Core::Crypto::Base64Encode(cipherText);
            }
            case Dto::KMS::KeySpec::ECC_NIST_P256:
                break;
            case Dto::KMS::KeySpec::ECC_NIST_P384:
                break;
            case Dto::KMS::KeySpec::ECC_NIST_P521:
                break;
            case Dto::KMS::KeySpec::ECC_SECG_P256K1:
                break;
            case Dto::KMS::KeySpec::HMAC_224:
                break;
            case Dto::KMS::KeySpec::HMAC_256:
                break;
            case Dto::KMS::KeySpec::HMAC_384:
                break;
            case Dto::KMS::KeySpec::HMAC_512:
                break;
        }
        return {};
    }

    std::string KMSService::DecryptPlaintext(const Database::Entity::KMS::Key &key, const std::string &ciphertext) {

        switch (Dto::KMS::KeySpecFromString(key.keySpec)) {
            case Dto::KMS::KeySpec::SYMMETRIC_DEFAULT: {

                // Preparation
                std::string rawKey = Core::Crypto::HexDecode(key.aes256Key);
                std::string rawCiphertext = Core::Crypto::Base64Decode(ciphertext);
                int ciphertextLenLen = static_cast<int>(rawCiphertext.length());
                unsigned char *rawPlaintext;

                // Description
                rawPlaintext = Core::Crypto::Aes256DecryptString((unsigned char *) rawCiphertext.c_str(), &ciphertextLenLen, (unsigned char *) rawKey.c_str());
                log_debug << "Decrypted plaintext, length: " << ciphertextLenLen;

                return Core::Crypto::Base64Encode({(char *) rawPlaintext});
            }

            case Dto::KMS::KeySpec::RSA_2048:
            case Dto::KMS::KeySpec::RSA_3072:
            case Dto::KMS::KeySpec::RSA_4096: {

                // Preparation
                std::string rawCiphertext = Core::Crypto::Base64Decode(ciphertext);
                EVP_PKEY *privateKey = Core::Crypto::ReadRsaPrivateKey(key.rsaPrivateKey);

                // Description
                std::string plainText = Core::Crypto::RsaDecrypt(privateKey, rawCiphertext);
                log_debug << "Decrypted plaintext, length: " << plainText.length();
                return Core::Crypto::Base64Encode(plainText);
            }

            case Dto::KMS::KeySpec::ECC_NIST_P256:
                break;
            case Dto::KMS::KeySpec::ECC_NIST_P384:
                break;
            case Dto::KMS::KeySpec::ECC_NIST_P521:
                break;
            case Dto::KMS::KeySpec::ECC_SECG_P256K1:
                break;
            case Dto::KMS::KeySpec::HMAC_224:
                break;
            case Dto::KMS::KeySpec::HMAC_256:
                break;
            case Dto::KMS::KeySpec::HMAC_384:
                break;
            case Dto::KMS::KeySpec::HMAC_512:
                break;
        }
        return {};
    }

}// namespace AwsMock::Service