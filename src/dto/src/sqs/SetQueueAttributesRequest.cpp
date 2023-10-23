//
// Created by vogje01 on 30/09/2023.
//

#include <awsmock/dto/sqs/SetQueueAttributesRequest.h>

namespace AwsMock::Dto::SQS {

    std::string SetQueueAttributesRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SetQueueAttributesRequest &r) {
        os << "SetQueueAttributesRequest={queueUrl='" + r.queueUrl + "' resource='" + r.resource + "' requestId='" + r.requestId + "'}";
        return os;
    }

} // namespace AwsMock::Dto::SQS
