//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/model/Subscription.h>

namespace AwsMock::Dto::SNS {

    std::string Subscription::ToJson() const {

        try {

            return Core::Bson::BsonUtils::ToJsonString(ToDocument());

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    view_or_value<view, value> Subscription::ToDocument() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "id", id);
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "topicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(document, "protocol", protocol);
            Core::Bson::BsonUtils::SetStringValue(document, "subscriptionArn", subscriptionArn);
            Core::Bson::BsonUtils::SetStringValue(document, "endpoint", endpoint);
            return document.extract();

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string Subscription::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Subscription &r) {
        os << "Subscription=" << r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SNS
