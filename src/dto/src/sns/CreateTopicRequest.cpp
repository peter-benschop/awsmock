//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/CreateTopicRequest.h>

namespace AwsMock::Dto::SNS {

    std::string CreateTopicRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateTopicRequest &r) {
        os << "CreateTopicRequest={region='" << r.region << "', topicName='" << r.topicName << "', owner='" << r.owner << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
