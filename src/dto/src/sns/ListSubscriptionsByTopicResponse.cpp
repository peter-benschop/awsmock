//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sns/ListSubscriptionsByTopicResponse.h>

namespace AwsMock::Dto::SNS {

    std::string ListSubscriptionsByTopicResponse::ToJson() const {

        try {
            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "NextToken", nextToken);

            if (!subscriptions.empty()) {
                array subscriptionArray;
                for (auto &it: subscriptions) {
                    document topicElement;
                    Core::Bson::BsonUtils::SetStringValue(topicElement, "TopicArn", it.topicArn);
                    Core::Bson::BsonUtils::SetStringValue(topicElement, "SubscriptionArn", it.subscriptionArn);
                    Core::Bson::BsonUtils::SetStringValue(topicElement, "Protocol", it.protocol);
                    Core::Bson::BsonUtils::SetStringValue(topicElement, "Endpoint", it.endpoint);
                    Core::Bson::BsonUtils::SetStringValue(topicElement, "Owner", it.owner);
                    subscriptionArray.append(topicElement);
                }
                rootDocument.append(kvp("Subscriptions", subscriptionArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListSubscriptionsByTopicResponse::ToXml() const {

        try {

            boost::property_tree::ptree root;

            if (!subscriptions.empty()) {
                boost::property_tree::ptree xmlTopics;
                for (auto &it: subscriptions) {
                    boost::property_tree::ptree xmlTopic;
                    xmlTopic.add("TopicArn", it.topicArn);
                    xmlTopic.add("SubscriptionArn", it.subscriptionArn);
                    xmlTopic.add("Protocol", it.protocol);
                    xmlTopic.add("Endpoint", it.endpoint);
                    xmlTopic.add("Owner", it.owner);
                    xmlTopics.add_child("member", xmlTopic);
                }
                root.add_child("ListSubscriptionsByTopicResponse.ListSubscriptionsByTopicResult.Subscriptions", xmlTopics);
            }
            root.add("ListSubscriptionsByTopicResponse.ResponseMetadata.RequestId", Core::StringUtils::CreateRandomUuid());

            return Core::XmlUtils::ToXmlString(root);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListSubscriptionsByTopicResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListSubscriptionsByTopicResponse &r) {
        os << "ListSubscriptionsByTopicResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SNS
