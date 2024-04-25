//
// Created by vogje01 on 21/12/2023.
//

#include <awsmock/dto/dynamodb/DeleteTableRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string DeleteTableRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            //rootJson.set("Region", region);
            rootJson.set("TableName", tableName);

            std::ostringstream os;
            rootJson.stringify(os);
            return os.str();

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void DeleteTableRequest::FromJson(const std::string &jsonBody) {

        body = jsonBody;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonBody);
        const auto &rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string DeleteTableRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DeleteTableRequest &r) {
        os << "DeleteTableRequest=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
