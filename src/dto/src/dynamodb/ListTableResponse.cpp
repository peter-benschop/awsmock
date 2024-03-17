//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ListTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

  std::string ListTableResponse::ToJson() {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("LastEvaluatedTableName", lastEvaluatedTableName);

      Poco::JSON::Array jsonTableArray;
      for (const auto &tableName : tableNames) {
        jsonTableArray.add(tableName);
      }

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void ListTableResponse::FromJson(const std::string &jsonString) {

    body = jsonString;

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("LastEvaluatedTableName", rootObject, lastEvaluatedTableName);

      Poco::JSON::Array::Ptr jsonTableArray = rootObject->getArray("TableNames");
      if(!jsonTableArray.isNull()) {
        for (const auto &tableName : *jsonTableArray) {
          tableNames.emplace_back(tableName);
        }
      }

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  std::string ListTableResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListTableResponse &r) {
    os << "ListTableResponse={region='" << r.region << "', lastEvaluatedTableName='" << r.lastEvaluatedTableName << " tableNames=[";
    for (const auto &tableName : r.tableNames) {
      os << "'" << tableName << "', ";
    }
    os.seekp(-2, std::ostream::cur);
    os << "}";
    return os;
  }

} // namespace AwsMock::Dto::DynamoDb
