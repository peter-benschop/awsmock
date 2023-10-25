//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageRequest.h>

namespace AwsMock::Dto::SQS {

    std::string SendMessageRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SendMessageRequest &r) {
        os << "SendMessageRequest={region='" << r.region << "', queueUrl='" << r.queueUrl << "', queueArn='" << r.queueArn << "', body: '" << r.body << "', requestId: "
           << r.requestId << "', attributes=[";
        for (const auto &a : r.messageAttributes) {
            os << a.ToString() << ", ";
        }
        os << "\b" << "\b" << "]}";
        return os;
    }

} // namespace AwsMock::Dto::SQS
