//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/PutBucketNotificationConfigurationResponse.h>

namespace AwsMock::Dto::S3 {

    std::string PutBucketNotificationConfigurationResponse::ToXml() const {

        /*Poco::XML::DOMParser parser;
        Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

        Poco::XML::Node *cloudNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration");
        if (cloudNode) {
            Poco::XML::Node *idNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Id");
            notificationId = idNode->innerText();

            Poco::XML::Node *functionNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/CloudFunction");
            lambdaArn = functionNode->innerText();

            Poco::XML::Node *eventNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Event");
            event = eventNode->innerText();
        }

        Poco::XML::Node *queueNodes = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfigurations");
        if (queueNodes) {

            for (int i = 0; i < queueNodes->childNodes()->length(); i++) {
                Poco::XML::Node *queueNode = queueNodes->childNodes()->item(i);
                QueueConfiguration queueConfiguration;
                //queueConfiguration.FromXml(queueNode);
                queueConfigurations.emplace_back(queueConfiguration);
            }
        }*/
        return {};
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
