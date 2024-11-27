//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ListTableRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string ListTableRequest::ToJson() const {

        try {

            bsoncxx::builder::basic::document document;
            Core::Bson::BsonUtils::SetStringValue(document, "Region", region);
            Core::Bson::BsonUtils::SetStringValue(document, "ExclusiveStartTableName", exclusiveStartTableName);
            Core::Bson::BsonUtils::SetIntValue(document, "Limit", limit);

            return Core::Bson::BsonUtils::ToJsonString(document);

        } catch (std::exception &exc) {
            log_error << exc.what();
            throw Core::JsonException(exc.what());
        }
    }

    void ListTableRequest::FromJson(const std::string &jsonBody) {

        // Save original body
        body = jsonBody;

        Poco::JSON::Parser parser;
        const Poco::Dynamic::Var result = parser.parse(jsonBody);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("ExclusiveStartTableName", rootObject, exclusiveStartTableName);
            Core::JsonUtils::GetJsonValueInt("Limit", rootObject, limit);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
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
