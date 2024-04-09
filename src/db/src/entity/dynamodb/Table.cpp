//
// Created by vogje01 on 03/09/2023.
//

#include <awsmock/entity/dynamodb/Table.h>

namespace AwsMock::Database::Entity::DynamoDb {

  view_or_value<view, value> Table::ToDocument() const {

    // Tags
    auto tagsDoc = bsoncxx::builder::basic::document{};
    if (!tags.empty()) {
      for (const auto &t : tags) {
        tagsDoc.append(kvp(t.first, t.second));
      }
    }

    // Attributes
    auto attributesDoc = bsoncxx::builder::basic::document{};
    if (!attributes.empty()) {
      for (const auto &t : attributes) {
        attributesDoc.append(kvp(t.first, t.second));
      }
    }

    // Key schemas
    auto keySchemaDoc = bsoncxx::builder::basic::document{};
    if (!keySchemas.empty()) {
      for (const auto &t : keySchemas) {
        keySchemaDoc.append(kvp(t.first, t.second));
      }
    }

    view_or_value<view, value> lambdaDoc = make_document(
        kvp("region", region),
        kvp("name", name),
        kvp("tags", tagsDoc),
        kvp("attributes", attributesDoc),
        kvp("keySchemas", keySchemaDoc),
        kvp("created",
            bsoncxx::types::b_date(std::chrono::milliseconds(created.timestamp().epochMicroseconds() / 1000))),
        kvp("modified",
            bsoncxx::types::b_date(std::chrono::milliseconds(modified.timestamp().epochMicroseconds() / 1000))));

    return lambdaDoc;
  }

  void Table::FromDocument(mongocxx::stdx::optional<bsoncxx::document::view> mResult) {

    oid = mResult.value()["_id"].get_oid().value.to_string();
    region = bsoncxx::string::to_string(mResult.value()["region"].get_string().value);
    name = bsoncxx::string::to_string(mResult.value()["name"].get_string().value);
    created = Poco::DateTime(Poco::Timestamp::fromEpochTime(
        bsoncxx::types::b_date(mResult.value()["created"].get_date().value) / 1000));
    modified = Poco::DateTime(Poco::Timestamp::fromEpochTime(
        bsoncxx::types::b_date(mResult.value()["modified"].get_date().value) / 1000));

    // Get tags
    if (mResult.value().find("tags") != mResult.value().end()) {
      bsoncxx::document::view tagsView = mResult.value()["tags"].get_document().value;
      for (bsoncxx::document::element tagElement : tagsView) {
        std::string key = bsoncxx::string::to_string(tagElement.key());
        std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
        tags.emplace(key, value);
      }
    }

    // Get attributes
    if (mResult.value().find("attributes") != mResult.value().end()) {
      bsoncxx::document::view tagsView = mResult.value()["attributes"].get_document().value;
      for (bsoncxx::document::element tagElement : tagsView) {
        std::string key = bsoncxx::string::to_string(tagElement.key());
        std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
        attributes.emplace(key, value);
      }
    }

    // Key schemas
    if (mResult.value().find("keySchemas") != mResult.value().end()) {
      bsoncxx::document::view keySchemaView = mResult.value()["keySchemas"].get_document().value;
      for (bsoncxx::document::element keySchemaElement : keySchemaView) {
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

    Poco::JSON::Array jsonTagsArray;
    for (const auto &tag : tags) {
      Poco::JSON::Object object;
      object.set("Key", tag.first);
      object.set("Value", tag.second);
      jsonTagsArray.add(object);
    }
    jsonObject.set("Tags", jsonTagsArray);

    Poco::JSON::Array jsonAttributeArray;
    for (const auto &attribute : attributes) {
      Poco::JSON::Object object;
      object.set("attributeName", attribute.first);
      object.set("AttributeType", attribute.second);
      jsonAttributeArray.add(object);
    }
    jsonObject.set("Attributes", jsonAttributeArray);

    jsonObject.set("created", Poco::DateTimeFormatter::format(created, Poco::DateTimeFormat::ISO8601_FORMAT));
    jsonObject.set("modified", Poco::DateTimeFormatter::format(modified, Poco::DateTimeFormat::ISO8601_FORMAT));

    return jsonObject;
  }

  void Table::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

    try {

      Core::JsonUtils::GetJsonValueString("region", jsonObject, region);
      Core::JsonUtils::GetJsonValueString("name", jsonObject, name);

      Poco::JSON::Array::Ptr jsonTagsArray = jsonObject->getArray("tags");
      for (int i = 0; i < jsonTagsArray->size(); i++) {
        Poco::JSON::Object::Ptr tagObject = jsonTagsArray->getObject(i);
        std::string keyStr, valueStr;
        Core::JsonUtils::GetJsonValueString("key", tagObject, keyStr);
        Core::JsonUtils::GetJsonValueString("value", tagObject, valueStr);
        tags[keyStr] = valueStr;
      }

      Poco::JSON::Array::Ptr jsonAttributesArray = jsonObject->getArray("attributes");
      for (int i = 0; i < jsonAttributesArray->size(); i++) {
        Poco::JSON::Object::Ptr attributeObject = jsonAttributesArray->getObject(i);
        std::string keyStr, valueStr;
        Core::JsonUtils::GetJsonValueString("key", attributeObject, keyStr);
        Core::JsonUtils::GetJsonValueString("value", attributeObject, valueStr);
        attributes[keyStr] = valueStr;
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

  std::ostream &operator<<(std::ostream &os, const Table &d) {
    os << "Table={oid='" << d.oid << "', region='" << d.region << "', name='" << d.name << "', attributes=[";
    for (const auto &attribute : d.attributes) {
      os << attribute.first << "='" << attribute.second << "', ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "], tags=[";
    for (const auto &tag : d.tags) {
      os << tag.first << "='" << tag.second << "', ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "], created='" << Poco::DateTimeFormatter::format(d.created, Poco::DateTimeFormat::HTTP_FORMAT)
       << "', modified='" << Poco::DateTimeFormatter::format(d.modified, Poco::DateTimeFormat::HTTP_FORMAT) << "'}";
    return os;
  }
}