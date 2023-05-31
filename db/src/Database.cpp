//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/Database.h"

namespace AwsMock::Database {

    Database::Database(const Core::Configuration &configuration) : _logger(Poco::Logger::get("Database")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("Database");
        Initialize();
    }

    void Database::Initialize() {

        // Register SQLite connector
        Poco::Data::SQLite::Connector::registerConnector();

        // Create the directory
        std::string dataDir = _configuration.getString("awsmock.db.dir", "/tmp/data");
        std::string dbFile = _configuration.getString("awsmock.db.file", "awsmock.db");

        _dbFile = dataDir + Poco::Path::separator() + dbFile;
        poco_debug(_logger, "Using database, file: " + _dbFile);

        if(!Core::FileUtils::FileExists(_dbFile)) {
            CreateDatabase(dataDir, dbFile);
        }
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

        session << "CREATE TABLE s3_bucket (id INTEGER NOT NULL PRIMARY KEY, name VARCHAR(255), region VARCHAR(32), owner VARCHAR(32), "
                   "created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)", Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX s3_bucket_idx1 ON s3_bucket(name, region)", Poco::Data::Keywords::now;
        poco_debug(_logger, "S3 bucket table created");

        session << "CREATE TABLE s3_object (id INTEGER NOT NULL PRIMARY KEY, bucket VARCHAR(255), key VARCHAR(255), owner VARCHAR(32), "
                   "size INTEGER, md5sum VARCHAR(32), content_type VARCHAR(64), created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
                   Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX s3_object_idx1 ON s3_object(bucket, key)", Poco::Data::Keywords::now;
        poco_debug(_logger, "S3 object table created");

        poco_debug(_logger, "Database initialized, dbFile: " + _dbFile);
        session.close();
    }

    Poco::Data::Session Database::GetSession(){
        return {"SQLite", _dbFile};
    }

} // namespace AwsMock::Database
