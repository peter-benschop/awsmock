//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sns/SubscribeResponse.h>

namespace AwsMock::Dto::SNS {

    std::string SubscribeResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "SubscriptionArn", subscriptionArn);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SubscribeResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("SubscribeResponse.SubscribeResult.SubscriptionArn", subscriptionArn);
            root.add("SubscribeResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string SubscribeResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const SubscribeResponse &r) {
        os << "SubscribeResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
