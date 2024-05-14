//
// Created by vogje01 on 24/09/2023.
//

#include <awsmock/entity/sqs/Message.h>

namespace AwsMock::Database::Entity::SQS {

    using bsoncxx::view_or_value;
    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::document::value;
    using bsoncxx::document::view;

    view_or_value<view, value> Message::ToDocument() const {

        auto messageAttributesDoc = bsoncxx::builder::basic::array{};
        for (const auto &messageAttribute: messageAttributes) {
            messageAttributesDoc.append(messageAttribute.ToDocument());
        }

        auto attributesDoc = bsoncxx::builder::basic::document{};
        for (const auto &attribute: attributes) {
            attributesDoc.append(kvp(attribute.first, attribute.second));
        }

        view_or_value<view, value> messageDoc = make_document(
                kvp("region", region),
                kvp("queueUrl", queueUrl),
                kvp("body", body),
                kvp("status", MessageStatusToString(status)),
                kvp("retries", retries),
                kvp("messageId", messageId),
                kvp("receiptHandle", receiptHandle),
                kvp("md5Body", md5Body),
                kvp("md5UserAttr", md5UserAttr),
                kvp("md5SystemAttr", md5SystemAttr),
                kvp("attributes", attributesDoc),
                kvp("messageAttributes", messageAttributesDoc),
                kvp("reset", MongoUtils::ToBson(reset)),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));

        return messageDoc;
    }

    void Message::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        queueUrl = bsoncxx::string::to_string(mResult.value()["queueUrl"].get_string().value);
        body = bsoncxx::string::to_string(mResult.value()["body"].get_string().value);
        status = MessageStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
        retries = mResult.value()["retries"].get_int32().value;
        messageId = bsoncxx::string::to_string(mResult.value()["messageId"].get_string().value);
        receiptHandle = bsoncxx::string::to_string(mResult.value()["receiptHandle"].get_string().value);
        md5Body = bsoncxx::string::to_string(mResult.value()["md5Body"].get_string().value);
        md5UserAttr = bsoncxx::string::to_string(mResult.value()["md5UserAttr"].get_string().value);
        md5SystemAttr = bsoncxx::string::to_string(mResult.value()["md5SystemAttr"].get_string().value);
        if (mResult.value()["reset"].type() != bsoncxx::type::k_null) {
            reset = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["reset"].get_date()));
        }
        created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date()));
        modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date()));

        // Attributes
        if (mResult.value().find("messageAttributes") != mResult.value().end()) {
            bsoncxx::array::view attributesView{mResult.value()["messageAttributes"].get_array().value};
            for (const bsoncxx::array::element &attributeElement: attributesView) {
                MessageAttribute attribute{
                        .attributeName = bsoncxx::string::to_string(attributeElement["attributeName"].get_string().value),
                        .attributeValue = bsoncxx::string::to_string(attributeElement["attributeValue"].get_string().value),
                        .attributeType = Database::Entity::SQS::MessageAttributeTypeFromString(bsoncxx::string::to_string(attributeElement["attributeType"].get_string().value)),
                };
                messageAttributes.push_back(attribute);
            }
        }

        // Get attributes
        if (mResult.value().find("attributes") != mResult.value().end()) {
            bsoncxx::document::view attributesView = mResult.value()["attributes"].get_document().value;
            for (const bsoncxx::document::element &attributeElement: attributesView) {
                std::string key = bsoncxx::string::to_string(attributeElement.key());
                std::string value = bsoncxx::string::to_string(attributesView[key].get_string().value);
                attributes.emplace(key, value);
            }
        }
    }

    Poco::JSON::Object Message::ToJsonObject() const {
        try {
            Poco::JSON::Object jsonObject;
            jsonObject.set("region", region);
            jsonObject.set("queueUrl", queueUrl);
            jsonObject.set("body", body);
            jsonObject.set("status", MessageStatusToString(status));
            jsonObject.set("messageId", messageId);
            jsonObject.set("receiptHandle", receiptHandle);
            jsonObject.set("md5Body", md5Body);
            jsonObject.set("md5UserAttr", md5UserAttr);
            jsonObject.set("md5SystemAttr", md5SystemAttr);
            jsonObject.set("reset", Poco::DateTimeFormatter::format(reset, Poco::DateTimeFormat::ISO8601_FORMAT));

            // Message attributes
            if (!messageAttributes.empty()) {
                Poco::JSON::Object jsonMessageAttributeObject;
                for (const auto &attribute: messageAttributes) {
                    Poco::JSON::Object jsonAttributeObject;
                    jsonAttributeObject.set("StringValue", attribute.attributeValue);
                    jsonAttributeObject.set("DataType", attribute.attributeType);
                    jsonMessageAttributeObject.set(attribute.attributeName, jsonAttributeObject);
                }
                jsonObject.set("MessageAttributes", jsonMessageAttributeObject);
            }

            // Attributes
            if (!attributes.empty()) {
                Poco::JSON::Array jsonAttributeArray;
                for (const auto &attribute: attributes) {
                    Poco::JSON::Object jsonAttributeObject;
                    jsonAttributeObject.set(attribute.first, attribute.second);
                    jsonAttributeArray.add(jsonAttributeObject);
                }
                jsonObject.set("attributes", jsonAttributeArray);
            }
            return jsonObject;
        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    void Message::FromJsonObject(Poco::JSON::Object::Ptr jsonObject) {

        try {
            Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("queueUrl", jsonObject, queueUrl);
            Core::JsonUtils::GetJsonValueString("body", jsonObject, body);
            Core::JsonUtils::GetJsonValueString("messageId", jsonObject, messageId);
            Core::JsonUtils::GetJsonValueString("receiptHandle", jsonObject, receiptHandle);
            Core::JsonUtils::GetJsonValueString("md5Body", jsonObject, md5Body);
            Core::JsonUtils::GetJsonValueString("md5UserAttr", jsonObject, md5UserAttr);
            Core::JsonUtils::GetJsonValueString("md5SystemAttr", jsonObject, md5SystemAttr);
            Core::JsonUtils::GetJsonValueDate("reset", jsonObject, reset);
            std::string statusStr;
            Core::JsonUtils::GetJsonValueString("status", jsonObject, statusStr);
            status = MessageStatusFromString(statusStr);

            // Attributes
            Poco::JSON::Array::Ptr jsonAttributeArray = jsonObject->getArray("attributes");
            for (int i = 0; i < jsonAttributeArray->size(); i++) {
                std::string key, value;
                Poco::JSON::Object::Ptr jsonAttributeObject = jsonAttributeArray->getObject(i);
                Core::JsonUtils::GetJsonValueString("name", jsonAttributeObject, key);
                Core::JsonUtils::GetJsonValueString("value", jsonAttributeObject, value);
                attributes[key] = value;
            }

            // Message attributes
            Poco::JSON::Array::Ptr jsonMessageAttributeArray = jsonObject->getArray("messageAttributes");
            for (int i = 0; i < jsonMessageAttributeArray->size(); i++) {
                MessageAttribute messageAttribute;
                Poco::JSON::Object::Ptr jsonAttributeObject = jsonAttributeArray->getObject(i);
                Core::JsonUtils::GetJsonValueString("name", jsonAttributeObject, messageAttribute.attributeName);
                Core::JsonUtils::GetJsonValueString("value", jsonAttributeObject, messageAttribute.attributeValue);
                attributes[messageAttribute.attributeName] = messageAttribute.attributeValue;
            }
        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    std::string Message::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Message &m) {
        os << "Message=" << bsoncxx::to_json(m.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SQS
