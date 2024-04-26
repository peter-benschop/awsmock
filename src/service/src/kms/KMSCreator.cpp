//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/service/kms/KMSCreator.h>

namespace AwsMock::Service {

    void KMSCreator::CreateKmsKey(const char *keyId) {

        log_debug << "Start creating KMS key, keyId: " << keyId;

        // Make local copy
        Database::Entity::KMS::Key keyEntity = _kmsDatabase.GetKeyByKeyId(keyId);

        log_debug << "KMS key created, keyId: " << keyId;
    }

}// namespace AwsMock::Service
