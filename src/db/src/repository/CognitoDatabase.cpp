//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/CognitoDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  CognitoDatabase::CognitoDatabase()
      : _logger(Poco::Logger::get("CognitoDatabase")), _memoryDb(CognitoMemoryDb::instance()),
        _hasDatabase(Database::HasDatabase()), _databaseName(GetDatabaseName()) {}

  bool CognitoDatabase::UserPoolExists(const std::string &region, const std::string &name) {

    if (_hasDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
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

    if (_hasDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
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

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _userPoolCollection.insert_one(userPool.ToDocument());
        session.commit_transaction();
        log_trace_stream(_logger) << "User pool created, oid: " << result->inserted_id().get_oid().value.to_string()
                                  << std::endl;
        return GetUserPoolById(result->inserted_id().get_oid().value);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CreateUserPool(userPool);

    }
  }

  Entity::Cognito::UserPool CognitoDatabase::GetUserPoolById(bsoncxx::oid oid) {

    try {

      auto client = GetClient();
      mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
      mongocxx::stdx::optional<bsoncxx::document::value>
          mResult = _userPoolCollection.find_one(make_document(kvp("_id", oid)));
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

  Entity::Cognito::UserPool CognitoDatabase::GetUserPoolByRegionName(const std::string &region,
                                                                     const std::string &name) {

    if (_hasDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
        mongocxx::stdx::optional<bsoncxx::document::value>
            mResult = _userPoolCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
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

    } else {

      return _memoryDb.GetUserPoolByRegionName(region, name);

    }
  }

  Entity::Cognito::UserPool CognitoDatabase::CreateOrUpdateUserPool(Entity::Cognito::UserPool &userPool) {

    if (UserPoolExists(userPool.region, userPool.name)) {

      return UpdateUserPool(userPool);

    } else {

      return CreateUserPool(userPool);

    }
  }

  Entity::Cognito::UserPool CognitoDatabase::UpdateUserPool(const Entity::Cognito::UserPool &userPool) {

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result =
            _userPoolCollection.replace_one(make_document(kvp("region", userPool.region), kvp("name", userPool.name)),
                                            userPool.ToDocument());
        session.commit_transaction();
        log_trace_stream(_logger) << "Cognito user pool updated: " << userPool.ToString() << std::endl;
        return GetUserPoolByRegionName(userPool.region, userPool.name);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UpdateUserPool(userPool);

    }
  }

  std::vector<Entity::Cognito::UserPool> CognitoDatabase::ListUserPools(const std::string &region) {

    std::vector<Entity::Cognito::UserPool> userPools;
    if (_hasDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
        if (region.empty()) {

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

    if (_hasDatabase) {

      try {
        long count = 0;
        auto client = GetClient();
        mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
        if (region.empty()) {
          count = _userPoolCollection.count_documents(make_document());
        } else {
          count = _userPoolCollection.count_documents(make_document(kvp("region", region)));
        }
        log_trace_stream(_logger) << "User pool count: " << count << std::endl;
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

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _userPoolCollection.delete_many(make_document(kvp("id", id)));
        session.commit_transaction();
        log_debug_stream(_logger) << "User pool deleted, id: " << id << " count: " << result->deleted_count()
                                  << std::endl;

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteUserPool(id);

    }
  }

  void CognitoDatabase::DeleteAllUserPools() {

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userPoolCollection = (*client)[_databaseName]["cognito_userpool"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _userPoolCollection.delete_many({});
        session.commit_transaction();
        log_debug_stream(_logger) << "All cognito user pools deleted, count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteAllUserPools();

    }
  }

  bool CognitoDatabase::UserExists(const std::string &region,
                                   const std::string &userPoolId,
                                   const std::string &userName) {

    if (_hasDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
        int64_t count = _userCollection.count_documents(make_document(kvp("region", region),
                                                                      kvp("userPoolId", userPoolId),
                                                                      kvp("userName", userName)));
        log_trace_stream(_logger) << "Cognito user exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UserExists(region, userPoolId, userName);

    }
  }

  Entity::Cognito::User CognitoDatabase::CreateUser(const Entity::Cognito::User &user) {

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _userCollection.insert_one(user.ToDocument());
        session.commit_transaction();
        log_trace_stream(_logger) << "User created, oid: " << result->inserted_id().get_oid().value.to_string()
                                  << std::endl;
        return GetUserById(result->inserted_id().get_oid().value);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CreateUser(user);

    }
  }

  Entity::Cognito::User CognitoDatabase::GetUserById(bsoncxx::oid oid) {

    try {

      auto client = GetClient();
      mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
      mongocxx::stdx::optional<bsoncxx::document::value>
          mResult = _userCollection.find_one(make_document(kvp("_id", oid)));
      if (!mResult) {
        _logger.error() << "Database exception: user not found " << std::endl;
        throw Core::DatabaseException("Database exception, user not found ", 500);
      }

      Entity::Cognito::User result;
      result.FromDocument(mResult);
      return result;

    } catch (const mongocxx::exception &exc) {
      _logger.error() << "Database exception " << exc.what() << std::endl;
      throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
    }

  }

  Entity::Cognito::User CognitoDatabase::GetUserByUserName(const std::string &region,
                                                           const std::string &userPoolId,
                                                           const std::string &userName) {

    if (_hasDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
        auto mResult = _userCollection.find_one(make_document(kvp("region", region),
                                                              kvp("userPoolId", userPoolId),
                                                              kvp("userName", userName)));
        if (!mResult) {
          _logger.error() << "Database exception: user not found " << std::endl;
          throw Core::DatabaseException("Database exception, user not found ", 500);
        }

        Entity::Cognito::User result;
        result.FromDocument(mResult);
        return result;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.GetUserByUserName(region, userPoolId, userName);

    }
  }

  Entity::Cognito::User CognitoDatabase::GetUserById(const std::string &oid) {

    if (_hasDatabase) {

      return GetUserById(bsoncxx::oid(oid));

    } else {

      return _memoryDb.GetUserByOid(oid);

    }

  }

  long CognitoDatabase::CountUsers(const std::string &region, const std::string &userPoolId) {

    if (_hasDatabase) {

      try {

        long count = 0;
        auto client = GetClient();
        mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
        if (!region.empty() && !userPoolId.empty()) {
          count = _userCollection.count_documents(make_document(kvp("region", region), kvp("userPoolId", userPoolId)));
        } else if (!region.empty()) {
          count = _userCollection.count_documents(make_document(kvp("region", region)));
        } else {
          count = _userCollection.count_documents(make_document());
        }
        log_trace_stream(_logger) << "User count: " << count << std::endl;
        return count;

      } catch (mongocxx::exception::system_error &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.CountUsers(region);

    }
  }

  std::vector<Entity::Cognito::User> CognitoDatabase::ListUsers(const std::string &region,
                                                                const std::string &userPoolId) {

    std::vector<Entity::Cognito::User> users;
    if (_hasDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
        if (!region.empty() && !userPoolId.empty()) {

          auto userCursor = _userCollection.find(make_document(kvp("region", region), kvp("userPoolId", userPoolId)));
          for (auto user : userCursor) {
            Entity::Cognito::User result;
            result.FromDocument(user);
            users.push_back(result);
          }

        } else if (!region.empty()) {

          auto userCursor = _userCollection.find(make_document(kvp("region", region)));
          for (auto user : userCursor) {
            Entity::Cognito::User result;
            result.FromDocument(user);
            users.push_back(result);
          }

        } else {

          auto userCursor = _userCollection.find(make_document());
          for (auto user : userCursor) {
            Entity::Cognito::User result;
            result.FromDocument(user);
            users.push_back(result);
          }
        }

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      users = _memoryDb.ListUsers(region, userPoolId);
    }

    log_trace_stream(_logger) << "Got user list, size:" << users.size() << std::endl;
    return users;
  }

  Entity::Cognito::User CognitoDatabase::UpdateUser(const Entity::Cognito::User &user) {

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _userCollection.replace_one(make_document(kvp("region", user.region),
                                                                kvp("userPoolId", user.userPoolId),
                                                                kvp("userName", user.userName)), user.ToDocument());
        session.commit_transaction();
        log_trace_stream(_logger) << "Cognito user updated: " << user.ToString() << std::endl;
        return GetUserByUserName(user.region, user.userPoolId, user.userName);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      return _memoryDb.UpdateUser(user);

    }
  }

  Entity::Cognito::User CognitoDatabase::CreateOrUpdateUser(Entity::Cognito::User &user) {

    if (UserExists(user.region, user.userPoolId, user.userName)) {

      return UpdateUser(user);

    } else {

      return CreateUser(user);

    }
  }

  void CognitoDatabase::DeleteUser(const Entity::Cognito::User &user) {

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _userCollection.delete_many(make_document(kvp("region", user.region),
                                                                kvp("userPoolId", user.userPoolId),
                                                                kvp("userName", user.userName)));
        session.commit_transaction();
        log_debug_stream(_logger) << "User deleted, userName: " << user.userName << " count: "
                                  << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteUser(user);

    }
  }

  void CognitoDatabase::DeleteAllUsers() {

    if (_hasDatabase) {

      auto client = GetClient();
      mongocxx::collection _userCollection = (*client)[_databaseName]["cognito_user"];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _userCollection.delete_many({});
        session.commit_transaction();
        log_debug_stream(_logger) << "All cognito users deleted, count: " << result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
      }

    } else {

      _memoryDb.DeleteAllUsers();

    }
  }

} // namespace AwsMock::Database
