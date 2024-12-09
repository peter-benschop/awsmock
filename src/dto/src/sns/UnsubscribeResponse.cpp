//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/UnsubscribeResponse.h>

namespace AwsMock::Dto::SNS {

    std::string UnsubscribeResponse::ToJson() const {

        try {

            document document;

            Core::Bson::BsonUtils::SetStringValue(document, "SubscriptionArn", subscriptionArn);
            Core::Bson::BsonUtils::SetStringValue(document, "RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (const std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UnsubscribeResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("UnsubscribeResponse.SubscriptionArn", subscriptionArn);
            root.add("UnsubscribeResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::XmlUtils::ToXmlString(root);

        } catch (const std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string UnsubscribeResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const UnsubscribeResponse &r) {
        os << "UnsubscribeResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
