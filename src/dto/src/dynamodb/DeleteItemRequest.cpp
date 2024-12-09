//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/DeleteItemRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string DeleteItemRequest::ToJson() const {

        try {

            bsoncxx::builder::basic::document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "TableName", tableName);

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void DeleteItemRequest::FromJson(const std::string &jsonBody) {

        // Save original body
        body = jsonBody;

        document document;
        const value documentValue = bsoncxx::from_json(body);

        try {

            region = Core::Bson::BsonUtils::GetStringValue(documentValue, "Region");
            tableName = Core::Bson::BsonUtils::GetStringValue(documentValue, "TableName");
            key.FromDocument(documentValue["Key"].get_document());

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string DeleteItemRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteItemRequest &r) {
        os << "DeleteItemRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
