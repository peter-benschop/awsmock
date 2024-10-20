//
// Created by vogje01 on 23/11/2023.
//

#include "awsmock/dto/sns/model/TopicCounter.h"

namespace AwsMock::Dto::SNS {

    std::string TopicCounter::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object TopicCounter::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("topicName", topicName);
            rootJson.set("topicArn", topicArn);
            rootJson.set("topicUrl", topicUrl);
            rootJson.set("available", available);
            rootJson.set("retentionPeriod", retentionPeriod);
            rootJson.set("maxMessageSize", maxMessageSize);

            rootJson.set("created", Core::DateTimeUtils::ToISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ToISO8601(modified));

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string TopicCounter::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TopicCounter &r) {
        os << "TopicCounter=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SNS
