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

    bool Message::HasAttribute(const std::string &key) {
        return find_if(attributes.begin(), attributes.end(), [key](const std::pair<std::string, std::string> &attribute) {
                   return attribute.first == key;
               }) != attributes.end();
    }

    int Message::GetIntAttribute(const std::string &key) {
        if (HasAttribute(key)) {
            auto it =
                    find_if(attributes.begin(), attributes.end(), [key](const std::pair<std::string, std::string> &attribute) {
                        return attribute.first == key;
                    });
            return std::stoi(it->second);
        }
        return -1;
    }

    view_or_value<view, value> Message::ToDocument() const {

        auto messageAttributesDoc = bsoncxx::builder::basic::array{};
        for (const auto &messageAttribute: messageAttributes) {
            messageAttributesDoc.append(messageAttribute.ToDocument());
        }

        auto attributesDoc = bsoncxx::builder::basic::document{};
        for (const auto &attribute: attributes) {
            attributesDoc.append(kvp(attribute.first, attribute.second));
        }

        auto messageDoc = bsoncxx::builder::basic::document{};

        messageDoc.append(kvp("queueArn", queueArn));
        messageDoc.append(kvp("queueName", queueName));
        messageDoc.append(kvp("body", body));
        messageDoc.append(kvp("status", MessageStatusToString(status)));
        messageDoc.append(kvp("retries", retries));
        messageDoc.append(kvp("size", size));
        messageDoc.append(kvp("messageId", messageId));
        messageDoc.append(kvp("receiptHandle", receiptHandle));
        messageDoc.append(kvp("md5Body", md5Body));
        messageDoc.append(kvp("md5UserAttr", md5UserAttr));
        messageDoc.append(kvp("md5SystemAttr", md5SystemAttr));
        messageDoc.append(kvp("contentType", contentType));
        messageDoc.append(kvp("attributes", attributesDoc));
        messageDoc.append(kvp("messageAttributes", messageAttributesDoc));
        if (reset.time_since_epoch().count() > 0) {
            messageDoc.append(kvp("reset", bsoncxx::types::b_date(reset)));
        }
        if (created.time_since_epoch().count() > 0) {
            messageDoc.append(kvp("created", bsoncxx::types::b_date(created)));
        }
        if (modified.time_since_epoch().count() > 0) {
            messageDoc.append(kvp("modified", bsoncxx::types::b_date(modified)));
        }

        return messageDoc.extract();
    }

    void Message::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        queueArn = bsoncxx::string::to_string(mResult.value()["queueArn"].get_string().value);
        queueName = bsoncxx::string::to_string(mResult.value()["queueName"].get_string().value);
        body = bsoncxx::string::to_string(mResult.value()["body"].get_string().value);
        status = MessageStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
        retries = mResult.value()["retries"].get_int32().value;
        messageId = bsoncxx::string::to_string(mResult.value()["messageId"].get_string().value);
        receiptHandle = bsoncxx::string::to_string(mResult.value()["receiptHandle"].get_string().value);
        md5Body = bsoncxx::string::to_string(mResult.value()["md5Body"].get_string().value);
        md5UserAttr = bsoncxx::string::to_string(mResult.value()["md5UserAttr"].get_string().value);
        md5SystemAttr = bsoncxx::string::to_string(mResult.value()["md5SystemAttr"].get_string().value);
        contentType = bsoncxx::string::to_string(mResult.value()["contentType"].get_string().value);
        if (mResult.value()["reset"].type() != bsoncxx::type::k_null) {
            reset = bsoncxx::types::b_date(mResult.value()["reset"].get_date());
        }
        size = mResult.value()["size"].get_int64().value;
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date());
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date());

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

        using Core::JsonUtils;

        try {

            Poco::JSON::Object jsonObject;
            JsonUtils::SetJsonValueString(jsonObject, "queueArn", queueArn);
            JsonUtils::SetJsonValueString(jsonObject, "queueName", queueName);
            JsonUtils::SetJsonValueString(jsonObject, "body", body);
            JsonUtils::SetJsonValueString(jsonObject, "status", MessageStatusToString(status));
            JsonUtils::SetJsonValueString(jsonObject, "messageId", messageId);
            JsonUtils::SetJsonValueString(jsonObject, "receiptHandle", receiptHandle);
            JsonUtils::SetJsonValueString(jsonObject, "md5Body", md5Body);
            JsonUtils::SetJsonValueString(jsonObject, "md5UserAttr", md5UserAttr);
            JsonUtils::SetJsonValueString(jsonObject, "md5SystemAttr", md5SystemAttr);
            JsonUtils::SetJsonValueString(jsonObject, "contentType", contentType);
            JsonUtils::SetJsonValueDate(jsonObject, "reset", reset);
            JsonUtils::SetJsonValueDate(jsonObject, "created", created);
            JsonUtils::SetJsonValueDate(jsonObject, "modified", modified);

            // Message attributes
            if (!messageAttributes.empty()) {
                Poco::JSON::Object jsonMessageAttributeObject;
                for (const auto &attribute: messageAttributes) {
                    Poco::JSON::Object jsonAttributeObject;
                    JsonUtils::SetJsonValueString(jsonAttributeObject, "StringValue", attribute.attributeValue);
                    JsonUtils::SetJsonValueString(jsonAttributeObject, "DataType", MessageAttributeTypeToString(attribute.attributeType));
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
            Core::JsonUtils::GetJsonValueString("queueArn", jsonObject, queueArn);
            Core::JsonUtils::GetJsonValueString("queueName", jsonObject, queueName);
            Core::JsonUtils::GetJsonValueString("body", jsonObject, body);
            Core::JsonUtils::GetJsonValueString("messageId", jsonObject, messageId);
            Core::JsonUtils::GetJsonValueString("receiptHandle", jsonObject, receiptHandle);
            Core::JsonUtils::GetJsonValueString("md5Body", jsonObject, md5Body);
            Core::JsonUtils::GetJsonValueString("md5UserAttr", jsonObject, md5UserAttr);
            Core::JsonUtils::GetJsonValueString("md5SystemAttr", jsonObject, md5SystemAttr);
            Core::JsonUtils::GetJsonValueString("contentType", jsonObject, contentType);
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
