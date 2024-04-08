//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/SecretsManagerDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  SecretsManagerDatabase::SecretsManagerDatabase() : _logger(Poco::Logger::get("LambdaDatabase")), _useDatabase(HasDatabase()), _databaseName(GetDatabaseName()), _memoryDb(SecretsManagerMemoryDb::instance()) {}

} // namespace AwsMock::Database
