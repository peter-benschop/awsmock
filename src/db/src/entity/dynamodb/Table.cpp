//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/dynamodb/Table.h>

namespace AwsMock::Database::Entity::DynamoDb {

    view_or_value<view, value> Table::ToDocument() const {

        try {

            bsoncxx::builder::basic::document tableDoc;
            tableDoc.append(
                    kvp("region", region),
                    kvp("name", name),
                    kvp("status", status),
                    kvp("created", bsoncxx::types::b_date(created)),
                    kvp("modified", bsoncxx::types::b_date(modified)));

            // Tags
            if (!tags.empty()) {
                auto tagsDoc = bsoncxx::builder::basic::document{};
                for (const auto &t: tags) {
                    tagsDoc.append(kvp(t.first, t.second));
                }
                tableDoc.append(kvp("tags", tagsDoc));
            }

            // Attributes
            if (!attributes.empty()) {
                auto attributesDoc = bsoncxx::builder::basic::document{};
                for (const auto &t: attributes) {
                    attributesDoc.append(kvp(t.first, t.second));
                }
                tableDoc.append(kvp("attributes", attributesDoc));
            }

            // Key schemas
            if (!keySchemas.empty()) {
                auto keySchemaDoc = bsoncxx::builder::basic::document{};
                for (const auto &t: keySchemas) {
                    keySchemaDoc.append(kvp(t.first, t.second));
                }
                tableDoc.append(kvp("keySchemas", keySchemaDoc));
            }
            return tableDoc.extract();

        } catch (mongocxx::exception &e) {
            log_error << e.what();
            throw Core::DatabaseException(e.what());
        }
    }

    void Table::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

        oid = mResult.value()["_id"].get_oid().value.to_string();
        region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
        name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
        status = bsoncxx::string::to_string(mResult.value()["status"].get_string().value);
        created = bsoncxx::types::b_date(mResult.value()["created"].get_date().value);
        modified = bsoncxx::types::b_date(mResult.value()["modified"].get_date().value);

        // Get tags
        if (mResult.value().find("tags") != mResult.value().end()) {
            bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
            for (const bsoncxx::document::element &tagElement: tagsView) {
                std::string key = bsoncxx::string::to_string(tagElement.key());
                std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                tags.emplace(key, value);
            }
        }

        // Get attributes
        if (mResult.value().find("attributes") != mResult.value().end()) {
            bsoncxx::document::view tagsView = mResult.value()["attributes"].get_document().value;
            for (const bsoncxx::document::element &tagElement: tagsView) {
                std::string key = bsoncxx::string::to_string(tagElement.key());
                std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                attributes.emplace(key, value);
            }
        }

        // Key schemas
        if (mResult.value().find("keySchemas") != mResult.value().end()) {
            bsoncxx::document::view keySchemaView = mResult.value()["keySchemas"].get_document().value;
            for (const bsoncxx::document::element &keySchemaElement: keySchemaView) {
                std::string key = bsoncxx::string::to_string(keySchemaElement.key());
                std::string value = bsoncxx::string::to_string(keySchemaView[key].get_string().value);
                keySchemas.emplace(key, value);
            }
        }
    }

    Poco::JSON::Object Table::ToJsonObject() const {

        Poco::JSON::Object jsonObject;
        jsonObject.set("region", region);
        jsonObject.set("name", name);

        // Tags
        if (!tags.empty()) {
            Poco::JSON::Array jsonTagsArray;
            for (const auto &tag: tags) {
                Poco::JSON::Object object;
                object.set("key", tag.first);
                object.set("value", tag.second);
                jsonTagsArray.add(object);
            }
            jsonObject.set("tags", jsonTagsArray);
        }

        // Attributes
        if (!attributes.empty()) {
            Poco::JSON::Array jsonAttributeArray;
            for (const auto &attribute: attributes) {
                Poco::JSON::Object object;
                object.set("attributeName", attribute.first);
                object.set("attributeType", attribute.second);
                jsonAttributeArray.add(object);
            }
            jsonObject.set("attributes", jsonAttributeArray);
        }

        // Key-schemas
        if (!keySchemas.empty()) {
            Poco::JSON::Array jsonKeySchemasArray;
            for (const auto &keySchema: keySchemas) {
                Poco::JSON::Object object;
                object.set("attributeName", keySchema.first);
                object.set("keyType", keySchema.second);
                jsonKeySchemasArray.add(object);
            }
            jsonObject.set("keySchemas", jsonKeySchemasArray);
        }

        jsonObject.set("created", Core::DateTimeUtils::ISO8601(created));
        jsonObject.set("modified", Core::DateTimeUtils::ISO8601(modified));

        return jsonObject;
    }

    std::string Table::ToJson() const {
        return bsoncxx::to_json(ToDocument());
    }

    void Table::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
            Core::JsonUtils::GetJsonValueString("name", jsonObject, name);

            // Tags
            if (jsonObject->has("tags")) {
                Poco::JSON::Array::Ptr jsonTagsArray = jsonObject->getArray("tags");
                for (int i = 0; i < jsonTagsArray->size(); i++) {
                    Poco::JSON::Object::Ptr tagObject = jsonTagsArray->getObject(i);
                    std::string keyStr, valueStr;
                    Core::JsonUtils::GetJsonValueString("key", tagObject, keyStr);
                    Core::JsonUtils::GetJsonValueString("value", tagObject, valueStr);
                    tags[keyStr] = valueStr;
                }
            }

            // Attributes
            if (jsonObject->has("attributes")) {
                Poco::JSON::Array::Ptr jsonAttributesArray = jsonObject->getArray("attributes");
                for (int i = 0; i < jsonAttributesArray->size(); i++) {
                    Poco::JSON::Object::Ptr attributeObject = jsonAttributesArray->getObject(i);
                    std::string keyStr, valueStr;
                    Core::JsonUtils::GetJsonValueString("attributeName", attributeObject, keyStr);
                    Core::JsonUtils::GetJsonValueString("attributeValue", attributeObject, valueStr);
                    attributes[keyStr] = valueStr;
                }
            }

            // Key schemas
            if (jsonObject->has("keySchemas")) {
                Poco::JSON::Array::Ptr jsonAttributesArray = jsonObject->getArray("keySchemas");
                for (int i = 0; i < jsonAttributesArray->size(); i++) {
                    Poco::JSON::Object::Ptr attributeObject = jsonAttributesArray->getObject(i);
                    std::string attributeNameStr, keyTypeStr;
                    Core::JsonUtils::GetJsonValueString("attributeName", attributeObject, attributeNameStr);
                    Core::JsonUtils::GetJsonValueString("keyType", attributeObject, keyTypeStr);
                    keySchemas[attributeNameStr] = keyTypeStr;
                }
            }

            Core::JsonUtils::GetJsonValueDate("created", jsonObject, created);
            Core::JsonUtils::GetJsonValueDate("modified", jsonObject, modified);

        } catch (Poco::Exception &exc) {
        }
    }

    std::string Table::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const Table &t) {
        os << "Table=" << bsoncxx::to_json(t.ToDocument());
        return os;
    }
}// namespace AwsMock::Database::Entity::DynamoDb