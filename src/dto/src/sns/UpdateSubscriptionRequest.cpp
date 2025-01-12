//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/UpdateSubscriptionRequest.h>

namespace AwsMock::Dto::SNS {

    void UpdateSubscriptionRequest::FromJson(const std::string &jsonString) {


        try {
            const value document = bsoncxx::from_json(jsonString);
            topicArn = Core::Bson::BsonUtils::GetStringValue(document, "topicArn");
            subscriptionArn = Core::Bson::BsonUtils::GetStringValue(document, "subscriptionArn");
            protocol = Core::Bson::BsonUtils::GetStringValue(document, "protocol");
            endpoint = Core::Bson::BsonUtils::GetStringValue(document, "endpoint");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UpdateSubscriptionRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "topicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(document, "subscriptionArn", subscriptionArn);
            Core::Bson::BsonUtils::SetStringValue(document, "protocol", protocol);
            Core::Bson::BsonUtils::SetStringValue(document, "endpoint", endpoint);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UpdateSubscriptionRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateSubscriptionRequest &r) {
        os << "UpdateSubscriptionRequest=" + r.ToJson();
        return os;
    }
}// namespace AwsMock::Dto::SNS
