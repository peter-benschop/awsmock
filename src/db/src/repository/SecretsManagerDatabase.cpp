//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/SecretsManagerDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  SecretsManagerDatabase::SecretsManagerDatabase()
    : _logger(Poco::Logger::get("SecretsManagerDatabase")), _useDatabase(HasDatabase()),
      _databaseName(GetDatabaseName()), _collectionName("secretsmanager_secret"),
      _memoryDb(SecretsManagerMemoryDb::instance()) {}

  bool SecretsManagerDatabase::SecretExists(const std::string &region, const std::string &name) {

    if (_useDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _secretCollection = (*client)[_databaseName][_collectionName];

        int64_t count = _secretCollection.count_documents(make_document(kvp("region", region), kvp("name", name)));
        log_trace_stream(_logger) << "Secret exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
      }

    } else {

      return _memoryDb.SecretExists(region, name);

    }
  }

  bool SecretsManagerDatabase::SecretExists(const Entity::SecretsManager::Secret &secret) {
    return SecretExists(secret.region, secret.name);
  }

  bool SecretsManagerDatabase::SecretExists(const std::string &secretId) {

    if (_useDatabase) {

      try {

        auto client = GetClient();
        mongocxx::collection _secretCollection = (*client)[_databaseName][_collectionName];

        int64_t count = _secretCollection.count_documents(make_document(kvp("secretId", secretId)));
        log_trace_stream(_logger) << "Secret exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;

      } catch (const mongocxx::exception &exc) {
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
      }

    } else {

      return _memoryDb.SecretExists(secretId);

    }
  }

  Entity::SecretsManager::Secret SecretsManagerDatabase::GetSecretById(bsoncxx::oid oid) {

    auto client = GetClient();
    mongocxx::collection _secretCollection = (*client)[_databaseName][_collectionName];

    mongocxx::stdx::optional<bsoncxx::document::value>
      mResult = _secretCollection.find_one(make_document(kvp("_id", oid)));
    Entity::SecretsManager::Secret result;
    result.FromDocument(mResult);

    return result;
  }

  Entity::SecretsManager::Secret SecretsManagerDatabase::GetSecretById(const std::string &oid) {

    if (_useDatabase) {

      return GetSecretById(bsoncxx::oid(oid));

    } else {

      return _memoryDb.GetSecretById(oid);

    }
  }

  Entity::SecretsManager::Secret SecretsManagerDatabase::GetSecretByRegionName(const std::string &region,
                                                                               const std::string &name) {

    if (_useDatabase) {

      auto client = GetClient();
      mongocxx::collection _bucketCollection = (*client)[_databaseName][_collectionName];
      mongocxx::stdx::optional<bsoncxx::document::value>
        mResult = _bucketCollection.find_one(make_document(kvp("region", region), kvp("name", name)));
      if (mResult->empty()) {
        return {};
      }

      Entity::SecretsManager::Secret result;
      result.FromDocument(mResult);
      log_trace_stream(_logger) << "Got secret: " << result.ToString() << std::endl;
      return result;

    } else {

      return _memoryDb.GetSecretByRegionName(region, name);

    }
  }

  Entity::SecretsManager::Secret SecretsManagerDatabase::GetSecretBySecretId(const std::string &secretId) {

    if (_useDatabase) {

      auto client = GetClient();
      mongocxx::collection _bucketCollection = (*client)[_databaseName][_collectionName];
      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _bucketCollection.find_one(make_document(kvp("secretId", secretId)));
      if (mResult->empty()) {
        return {};
      }

      Entity::SecretsManager::Secret result;
      result.FromDocument(mResult);
      log_trace_stream(_logger) << "Got secret: " << result.ToString() << std::endl;
      return result;

    } else {

      return _memoryDb.GetSecretBySecretId(secretId);

    }
  }

  Entity::SecretsManager::Secret SecretsManagerDatabase::CreateSecret(const Entity::SecretsManager::Secret &secret) {

    if (_useDatabase) {

      auto client = GetClient();
      mongocxx::collection _secretCollection = (*client)[_databaseName][_collectionName];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto insert_one_result = _secretCollection.insert_one(secret.ToDocument());
        session.commit_transaction();
        log_trace_stream(_logger) << "Secret created, oid: "
                                  << insert_one_result->inserted_id().get_oid().value.to_string() << std::endl;

        return GetSecretById(insert_one_result->inserted_id().get_oid().value);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), Poco::Net::HTTPResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR);
      }

    } else {

      return _memoryDb.CreateSecret(secret);

    }
  }

  Entity::SecretsManager::Secret SecretsManagerDatabase::UpdateSecret(const Entity::SecretsManager::Secret &secret) {

    if (_useDatabase) {

      auto client = GetClient();
      mongocxx::collection _secretCollection = (*client)[_databaseName][_collectionName];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto result = _secretCollection.replace_one(make_document(kvp("secretId", secret.secretId)), secret.ToDocument());
        session.commit_transaction();
        log_trace_stream(_logger) << "Bucket updated: " << secret.ToString() << std::endl;

        return GetSecretBySecretId(secret.secretId);

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      return _memoryDb.UpdateSecret(secret);
    }
  }

  Entity::SecretsManager::Secret SecretsManagerDatabase::CreateOrUpdateSecret(const Entity::SecretsManager::Secret &secret) {

    if (SecretExists(secret)) {

      return UpdateSecret(secret);

    } else {

      return CreateSecret(secret);
    }
  }

  Entity::SecretsManager::SecretList SecretsManagerDatabase::ListSecrets() {

    Entity::SecretsManager::SecretList secretList;
    if (_useDatabase) {

      auto client = GetClient();
      mongocxx::collection _secretCollection = (*client)[_databaseName][_collectionName];

      auto secretCursor = _secretCollection.find({});
      for (auto bucket : secretCursor) {
        Entity::SecretsManager::Secret result;
        result.FromDocument(bucket);
        secretList.push_back(result);
      }

    } else {

      secretList = _memoryDb.ListSecrets();

    }
    log_trace_stream(_logger) << "Got secret list, size:" << secretList.size() << std::endl;
    return secretList;
  }

  void SecretsManagerDatabase::DeleteSecret(const Entity::SecretsManager::Secret &secret) {

    if (_useDatabase) {

      auto client = GetClient();
      mongocxx::collection _bucketCollection = (*client)[_databaseName][_collectionName];
      auto session = client->start_session();

      try {

        session.start_transaction();
        auto delete_many_result =
          _bucketCollection.delete_one(make_document(kvp("region", secret.region), kvp("name", secret.name)));
        session.commit_transaction();
        log_debug_stream(_logger) << "Secret deleted, count: " << delete_many_result->deleted_count() << std::endl;

      } catch (const mongocxx::exception &exc) {
        session.abort_transaction();
        _logger.error() << "Database exception " << exc.what() << std::endl;
        throw Core::DatabaseException(exc.what(), 500);
      }

    } else {

      _memoryDb.DeleteSecret(secret);

    }
  }
} // namespace AwsMock::Database
