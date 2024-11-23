//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ListTableRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string ListTableRequest::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            if (!region.empty()) {
                rootJson.set("Region", region);
            }
            if (!exclusiveStartTableName.empty()) {
                rootJson.set("ExclusiveStartTableName", exclusiveStartTableName);
            }
            if (limit > 0) {
                rootJson.set("Limit", limit);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ListTableRequest::FromJson(const std::string &jsonBody) {

        // Save original body
        body = jsonBody;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonBody);
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
