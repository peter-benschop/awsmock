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
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Queue", queueConfiguration.queueArn);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Event", EventTypeToString(queueConfiguration.events.front()));
        }

        // Topic notification configurations
        for (const auto &topicConfiguration: topicConfigurations) {

            Poco::XML::AutoPtr<Poco::XML::Element> pQueueConfiguration = Core::XmlUtils::CreateNode(pDoc, pRoot, "TopicNotification");
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Id", topicConfiguration.id);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Topic", topicConfiguration.topicArn);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Event", EventTypeToString(topicConfiguration.events.front()));
        }

        // Lambda notification configurations
        for (const auto &lambdaConfiguration: lambdaConfigurations) {

            Poco::XML::AutoPtr<Poco::XML::Element> pQueueConfiguration = Core::XmlUtils::CreateNode(pDoc, pRoot, "CloudFunctionNotification");
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Id", lambdaConfiguration.id);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "CloudFunction", lambdaConfiguration.lambdaArn);
            Core::XmlUtils::CreateTextNode(pDoc, pQueueConfiguration, "Event", EventTypeToString(lambdaConfiguration.events.front()));
        }

        return Core::XmlUtils::ToXmlString(pDoc);
    }

    std::string PutBucketNotificationConfigurationResponse::ToJson() const {
        return {};
    }

    std::string PutBucketNotificationConfigurationResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutBucketNotificationConfigurationResponse &r) {
        os << "PutBucketNotificationConfigurationRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
