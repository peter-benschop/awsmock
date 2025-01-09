//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ListTableCountersResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string ListTableCountersResponse::ToJson() const {

        try {

            document document;
            Core::Bson::BsonUtils::SetStringValue(document, "region", region);

            if (!tableNames.empty()) {
                array array;
                for (const auto &tableName: tableNames) {
                    array.append(tableName);
                }
                document.append(kvp("tableNames", array));
            }
            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ListTableCountersResponse::FromJson(const std::string &body, const std::map<std::string, std::string> &headers) {

        try {

            if (const value documentValue = bsoncxx::from_json(body); documentValue.find("TableNames") != documentValue.end()) {
                Core::Bson::FromBsonStringArray(documentValue, "TableNames", &tableNames);
            }

        } catch (std::exception &exc) {
            log_error << exc.what() << " body: " << body;
            throw Core::JsonException(exc.what());
        }
    }

    std::string ListTableCountersResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListTableCountersResponse &r) {
        os << "ListTableCountersResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
