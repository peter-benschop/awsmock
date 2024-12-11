//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ScanResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string ScanResponse::ToJson() const {

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

    void ScanResponse::FromJson(const std::string &jsonString) {

        body = jsonString;

        // Todo:
        /*
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            //Poco::JSON::Object::Ptr jsonTableDescription = rootObject->getObject("TableDescription");

            //Core::JsonUtils::GetJsonValueString("TableName", jsonTableDescription, tableName);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }*/
    }

    std::string ScanResponse::ToString() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ScanResponse &r) {
        os << "ScanResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
