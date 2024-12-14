//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/QueryRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string QueryRequest::ToJson() const {

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

    void QueryRequest::FromJson(const std::string &jsonString) {

        // Save original body
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

    std::string QueryRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const QueryRequest &r) {
        os << "QueryRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
