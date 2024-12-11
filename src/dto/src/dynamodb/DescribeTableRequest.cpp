//
// Created by vogje01 on 21/12/2023.
//

#include <awsmock/dto/dynamodb/DescribeTableRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string DescribeTableRequest::ToJson() const {

        // TOdo:
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

    void DescribeTableRequest::FromJson(const std::string &jsonBody) {

        body = jsonBody;

        // TOdo:
        /*
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonBody);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string DescribeTableRequest::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeTableRequest &r) {
        os << "DescribeTableRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
