//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/ServiceDatabase.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    ServiceDatabase::ServiceDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("S3Database")) {
        Core::Logger::SetDefaultConsoleLogger("S3Database");
    }

    bool ServiceDatabase::IsActive(const std::string &name) {

        int count = 0;
        /*try {

            Poco::Data::Session session = GetSession();
            session.begin();
            session << "SELECT COUNT(*) FROM service WHERE name=? AND active=1", bind(name), into(count), now;
            session.close();

            poco_trace(_logger, "Service is active: " + std::string(count > 0 ? "true" : "false"));

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Database exception: " + exc.message());
        }*/
        return count > 0;
    }
} // namespace AwsMock::Database
