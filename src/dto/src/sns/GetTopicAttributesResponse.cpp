//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/GetTopicAttributesResponse.h>

namespace AwsMock::Dto::SNS {

    std::string GetTopicAttributesResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "TopicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Owner", owner);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "DisplayName", displayName);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "RequestId", requestId);
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetTopicAttributesResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;

            boost::property_tree::ptree attributesArray;
            boost::property_tree::ptree attributesElement1;
            attributesElement1.put("key", "TopicArn");
            attributesElement1.put("value", topicArn);
            attributesArray.push_back(std::make_pair("entry", attributesElement1));

            boost::property_tree::ptree attributesElement2;
            attributesElement2.put("key", "Owner");
            attributesElement2.put("value", owner);
            attributesArray.push_back(std::make_pair("entry", attributesElement2));

            boost::property_tree::ptree attributesElement3;
            attributesElement3.put("key", "DisplayName");
            attributesElement3.put("value", displayName);
            attributesArray.push_back(std::make_pair("entry", attributesElement3));

            root.add_child("GetTopicAttributesResponse.GetTopicAttributesResult.Attributes", attributesArray);
            root.add("GetTopicAttributesResponse.ResponseMetadata.RequestId", requestId);

            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string GetTopicAttributesResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetTopicAttributesResponse &r) {
        os << "GetTopicAttributesResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
