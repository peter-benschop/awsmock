//
// Created by vogje01 on 01/06/2023.
//

#include <awsmock/entity/sns/Message.h>

namespace AwsMock::Database::Entity::SNS {

    view_or_value<view, value> Message::ToDocument() const {

        auto messageAttributesDoc = bsoncxx::builder::basic::array{};
        for (const auto &attribute: attributes) {
            messageAttributesDoc.append(attribute.ToDocument());
        }

        // Mandatory fields
        bsoncxx::builder::basic::document messageDoc;
        messageDoc.append(kvp("region", region),
                          kvp("topicArn", topicArn),
                          kvp("targetArn", targetArn),
                          kvp("message", message),
                          kvp("messageId", messageId),
                          kvp("size", size),
                          kvp("status", MessageStatusToString(status)),
                          kvp("userAttributes", messageAttributesDoc),
                          kvp("reset", bsoncxx::types::b_null()));

        if (lastSend.time_since_epoch().count() != 0) {
            messageDoc.append(kvp("lastSend", bsoncxx::types::b_date(lastSend)));
        }
        if (created.time_since_epoch().count() != 0) {
            messageDoc.append(kvp("created", bsoncxx::types::b_date(created)));
        }
        if (modified.time_since_epoch().count() != 0) {
            messageDoc.append(kvp("modified", bsoncxx::types::b_date(modified)));
        }
        return messageDoc.extract();
    }

    void Message::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        try {
            oid = mResult.value()["_id"].get_oid().value.to_string();
            region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
            topicArn = bsoncxx::string::to_string(mResult.value()["topicArn"].get_string().value);
            targetArn = bsoncxx::string::to_string(mResult.value()["targetArn"].get_string().value);
            message = bsoncxx::string::to_string(mResult.value()["message"].get_string().value);
            status = MessageStatusFromString(bsoncxx::string::to_string(mResult.value()["status"].get_string().value));
            messageId = bsoncxx::string::to_string(mResult.value()["messageId"].get_string().value);
            size = mResult.value()["size"].get_int64().value;

            if (mResult.value().find("lastSend") != mResult.value().end()) {
                lastSend = bsoncxx::types::b_date(mResult.value()["lastSend"].get_date());
            }
            if (mResult.value().find("created") != mResult.value().end()) {
                created = bsoncxx::types::b_date(mResult.value()["created"].get_date());
            }
            if (mResult.value().find("modified") != mResult.value().end()) {
                modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date());
            }

            if (mResult.value().find("userAttributes") != mResult.value().end()) {
                bsoncxx::array::view attributesView{mResult.value()["userAttributes"].get_array().value};
                if (!attributesView.empty()) {
                    for (const bsoncxx::array::element &attributeElement: attributesView) {
                        MessageAttribute attribute{
                                .attributeName = bsoncxx::string::to_string(attributeElement["attributeName"].get_string().value),
                                .attributeValue = bsoncxx::string::to_string(attributeElement["attributeValue"].get_string().value)};
                        attributes.push_back(attribute);
                    }
                }
            }
        } catch (std::exception &exc) {
            log_error << "SNS message exception: " << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    Poco::JSON::Object Message::ToJsonObject() const {

        try {

            Poco::JSON::Object jsonObject;
            Core::JsonUtils::SetJsonValueString(jsonObject, "region", region);
            Core::JsonUtils::SetJsonValueString(jsonObject, "topicArn", topicArn);
            Core::JsonUtils::SetJsonValueString(jsonObject, "targetArn", targetArn);
            Core::JsonUtils::SetJsonValueString(jsonObject, "message", message);
            Core::JsonUtils::SetJsonValueString(jsonObject, "status", MessageStatusToString(status));
            Core::JsonUtils::SetJsonValueString(jsonObject, "messageId", messageId);
            if (lastSend.time_since_epoch().count() > 0) {
                Core::JsonUtils::SetJsonValueDate(jsonObject, "lastSend", lastSend);
            }
            if (created.time_since_epoch().count() > 0) {
                Core::JsonUtils::SetJsonValueDate(jsonObject, "created", created);
            }
            if (modified.time_since_epoch().count() > 0) {
                Core::JsonUtils::SetJsonValueDate(jsonObject, "modified", modified);
            }

            // Attributes
            if (!attributes.empty()) {
                Poco::JSON::Array jsonAttributeArray;
                for (const auto &attribute: attributes) {
                    jsonAttributeArray.add(attribute.ToJsonObject());
                }
                jsonObject.set("attributes", jsonAttributeArray);
            }
            return jsonObject;

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    void Message::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {
            Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("topicArn", jsonObject, topicArn);
            Core::JsonUtils::GetJsonValueString("targetArn", jsonObject, targetArn);
            Core::JsonUtils::GetJsonValueString("message", jsonObject, message);
            Core::JsonUtils::GetJsonValueString("messageId", jsonObject, messageId);
            std::string statusStr;
            Core::JsonUtils::GetJsonValueString("status", jsonObject, statusStr);
            status = MessageStatusFromString(statusStr);

            // Message attributes
            Poco::JSON::Array::Ptr jsonAttributeArray = jsonObject->getArray("messageAttributes");
            for (int i = 0; i < jsonAttributeArray->size(); i++) {
                MessageAttribute messageAttribute;
                Poco::JSON::Object::Ptr jsonAttributeObject = jsonAttributeArray->getObject(i);
                Core::JsonUtils::GetJsonValueString("name", jsonAttributeObject, messageAttribute.attributeName);
                Core::JsonUtils::GetJsonValueString("value", jsonAttributeObject, messageAttribute.attributeValue);
                attributes.emplace_back(messageAttribute);
            }

        } catch (Poco::Exception &e) {
            log_error << e.message();
            throw Core::JsonException(e.message());
        }
    }

    std::string Message::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Message &message) {
        os << "Message=" << bsoncxx::to_json(message.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SNS
