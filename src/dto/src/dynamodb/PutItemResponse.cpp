//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/PutItemResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string PutItemResponse::ToJson() const {

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

    void PutItemResponse::FromJson(const std::string &jsonString) {

        body = jsonString;

        try {

            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            tableName = Core::Bson::BsonUtils::GetStringValue(document, "TableName");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string PutItemResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutItemResponse &r) {
        os << "PutItemResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
