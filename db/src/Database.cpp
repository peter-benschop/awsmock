//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/Database.h"

namespace AwsMock::Database {

    Database::Database(const Core::Configuration &configuration) : _logger(Poco::Logger::get("Database")), _configuration(configuration) {
        Initialize();
    }

    void Database::Initialize() {

        // Register SQLite connector
        Poco::Data::SQLite::Connector::registerConnector();

        // Create the directory
        std::string dataDir = _configuration.getString("awsmock.db.dir", "/tmp/data");
        std::string dbFile = _configuration.getString("awsmock.db.file", "awsmock.db");

        _dbFile = dataDir + "/db/" + dbFile;
        poco_debug(_logger, "Using database, file: " + _dbFile);

        if(!Core::FileUtils::FileExists(_dbFile)) {
            CreateDatabase(dataDir + "/db", dbFile);
        }

        poco_debug(_logger, "Database initialized,dir: " + dataDir + " file: " + _dbFile);
    }

    void Database::CreateDatabase(const std::string &dataDir, const std::string &dbFile){

        if(!Core::DirUtils::DirectoryExists(dataDir)){
            Core::DirUtils::MakeDirectory(dataDir);
        }

        // Create a session
        Poco::Data::Session session("SQLite", _dbFile);

        session << "CREATE TABLE service (id INTEGER NOT NULL PRIMARY KEY, name VARCHAR(30), active INTEGER)", Poco::Data::Keywords::now;
        session << "CREATE INDEX service_idx1 ON service(name)", Poco::Data::Keywords::now;
        poco_debug(_logger, "Service table created");

        session << "CREATE TABLE bucket (id INTEGER NOT NULL PRIMARY KEY, name VARCHAR(255))", Poco::Data::Keywords::now;
        session << "CREATE INDEX bucket_idx1 ON bucket(name)", Poco::Data::Keywords::now;
        poco_debug(_logger, "Bucket table created");
    }

    Poco::Data::Session Database::GetSession(){
        return {"SQLite", _dbFile};
    }

} // namespave AwsMock::Database
