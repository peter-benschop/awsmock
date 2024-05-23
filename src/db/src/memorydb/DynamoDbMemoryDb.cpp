//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/DynamoDbMemoryDb.h>

namespace AwsMock::Database {

    Poco::Mutex DynamoDbMemoryDb::_tableMutex;
    Poco::Mutex DynamoDbMemoryDb::_itemMutex;


    template<typename Map, typename Key>
    bool KeyCompare(Map const &lhs, Map const &rhs, Key const &keys) {

        auto pred = [](auto a, auto b) { return a.first == b.first; };

        return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin(), pred);
    }

    bool DynamoDbMemoryDb::TableExists(const std::string &region, const std::string &tableName) {

        if (!region.empty()) {
            return find_if(_tables.begin(),
                           _tables.end(),
                           [region, tableName](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
                               return table.second.region == region && table.second.name == tableName;
                           }) != _tables.end();
        } else {
            return find_if(_tables.begin(),
                           _tables.end(),
                           [tableName](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
                               return table.second.name == tableName;
                           }) != _tables.end();
        }
    }

    Entity::DynamoDb::TableList DynamoDbMemoryDb::ListTables(const std::string &region) {

        Entity::DynamoDb::TableList tables;
        if (region.empty()) {
            for (const auto &table: _tables) {
                tables.emplace_back(table.second);
            }
        } else {
            for (const auto &table: _tables) {
                if (table.second.region == region) {
                    tables.emplace_back(table.second);
                }
            }
        }

        log_trace << "Got DynamoDB table, size: " << tables.size();
        return tables;
    }

    Entity::DynamoDb::Table DynamoDbMemoryDb::CreateTable(const Entity::DynamoDb::Table &table) {
        Poco::ScopedLock lock(_tableMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _tables[oid] = table;
        log_trace << "Lambda created, oid: " << oid;
        return GetTableById(oid);
    }

    Entity::DynamoDb::Table DynamoDbMemoryDb::GetTableById(const std::string &oid) {

        auto it =
                find_if(_tables.begin(), _tables.end(), [oid](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
                    return table.first == oid;
                });

        if (it == _tables.end()) {
            log_error << "Get table by ID failed, oid: " << oid;
            throw Core::DatabaseException("Get table by ID failed, oid: " + oid);
        }

        it->second.oid = oid;
        return it->second;
    }

    Entity::DynamoDb::Table DynamoDbMemoryDb::GetTableByRegionName(const std::string &region, const std::string &name) {

        auto it = find_if(_tables.begin(),
                          _tables.end(),
                          [region, name](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
                              return table.second.region == region && table.second.name == name;
                          });

        if (it == _tables.end()) {
            log_error << "Get table by region and name failed, region: " << region << " name: " << name;
            throw Core::DatabaseException("Get table by region and name failed, region: " + region + " name: " + name);
        }

        it->second.oid = it->first;
        return it->second;
    }

    Entity::DynamoDb::Table DynamoDbMemoryDb::UpdateTable(const Entity::DynamoDb::Table &table) {
        Poco::ScopedLock lock(_tableMutex);

        std::string region = table.region;
        std::string name = table.name;
        auto it = find_if(_tables.begin(),
                          _tables.end(),
                          [region, name](const std::pair<std::string, Entity::DynamoDb::Table> &table) {
                              return table.second.region == region && table.second.name == name;
                          });
        _tables[it->first] = table;
        return _tables[it->first];
    }

    void DynamoDbMemoryDb::DeleteTable(const std::string &tableName) {
        Poco::ScopedLock lock(_tableMutex);

        const auto count = std::erase_if(_tables, [tableName](const auto &item) {
            auto const &[key, value] = item;
            return value.name == tableName;
        });
        log_debug << "DynamoDB table deleted, count: " << count;
    }

    void DynamoDbMemoryDb::DeleteAllTables() {
        Poco::ScopedLock lock(_tableMutex);

        log_debug << "All DynamoDb tables deleted, count: " << _tables.size();
        _tables.clear();
    }

    bool DynamoDbMemoryDb::ItemExists(const Entity::DynamoDb::Item &item) {

        std::string region = item.region;
        std::string tableName = item.tableName;

        // Get table
        Entity::DynamoDb::Table table = GetTableByRegionName(region, tableName);

        if (!region.empty()) {
            return find_if(_items.begin(),
                           _items.end(),
                           [table, item](const std::pair<std::string, Entity::DynamoDb::Item> &item1) {
                               bool result = item1.second.region == table.region && item1.second.tableName == table.name;
                               result &= KeyCompare(item.attributes, item1.second.attributes, table.keySchemas);
                               return result;
                           }) != _items.end();
        } else {
            return find_if(_items.begin(),
                           _items.end(),
                           [tableName](const std::pair<std::string, Entity::DynamoDb::Item> &item) {
                               return item.second.tableName == tableName;
                           }) != _items.end();
        }
    }

    Entity::DynamoDb::ItemList DynamoDbMemoryDb::ListItems(const std::string &region, const std::string &tableName) {

        Entity::DynamoDb::ItemList items;
        if (region.empty() && tableName.empty()) {

            for (const auto &item: _items) {
                items.emplace_back(item.second);
            }

        } else if (tableName.empty()) {

            for (const auto &item: _items) {
                if (item.second.region == region) {
                    items.emplace_back(item.second);
                }
            }

        } else {

            for (const auto &item: _items) {
                if (item.second.region == region && item.second.tableName == tableName) {
                    items.emplace_back(item.second);
                }
            }
        }

        log_trace << "Got DynamoDB items, size: " << items.size();
        return items;
    }

    long DynamoDbMemoryDb::CountTables(const std::string &region) {

        if (!region.empty()) {

            long count = 0;
            for (const auto &table: _tables) {
                if (table.second.region == region) {
                    count++;
                }
            }
            return count;

        } else {

            return static_cast<long>(_tables.size());
        }
    }

    Entity::DynamoDb::Item DynamoDbMemoryDb::GetItemById(const std::string &oid) {

        auto it =
                find_if(_items.begin(), _items.end(), [oid](const std::pair<std::string, Entity::DynamoDb::Item> &item) {
                    return item.first == oid;
                });

        if (it == _items.end()) {
            log_error << "Get item by ID failed, oid: " << oid;
            throw Core::DatabaseException("Get item by ID failed, oid: " + oid);
        }

        it->second.oid = oid;
        return it->second;
    }

    Entity::DynamoDb::Item DynamoDbMemoryDb::CreateItem(const Entity::DynamoDb::Item &item) {
        Poco::ScopedLock lock(_itemMutex);

        std::string oid = Poco::UUIDGenerator().createRandom().toString();
        _items[oid] = item;
        log_trace << "Item created, oid: " << oid;
        return GetItemById(oid);
    }

    Entity::DynamoDb::Item DynamoDbMemoryDb::UpdateItem(const Entity::DynamoDb::Item &item) {
        Poco::ScopedLock lock(_itemMutex);

        std::string region = item.region;
        std::string tableName = item.tableName;
        auto it = find_if(_items.begin(),
                          _items.end(),
                          [region, tableName](const std::pair<std::string, Entity::DynamoDb::Item> &item) {
                              return item.second.region == region && item.second.tableName == tableName;
                          });
        _items[it->first] = item;
        return _items[it->first];
    }

    long DynamoDbMemoryDb::CountItems(const std::string &region) {

        if (!region.empty()) {
            long count = 0;
            for (const auto &table: _items) {
                if (table.second.region == region) {
                    count++;
                }
            }
            return count;

        } else {

            return static_cast<long>(_items.size());
        }
    }

    void DynamoDbMemoryDb::DeleteItem(const std::string &region, const std::string &tableName, const std::string &key) {
        Poco::ScopedLock lock(_itemMutex);

        const auto count = std::erase_if(_items, [region, tableName, key](const auto &item) {
            auto const &[k, v] = item;
            return v.region == region && v.tableName == tableName;
        });
        log_debug << "DynamoDB items deleted, count: " << count;
    }

    void DynamoDbMemoryDb::DeleteItems(const std::string &region, const std::string &tableName) {
        Poco::ScopedLock lock(_itemMutex);

        const auto count = std::erase_if(_items, [region, tableName](const auto &item) {
            auto const &[k, v] = item;
            return v.region == region && v.tableName == tableName;
        });
        log_debug << "DynamoDB items deleted, tableName: " << tableName << " count: " << count;
    }

    void DynamoDbMemoryDb::DeleteAllItems() {
        Poco::ScopedLock lock(_itemMutex);

        log_debug << "DynamoDB items deleted, count: " << _items.size();

        _items.clear();
    }

}// namespace AwsMock::Database