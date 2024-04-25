//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/sns/SNSWorker.h>

namespace AwsMock::Service {

    void SNSWorker::Initialize() {

        Core::Configuration &configuration = Core::Configuration::instance();
        _messageTimeout = configuration.getInt("awsmock.service.sns.message.timeout", SNS_DEFAULT_MESSAGE_TIMEOUT);

        // Message timeout in seconds
        _messageTimeout *= 60 * 24;

        log_debug << "SNSWorker initialized, messageTimeout: " << _messageTimeout;
    }

    void SNSWorker::Run() {
        DeleteOldMessages();
    }

    void SNSWorker::Shutdown() {}

    void SNSWorker::DeleteOldMessages() {
        _snsDatabase.DeleteOldMessages(_messageTimeout);
    }
}// namespace AwsMock::Service