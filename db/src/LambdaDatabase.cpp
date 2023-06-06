//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/LambdaDatabase.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    LambdaDatabase::LambdaDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("LambdaDatabase")) {
        Core::Logger::SetDefaultConsoleLogger("LambdaDatabase");
    }

    bool LambdaDatabase::LambdaExists(const std::string &region, const std::string &name) {

        int count = 0;
        Poco::Data::Session session = GetSession();

        session << "SELECT COUNT(*) FROM lambda WHERE region=? AND name=?", bind(region), bind(name), into(count), now;

        session.close();
        poco_trace(_logger, "Lambda exists: " + std::to_string(count));

        return count > 0;
    }

    bool LambdaDatabase::CreateLambda(const std::string &region, const std::string &name) {

        int count = 0;
        Poco::Data::Session session = GetSession();

        session << "SELECT COUNT(*) FROM lambda WHERE region=? AND name=?", bind(region), bind(name), into(count), now;

        session.close();
        poco_trace(_logger, "Lambda exists: " + std::to_string(count));

        return count > 0;
    }

} // namespace AwsMock::Database
