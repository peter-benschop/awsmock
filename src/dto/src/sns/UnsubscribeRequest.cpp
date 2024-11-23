//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/UnsubscribeRequest.h>

namespace AwsMock::Dto::SNS {

    std::string UnsubscribeRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UnsubscribeRequest &r) {
        os << "UnsubscribeRequest={region='" << r.region << "', subscriptionArn='" << r.subscriptionArn << "'}";
        return os;
    }

}// namespace AwsMock::Dto::SNS
