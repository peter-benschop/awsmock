//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/ListTopicsResponse.h>

namespace AwsMock::Dto::SNS {

    std::string ListTopicsResponse::ToJson() const {

        try {
            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "NextToken", nextToken);

            if (!topicList.empty()) {
                array topicArray;
                for (auto &it: topicList) {
                    document topicElement;
                    Core::Bson::BsonUtils::SetStringValue(topicElement, "TopicArn", it.topicArn);
                    topicArray.append(topicElement);
                }
                rootDocument.append(kvp("Topics", topicArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListTopicsResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;

            if (!topicList.empty()) {
                boost::property_tree::ptree xmlTopics;
                for (auto &it: topicList) {
                    boost::property_tree::ptree xmlTopic;
                    xmlTopic.add("TopicArn", it.topicArn);
                    xmlTopics.add_child("member", xmlTopic);
                }
                root.add_child("ListTopicsResponse.ListTopicsResult.Topics", xmlTopics);
            }
            root.add("ListTopicsResponse.ListTopicsResult.NextToken", nextToken);
            root.add("ListTopicsResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());

            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListTopicsResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListTopicsResponse &r) {
        os << "ListTopicsResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
