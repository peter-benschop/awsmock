//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/SecretsManagerDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  SecretsManagerDatabase::SecretsManagerDatabase() : _logger(Poco::Logger::get("SecretsManagerDatabase")), _useDatabase(HasDatabase()), _databaseName(GetDatabaseName()), _collectionName("secretsmanager_secret"), _memoryDb(SecretsManagerMemoryDb::instance()) {}
  
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
  
  Entity::SecretsManager::Secret SecretsManagerDatabase::GetSecretById(bsoncxx::oid oid) {

    auto client = GetClient();
    mongocxx::collection _secretCollection = (*client)[_databaseName][_collectionName];

    mongocxx::stdx::optional<bsoncxx::document::value> mResult = _secretCollection.find_one(make_document(kvp("_id", oid)));
    Entity::SecretsManager::Secret result;
    result.FromDocument(mResult);

    return result;
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
        log_trace_stream(_logger) << "Secret created, oid: " << insert_one_result->inserted_id().get_oid().value.to_string() << std::endl;

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

} // namespace AwsMock::Database
