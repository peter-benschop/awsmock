//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/DynamoDbDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  DynamoDbDatabase::DynamoDbDatabase(Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("DynamoDbDatabase")), _memoryDb(DynamoDbMemoryDb::instance()) {

    if (HasDatabase()) {

      // Get collection
      _dynamodbCollection = GetConnection()["dynamodb"];
      _tableCollection = GetConnection()["dynamodb_table"];

    }
  }

  bool DynamoDbDatabase::DatabaseExists(const std::string &region, const std::string &name) {

    if (HasDatabase()) {

      try {

        int64_t count = _dynamodbCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
        log_trace_stream(_logger) << "DynamoDb database exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.DatabaseExists(region, name);

    }
  }

  Entity::DynamoDb::DynamoDb DynamoDbDatabase::GetDatabaseByName(const std::string &region, const std::string &name) {

    if (HasDatabase()) {

      try {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _dynamodbCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
        if (!mResult) {
          _logger.error() << "Database exception: DynamoDb not found " << std::endl;
          throw Core::DatabaseException("Database exception, DynamoDb not found ", 500);
        }

        Entity::DynamoDb::DynamoDb result;
        result.FromDocument(mResult);
        return result;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get DynamoDb by name failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.GetDatabaseByName(region, name);
    }
    return {};
  }

  /*bool LambdaDatabase::LambdaExists(const Entity::Lambda::Lambda &lambda) {

    return LambdaExists(lambda.region, lambda.function, lambda.runtime);
  }

  bool LambdaDatabase::LambdaExists(const std::string &functionName) {

    if (HasDatabase()) {

      try {

        int64_t count = _lambdaCollection.count_documents(make_document(kvp("function", functionName)));
        log_trace_stream(_logger) << "lambda function exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.LambdaExists(functionName);

    }
  }

  bool LambdaDatabase::LambdaExistsByArn(const std::string &arn) {

    if (HasDatabase()) {

      try {

        int64_t count = _lambdaCollection.count_documents(make_document(kvp("arn", arn)));
        log_trace_stream(_logger) << "lambda function exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.LambdaExistsByArn(arn);

    }
  }

  long LambdaDatabase::LambdaCount(const std::string &region) {

    if (HasDatabase()) {

      bsoncxx::builder::basic::document builder;
      if (!region.empty()) {
        builder.append(bsoncxx::builder::basic::kvp("region", region));
      }
      bsoncxx::document::value filter = builder.extract();

      try {
        long count = _lambdaCollection.count_documents({filter});
        log_trace_stream(_logger) << "lambda count: " << count << std::endl;
        return count;

      } catch (mongocxx::exception::system_error &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.LambdaCount(region);

    }
    return -1;
  }*/

  Entity::DynamoDb::Table DynamoDbDatabase::CreateTable(const Entity::DynamoDb::Table &table) {

    if (HasDatabase()) {

      try {
        auto result = _tableCollection.insert_one(table.ToDocument());
        log_trace_stream(_logger) << "DynamoDb table created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;
        return GetTableById(result->inserted_id().get_oid().value);

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CreateTable(table);

    }
  }

  Entity::DynamoDb::Table DynamoDbDatabase::GetTableById(bsoncxx::oid oid) {

    try {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _tableCollection.find_one(make_document(kvp("_id", oid)));
      if (!mResult) {
        _logger.error() << "Database exception: Table not found " << std::endl;
        throw Core::DatabaseException("Database exception, Table not found ", 500);
      }

      Entity::DynamoDb::Table result;
      result.FromDocument(mResult);
      _logger.debug() << "Got table by ID, table: " << result.ToString() << std::endl;
      return result;

    } catch (const mongocxx::exception &exc) {
      _logger.error() << "Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
    }

  }

  Entity::DynamoDb::Table DynamoDbDatabase::GetTableById(const std::string &oid) {

    if (HasDatabase()) {

      return GetTableById(bsoncxx::oid(oid));

    } else {

      return _memoryDb.GetTableById(oid);
    }
  }

/*  Entity::Lambda::Lambda LambdaDatabase::GetLambdaByArn(const std::string &arn) {

    if (HasDatabase()) {

      try {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _lambdaCollection.find_one(make_document(kvp("arn", arn)));
        if (!mResult) {
          _logger.error() << "Database exception: Lambda not found " << std::endl;
          throw Core::DatabaseException("Database exception, Lambda not found ", 500);
        }

        Entity::Lambda::Lambda result;
        result.FromDocument(mResult);
        return result;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get lambda by ARN failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.GetLambdaByArn(arn);
    }
    return {};
  }

  Entity::Lambda::Lambda LambdaDatabase::CreateOrUpdateLambda(const Entity::Lambda::Lambda &lambda) {

    if (LambdaExists(lambda)) {
      return UpdateLambda(lambda);
    } else {
      return CreateLambda(lambda);
    }
  }

  Entity::Lambda::Lambda LambdaDatabase::UpdateLambda(const Entity::Lambda::Lambda &lambda) {

    if (HasDatabase()) {

      try {
        auto result = _lambdaCollection.replace_one(make_document(kvp("region", lambda.region), kvp("function", lambda.function), kvp("runtime", lambda.runtime)), lambda.ToDocument());

        log_trace_stream(_logger) << "lambda updated: " << lambda.ToString() << std::endl;

        return GetLambdaByArn(lambda.arn);

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UpdateLambda(lambda);

    }
  }*/

  bool DynamoDbDatabase::TableExists(const std::string &region, const std::string &tableName) {

    if (HasDatabase()) {

      try {

        int64_t count;
        if(!region.empty()) {
          count = _tableCollection.count_documents(make_document(kvp("region", region), kvp("name", tableName)));
        } else {
          count = _tableCollection.count_documents(make_document(kvp("name", tableName)));
        }
        log_trace_stream(_logger) << "DynamoDb table exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.TableExists(region, tableName);

    }
  }

  std::vector<Entity::DynamoDb::Table> DynamoDbDatabase::ListTables(const std::string &region) {

    std::vector<Entity::DynamoDb::Table> tables;
    if (HasDatabase()) {

      try {

        if(region.empty()) {

          auto lambdaCursor = _tableCollection.find({});
          for (auto lambda : lambdaCursor) {
            Entity::DynamoDb::Table result;
            result.FromDocument(lambda);
            tables.push_back(result);
          }
        } else{
          auto lambdaCursor = _tableCollection.find(make_document(kvp("region", region)));
          for (auto lambda : lambdaCursor) {
            Entity::DynamoDb::Table result;
            result.FromDocument(lambda);
            tables.push_back(result);
          }

        }

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      tables = _memoryDb.ListTables(region);
    }

    log_trace_stream(_logger) << "Got DynamoDb table list, size:" << tables.size() << std::endl;
    return tables;
  }

  void DynamoDbDatabase::DeleteTable(const std::string &tableName) {

    if (HasDatabase()) {

      try {

        auto result = _tableCollection.delete_many(make_document(kvp("name", tableName)));
        log_debug_stream(_logger) << "DynamoDB table deleted, tableName: " << tableName << " count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteTable(tableName);

    }
  }

  void DynamoDbDatabase::DeleteAllTables() {

    if (HasDatabase()) {

      try {

        auto result = _tableCollection.delete_many({});
        log_debug_stream(_logger) << "All DynamoDb tables deleted, count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteAllTables();

    }
  }

} // namespace AwsMock::Database
