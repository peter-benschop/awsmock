//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/PutBucketNotificationConfigurationResponse.h>

namespace AwsMock::Dto::S3 {

    std::string PutBucketNotificationConfigurationResponse::ToXml() {

        Poco::XML::AutoPtr<Poco::XML::Document> pDoc = Core::XmlUtils::CreateDocument();
        Poco::XML::AutoPtr<Poco::XML::Element> pRoot = Core::XmlUtils::CreateRootNode(pDoc, "NotificationConfiguration");

        // Queue notification configurations
        for (const auto &queueConfiguration: queueConfigurations) {

            Poco::XML::AutoPtr<Poco::XML::Element> pQueueConfiguration = Core::XmlUtils::CreateNode(pDoc, pRoot, "QueueNotification");
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Id", queueConfiguration.id);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "QueueArn", queueConfiguration.queueArn);

            // Events
            if (!queueConfiguration.events.empty()) {
                std::vector<std::string> stringArray;
                for (const auto &event: queueConfiguration.events) {
                    stringArray.emplace_back(EventTypeToString(event));
                }
                Core::XmlUtils::CreateTextArray(pDoc, pQueueConfiguration, "Events", "Event", stringArray);
            }
        }

        // Topic notification configurations
        for (const auto &topicConfiguration: topicConfigurations) {

            Poco::XML::AutoPtr<Poco::XML::Element> pQueueConfiguration = Core::XmlUtils::CreateNode(pDoc, pRoot, "TopicNotification");
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Id", topicConfiguration.id);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Topic", topicConfiguration.topicArn);

            // Events
            if (!topicConfiguration.events.empty()) {
                std::vector<std::string> stringArray;
                for (const auto &event: topicConfiguration.events) {
                    stringArray.emplace_back(EventTypeToString(event));
                }
                Core::XmlUtils::CreateTextArray(pDoc, pQueueConfiguration, "Events", "Event", stringArray);
            }
        }

        // Lambda notification configurations
        for (const auto &lambdaConfiguration: lambdaConfigurations) {

            Poco::XML::AutoPtr<Poco::XML::Element> pQueueConfiguration = Core::XmlUtils::CreateNode(pDoc, pRoot, "CloudFunctionNotification");
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Id", lambdaConfiguration.id);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "CloudFunction", lambdaConfiguration.lambdaArn);

            // Events
            if (!lambdaConfiguration.events.empty()) {
                std::vector<std::string> stringArray;
                for (const auto &event: lambdaConfiguration.events) {
                    stringArray.emplace_back(EventTypeToString(event));
                }
                Core::XmlUtils::CreateTextArray(pDoc, pQueueConfiguration, "Events", "Event", stringArray);
            }
        }

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string PutBucketNotificationConfigurationResponse::ToJson() const {
        return {};
    }

    std::string PutBucketNotificationConfigurationResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutBucketNotificationConfigurationResponse &r) {
        os << "PutBucketNotificationConfigurationRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
