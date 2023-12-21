//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/DynamoDbMemoryDb.h>

namespace AwsMock::Database {

  DynamoDbMemoryDb::DynamoDbMemoryDb() : _logger(Poco::Logger::get("DynamoDbMemoryDb")) {}

  bool DynamoDbMemoryDb::TableExists(const std::string &region, const std::string &tableName) {

    if (!region.empty()) {
      return find_if(_tables.begin(), _tables.end(), [region, tableName](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
        return table.second.region == region && table.second.name == tableName;
      }) != _tables.end();
    } else {
      return find_if(_tables.begin(), _tables.end(), [tableName](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
        return table.second.name == tableName;
      }) != _tables.end();
    }
  }

  Entity::DynamoDb::TableList DynamoDbMemoryDb::ListTables(const std::string &region) {

    Entity::DynamoDb::TableList tables;
    if (region.empty()) {
      for (const auto &table : _tables) {
        tables.emplace_back(table.second);
      }
    } else {
      for (const auto &table : _tables) {
        if (table.second.region == region) {
          tables.emplace_back(table.second);
        }
      }
    }

    log_trace_stream(_logger) << "Got DynamoDB table, size: " << tables.size() << std::endl;
    return tables;
  }

  Entity::DynamoDb::Table DynamoDbMemoryDb::CreateTable(const Entity::DynamoDb::Table &table) {
    Poco::ScopedLock lock(_tableMutex);

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _tables[oid] = table;
    log_trace_stream(_logger) << "Lambda created, oid: " << oid << std::endl;
    return GetTableById(oid);
  }

  Entity::DynamoDb::Table DynamoDbMemoryDb::GetTableById(const std::string &oid) {

    auto it = find_if(_tables.begin(), _tables.end(), [oid](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
      return table.first == oid;
    });

    if (it == _tables.end()) {
      log_error_stream(_logger) << "Get table by ID failed, oid: " << oid << std::endl;
      throw Core::DatabaseException("Get table by ID failed, oid: " + oid);
    }

    it->second.oid = oid;
    return it->second;
  }

  void DynamoDbMemoryDb::DeleteTable(const std::string &tableName) {
    Poco::ScopedLock lock(_tableMutex);

    const auto count = std::erase_if(_tables, [tableName](const auto &item) {
      auto const &[key, value] = item;
      return value.name == tableName;
    });
    log_debug_stream(_logger) << "DynamoDB table deleted, count: " << count << std::endl;
  }

  void DynamoDbMemoryDb::DeleteAllTables() {
    Poco::ScopedLock lock(_tableMutex);

    log_debug_stream(_logger) << "All DynamoDb tables deleted, count: " << _tables.size() << std::endl;
    _tables.clear();
  }

  bool DynamoDbMemoryDb::ItemExists(const std::string &region, const std::string &tableName, const std::string &key) {

    if (!region.empty()) {
      return find_if(_items.begin(), _items.end(), [region, tableName](const std::pair<std::string, Entity::DynamoDb::Item> &item) {
        return item.second.region == region && item.second.name == tableName;
      }) != _items.end();
    } else {
      return find_if(_items.begin(), _items.end(), [tableName](const std::pair<std::string, Entity::DynamoDb::Item> &item) {
        return item.second.name == tableName;
      }) != _items.end();
    }
  }

  void DynamoDbMemoryDb::DeleteItem(const std::string &region, const std::string &tableName, const std::string &key) {
    Poco::ScopedLock lock(_itemMutex);

    const auto count = std::erase_if(_items, [region, tableName, key](const auto &item) {
      auto const &[key, value] = item;
      return value.region == region && value.name == tableName;
    });
    log_debug_stream(_logger) << "DynamoDB items deleted, count: " << count << std::endl;
  }

}