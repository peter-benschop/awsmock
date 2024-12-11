//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/model/AttributeValue.h>

namespace AwsMock::Dto::DynamoDb {

    view_or_value<view, value> AttributeValue::ToDocument() const {

        // Todo:
        /*
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
        }*/
        return {};
    }

    void AttributeValue::FromDocument(const view &jsonObject) {

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
        return Core::Bson::BsonUtils::ToJsonString(ToDocument());
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
