//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/PutBucketNotificationConfigurationResponse.h>

namespace AwsMock::Dto::S3 {

    std::string PutBucketNotificationConfigurationResponse::ToXml() {

        try {
            boost::property_tree::ptree root;

            // Queue notification configurations
            for (const auto &queueConfiguration: queueConfigurations) {

                boost::property_tree::ptree xmlQueueNotification;
                xmlQueueNotification.add("Id", queueConfiguration.id);
                xmlQueueNotification.add("QueueArn", queueConfiguration.queueArn);

                // Events
                if (!queueConfiguration.events.empty()) {
                    boost::property_tree::ptree xmlEventArray;
                    for (const auto &event: queueConfiguration.events) {
                        std::string strEvent = EventTypeToString(event);
                        xmlEventArray.push_back(boost::property_tree::basic_ptree<std::string, std::string>::value_type(std::make_pair("", strEvent)));
                    }
                    xmlQueueNotification.add_child("Events", xmlEventArray);
                }
                root.add_child("NotificationConfiguration.QueueConfiguration", xmlQueueNotification);
            }
            /*
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
*/
            return Core::XmlUtils::ToXmlString(root);
        } catch (std::exception &e) {
            log_error << e.what();
            throw Core::JsonException(e.what());
        }
    }

    std::string PutBucketNotificationConfigurationResponse::ToJson() const {

        try {
            document document;
            if (queueConfigurations.empty()) {
                array queueArray;
                for (const auto &queueConfiguration: queueConfigurations) {
                    queueArray.append(queueConfiguration.ToDocument());
                }
                document.append(kvp("NotificationConfigurations", queueArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &e) {
            log_error << e.what();
            throw Core::JsonException(e.what());
        }
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
