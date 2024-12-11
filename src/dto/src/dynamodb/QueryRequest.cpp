//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/QueryRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string QueryRequest::ToJson() const {

        // Todo:
        /*
        try {

            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("TableName", tableName);

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
        return {};
    }

    void QueryRequest::FromJson(const std::string &jsonBody) {

        // Save original body
        body = jsonBody;

        // Todo:
        /*
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonBody);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
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
