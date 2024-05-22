//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/dynamodb/mapper/Mapper.h>

namespace AwsMock::Dto::DynamoDb {

    Database::Entity::DynamoDb::Item Mapper::map(const Dto::DynamoDb::DeleteItemRequest &request) {

        Database::Entity::DynamoDb::Item item;
        item.region = request.region;
        item.tableName = request.tableName;

        for (const auto &key: request.key.keys) {
            Database::Entity::DynamoDb::AttributeValue attributeValue;
            attributeValue.type = key.second.type;
            attributeValue.stringValue = key.second.stringValue;
            attributeValue.stringSetValue = key.second.stringSetValue;
            attributeValue.numberValue = key.second.numberValue;
            attributeValue.numberSetValue = key.second.numberSetValue;
            attributeValue.boolValue = key.second.boolValue;
            attributeValue.nullValue = key.second.nullValue;
            item.keys[key.first] = attributeValue;
        }

        return item;
    }

    Database::Entity::DynamoDb::Item Mapper::map(const Dto::DynamoDb::PutItemRequest &request) {

        Database::Entity::DynamoDb::Item item;
        item.region = request.region;
        item.tableName = request.tableName;

        for (const auto &key: request.attributes) {
            Database::Entity::DynamoDb::AttributeValue keyValue;
            keyValue.type = key.second.type;
            keyValue.stringValue = key.second.stringValue;
            keyValue.stringSetValue = key.second.stringSetValue;
            keyValue.numberValue = key.second.numberValue;
            keyValue.numberSetValue = key.second.numberSetValue;
            keyValue.boolValue = key.second.boolValue;
            keyValue.nullValue = key.second.nullValue;
            item.attributes[key.first] = keyValue;
        }

        return item;
    }

}// namespace AwsMock::Dto::DynamoDb