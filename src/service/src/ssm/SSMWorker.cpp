//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/ssm/SSMWorker.h>

namespace AwsMock::Service {

    SSMWorker::SSMWorker(int timeout) : Core::Timer("kms-worker", timeout) {
        Start();
    }

    void SSMWorker::Initialize() {
        log_debug << "SSMWorker initialized";
    }

    void SSMWorker::Run() {
    }

    void SSMWorker::Shutdown() {}

}// namespace AwsMock::Service