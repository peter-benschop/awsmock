//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/ListSubscriptionsByTopicRequest.h>

namespace AwsMock::Dto::SNS {

    std::string ListSubscriptionsByTopicRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListSubscriptionsByTopicRequest &r) {
        os << "ListSubscriptionsByTopicRequest={region='" << r.region << "', topicArn='" << r.topicArn << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
