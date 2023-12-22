//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/DeleteItemRequest.h>

namespace AwsMock::Dto::DynamoDb {

  std::string DeleteItemRequest::ToJson() {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("TableName", tableName);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void DeleteItemRequest::FromJson(const std::string &jsonBody) {

    // Save original body
    body = jsonBody;

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonBody);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

    } catch (Poco::Exception &exc) {
      std::cerr << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  std::string DeleteItemRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const DeleteItemRequest &r) {
    os << "DeleteItemRequest={region='" << r.region << "', tableName='" << r.tableName << "}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
