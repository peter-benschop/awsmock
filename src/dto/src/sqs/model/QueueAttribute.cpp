//
// Created by vogje01 on 23/11/2023.
//

#include "awsmock/dto/sqs/model/QueueAttribute.h"

namespace AwsMock::Dto::SQS {

    std::string QueueAttribute::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueueAttribute &r) {
        os << "QueueAttribute={attributeName='" << r.attributeName << "', attributeValue='" << r.attributeValue << "'}";
        return os;
    }
}// namespace AwsMock::Dto::SQS
