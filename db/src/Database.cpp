//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/Database.h"

namespace AwsMock::Database {

    Database::Database(const Core::Configuration &configuration) : _logger(Poco::Logger::get("Database")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("Database");

        uri = mongocxx::uri("mongodb://" + _configuration.getString("awsmock.mongodb.host", "localhost") + ":"
                                + std::to_string(_configuration.getInt("awsmock.mongodb.port", 27017))
                                + "/?maxPoolSize=32");
        _connectionPool = std::make_shared<mongocxx::pool>(uri);
        poco_debug(_logger, "MongoDB connection pool initialized");
    }

    void Database::CreateCollection(const std::string &name) {
        mongocxx::database _database = GetConnection();
        if (!_database.has_collection(name)) {
            _database.create_collection(name);
            _logger.debug() << "Collection created, name: " << name;
        }
    }

    void Database::DropCollection(const std::string &name) {
        mongocxx::database _database = GetConnection();
        if (!_database.has_collection(name)) {
            _database.drop();
            _logger.debug() << "Collection dropped, name: " << name;
        }
    }

    mongocxx::database Database::GetConnection() {
        auto client = _connectionPool->acquire();
        return client->database("awsmock");
    }

    mongocxx::database Database::GetCollection() {
        mongocxx::client client{ uri };
        return client["awsmock"];
    }

} // namespace AwsMock::Database
