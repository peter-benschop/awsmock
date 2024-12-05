//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/model/AttributeValue.h>

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
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void AttributeValue::FromDocument(const bsoncxx::document::view &jsonObject) {

        for (bsoncxx::document::element ele: jsonObject) {
            type = ele["type"].get_string();
            if (type == "S") {
                stringValue = ele["S"].get_string();
            } else if (type == "SS") {
                /*Poco::JSON::Array::Ptr jsonNumberArray = jsonObject->getArray("SS");
                for (const auto &nValue: *jsonNumberArray) {
                    stringSetValue.emplace_back(nValue.convert<std::string>());
                }*/
            } else if (type == "N") {
                numberValue = ele["S"].get_int64();
            } else if (type == "NS") {
                /*Poco::JSON::Array::Ptr jsonNumberArray = jsonObject->getArray("NS");
                for (const auto &nValue: *jsonNumberArray) {
                    numberSetValue.emplace_back(nValue.convert<std::string>());
                }*/
            } else if (type == "BOOL") {
                boolValue = ele["S"].get_bool();
            } else if (type == "NULL") {
                nullValue = true;
            }
        }
    }

    std::string AttributeValue::ToJson() const {
        return Core::JsonUtils::ToJsonString(ToJsonObject());
    }

    std::string AttributeValue::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const AttributeValue &r) {
        os << "AttributeValue=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
