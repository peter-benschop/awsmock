//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/Message.h>

namespace AwsMock::Dto::SQS {

    std::string Message::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Message::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("region", region);
            rootJson.set("messageId", messageId);
            rootJson.set("receiptHandle", receiptHandle);
            rootJson.set("body", body);
            rootJson.set("md5OfBody", md5Sum);
            rootJson.set("created", Core::DateTimeUtils::ToISO8601(created));
            rootJson.set("modified", Core::DateTimeUtils::ToISO8601(modified));

            if (!messageAttributes.empty()) {
                Poco::JSON::Array jsonMessageAttributeArray;
                for (const auto &messageAttribute: messageAttributes) {
                    Poco::JSON::Object jsonAttribute;
                    jsonAttribute.set(messageAttribute.first, messageAttribute.second.ToJsonObject());
                    jsonMessageAttributeArray.add(jsonAttribute);
                }
                rootJson.set("messageAttributes", jsonMessageAttributeArray);
            }

            if (!attributes.empty()) {
                Poco::JSON::Array jsonAttributeArray;
                for (const auto &attribute: attributes) {
                    Poco::JSON::Object jsonAttribute;
                    jsonAttribute.set(attribute.first, attribute.second);
                    jsonAttributeArray.add(jsonAttribute);
                }
                rootJson.set("attributes", jsonAttributeArray);
            }
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void Message::FromJson(const Poco::JSON::Object::Ptr &rootObject) {

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("Id", rootObject, id);
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
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string Message::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Message &r) {
        os << "Message=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
