//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/GetItemRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string GetItemRequest::ToJson() const {

        // Todo:
        /*
        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("TableName", tableName);
            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    void GetItemRequest::FromJson(const std::string &jsonBody) {

        // Todo:
        /*
        // Save original body
        body = jsonBody;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonBody);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

            // Tags
            Poco::JSON::Object::Ptr jsonKeyObject = rootObject->getObject("Key");
            if (!jsonKeyObject.isNull()) {
                for (size_t i = 0; i < jsonKeyObject->getNames().size(); i++) {
                    Poco::JSON::Object::Ptr jsonGetKeyObject = jsonKeyObject->getObject(jsonKeyObject->getNames()[i]);
                    GetItemKey getItemKey;
                    for (size_t j = 0; j < jsonGetKeyObject->getNames().size(); j++) {
                        getItemKey.type = jsonGetKeyObject->getNames()[j];
                        if (getItemKey.type == "S") {
                            getItemKey.value = jsonGetKeyObject->getValue<std::string>(getItemKey.type);
                        } else if (getItemKey.type == "N") {
                            getItemKey.value = std::to_string(jsonGetKeyObject->getValue<int>(getItemKey.type));
                        }
                    }
                    //keys[jsonKeyObject->getNames()[i]] = getItemKey;
                }
            }
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string GetItemRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetItemRequest &r) {
        os << "GetItemRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
