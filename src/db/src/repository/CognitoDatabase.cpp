//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/CognitoDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  CognitoDatabase::CognitoDatabase(Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("CognitoDatabase")), _memoryDb(CognitoMemoryDb::instance()) {

    if (HasDatabase()) {

      // Get collections
      _userPoolCollection = GetConnection()["cognito_userpool"];

    }
  }

  bool CognitoDatabase::UserPoolExists(const std::string &region, const std::string &name) {

    if (HasDatabase()) {

      try {

        int64_t count = _userPoolCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
        log_trace_stream(_logger) << "Cognito user pool exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UserPoolExists(region, name);

    }
  }
  bool CognitoDatabase::UserPoolExists(const std::string &id) {

    if (HasDatabase()) {

      try {

        int64_t count = _userPoolCollection.count_documents(make_document(kvp("id", id)));
        log_trace_stream(_logger) << "Cognito user pool exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UserPoolExists(id);

    }
  }

  Entity::Cognito::UserPool CognitoDatabase::CreateUserPool(const Entity::Cognito::UserPool &userPool) {

    if (HasDatabase()) {

      try {
        auto result = _userPoolCollection.insert_one(userPool.ToDocument());
        log_trace_stream(_logger) << "User pool created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;
        return GetUserPoolById(result->inserted_id().get_oid().value);

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CreateUserPool(userPool);

    }
  }

  Entity::Cognito::UserPool CognitoDatabase::GetUserPoolById(bsoncxx::oid oid) {

    try {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _userPoolCollection.find_one(make_document(kvp("_id", oid)));
      if (!mResult) {
        _logger.error() << "Database exception: Cognito not found " << std::endl;
        throw Core::DatabaseException("Database exception, Cognito not found ", 500);
      }

      Entity::Cognito::UserPool result;
      result.FromDocument(mResult);
      return result;

    } catch (const mongocxx::exception &exc) {
      _logger.error() << "Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
    }

  }

  Entity::Cognito::UserPool CognitoDatabase::GetUserPoolByRegionName(const std::string &region, const std::string &name) {

    try {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _userPoolCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
      if (!mResult) {
        _logger.error() << "Database exception: Cognito not found " << std::endl;
        throw Core::DatabaseException("Database exception, Cognito not found ", 500);
      }

      Entity::Cognito::UserPool result;
      result.FromDocument(mResult);
      return result;

    } catch (const mongocxx::exception &exc) {
      _logger.error() << "Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
    }

  }

  /*  Entity::Cognito::Cognito CognitoDatabase::CreateOrUpdateCognito(const Entity::Cognito::Cognito &cognito) {

    if (CognitoExists(cognito)) {
      return UpdateCognito(cognito);
    } else {
      return CreateCognito(cognito);
    }
  }*/

  Entity::Cognito::UserPool CognitoDatabase::UpdateUserPool(const Entity::Cognito::UserPool &userPool) {

    if (HasDatabase()) {

      try {
        auto result = _userPoolCollection.replace_one(make_document(kvp("region", userPool.region), kvp("name", userPool.name)), userPool.ToDocument());

        log_trace_stream(_logger) << "Cognito user pool updated: " << userPool.ToString() << std::endl;

        return GetUserPoolByRegionName(userPool.region, userPool.name);

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UpdateUserPool(userPool);

    }
  }

  std::vector<Entity::Cognito::UserPool> CognitoDatabase::ListUserPools(const std::string &region) {

    std::vector<Entity::Cognito::UserPool> userPools;
    if (HasDatabase()) {

      try {

        if(region.empty()) {

          auto userPoolCursor = _userPoolCollection.find(make_document());
          for (auto userPool : userPoolCursor) {
            Entity::Cognito::UserPool result;
            result.FromDocument(userPool);
            userPools.push_back(result);
          }

        } else {
          auto userPoolCursor = _userPoolCollection.find(make_document(kvp("region", region)));
          for (auto userPool : userPoolCursor) {
            Entity::Cognito::UserPool result;
            result.FromDocument(userPool);
            userPools.push_back(result);
          }
        }
      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      userPools = _memoryDb.ListUserPools(region);
    }

    log_trace_stream(_logger) << "Got user pool list, size:" << userPools.size() << std::endl;
    return userPools;
  }

  long CognitoDatabase::CountUserPools(const std::string &region) {

    if (HasDatabase()) {

      try {
        long count = 0;
        if (region.empty()) {
          count = _userPoolCollection.count_documents(make_document());
        } else {
          count = _userPoolCollection.count_documents(make_document(kvp("region", region)));
        }
        log_trace_stream(_logger) << "lambda count: " << count << std::endl;
        return count;

      } catch (mongocxx::exception::system_error &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CountUserPools(region);

    }
  }

  void CognitoDatabase::DeleteUserPool(const std::string &id) {

    if (HasDatabase()) {

      try {

        auto result = _userPoolCollection.delete_many(make_document(kvp("id", id)));
        log_debug_stream(_logger) << "User pool deleted, id: " << id << " count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteUserPool(id);

    }
  }

  void CognitoDatabase::DeleteAllUserPools() {

    if (HasDatabase()) {

      try {

        auto result = _userPoolCollection.delete_many({});
        log_debug_stream(_logger) << "All cognito user pools deleted, count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteAllUserPools();

    }
  }

} // namespace AwsMock::Database
