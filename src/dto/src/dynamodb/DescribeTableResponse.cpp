//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/DescribeTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string DescribeTableResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("TableName", tableName);
            rootJson.set("TableId", tableId);
            rootJson.set("TableArn", tableArn);
            rootJson.set("TableStatus", TableStatusTypeToString(tableStatus));
            rootJson.set("ProvisionedThroughput", provisionedThroughput.ToDocument());

            if (!keySchemas.empty()) {
                Poco::JSON::Array jsonKeySchemasArray;
                for (const auto &keySchema: keySchemas) {
                    Poco::JSON::Object object;
                    object.set("AttributeName", keySchema.first);
                    object.set("KeyType", keySchema.second);
                    jsonKeySchemasArray.add(object);
                }
                rootJson.set("KeySchema", jsonKeySchemasArray);
            }

            if (!attributes.empty()) {
                Poco::JSON::Array jsonAttributesArray;
                for (const auto &attribute: attributes) {
                    Poco::JSON::Object object;
                    object.set("AttributeName", attribute.first);
                    object.set("AttributeType", attribute.second);
                    jsonAttributesArray.add(object);
                }
                rootJson.set("AttributeDefinitions", jsonAttributesArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void DescribeTableResponse::FromJson(const std::string &jsonString, const std::map<std::string, std::string> &headerMap) {

        body = jsonString;
        headers = headerMap;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Poco::JSON::Object::Ptr tableObject = rootObject->getObject("Table");

            Core::JsonUtils::GetJsonValueString("Region", tableObject, region);
            Core::JsonUtils::GetJsonValueString("TableName", tableObject, tableName);
            Core::JsonUtils::GetJsonValueString("TableId", tableObject, tableId);
            Core::JsonUtils::GetJsonValueString("TableArn", tableObject, tableArn);
            //provisionedThroughput.FromJsonObject(tableObject->getObject("ProvisionedThroughput"));
            std::string tableStatusStr;
            Core::JsonUtils::GetJsonValueString("TableStatus", tableObject, tableStatusStr);
            tableStatus = TableStatusTypeFromString(tableStatusStr);

            // Attributes
            if (tableObject->has("AttributeDefinitions")) {
                Poco::JSON::Array::Ptr jsonAttributeArray = tableObject->getArray("AttributeDefinitions");
                for (int i = 0; i < jsonAttributeArray->size(); i++) {
                    Poco::JSON::Object::Ptr jsonObject = jsonAttributeArray->getObject(i);
                    std::string name, type;
                    Core::JsonUtils::GetJsonValueString("AttributeName", jsonObject, name);
                    Core::JsonUtils::GetJsonValueString("AttributeType", jsonObject, type);
                    attributes[name] = type;
                }
            }

            // Key schemas
            if (tableObject->has("KeySchema")) {
                Poco::JSON::Array::Ptr jsonKeySchemaArray = tableObject->getArray("KeySchema");
                for (int i = 0; i < jsonKeySchemaArray->size(); i++) {
                    Poco::JSON::Object::Ptr jsonObject = jsonKeySchemaArray->getObject(i);
                    std::string name, type;
                    Core::JsonUtils::GetJsonValueString("AttributeName", jsonObject, name);
                    Core::JsonUtils::GetJsonValueString("KeyType", jsonObject, type);
                    keySchemas[name] = type;
                }
            }

            // Key schemas
            if (tableObject->has("Tags")) {
                Poco::JSON::Array::Ptr jsonTagsArray = tableObject->getArray("Tags");
                for (int i = 0; i < jsonTagsArray->size(); i++) {
                    Poco::JSON::Object::Ptr jsonObject = jsonTagsArray->getObject(i);
                    std::string name, type;
                    Core::JsonUtils::GetJsonValueString("Key", jsonObject, name);
                    Core::JsonUtils::GetJsonValueString("Value", jsonObject, type);
                    tags[name] = type;
                }
            }

        } catch (Poco::Exception &exc) {
            throw Core::JsonException(exc.message());
        }
    }

    std::string DescribeTableResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeTableResponse &r) {
        os << "DescribeTableResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
