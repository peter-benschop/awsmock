//
// Created by vogje01 on 5/10/24.
//

#include <awsmock/dto/dynamodb/mapper/Mapper.h>

namespace AwsMock::Dto::DynamoDb {

    Database::Entity::DynamoDb::Table Mapper::map(const DescribeTableResponse &response) {
        Database::Entity::DynamoDb::Table tableEntity;
        tableEntity.region = response.region,
        tableEntity.name = response.tableName,
        tableEntity.status = TableStatusTypeToString(response.tableStatus),
        tableEntity.attributes = response.attributes,
        tableEntity.keySchemas = response.keySchemas;
        tableEntity.itemCount = response.itemCount;
        tableEntity.size = response.tableSize;
        tableEntity.provisionedThroughput.FromDocument(response.provisionedThroughput.ToDocument());
        return tableEntity;
    }

    Database::Entity::DynamoDb::Item Mapper::map(const DeleteItemRequest &request) {

        Database::Entity::DynamoDb::Item item;
        item.region = request.region;
        item.tableName = request.tableName;

        for (const auto &[fst, snd]: request.key.keys) {
            Database::Entity::DynamoDb::AttributeValue attributeValue;
            attributeValue.type = snd.type;
            attributeValue.stringValue = snd.stringValue;
            attributeValue.stringSetValue = snd.stringSetValue;
            attributeValue.numberValue = snd.numberValue;
            attributeValue.numberSetValue = snd.numberSetValue;
            attributeValue.boolValue = snd.boolValue;
            attributeValue.nullValue = snd.nullValue;
            item.keys[fst] = attributeValue;
        }

        return item;
    }

    Database::Entity::DynamoDb::Item Mapper::map(const PutItemRequest &request) {

        Database::Entity::DynamoDb::Item item;
        item.region = request.region;
        item.tableName = request.tableName;

        for (const auto &[fst, snd]: request.attributes) {
            Database::Entity::DynamoDb::AttributeValue keyValue;
            keyValue.type = snd.type;
            keyValue.stringValue = snd.stringValue;
            keyValue.stringSetValue = snd.stringSetValue;
            keyValue.numberValue = snd.numberValue;
            keyValue.numberSetValue = snd.numberSetValue;
            keyValue.boolValue = snd.boolValue;
            keyValue.nullValue = snd.nullValue;
            item.attributes[fst] = keyValue;
        }

        return item;
    }

}// namespace AwsMock::Dto::DynamoDb