//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/kms/KMSWorker.h>

namespace AwsMock::Service {

    void KMSWorker::Initialize() {

        Core::Configuration &configuration = Core::Configuration::instance();

        log_debug << "KMSWorker initialized";
    }

    void KMSWorker::Run() {
    }

    void KMSWorker::Shutdown() {}

}// namespace AwsMock::Service