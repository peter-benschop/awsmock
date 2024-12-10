//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/CreateTopicResponse.h>

namespace AwsMock::Dto::SNS {

    std::string CreateTopicResponse::ToJson() const {

        try {

            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "region", topicArn);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "name", name);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "owner", owner);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "topicArn", topicArn);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "requestId", requestId);
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateTopicResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;
            root.add("CreateTopicResponse.CreateTopicResult.TopicArn", topicArn);
            root.add("CreateTopicResponse.CreateTopicResult.Name", name);
            root.add("CreateTopicResponse.CreateTopicResult.Owner", owner);
            root.add("CreateTopicResponse.ResponseMetadata.RequestId", requestId);
            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateTopicResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateTopicResponse &r) {
        os << "CreateTopicResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
