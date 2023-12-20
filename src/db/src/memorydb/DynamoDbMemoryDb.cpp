//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/DynamoDbMemoryDb.h>

namespace AwsMock::Database {

  DynamoDbMemoryDb::DynamoDbMemoryDb() : _logger(Poco::Logger::get("DynamoDbMemoryDb")) {}

  bool DynamoDbMemoryDb::DatabaseExists(const std::string &region, const std::string &name) {

    return find_if(_dynamoDbs.begin(), _dynamoDbs.end(), [region, name](const std::pair<std::string, Entity::DynamoDb::DynamoDb> &dynamoDb) {
      return dynamoDb.second.region == region && dynamoDb.second.name == name;
    }) != _dynamoDbs.end();
  }

  bool DynamoDbMemoryDb::TableExists(const std::string &region, const std::string &tableName) {

    return find_if(_tables.begin(), _tables.end(), [region, tableName](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
      return table.second.region == region && table.second.name == tableName;
    }) != _tables.end();
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
      throw Core::DatabaseException("Get table by ID failed, oid: "+oid);
    }

    it->second.oid = oid;
    return it->second;
  }

  Entity::DynamoDb::DynamoDb DynamoDbMemoryDb::GetDatabaseByName(const std::string &region, const std::string &name) {

    auto it = find_if(_dynamoDbs.begin(), _dynamoDbs.end(), [region, name](const std::pair<std::string, Entity::DynamoDb::DynamoDb> &dynamoDb) {
      return dynamoDb.second.region == region && dynamoDb.second.name == name;
    });

    if (it == _dynamoDbs.end()) {
      log_error_stream(_logger) << "Get DynamoDb by name failed, region: " << region << " name: " << name << std::endl;
      throw Core::DatabaseException("Get DynamoDb by name failed, region: " + region + " name: " + name);
    }

    it->second.oid = it->first;
    return it->second;
  }

  /*long LambdaMemoryDb::LambdaCount(const std::string &region) {

    long count = 0;
    if (region.empty()) {
      return static_cast<long>(_lambdas.size());
    } else {
      for (const auto &lambda : _lambdas) {
        if (lambda.second.region == region) {
          count++;
        }
      }
    }
    return count;
  }

  Entity::Lambda::Lambda LambdaMemoryDb::UpdateLambda(const Entity::Lambda::Lambda &lambda) {

    Poco::ScopedLock lock(_lambdaMutex);

    std::string region = lambda.region;
    std::string function = lambda.function;
    auto it = find_if(_lambdas.begin(), _lambdas.end(), [region, function](const std::pair<std::string, Entity::Lambda::Lambda> &lambda) {
      return lambda.second.region == region && lambda.second.function == function;
    });

    if(it == _lambdas.end()) {
      log_error_stream(_logger) << "Update lambda failed, region: " << lambda.region << " function: " << lambda.function << std::endl;
      throw Core::DatabaseException("Update lambda failed, region: " + lambda.region + " function: " + lambda.function);
    }
    _lambdas[it->first] = lambda;
    return _lambdas[it->first];
  }*/

  void DynamoDbMemoryDb::DeleteTable(const std::string &tableName) {
    Poco::ScopedLock lock(_tableMutex);

    const auto count = std::erase_if(_tables, [tableName](const auto &item) {
      auto const &[key, value] = item;
      return value.name == tableName;
    });
    log_debug_stream(_logger) << "Lambda deleted, count: " << count << std::endl;
  }

  void DynamoDbMemoryDb::DeleteAllTables() {
    Poco::ScopedLock lock(_tableMutex);

    log_debug_stream(_logger) << "All DynamoDb tables deleted, count: " << _tables.size() << std::endl;
    _tables.clear();
  }
}