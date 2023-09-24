//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

    bool MessageAttribute::operator<(const AwsMock::Dto::SQS::MessageAttribute &other) const {
        return attributeName < other.attributeName;
    }

    std::string MessageAttribute::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const MessageAttribute &r) {
        os << "MessageAttribute={attributeName='" + r.attributeName + "' attributeValue='" + r.attributeValue + "' type='" + r.type + "' transportType='"
            + r.transportType + "'}";
        return os;
    }
}
