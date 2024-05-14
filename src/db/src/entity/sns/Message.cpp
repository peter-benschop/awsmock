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

        view_or_value<view, value> messageDoc = make_document(
                kvp("region", region),
                kvp("topicArn", topicArn),
                kvp("targetArn", targetArn),
                kvp("message", message),
                kvp("messageId", messageId),
                kvp("status", MessageStatusToString(status)),
                kvp("userAttributes", messageAttributesDoc),
                kvp("reset", bsoncxx::types::b_date(std::chrono::milliseconds(0))),
                kvp("created", MongoUtils::ToBson(created)),
                kvp("modified", MongoUtils::ToBson(modified)));
        return messageDoc;
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
            lastSend = MongoUtils::FromBson(mResult.value()["reset"].get_date());
            created = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["created"].get_date()));
            modified = MongoUtils::FromBson(bsoncxx::types::b_date(mResult.value()["modified"].get_date()));

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
        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("topicArn", topicArn);
        jsonObject.set("targetArn", targetArn);
        jsonObject.set("message", message);
        jsonObject.set("status", MessageStatusToString(status));
        jsonObject.set("messageId", messageId);
        jsonObject.set("lastSend", Poco::DateTimeFormatter::format(lastSend, Poco::DateTimeFormat::ISO8601_FORMAT));

        // Attributes
        if (!attributes.empty()) {
            Poco::JSON::Array jsonAttributeArray;
            for (const auto &attribute: attributes) {
                jsonAttributeArray.add(attribute.ToJsonObject());
            }
            jsonObject.set("attributes", jsonAttributeArray);
        }
        return jsonObject;
    }

    void Message::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

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
    }

    std::string Message::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Message &message) {
        os << "Message=" << bsoncxx::to_json(message.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::SNS
