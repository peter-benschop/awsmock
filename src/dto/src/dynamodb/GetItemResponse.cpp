//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/GetItemResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string GetItemResponse::ToJson() const {

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

    void GetItemResponse::FromJson(const std::string &jsonString) {

        body = jsonString;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Poco::JSON::Object::Ptr jsonItemObject = rootObject->getObject("Item");


        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string GetItemResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const GetItemResponse &r) {
        os << "GetItemResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
