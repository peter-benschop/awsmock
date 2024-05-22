//
// Created by vogje01 on 03/10/2023.
//

#include <awsmock/dto/sqs/ReceiveMessageRequest.h>

namespace AwsMock::Dto::SQS {

    void ReceiveMessageRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // Attributes
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
            Core::JsonUtils::GetJsonValueInt("MaxNumberOfMessages", rootObject, maxMessages);
            Core::JsonUtils::GetJsonValueInt("WaitTimeSeconds", rootObject, waitTimeSeconds);
            Core::JsonUtils::GetJsonValueInt("VisibilityTimeout", rootObject, visibilityTimeout);

            // Sanitize
            queueUrl = Core::SanitizeSQSUrl(queueUrl);

            // Attributes
            if (rootObject->has("AttributeNames")) {
                Poco::JSON::Array::Ptr attributes = rootObject->getArray("AttributeNames");
                for (const auto &attribute: *attributes) {
                    messageAttributeNames.emplace_back(attribute.convert<std::string>());
                }
            }

            // Message attributes
            if (rootObject->has("MessageAttributeNames")) {
                Poco::JSON::Array::Ptr messageAttributes = rootObject->getArray("MessageAttributeNames");
                for (const auto &messageAttribute: *messageAttributes) {
                    messageAttributeNames.emplace_back(messageAttribute.convert<std::string>());
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ReceiveMessageRequest::ToJson() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("QueueUrl", queueUrl);
            rootJson.set("RequestId", requestId);
            rootJson.set("MaxNumberOfMessages", maxMessages);
            rootJson.set("WaitTimeSeconds", waitTimeSeconds);
            rootJson.set("VisibilityTimeout", visibilityTimeout);

            if (!attributeNames.empty()) {
                Poco::JSON::Array jsonAttributeNamesArray;
                for (const auto &attributeName: attributeNames) {
                    jsonAttributeNamesArray.add(attributeName);
                }
            }

            if (!messageAttributeNames.empty()) {
                Poco::JSON::Array jsonMessageAttributeNamesArray;
                for (const auto &messageAttributeName: messageAttributeNames) {
                    jsonMessageAttributeNamesArray.add(messageAttributeName);
                }
            }
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message());
        }
    }

    std::string ReceiveMessageRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ReceiveMessageRequest &r) {
        os << "ReceiveMessageRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
