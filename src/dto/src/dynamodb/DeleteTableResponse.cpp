//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/DeleteTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

  std::string DeleteTableResponse::ToJson() {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("TableName", tableName);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void DeleteTableResponse::FromJson(const std::string &body) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(body);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {
      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string DeleteTableResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteTableResponse &r) {
    os << "DeleteTableResponse={region='" << r.region << "', tableName='" << r.tableName << "]}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
