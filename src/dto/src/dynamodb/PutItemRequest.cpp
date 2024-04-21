//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/PutItemRequest.h>

namespace AwsMock::Dto::DynamoDb {

    std::string PutItemRequest::ToJson() {

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

    void PutItemRequest::FromJson(const std::string &jsonBody) {

        // Save original body
        body = jsonBody;

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonBody);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {
            Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
            Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

            // Tags
            Poco::JSON::Object::Ptr jsonKeyObject = rootObject->getObject("Item");
            if (!jsonKeyObject.isNull()) {
                for (size_t i = 0; i < jsonKeyObject->getNames().size(); i++) {
                    AttributeValue attributeValue;
                    attributeValue.FromJsonObject(jsonKeyObject->getObject(jsonKeyObject->getNames()[i]));
                    item[jsonKeyObject->getNames()[i]] = attributeValue;
                }
            }
        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    std::string PutItemRequest::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const PutItemRequest &r) {
        os << "PutItemRequest=" << r.ToJson();
        return os;
    }

} // namespace AwsMock::Dto::DynamoDb
