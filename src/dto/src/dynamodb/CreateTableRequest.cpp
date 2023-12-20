//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/CreateTableRequest.h>

namespace AwsMock::Dto::DynamoDb {

  std::string CreateTableRequest::ToJson() {

    try {
      Poco::JSON::Object rootJson;
      rootJson.set("Region", region);
      rootJson.set("TableClass", tableClass);
      rootJson.set("TableName", tableName);

      Poco::JSON::Array jsonTagsArray;
      for(const auto &tag: tags) {
        Poco::JSON::Object object;
        object.set("Key", tag.first);
        object.set("Value", tag.second);
        jsonTagsArray.add(object);
      }
      rootJson.set("Tags", jsonTagsArray);

      Poco::JSON::Array jsonAttributeArray;
      for(const auto &tag: attributes) {
        Poco::JSON::Object object;
        object.set("AttributeName", tag.first);
        object.set("AttributeType", tag.second);
        jsonAttributeArray.add(object);
      }
      rootJson.set("Tags", jsonAttributeArray);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  void CreateTableRequest::FromJson(const std::string &body) {

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(body);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {
      Core::JsonUtils::GetJsonValueString("Region", rootObject, region);
      Core::JsonUtils::GetJsonValueString("TableClass", rootObject, tableClass);
      Core::JsonUtils::GetJsonValueString("TableName", rootObject, tableName);

      // Tags
      Poco::JSON::Array::Ptr jsonTagsArray = rootObject->getArray("Tags");
      for(size_t i = 0; i < jsonTagsArray->size(); i++) {
        std::string key, value;
        Poco::JSON::Object::Ptr jsonTagsObject = jsonTagsArray->getObject(i);
        Core::JsonUtils::GetJsonValueString("Key", jsonTagsObject, key);
        Core::JsonUtils::GetJsonValueString("Value", jsonTagsObject, value);
        tags[key] = value;
      }

      // Attributes
      Poco::JSON::Array::Ptr jsonAttributeArray = rootObject->getArray("AttributeDefinitions");
      for(size_t i = 0; i < jsonAttributeArray->size(); i++) {
        std::string name, type;
        Poco::JSON::Object::Ptr jsonAttributeObject = jsonAttributeArray->getObject(i);
        Core::JsonUtils::GetJsonValueString("Name", jsonAttributeObject, name);
        Core::JsonUtils::GetJsonValueString("Type", jsonAttributeObject, type);
        tags[name] = type;
      }

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), 500);
    }
  }

  std::string CreateTableRequest::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateTableRequest &r) {
    os << "CreateTableRequest={region='" << r.region << "', tableClass='" << r.tableClass << "', tableName='" << r.tableName
    << "' tags=[";
    for (const auto &tag : r.tags) {
      os << "key='" << tag.first << "' value='" << tag.second << "', ";
    }
    os.seekp(-2,std::ostream::cur);
    os << "' attributes=[";
    for (const auto &attribute : r.attributes) {
      os << "name='" << attribute.first << "' type='" << attribute.second << "', ";
    }
    os.seekp(-2,std::ostream::cur);
    os << "]}";
    return os;
  }

} // namespace AwsMock::Dto::lambda
