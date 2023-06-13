//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/Database.h"

namespace AwsMock::Database {

    Database::Database(const Core::Configuration &configuration) : _logger(Poco::Logger::get("Database")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("Database");

        _name = _configuration.getString("awsmock.mongodb.name", "awsmock");
        _host = _configuration.getString("awsmock.mongodb.host", "localhost");
        _port = _configuration.getInt("awsmock.mongodb.port", 27017);

        // MongoDB URI
        _uri = mongocxx::uri("mongodb://" + _host + ":" + std::to_string(_port) + "/?maxPoolSize=32");

        // Define connection pool
        _connectionPool = std::make_shared<mongocxx::pool>(_uri);
        _logger.debug() << "MongoDB connection pool initialized" << std::endl;
    }

    void Database::CreateCollection(const std::string &name) {
        mongocxx::database _database = GetConnection();
        if (!_database.has_collection(name)) {
            _database.create_collection(name);
            _logger.debug() << "Collection created, name: " << name << std::endl << std::endl;
        }
    }

    void Database::DropCollection(const std::string &name) {
        mongocxx::database _database = GetConnection();
        if (!_database.has_collection(name)) {
            _database.drop();
            _logger.debug() << "Collection dropped, name: " << name << std::endl << std::endl;
        }
    }

    mongocxx::database Database::GetConnection() {
        auto client = _connectionPool->acquire();
        return client->database(_name);
    }

    mongocxx::database Database::GetCollection() {
        mongocxx::client client{_uri };
        return client[_name];
    }

} // namespace AwsMock::Database
