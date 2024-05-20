//
// Created by vogje01 on 20/12/2023.
//

#include "awsmock/dto/dynamodb/model/AttributeValue.h"

namespace AwsMock::Dto::DynamoDb {

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
            throw Core::JsonException(exc.message());
        }
    }

    void AttributeValue::FromJsonObject(const Poco::JSON::Object::Ptr &jsonObject) {

        try {

            for (size_t i = 0; i < jsonObject->getNames().size(); i++) {
                std::string valueType = jsonObject->getNames()[i];
                if (valueType == "S" && jsonObject->has(valueType)) {
                    stringValue = jsonObject->getValue<std::string>(valueType);
                } else if (valueType == "SS") {
                    Poco::JSON::Array::Ptr jsonNumberArray = jsonObject->getArray("SS");
                    for (const auto &nValue: *jsonNumberArray) {
                        stringSetValue.emplace_back(nValue.convert<std::string>());
                    }
                } else if (valueType == "N") {
                    numberValue = jsonObject->get(valueType).convert<std::string>();
                } else if (valueType == "NS") {
                    Poco::JSON::Array::Ptr jsonNumberArray = jsonObject->getArray("NS");
                    for (const auto &nValue: *jsonNumberArray) {
                        numberSetValue.emplace_back(nValue.convert<std::string>());
                    }
                } else if (valueType == "BOOL") {
                    boolValue = jsonObject->get(valueType).convert<bool>();
                } else if (valueType == "NULL") {
                    nullValue = jsonObject->get(valueType).convert<bool>();
                }
            }

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string AttributeValue::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string AttributeValue::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AttributeValue &r) {
        os << "AttributeValue=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
