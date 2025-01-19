//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/entity/dynamodb/AttributeValue.h>

namespace AwsMock::Database::Entity::DynamoDb {

    view_or_value<view, value> AttributeValue::ToDocument() const {

        auto attributeDoc = document{};
        Core::Bson::BsonUtils::SetStringValue(attributeDoc, "S", stringValue);
        Core::Bson::BsonUtils::SetStringValue(attributeDoc, "N", numberValue);
        Core::Bson::BsonUtils::SetBoolValue(attributeDoc, "BOOL", boolValue);
        Core::Bson::BsonUtils::SetBoolValue(attributeDoc, "NULL", nullValue);

        // Convert string set to document
        if (!stringSetValue.empty()) {
            auto stringSetDoc = array{};
            for (const auto &sValue: stringSetValue) {
                stringSetDoc.append(sValue);
            }
            attributeDoc.append(kvp("SS", stringSetDoc));
        }

        // Convert number set to document
        if (!numberSetValue.empty()) {
            auto numberSetDoc = array{};
            for (const auto &nValue: numberSetValue) {
                numberSetDoc.append(nValue);
            }
            attributeDoc.append(kvp("NS", numberSetDoc));
        }
        return attributeDoc.extract();
    }

    void AttributeValue::FromDocument(view_or_value<view, value> mResult) {
        stringValue = Core::Bson::BsonUtils::GetStringValue(mResult, "S");
        numberValue = Core::Bson::BsonUtils::GetStringValue(mResult, "N");
        boolValue = Core::Bson::BsonUtils::GetBoolValue(mResult, "BOOL");
        nullValue = Core::Bson::BsonUtils::GetBoolValue(mResult, "NULL");
    }

    std::string AttributeValue::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AttributeValue &r) {
        os << "AttributeValue=" << to_json(r.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::DynamoDb
