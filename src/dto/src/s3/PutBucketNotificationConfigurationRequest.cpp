//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/dto/s3/PutBucketNotificationConfigurationRequest.h>

namespace AwsMock::Dto::S3 {

    void PutBucketNotificationConfigurationRequest::FromXml(const std::string &xmlString) {

        try {

            boost::property_tree::ptree pt;
            Core::XmlUtils::ReadXml(xmlString, &pt);

            boost::property_tree::ptree notificationTree = pt.get_child("NotificationConfiguration");

            // SQS queues
            if (notificationTree.find("QueueConfiguration") != notificationTree.not_found()) {
                QueueConfiguration queueConfiguration;
                queueConfiguration.FromXml(notificationTree.get_child("QueueConfiguration"));
                queueConfigurations.emplace_back(queueConfiguration);
            }

            // SNS topics
            if (notificationTree.find("TopicConfiguration") != notificationTree.not_found()) {
                TopicConfiguration topicConfiguration;
                topicConfiguration.FromXml(pt.get_child("TopicConfiguration"));
                topicConfigurations.emplace_back(topicConfiguration);
            }

            // Lambdas
            if (notificationTree.find("CloudFunctionConfiguration") != notificationTree.not_found()) {
                LambdaConfiguration lambdaConfiguration;
                lambdaConfiguration.FromXml(notificationTree.get_child("CloudFunctionConfiguration"));
                lambdaConfigurations.emplace_back(lambdaConfiguration);
            }

        } catch (std::exception &e) {
            log_error << e.what();
            throw Core::JsonException(e.what());
        }
    }

    std::string PutBucketNotificationConfigurationRequest::ToJson() const {

        try {

            document rootDocument;

            // SQS queues
            if (!queueConfigurations.empty()) {
                array queueConfigurationsArray;
                for (const auto &queueConfiguration: queueConfigurations) {
                    queueConfigurationsArray.append(queueConfiguration.ToDocument());
                }
                rootDocument.append(kvp("QueueConfiguration", queueConfigurationsArray));
            }

            // SQS topics
            if (!topicConfigurations.empty()) {
                array topicConfigurationsArray;
                for (const auto &topicConfiguration: topicConfigurations) {
                    topicConfigurationsArray.append(topicConfiguration.ToDocument());
                }
                rootDocument.append(kvp("TopicConfiguration", topicConfigurationsArray));
            }

            // Lambdas
            if (!lambdaConfigurations.empty()) {
                array lambdaConfigurationsArray;
                for (const auto &lambdaConfiguration: lambdaConfigurations) {
                    lambdaConfigurationsArray.append(lambdaConfiguration.ToDocument());
                }
                rootDocument.append(kvp("CloudFunctionConfiguration", lambdaConfigurationsArray));
            }
            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
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
