//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ListTableRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string ListTableRequest::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "ExclusiveStartTableName", exclusiveStartTableName);
            Core::Bson::BsonUtils::SetIntValue(document, "Limit", limit);

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ListTableRequest::FromJson(const std::string &jsonString) {

        // Save original body
        body = jsonString;

        try {
            const value document = bsoncxx::from_json(jsonString);
            region = Core::Bson::BsonUtils::GetStringValue(document, "Region");
            exclusiveStartTableName = Core::Bson::BsonUtils::GetStringValue(document, "ExclusiveStartTableName");
            limit = Core::Bson::BsonUtils::GetIntValue(document, "Limit");

        } catch (bsoncxx::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListTableRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListTableRequest &r) {
        os << "ListTableRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
