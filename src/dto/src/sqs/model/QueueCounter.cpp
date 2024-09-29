//
// Created by vogje01 on 23/11/2023.
//

#include "awsmock/dto/sqs/model/QueueCounter.h"

namespace AwsMock::Dto::SQS {

    std::string QueueCounter::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object QueueCounter::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("queueName", queueName);
            rootJson.set("queueArn", queueArn);
            rootJson.set("queueUrl", queueUrl);
            rootJson.set("available", available);
            rootJson.set("invisible", invisible);
            rootJson.set("delayed", delayed);

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string QueueCounter::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueueCounter &r) {
        os << "QueueCounter=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SQS
