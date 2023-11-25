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
      _cognitoUserPoolCollection = GetConnection()["cognito"];

    }
  }

  bool CognitoDatabase::UserPoolExists(const std::string &region, const std::string &name) {

    if (HasDatabase()) {

      try {

        int64_t count = _cognitoUserPoolCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
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

/*  bool CognitoDatabase::CognitoExists(const Entity::Cognito::Cognito &cognito) {

    return CognitoExists(cognito.region, cognito.function, cognito.runtime);
  }

  bool CognitoDatabase::CognitoExists(const std::string &functionName) {

    if (HasDatabase()) {

      try {

        int64_t count = _cognitoCollection.count_documents(make_document(kvp("function", functionName)));
        log_trace_stream(_logger) << "cognito function exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CognitoExists(functionName);

    }
  }

  bool CognitoDatabase::CognitoExistsByArn(const std::string &arn) {

    if (HasDatabase()) {

      try {

        int64_t count = _cognitoCollection.count_documents(make_document(kvp("arn", arn)));
        log_trace_stream(_logger) << "cognito function exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CognitoExistsByArn(arn);

    }
  }

  long CognitoDatabase::CognitoCount(const std::string &region) {

    if (HasDatabase()) {

      bsoncxx::builder::basic::document builder;
      if (!region.empty()) {
        builder.append(bsoncxx::builder::basic::kvp("region", region));
      }
      bsoncxx::document::value filter = builder.extract();

      try {
        long count = _cognitoCollection.count_documents({filter});
        log_trace_stream(_logger) << "cognito count: " << count << std::endl;
        return count;

      } catch (mongocxx::exception::system_error &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CognitoCount(region);

    }
    return -1;
  }*/

  Entity::Cognito::UserPool CognitoDatabase::CreateUserPool(const Entity::Cognito::UserPool &userPool) {

    if (HasDatabase()) {

      try {
        auto result = _cognitoUserPoolCollection.insert_one(userPool.ToDocument());
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

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _cognitoUserPoolCollection.find_one(make_document(kvp("_id", oid)));
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
/*
  Entity::Cognito::Cognito CognitoDatabase::GetCognitoById(const std::string &oid) {

    if (HasDatabase()) {

      return GetCognitoById(bsoncxx::oid(oid));

    } else {

      return _memoryDb.GetCognitoById(oid);
    }
  }

  Entity::Cognito::Cognito CognitoDatabase::GetCognitoByArn(const std::string &arn) {

    if (HasDatabase()) {

      try {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _cognitoCollection.find_one(make_document(kvp("arn", arn)));
        if (!mResult) {
          _logger.error() << "Database exception: Cognito not found " << std::endl;
          throw Core::DatabaseException("Database exception, Cognito not found ", 500);
        }

        Entity::Cognito::Cognito result;
        result.FromDocument(mResult);
        return result;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get cognito by ARN failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.GetCognitoByArn(arn);
    }
    return {};
  }

  Entity::Cognito::Cognito CognitoDatabase::CreateOrUpdateCognito(const Entity::Cognito::Cognito &cognito) {

    if (CognitoExists(cognito)) {
      return UpdateCognito(cognito);
    } else {
      return CreateCognito(cognito);
    }
  }

  Entity::Cognito::Cognito CognitoDatabase::UpdateCognito(const Entity::Cognito::Cognito &cognito) {

    if (HasDatabase()) {

      try {
        auto result = _cognitoCollection.replace_one(make_document(kvp("region", cognito.region), kvp("function", cognito.function), kvp("runtime", cognito.runtime)), cognito.ToDocument());

        log_trace_stream(_logger) << "cognito updated: " << cognito.ToString() << std::endl;

        return GetCognitoByArn(cognito.arn);

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UpdateCognito(cognito);

    }
  }

  std::vector<Entity::Cognito::Cognito> CognitoDatabase::ListCognitos(const std::string &region) {

    std::vector<Entity::Cognito::Cognito> cognitos;
    if (HasDatabase()) {

      try {
        auto cognitoCursor = _cognitoCollection.find(make_document(kvp("region", region)));
        for (auto cognito : cognitoCursor) {
          Entity::Cognito::Cognito result;
          result.FromDocument(cognito);
          cognitos.push_back(result);
        }

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      cognitos = _memoryDb.ListCognitos(region);
    }

    log_trace_stream(_logger) << "Got lamda list, size:" << cognitos.size() << std::endl;
    return cognitos;
  }

  void CognitoDatabase::DeleteCognito(const std::string &functionName) {

    if (HasDatabase()) {

      try {

        auto result = _cognitoCollection.delete_many(make_document(kvp("function", functionName)));
        log_debug_stream(_logger) << "cognito deleted, function: " << functionName << " count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteCognito(functionName);

    }
  }

  void CognitoDatabase::DeleteAllCognitos() {

    if (HasDatabase()) {

      try {

        auto result = _cognitoCollection.delete_many({});
        log_debug_stream(_logger) << "All cognitos deleted, count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteAllCognitos();

    }
  }*/

} // namespace AwsMock::Database
