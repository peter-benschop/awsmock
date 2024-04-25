//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/repository/Database.h"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    Database::Database() : _configuration(Core::Configuration::instance()), _useDatabase(false) {

        _useDatabase = _configuration.getBool("awsmock.mongodb.active", false);
        _name = _configuration.getString("awsmock.mongodb.name", "awsmock");
        _host = _configuration.getString("awsmock.mongodb.host", "localhost");
        _port = _configuration.getInt("awsmock.mongodb.port", 27017);
        _user = _configuration.getString("awsmock.mongodb.user", "admin");
        _password = _configuration.getString("awsmock.mongodb.password", "admin");
        _poolSize = _configuration.getInt("awsmock.mongodb.pool.size", 256);

        // MongoDB URI
        _uri = mongocxx::uri("mongodb://" + _user + ":" + _password + "@" + _host + ":" + std::to_string(_port) + "/?maxPoolSize=" + std::to_string(_poolSize));
        _pool = std::make_unique<mongocxx::pool>(_uri);
    }

    mongocxx::database Database::GetConnection() {
        mongocxx::pool::entry _client = _pool->acquire();
        return (*_client)[_name];
    }

    mongocxx::pool::entry Database::GetClient() {
        if (!_pool) {
            log_fatal << "Pool is NULL";
        }
        return _pool->acquire();
    }

    bool Database::HasDatabase() const {
        return _useDatabase;
    }

    std::string Database::GetDatabaseName() const {
        return _name;
    }

    void Database::StartDatabase() {

        _useDatabase = true;
        _configuration.SetValue("awsmock.mongodb.active", true);

        // Update module database
        mongocxx::pool::entry _client = _pool->acquire();
        (*_client)[_name]["module"].update_one(make_document(kvp("name", "database")), make_document(kvp("$set", make_document(kvp("state", "RUNNING")))));
        log_info << "Database module started, poolSize: " << _poolSize;
    }

    void Database::StopDatabase() {

        // Update module database
        _configuration.SetValue("awsmock.mongodb.active", false);
        mongocxx::pool::entry _client = _pool->acquire();
        (*_client)[_name]["module"].update_one(make_document(kvp("name", "database")),
                                               make_document(kvp("$set", make_document(kvp("state", "STOPPED")))));

        _useDatabase = false;
        log_info << "Database module stopped";
    }

    void Database::CreateIndexes() {

        if (_useDatabase) {

            GetConnection()["sqs_message"].create_index(make_document(kvp("queueUrl", 1), kvp("status", 1), kvp("reset", 1)),
                                                        make_document(kvp("name", "sqs_queueurl_status_reset_idx1")));
            GetConnection()["sqs_message"].create_index(make_document(kvp("queueUrl", 1),
                                                                      kvp("status", 1),
                                                                      kvp("retries", 1)),
                                                        make_document(kvp("name", "sqs_queueurl_status_retries_idx2")));
            GetConnection()["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("name", 1)),
                                                      make_document(kvp("name", "sqs_region_name_idx1")));
            GetConnection()["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("url", 1)),
                                                      make_document(kvp("name", "sqs_region_url_idx2")));
            GetConnection()["s3_bucket"].create_index(make_document(kvp("region", 1), kvp("name", 1)),
                                                      make_document(kvp("name", "s3_region_name_idx1")));
            GetConnection()["module"].create_index(make_document(kvp("name", 1), kvp("state", 1)),
                                                   make_document(kvp("name", "module_name_status_idx1")));
            log_debug << "SQS indexes created";
        }
    }

    void Database::UpdateModuleStatus() {
        /*    auto session = GetSession();
    session.start_transaction();
    session.client()[_name]["module"].update_one(make_document(kvp("name", "database")), make_document(kvp("$set", make_document(kvp("state", "RUNNING")))));
    session.commit_transaction();*/
    }

}// namespace AwsMock::Database
