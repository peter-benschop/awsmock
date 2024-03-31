//
// Created by vogje01 on 20/12/2023.
//

#include <awsmock/dto/dynamodb/CreateTableResponse.h>

namespace AwsMock::Dto::DynamoDb {

  std::string CreateTableResponse::ToJson() {

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
        object.set("attributeName", tag.first);
        object.set("AttributeType", tag.second);
        jsonAttributeArray.add(object);
      }
      rootJson.set("AttributeDefinitions", jsonAttributeArray);

      Poco::JSON::Array jsonKeySchemaArray;
      for(const auto &key: keySchemas) {
        Poco::JSON::Object object;
        object.set("attributeName", key.first);
        object.set("KeyType", key.second);
        jsonKeySchemaArray.add(object);
      }
      rootJson.set("KeySchema", jsonKeySchemaArray);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void CreateTableResponse::FromJson(const std::string &jsonString, const std::map<std::string, std::string>&headerMap) {

    this->body = jsonString;
    this->headers = headerMap;

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    Poco::JSON::Object::Ptr rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Poco::JSON::Object::Ptr jsonTableDescription = rootObject->getObject("TableDescription");

      Core::JsonUtils::GetJsonValueString("TableName", jsonTableDescription, tableName);
      Core::JsonUtils::GetJsonValueString("TableArn", jsonTableDescription, tableArn);
      Core::JsonUtils::GetJsonValueLong("TableSizeBytes", jsonTableDescription, tableSizeBytes);
      Core::JsonUtils::GetJsonValueLong("ItemCount", jsonTableDescription, tableSizeBytes);
      Core::JsonUtils::GetJsonValueBool("DeletionProtectionEnabled", jsonTableDescription, deleteProtectionEnabled);
      std::string tableStatusStr;
      Core::JsonUtils::GetJsonValueString("TableStatus", jsonTableDescription, tableStatusStr);
      tableStatus = TableStatusFromString(tableStatusStr);

      // Key schema
      Poco::JSON::Array::Ptr jsonKeySchemaArray = jsonTableDescription->getArray("KeySchema");
      if(!jsonKeySchemaArray.isNull()) {
        for (size_t i = 0; i < jsonKeySchemaArray->size(); i++) {
          std::string key, value;
          Poco::JSON::Object::Ptr jsonKeySchemaObject = jsonKeySchemaArray->getObject(i);
          Core::JsonUtils::GetJsonValueString("attributeName", jsonKeySchemaObject, key);
          Core::JsonUtils::GetJsonValueString("KeyType", jsonKeySchemaObject, value);
          keySchemas[key] = value;
        }
      }

      // Attributes
      Poco::JSON::Array::Ptr jsonAttributeArray = jsonTableDescription->getArray("AttributeDefinitions");
      if(!jsonAttributeArray.isNull()) {
        for (size_t i = 0; i < jsonAttributeArray->size(); i++) {
          std::string name, type;
          Poco::JSON::Object::Ptr jsonAttributeObject = jsonAttributeArray->getObject(i);
          Core::JsonUtils::GetJsonValueString("attributeName", jsonAttributeObject, name);
          Core::JsonUtils::GetJsonValueString("AttributeType", jsonAttributeObject, type);
          attributes[name] = type;
        }
      }

    } catch (Poco::Exception &exc) {
      std::cerr << exc.message()  <<std::endl;
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  std::string CreateTableResponse::ToString() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  std::ostream &operator<<(std::ostream &os, const CreateTableResponse &r) {
    os << "CreateTableResponse={region='" << r.region << "', tableClass='" << r.tableClass << "', tableName='" << r.tableName
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

} // namespace AwsMock::Dto::DynamoDb
