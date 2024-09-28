//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueArnsResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListQueueArnsResponse::ToJson() const {

        try {
            Poco::JSON::Array queueArnsArrayJson;
            for (const auto &queueArn: queueArns) {
                queueArnsArrayJson.add(queueArn);
            }

            Poco::JSON::Object rootJson;
            rootJson.set("QueueArns", queueArnsArrayJson);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ListQueueArnsResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueueArnsResponse &r) {
        os << "ListQueueArnsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
