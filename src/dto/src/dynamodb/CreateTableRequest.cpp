//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/CreateTableRequest.h>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/config/util.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <bsoncxx/types/bson_value/view.hpp>

namespace AwsMock::Dto::DynamoDb {

    std::string CreateTableRequest::ToJson() const {

        try {

            bsoncxx::builder::basic::document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "TableName", tableName);
            Core::Bson::BsonUtils::SetStringValue(document, "TableClass", tableClass);

            // Attributes
            if (!attributes.empty()) {
                bsoncxx::builder::basic::array attributeArray;
                for (const auto &[fst, snd]: attributes) {
                    bsoncxx::builder::basic::document attributeDocument;
                    Core::Bson::BsonUtils::SetStringValue(attributeDocument, "AttributeName", fst);
                    Core::Bson::BsonUtils::SetStringValue(attributeDocument, "AttributeType", snd);
                    attributeArray.append(attributeDocument);
                }
                document.append(kvp("AttributeDefinitions", attributeArray));
            }

            // Key schema
            if (!keySchemas.empty()) {
                bsoncxx::builder::basic::array keySchemasArray;
                for (const auto &[fst, snd]: keySchemas) {
                    bsoncxx::builder::basic::document keySchemaDocument;
                    Core::Bson::BsonUtils::SetStringValue(keySchemaDocument, "AttributeName", fst);
                    Core::Bson::BsonUtils::SetStringValue(keySchemaDocument, "KeyType", snd);
                    keySchemasArray.append(keySchemaDocument);
                }
                document.append(kvp("KeySchema", keySchemasArray));
            }

            // Provisioned throughput
            document.append(kvp("ProvisionedThroughput", provisionedThroughput.ToDocument()));

            // Tags
            if (!tags.empty()) {
                bsoncxx::builder::basic::array tagsArray;
                for (const auto &[fst, snd]: tags) {
                    bsoncxx::builder::basic::document tagDocument;
                    Core::Bson::BsonUtils::SetStringValue(tagDocument, "Key", fst);
                    Core::Bson::BsonUtils::SetStringValue(tagDocument, "Value", snd);
                    tagsArray.append(tagDocument);
                }
                document.append(kvp("Tags", tagsArray));
            }

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void CreateTableRequest::FromJson(const std::string &jsonBody) {

        if (jsonBody.empty()) {
            return;
        }

        // Save original body
        body = jsonBody;

        try {

            bsoncxx::builder::basic::document document;
            const value documentValue = bsoncxx::from_json(body);

            region = Core::Bson::BsonUtils::GetStringValue(documentValue, "Region");
            tableClass = Core::Bson::BsonUtils::GetStringValue(documentValue, "TableClass");
            tableName = Core::Bson::BsonUtils::GetStringValue(documentValue, "TableName");

            // Tags
            if (documentValue.find("Tags") != documentValue.end()) {
                for (const view tagsView = documentValue["Tags"].get_document().value; const bsoncxx::document::element &tagElement: tagsView) {
                    std::string key = bsoncxx::string::to_string(tagElement.key());
                    std::string value = bsoncxx::string::to_string(tagsView[key].get_string().value);
                    tags.emplace(key, value);
                }
            }

            // Attributes
            if (documentValue.find("AttributeDefinitions") != documentValue.end()) {
                for (const view attributesView = documentValue["AttributeDefinitions"].get_document().value; const bsoncxx::document::element &attributeElement: attributesView) {
                    const std::string name = Core::Bson::BsonUtils::GetStringValue(attributeElement["AttributeName"]);
                    const std::string type = Core::Bson::BsonUtils::GetStringValue(attributeElement["AttributeType"]);
                    attributes[name] = type;
                }
            }

            // Key schemas
            if (documentValue.find("KeySchema") != documentValue.end()) {
                for (const view attributesView = documentValue["KeySchema"].get_document().value; const bsoncxx::document::element &attributeElement: attributesView) {
                    const std::string name = Core::Bson::BsonUtils::GetStringValue(attributeElement["AttributeName"]);
                    const std::string type = Core::Bson::BsonUtils::GetStringValue(attributeElement["AttributeType"]);
                    keySchemas[name] = type;
                }
            }

            // Provisioned throughput
            if (documentValue.find("ProvisionedThroughput") != documentValue.end()) {
                provisionedThroughput.FromDocument(documentValue["ProvisionedThroughput"].get_document().view());
            }

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string CreateTableRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const CreateTableRequest &r) {
        os << "CreateTableRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
