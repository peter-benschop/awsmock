//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_DYNAMODB_MEMORYDB_H
#define AWSMOCK_REPOSITORY_DYNAMODB_MEMORYDB_H

// C++ standard includes
#include <string>
#include <vector>
#include <iostream>

// Poco includes
#include <Poco/Mutex.h>
#include <Poco/ScopedLock.h>
#include <Poco/SingletonHolder.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include <awsmock/core/DatabaseException.h>
#include <awsmock/core/DirUtils.h>
#include <awsmock/core/FileUtils.h>
#include <awsmock/entity/dynamodb/Item.h>
#include "awsmock/entity/dynamodb/Table.h"
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

  class DynamoDbMemoryDb {

    public:

      /**
       * Constructor
       */
      DynamoDbMemoryDb();

      /**
       * Singleton instance
       */
      static DynamoDbMemoryDb &instance() {
        static Poco::SingletonHolder<DynamoDbMemoryDb> sh;
        return *sh.get();
      }

      /**
       * Check existence of DynamoDb table
       *
       * @param region AWS region name
       * @param tableName table name
       * @return true if DynamoDb table already exists
       * @throws DatabaseException
       */
      bool TableExists(const std::string &region, const std::string &tableName);

      /**
       * Create a new DynamoDb table
       *
       * @param table DynamoDb table
       * @return created DynamoDb table.
       */
      Entity::DynamoDb::Table CreateTable(const Entity::DynamoDb::Table &table);

      /**
       * Returns a table entity by primary key
       *
       * @param oid table primary key
       * @return table entity
       * @throws DatabaseException
       */
      Entity::DynamoDb::Table GetTableById(const std::string &oid);

      /**
       * Returns a list of DynamoDB tables
       *
       * @param region AWS region name
       * @return list of DynamoDB tables
       */
      std::vector<Entity::DynamoDb::Table> ListTables(const std::string &region = {});

      /**
       * Deletes an existing DynamoDB table
       *
       * @param tableName name of the table
       * @throws DatabaseException
       */
      void DeleteTable(const std::string &tableName);

      /**
       * Deletes all existing DynamoDB tables
       *
       * @throws DatabaseException
       */
      void DeleteAllTables();

      /**
       * Checks the existence of an item.
       *
       * @param region AWS region.
       * @param tableName name of the table
       * @param key primary key of the item
       * @return true if database exists, otherwise false
       */
      bool ItemExists(const std::string &region, const std::string &tableName, const std::string & key);

      /**
       * Deletes an item
       *
       * @param region AWS region.
       * @param tableName name of the table
       * @param key primary key of the item
       * @return true if database exists, otherwise false
       */
      void DeleteItem(const std::string &region, const std::string &tableName, const std::string & key);

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Table map
       */
      std::map<std::string, Entity::DynamoDb::Table> _tables{};

      /**
       * Item map
       */
      std::map<std::string, Entity::DynamoDb::Item> _items{};

      /**
       * Table mutex
       */
      Poco::Mutex _tableMutex;

      /**
       * Item mutex
       */
      Poco::Mutex _itemMutex;
  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_DYNAMODB_MEMORYDB_H
