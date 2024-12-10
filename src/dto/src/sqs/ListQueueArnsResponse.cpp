//
// Created by vogje01 on 23/09/2023.
//

#include <awsmock/dto/sqs/ListQueueArnsResponse.h>

namespace AwsMock::Dto::SQS {

    std::string ListQueueArnsResponse::ToJson() const {

        try {

            document document;

            if (!queueArns.empty()) {
                array queueArnsArrayJson;
                for (const auto &queueArn: queueArns) {
                    queueArnsArrayJson.append(queueArn);
                }
                document.append(kvp("QueueArns", queueArnsArrayJson));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::ServiceException(exc.what());
        }
    }

    std::string ListQueueArnsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListQueueArnsResponse &r) {
        os << "ListQueueArnsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
