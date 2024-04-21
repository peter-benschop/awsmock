//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ListTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

    std::string ListTableResponse::ToJson() const {

        try {
            Poco::JSON::Object rootJson;
            rootJson.set("Region", region);
            rootJson.set("LastEvaluatedTableName", lastEvaluatedTableName);

            Poco::JSON::Array jsonTableArray;
            for (const auto &tableName: tableNames) {
                jsonTableArray.add(tableName);
            }

            return Core::JsonUtils::ToJsonString(rootJson);

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            throw Core::JsonException(exc.message());
        }
    }

    void ListTableResponse::FromJson(const std::string &jsonString, const std::map<std::string, std::string> &headerMap) {

        body = jsonString;
        headers = headerMap;

        /*Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(jsonString);
        Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

        try {

          Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
          Core::JsonUtils::GetJsonValueString("LastEvaluatedTableName", rootObject, lastEvaluatedTableName);

          Poco::JSON::Array::Ptr jsonTableArray = rootObject->getArray("TableNames");
          if (!jsonTableArray.isNull()) {
            for (const auto &tableName : *jsonTableArray) {
              tableNames.emplace_back(tableName);
            }
          }

        } catch (Poco::Exception &exc) {
          throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
        }*/
    }

    std::string ListTableResponse::ToString() const {
        std::stringstream ss;
        ss << (*this);
        return ss.str();
    }

    std::ostream &operator<<(std::ostream &os, const ListTableResponse &r) {
        os << "ListTableResponse=" << r.ToJson();
        return os;
    }

} // namespace AwsMock::Dto::DynamoDb
