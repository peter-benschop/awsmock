//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/entity/dynamodb/AttributeValue.h>

namespace AwsMock::Database::Entity::DynamoDb {

    Poco::JSON::Object AttributeValue::ToJsonObject() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("S", stringValue);
            rootJson.set("N", numberValue);
            rootJson.set("BOOL", boolValue);
            rootJson.set("NULL", nullValue);

            // String array
            if (!stringSetValue.empty()) {
                Poco::JSON::Array jsonStringArray;
                for (const auto &sValue: stringSetValue) {
                    jsonStringArray.add(sValue);
                }
                rootJson.set("SS", jsonStringArray);
            }

            // Number array
            if (!numberSetValue.empty()) {
                Poco::JSON::Array jsonNumberArray;
                for (const auto &nValue: numberSetValue) {
                    jsonNumberArray.add(nValue);
                }
                rootJson.set("NS", jsonNumberArray);
            }

            return rootJson;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    void AttributeValue::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            for (size_t i = 0; i < jsonObject->getNames().size(); i++) {
                type = jsonObject->getNames()[i];
                if (type == "S" && jsonObject->has(type)) {
                    stringValue = jsonObject->getValue<std::string>(type);
                } else if (type == "SS") {
                    Poco::JSON::Array::Ptr jsonNumberArray = jsonObject->getArray("SS");
                    for (const auto &nValue: *jsonNumberArray) {
                        stringSetValue.emplace_back(nValue.convert<std::string>());
                    }
                } else if (type == "N") {
                    numberValue = jsonObject->get(type).convert<std::string>();
                } else if (type == "NS") {
                    Poco::JSON::Array::Ptr jsonNumberArray = jsonObject->getArray("NS");
                    for (const auto &nValue: *jsonNumberArray) {
                        numberSetValue.emplace_back(nValue.convert<std::string>());
                    }
                } else if (type == "BOOL") {
                    boolValue = jsonObject->get(type).convert<bool>();
                } else if (type == "NULL") {
                    nullValue = jsonObject->get(type).convert<bool>();
                }
            }

        } catch (Poco::Exception &exc) {
            std::cerr << exc.message();
            throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        }
    }

    view_or_value<view, value> AttributeValue::ToDocument() const {

        auto attributeDoc = bsoncxx::builder::basic::document{};
        attributeDoc.append(
                kvp("S", stringValue),
                kvp("N", numberValue),
                kvp("BOOL", boolValue),
                kvp("NULL", nullValue),
                kvp("created", bsoncxx::types::b_date(created)),
                kvp("modified", bsoncxx::types::b_date(modified)));

        // Convert string set to document
        if (!stringSetValue.empty()) {
            auto stringSetDoc = bsoncxx::builder::basic::array{};
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
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AttributeValue &a) {
        os << "AttributeValue=" << bsoncxx::to_json(a.ToDocument());
        return os;
    }

}// namespace AwsMock::Database::Entity::DynamoDb
