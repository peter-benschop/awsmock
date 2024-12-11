//
// Created by vogje01 on 23/11/2023.
//

#include "awsmock/dto/sns/model/TopicCounter.h"

namespace AwsMock::Dto::SNS {

    std::string TopicCounter::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> TopicCounter::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "topicName", topicName);
            Core::Bson::BsonUtils::SetStringValue(document, "topicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(document, "topicUrl", topicUrl);
            Core::Bson::BsonUtils::SetLongValue(document, "retentionPeriod", retentionPeriod);
            Core::Bson::BsonUtils::SetLongValue(document, "maxMessageSize", maxMessageSize);
            Core::Bson::BsonUtils::SetLongValue(document, "availableMessages", availableMessages);
            Core::Bson::BsonUtils::SetDateValue(document, "created", created);
            Core::Bson::BsonUtils::SetDateValue(document, "modified", modified);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string TopicCounter::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const TopicCounter &r) {
        os << "TopicCounter=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SNS
