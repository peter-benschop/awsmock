//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/kms/KMSWorker.h>

namespace AwsMock::Service {

    KMSWorker::KMSWorker(int timeout) : Core::Timer("kms-worker", timeout) {
        Start();
    }

    void KMSWorker::Initialize() {
        log_debug << "KMSWorker initialized";
        DeleteKeys();
    }

    void KMSWorker::Run() {
        DeleteKeys();
    }

    void KMSWorker::Shutdown() {}

    void KMSWorker::DeleteKeys() {
        log_trace << "Starting delete keys";

        for (const auto &key: _kmsDatabase.ListKeys()) {
            if (key.keyState == Dto::KMS::KeyStateToString(Dto::KMS::KeyState::PENDING_DELETION) && key.scheduledDeletion < system_clock::now()) {
                _kmsDatabase.DeleteKey(key);
                log_debug << "Key deleted, keyId: " << key.keyId;
            }
        }
        log_trace << "Finished key deletion";
    }
}// namespace AwsMock::Service