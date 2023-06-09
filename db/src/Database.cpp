//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/db/Database.h"

namespace AwsMock::Database {

    using namespace Poco::Data::Keywords;

    Database::Database(const Core::Configuration &configuration) : _logger(Poco::Logger::get("Database")), _configuration(configuration) {
        Core::Logger::SetDefaultConsoleLogger("Database");
        Initialize();
    }

    Database::~Database(){
        _sessionPool->shutdown();
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

        // Create session pool
        _sessionPool = new Poco::Data::SessionPool("SQLite", _dbFile);
        poco_debug(_logger, "Database session pool initialized");
    }

    void Database::CreateDatabase(const std::string &dataDir, const std::string &dbFile){

        if (!Core::DirUtils::DirectoryExists(dataDir)) {
            Core::DirUtils::MakeDirectory(dataDir);
        }

        // Create a session
        Poco::Data::Session session("SQLite", _dbFile);
        session.begin();

        // Service
        session << "CREATE TABLE service (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name VARCHAR(30), active INTEGER)",
            Poco::Data::Keywords::now;
        session << "CREATE INDEX service_idx1 ON service(name)",
            Poco::Data::Keywords::now;
        session << "INSERT INTO service(name, active) VALUES(?,1)", bind("S3"),
            Poco::Data::Keywords::now;
        session << "INSERT INTO service(name, active) VALUES(?,1)", bind("SQS"),
            Poco::Data::Keywords::now;
        session << "INSERT INTO service(name, active) VALUES(?,1)", bind("SNS"),
            Poco::Data::Keywords::now;
        session << "INSERT INTO service(name, active) VALUES(?,1)", bind("Lambda"),
            Poco::Data::Keywords::now;
        poco_debug(_logger, "Service table created");

        // S3
        session << "CREATE TABLE s3_bucket (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name VARCHAR(255), region VARCHAR(32), owner VARCHAR(32), "
                   "created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX s3_bucket_idx1 ON s3_bucket(name, region)",
            Poco::Data::Keywords::now;
        poco_debug(_logger, "S3 bucket table created");

        session << "CREATE TABLE s3_object (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, bucket VARCHAR(255), key VARCHAR(255), owner VARCHAR(32), "
                   "size INTEGER, md5sum VARCHAR(32), content_type VARCHAR(64), created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX s3_object_idx1 ON s3_object(bucket, key)",
            Poco::Data::Keywords::now;
        poco_debug(_logger, "S3 object table created");

        session << "CREATE TABLE s3_notification (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, region VARCHAR(255), bucket VARCHAR(255), notification_id INT, "
                   "function VARCHAR(255), queue_arn VARCHAR(255), event VARCHAR(128), created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX s3_notification_idx1 ON s3_notification(region,bucket,event)",
            Poco::Data::Keywords::now;
        poco_debug(_logger, "SQS message table created");

        // SQS
        session << "CREATE TABLE sqs_queue (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name VARCHAR(255), region VARCHAR(255), owner VARCHAR(32), queue_url VARCHAR(255), "
                   "queue_arn VARCHAR(255), created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX sqs_queue_idx1 ON sqs_queue(name, region)", Poco::Data::Keywords::now;
        poco_debug(_logger, "SQS queue table created");

        session
            << "CREATE TABLE sqs_queue_attribute (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, queue_url VARCHAR(255), delay_seconds INT, "
               "max_message_size INT DEFAULT 262144, message_retention_period INT DEFAULT 345600, policy TEXT, redrive_policy TEXT, redrive_allow_policy TEXT, "
               "receive_message_wait_time INT DEFAULT 20, visibility_timeout INT DEFAULT 30, created DATETIME DEFAULT CURRENT_TIMESTAMP, "
               "modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX sqs_queue_attribute_idx1 ON sqs_queue_attribute(queue_url)", Poco::Data::Keywords::now;
        poco_debug(_logger, "SQS queue attribute table created");

        session << "CREATE TABLE sqs_message (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, queue_url VARCHAR(255), body BLOB, status INT, message_id VARCHAR(100), "
                   "receipt_handle TEXT, md5_body VARCHAR(32), md5_attr VARCHAR(32), last_send DATETIME, retries INT, created DATETIME DEFAULT CURRENT_TIMESTAMP, "
                   "modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX sqs_message_idx1 ON sqs_message(message_id)", Poco::Data::Keywords::now;
        poco_debug(_logger, "SQS message table created");

        session << "CREATE TABLE sqs_message_attribute (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, name VARCHAR(255), value BLOB, "
                   "created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        //session << "CREATE UNIQUE INDEX sqs_message_attribute_idx1 ON sqs_message(message_id)", Poco::Data::Keywords::now;
        poco_debug(_logger, "SQS message attribute table created");

        session << "CREATE TABLE lambda (id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, function VARCHAR(255), runtime VARCHAR(128), role VARCHAR(128), "
                   "handler VARCHAR(255), size INT, image_id VARCHAR(255), container_id VARCHAR(255), tag VARCHAR(32), arn VARCHAR(64), host_port INT, "
                   "last_started DATETIME, created DATETIME DEFAULT CURRENT_TIMESTAMP, modified DATETIME DEFAULT CURRENT_TIMESTAMP)",
            Poco::Data::Keywords::now;
        session << "CREATE UNIQUE INDEX lambda_idx1 ON lambda(function, runtime)", Poco::Data::Keywords::now;
        poco_debug(_logger, "Lambda table created");

        session.commit();

        poco_debug(_logger, "Database initialized, dbFile: " + _dbFile);

    }

    Poco::Data::Session Database::GetSession(){
        if (!_sessionPool->available()) {
            poco_warning(_logger, "Session pool exhausted, will wait for next available session");
            while (!_sessionPool->available()) {
                Poco::Thread::sleep(1000);
            }
        }
        return _sessionPool->get();
    }

} // namespace AwsMock::Database
