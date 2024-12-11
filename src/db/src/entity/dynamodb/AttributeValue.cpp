//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/entity/dynamodb/AttributeValue.h>

namespace AwsMock::Database::Entity::DynamoDb {

    view_or_value<view, value> AttributeValue::ToDocument() const {

        auto attributeDoc = document{};
        attributeDoc.append(
                kvp("S", stringValue),
                kvp("N", numberValue),
                kvp("BOOL", boolValue),
                kvp("NULL", nullValue),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));

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
            auto numberSetDoc = bsoncxx::builder::basic::array{};
            for (const auto &nValue: numberSetValue) {
                numberSetDoc.append(nValue);
            }
            attributeDoc.append(kvp("NS", numberSetDoc));
        }
        return attributeDoc.extract();
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
