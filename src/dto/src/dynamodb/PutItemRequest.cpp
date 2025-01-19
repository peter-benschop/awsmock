//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/PutItemRequest.h>
#include <awsmock/entity/dynamodb/AttributeValue.h>

namespace AwsMock::Dto::DynamoDb {

    std::string PutItemRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "TableName", tableName);
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void PutItemRequest::FromJson(const std::string &jsonString) {

        // Save original body
        body = jsonString;

        try {

            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            tableName = Core::Bson::BsonUtils::GetStringValue(document, "TableName");

            if (document.find("Item") != document.end()) {
                for (const view attributesView = document.view()["Item"].get_document().value; const bsoncxx::document::element &attribute: attributesView) {
                    std::string key = bsoncxx::string::to_string(attribute.key());
                    AttributeValue value;
                    value.FromDocument(attributesView[key].get_document().value);
                    attributes.emplace(key, value);
                }
            }

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PutItemRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutItemRequest &r) {
        os << "PutItemRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
