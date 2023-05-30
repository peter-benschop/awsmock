//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/ServiceDatabase.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    ServiceDatabase::ServiceDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("S3Database")) {
        Core::Logger::SetDefaultConsoleLogger("S3Database");
    }

} // namespace AwsMock::Database
