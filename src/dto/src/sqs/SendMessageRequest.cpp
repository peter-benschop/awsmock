//
// Created by vogje01 on 30/05/2023.
//

#include <awsmock/dto/sqs/SendMessageRequest.h>

namespace AwsMock::Dto::SQS {

    void SendMessageRequest::FromJson(const std::string &jsonString) {

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            // General
            Core::JsonUtils::GetJsonValueString("QueueUrl", rootObject, queueUrl);
            Core::JsonUtils::GetJsonValueString("MessageBody", rootObject, body);

            // User attributes
            if (rootObject->has("MessageAttributes")) {

                Poco::JSON::Object::Ptr attributesObject = rootObject->getObject("MessageAttributes");

                if (!attributesObject.isNull()) {
                    for (size_t i = 0; i < attributesObject->getNames().size(); i++) {
                        std::string attributeName = attributesObject->getNames()[i];
                        MessageAttribute attributeValue;
                        attributeValue.FromJsonObject(attributesObject->getObject(attributeName));
                        messageAttributes[attributeName] = attributeValue;
                    }
                }
            }

            // System attributes
            if (rootObject->has("MessageSystemAttributes")) {

                Poco::JSON::Object::Ptr attributesObject = rootObject->getObject("MessageSystemAttributes");

                if (!attributesObject.isNull()) {
                    for (size_t i = 0; i < attributesObject->getNames().size(); i++) {
                        auto name = attributesObject->getNames()[i];
                        auto value = attributesObject->get(name).convert<std::string>();
                        attributes[name] = value;
                    }
                }
            }
        } catch (Poco::Exception &exc) {
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string SendMessageRequest::ToJson() {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("QueueUrl", queueUrl);
            rootJson.set("MessageBody", body);

            Poco::JSON::Array jsonMessageAttributeArray;
            for (const auto &messageAttribute: messageAttributes) {
                Poco::JSON::Object jsonAttribute;
                jsonAttribute.set(messageAttribute.first, messageAttribute.second.ToJsonObject());
                jsonMessageAttributeArray.add(jsonAttribute);
            }
            rootJson.set("MessageAttributes", jsonMessageAttributeArray);

            Poco::JSON::Array jsonAttributeArray;
            for (const auto &attribute: attributes) {
                Poco::JSON::Object jsonAttribute;
                jsonAttribute.set(attribute.first, attribute.second);
                jsonMessageAttributeArray.add(jsonAttribute);
            }
            rootJson.set("Attributes", jsonMessageAttributeArray);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message(), 500);
        }
    }

    std::string SendMessageRequest::ToString() {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, SendMessageRequest &r) {
        os << "SendMessageRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::SQS
