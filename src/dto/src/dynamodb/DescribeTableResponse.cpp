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

            try {

                const value rootDocument = bsoncxx::from_json(body);
                region = Core::Bson::BsonUtils::GetStringValue(rootDocument, "Region");
                tableName = Core::Bson::BsonUtils::GetStringValue(rootDocument, "TableName");
                tableId = Core::Bson::BsonUtils::GetBoolValue(rootDocument, "TableId");
                tableArn = Core::Bson::BsonUtils::GetStringValue(rootDocument, "TableArn");

                // Attributes
                if (rootDocument.view().find("AttributeDefinitions") != rootDocument.view().end()) {
                    for (const bsoncxx::array::view jsonArray = rootDocument.view()["AttributeDefinitions"].get_array().value; const auto &element: jsonArray) {
                        view jsonObject = element.get_document().value;
                        std::string name = Core::Bson::BsonUtils::GetStringValue(jsonObject, "AttributeName");
                        const std::string type = Core::Bson::BsonUtils::GetStringValue(jsonObject, "AttributeType");
                        attributes[name] = type;
                    }
                }

                // Key schemas
                if (rootDocument.view().find("KeySchema") != rootDocument.view().end()) {
                    for (const bsoncxx::array::view jsonArray = rootDocument.view()["KeySchema"].get_array().value; const auto &element: jsonArray) {
                        view jsonObject = element.get_document().value;
                        std::string name = Core::Bson::BsonUtils::GetStringValue(jsonObject, "AttributeName");
                        const std::string type = Core::Bson::BsonUtils::GetStringValue(jsonObject, "KeyType");
                        keySchemas[name] = type;
                    }
                }

                // Tags
                if (rootDocument.view().find("Tags") != rootDocument.view().end()) {
                    for (const bsoncxx::array::view jsonArray = rootDocument.view()["Tags"].get_array().value; const auto &element: jsonArray) {
                        view jsonObject = element.get_document().value;
                        std::string key = Core::Bson::BsonUtils::GetStringValue(jsonObject, "Key");
                        const std::string value = Core::Bson::BsonUtils::GetStringValue(jsonObject, "Value");
                        tags[key] = value;
                    }
                }

            } catch (bsoncxx::exception &exc) {
                log_error << exc.what();
                throw Core::JsonException(exc.what());
            }

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
