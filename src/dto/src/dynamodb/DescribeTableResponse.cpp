//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/DescribeTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string DescribeTableResponse::ToJson() const {

        try {
            document rootDocument;
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "TableName", tableName);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "TableId", tableId);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "TableArn", tableArn);
            Core::Bson::BsonUtils::SetStringValue(rootDocument, "TableStatus", TableStatusTypeToString(tableStatus));
            rootDocument.append(kvp("ProvisionedThroughput", provisionedThroughput.ToDocument()));

            if (!keySchemas.empty()) {
                array jsonKeySchemasArray;
                for (const auto &[fst, snd]: keySchemas) {
                    document object;
                    object.append(kvp("AttributeName", fst));
                    object.append(kvp("KeyType", snd));
                    jsonKeySchemasArray.append(object);
                }
                rootDocument.append(kvp("KeySchema", jsonKeySchemasArray));
            }

            if (!attributes.empty()) {
                array jsonAttributesArray;
                for (const auto &[fst, snd]: attributes) {
                    document object;
                    object.append(kvp("AttributeName", fst));
                    object.append(kvp("AttributeType", snd));
                    jsonAttributesArray.append(object);
                }
                rootDocument.append(kvp("AttributeDefinitions", jsonAttributesArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(rootDocument);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DescribeTableResponse::FromJson(const std::string &body, const std::map<std::string, std::string> &headers) {

        this->body = body;
        this->headers = headers;

        try {

            boost::property_tree::ptree root;
            read_xml(body, root);
            region = root.get<std::string>("Table.Region");
            tableName = root.get<std::string>("Table.TableName");
            tableId = root.get<std::string>("Table.TableId");
            tableArn = root.get<std::string>("Table.TableArn");
            tableStatus = TableStatusTypeFromString(root.get<std::string>("Table.TableStatus"));

            // TODO: FIx
            /*// Attributes
            if (root.find("Table.AttributeDefinitions") != root.end()) {
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
            }*/

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
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
