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

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
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
      Poco::JSON::Object::Ptr jsonKeyObject = rootObject->getObject("Key");
      if (!jsonKeyObject.isNull()) {
        for (size_t i = 0; i < jsonKeyObject->getNames().size(); i++) {
          Poco::JSON::Object::Ptr jsonGetKeyObject = jsonKeyObject->getObject(jsonKeyObject->getNames()[i]);
          GetItemKey getItemKey;
          for (size_t j = 0; j < jsonGetKeyObject->getNames().size(); j++) {
            getItemKey.type = jsonGetKeyObject->getNames()[j];
            if (getItemKey.type == "S") {
              getItemKey.value = jsonGetKeyObject->getValue<std::string>(getItemKey.type);
            } else if (getItemKey.type == "N") {
              getItemKey.value = jsonGetKeyObject->getValue<int>(getItemKey.type);
            }
          }
          item[jsonKeyObject->getNames()[i]] = getItemKey;
        }
      }
    } catch (Poco::Exception &exc) {
      std::cerr << exc.message() << std::endl;
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string PutItemRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const PutItemRequest &r) {
    os << "PutItemRequest={region='" << r.region << "', tableName='" << r.tableName << "}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
