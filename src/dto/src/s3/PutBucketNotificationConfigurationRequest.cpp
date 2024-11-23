//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/PutBucketNotificationConfigurationRequest.h>

namespace AwsMock::Dto::S3 {

    void PutBucketNotificationConfigurationRequest::FromXml(const std::string &xmlString) {

        log_debug << "FromXML: " << xmlString;

        Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *rootNode = pDoc->getNodeByPath("/NotificationConfiguration");
        if (rootNode) {
            Poco::XML::NodeList *childNodes = rootNode->childNodes();
            if (childNodes) {
                for (int i = 0; i < childNodes->length(); i++) {
                    Poco::XML::Node *childNode = childNodes->item(i);
                    if (childNode->nodeName() == "QueueConfiguration") {
                        QueueConfiguration queueConfiguration;
                        queueConfiguration.FromXmlNode(childNode);
                        queueConfigurations.emplace_back(queueConfiguration);
                    } else if (childNode->nodeName() == "TopicConfiguration") {
                        TopicConfiguration topicConfiguration;
                        topicConfiguration.FromXmlNode(childNode);
                        topicConfigurations.emplace_back(topicConfiguration);
                    } else if (childNode->nodeName() == "CloudFunctionConfiguration") {
                        LambdaConfiguration lambdaConfiguration;
                        lambdaConfiguration.FromXmlNode(childNode);
                        lambdaConfigurations.emplace_back(lambdaConfiguration);
                    }
                }
            }
        }
    }

    std::string PutBucketNotificationConfigurationRequest::ToJson() const {
        return {};
    }

    std::string PutBucketNotificationConfigurationRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutBucketNotificationConfigurationRequest &r) {
        os << "PutBucketNotificationConfigurationRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::S3
