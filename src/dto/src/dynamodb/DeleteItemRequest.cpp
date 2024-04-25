//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/DeleteItemRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string DeleteItemRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("TableName", tableName);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void DeleteItemRequest::FromJson(const std::string &jsonBody) {

        // Save original body
        body = jsonBody;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonBody);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteItemRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteItemRequest &r) {
        os << "DeleteItemRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
