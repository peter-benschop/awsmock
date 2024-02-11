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
      rootJson.set("TableId", tableId);
      rootJson.set("TableArn", tableArn);
      rootJson.set("ProvisionedThroughput", provisionedThroughput.ToJsonObject());

      Poco::JSON::Array jsonKeySchemasArray;
      for (const auto &keySchema : keySchemas) {
        Poco::JSON::Object object;
        object.set("attributeName", keySchema.first);
        object.set("KeyType", keySchema.second);
        jsonKeySchemasArray.add(object);
      }
      rootJson.set("KeySchema", jsonKeySchemasArray);

      Poco::JSON::Array jsonAttributesArray;
      for (const auto &attribute : attributes) {
        Poco::JSON::Object object;
        object.set("attributeName", attribute.first);
        object.set("AttributeType", attribute.second);
        jsonAttributesArray.add(object);
      }
      rootJson.set("AttributeDefinitions", jsonAttributesArray);

      std::ostringstream os;
      rootJson.stringify(os);
      return os.str();

    } catch (Poco::Exception &exc) {
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
    }
  }

  void DeleteTableResponse::FromJson(const std::string &jsonString) {

    body = jsonString;

    Poco::JSON::Parser parser;
    Poco::Dynamic::Var result = parser.parse(jsonString);
    const auto& rootObject = result.extract<Poco::JSON::Object::Ptr>();

    try {

      Poco::JSON::Object::Ptr jsonTableDescription = rootObject->getObject("TableDescription");

      Core::JsonUtils::GetJsonValueString("Region", jsonTableDescription, region);
      Core::JsonUtils::GetJsonValueString("TableName", jsonTableDescription, tableName);
      std::string tableStatusStr;
      Core::JsonUtils::GetJsonValueString("TableStatus", jsonTableDescription, tableStatusStr);
      tableStatus = TableStatusFromString(tableStatusStr);

      // Key schema
      Poco::JSON::Array::Ptr jsonKeySchemaArray = jsonTableDescription->getArray("KeySchema");
      if(!jsonKeySchemaArray.isNull()) {
        for (size_t i = 0; i < jsonKeySchemaArray->size(); i++) {
          std::string name, type;
          Poco::JSON::Object::Ptr jsonKeySchemaObject = jsonKeySchemaArray->getObject(i);
          Core::JsonUtils::GetJsonValueString("attributeName", jsonKeySchemaObject, name);
          Core::JsonUtils::GetJsonValueString("KeyType", jsonKeySchemaObject, type);
          keySchemas[name] = type;
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
      throw Core::ServiceException(exc.message(), Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
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
