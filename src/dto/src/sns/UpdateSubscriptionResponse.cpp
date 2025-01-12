//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/UpdateSubscriptionResponse.h>

namespace AwsMock::Dto::SNS {

    std::string UpdateSubscriptionResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "SubscriptionArn", subscriptionArn);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UpdateSubscriptionResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UpdateSubscriptionResponse &r) {
        os << "UpdateSubscriptionResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
