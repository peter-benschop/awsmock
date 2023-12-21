//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/ListTableRequest.h>

namespace AwsMock::Dto::DynamoDb {

  std::string ListTableRequest::ToJson() {

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

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
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
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string ListTableRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const ListTableRequest &r) {
    os << "ListTableRequest={region='" << r.region << "', exclusiveStartTableName='" << r.exclusiveStartTableName << "', limit='" << r.limit << "}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
