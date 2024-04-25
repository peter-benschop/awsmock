//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/DescribeTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string DescribeTableResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("TableName", tableName);
            rootJson.set("TableId", tableId);
            rootJson.set("TableArn", tableArn);
            rootJson.set("ProvisionedThroughput", provisionedThroughput.ToJsonObject());

            if (!keySchemas.empty()) {
                Poco::JSON::Array jsonKeySchemasArray;
                for (const auto &keySchema: keySchemas) {
                    Poco::JSON::Object object;
                    object.set("attributeName", keySchema.first);
                    object.set("KeyType", keySchema.second);
                    jsonKeySchemasArray.add(object);
                }
                rootJson.set("KeySchema", jsonKeySchemasArray);
            }

            if (!attributes.empty()) {
                Poco::JSON::Array jsonAttributesArray;
                for (const auto &attribute: attributes) {
                    Poco::JSON::Object object;
                    object.set("attributeName", attribute.first);
                    object.set("AttributeType", attribute.second);
                    jsonAttributesArray.add(object);
                }
                rootJson.set("AttributeDefinitions", jsonAttributesArray);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void DescribeTableResponse::FromJson(const std::string &jsonString, const std::map<std::string, std::string> &headerMap) {

        body = jsonString;
        headers = headerMap;
    }

    std::string DescribeTableResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const DescribeTableResponse &r) {
        os << "DescribeTableResponse=" << r.ToJson();
        return os;
    }

}// namespace AwsMock::Dto::DynamoDb
