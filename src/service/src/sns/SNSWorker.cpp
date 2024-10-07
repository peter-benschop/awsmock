//
// Created by vogje01 on 4/21/24.
//

#include <awsmock/service/sns/SNSWorker.h>

namespace AwsMock::Service {

    void SNSWorker::DeleteOldMessages() {
        Core::Configuration &configuration = Core::Configuration::instance();
        int messageTimeout = configuration.getInt("awsmock.service.sns.message.timeout", SNS_DEFAULT_MESSAGE_TIMEOUT);
        _snsDatabase.DeleteOldMessages(messageTimeout);
    }
}// namespace AwsMock::Service