//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/SecretsManagerMemoryDb.h>

namespace AwsMock::Database {

  SecretsManagerMemoryDb::SecretsManagerMemoryDb() : _logger(Poco::Logger::get("SecretsManagerDb")) {}

}