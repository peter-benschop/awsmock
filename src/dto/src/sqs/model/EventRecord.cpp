//
// Created by vogje01 on 7/6/24.
//

#include <awsmock/dto/sqs/model/EventRecord.h>

namespace AwsMock::Dto::SQS {

    std::string Record::ToJson() const {

        try {

            return Core::JsonUtils::ToJsonString(ToJsonObject());

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    Poco::JSON::Object Record::ToJsonObject() const {

        try {

            Poco::JSON::Object rootJson;
            rootJson.set("awsRegion", region);
            rootJson.set("messageId", messageId);
            rootJson.set("receiptHandle", receiptHandle);
            rootJson.set("body", body);
            rootJson.set("md5OfBody", md5Sum);
            rootJson.set("eventSource", eventSource);
            rootJson.set("eventSourceARN", eventSourceArn);

            if (!messagesAttributes.empty()) {
                Poco::JSON::Array jsonMessageAttributeArray;
                for (const auto &messageAttribute: messagesAttributes) {
                    Poco::JSON::Object jsonAttribute;
                    jsonAttribute.set(messageAttribute.first, messageAttribute.second.ToJsonObject());
                    jsonMessageAttributeArray.add(jsonAttribute);
                }
                rootJson.set("messageAttributes", jsonMessageAttributeArray);
            }

            if (!attributes.empty()) {
                Poco::JSON::Object jsonAttributeObject;
                for (const auto &attribute: attributes) {
                    jsonAttributeObject.set(attribute.first, attribute.second);
                }
                rootJson.set("attributes", jsonAttributeObject);
            }
            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void Record::FromJson(const Poco::JSON::Object::Ptr &object) {

        try {

            Core::JsonUtils::GetJsonValueString("awsRegion", object, region);
            Core::JsonUtils::GetJsonValueString("messageId", object, messageId);
            Core::JsonUtils::GetJsonValueString("receiptHandle", object, receiptHandle);
            Core::JsonUtils::GetJsonValueString("body", object, body);
            Core::JsonUtils::GetJsonValueString("md5OfBody", object, md5Sum);
            Core::JsonUtils::GetJsonValueString("eventSource", object, eventSource);
            Core::JsonUtils::GetJsonValueString("eventSourceArn", object, eventSourceArn);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    [[nodiscard]] std::string Record::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Record &r) {
        os << "Record=" + r.ToJson();
        return os;
    }
};// namespace AwsMock::Dto::SQS
