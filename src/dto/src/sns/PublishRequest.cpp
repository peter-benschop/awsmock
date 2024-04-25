//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/PublishRequest.h>

namespace AwsMock::Dto::SNS {

    std::string PublishRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PublishRequest &r) {
        os << "PublishRequest={region='" + r.region + "' topicArn='" + r.topicArn + "' targetArn: '" + r.targetArn + "' message='" + r.message + "'}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
