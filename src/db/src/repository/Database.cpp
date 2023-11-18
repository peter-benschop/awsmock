//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/repository/Database.h"

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  Database::Database(const Core::Configuration &configuration) : _logger(Poco::Logger::get("Database")), _configuration(configuration) {

    _name = _configuration.getString("awsmock.mongodb.name", "awsmock");
    _host = _configuration.getString("awsmock.mongodb.host", "localhost");
    _port = _configuration.getInt("awsmock.mongodb.port", 27017);
    _user = _configuration.getString("awsmock.mongodb.user", "admin");
    _password = _configuration.getString("awsmock.mongodb.password", "admin");

    // MongoDB URI
    _uri = mongocxx::uri("mongodb://" + _user + ":" + _password + "@" + _host + ":" + std::to_string(_port) + "/?maxPoolSize=32");
    _client = mongocxx::client{_uri};
    log_debug_stream(_logger) << "MongoDB connection initialized" << std::endl;
  }

  mongocxx::database Database::GetConnection() {
    return _client[_name];
  }

  mongocxx::client_session Database::GetSession() {
    return _client.start_session();
  }

  void Database::CreateIndexes() {

    // SQS indexes
    GetConnection()["sqs_message"].create_index(make_document(kvp("queueUrl", 1), kvp("status", 1), kvp("reset", 1)), make_document(kvp("name", "queueurl_status_reset_idx1")));
    GetConnection()["sqs_message"].create_index(make_document(kvp("queueUrl", 1), kvp("status", 1), kvp("retries", 1)), make_document(kvp("name", "queueurl_status_retries_idx2")));
    GetConnection()["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("name", 1)), make_document(kvp("name", "region_name_idx1")));
    GetConnection()["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("url", 1)), make_document(kvp("name", "region_url_idx2")));
    GetConnection()["module"].create_index(make_document(kvp("name", 1), kvp("status", 1)), make_document(kvp("name", "name_status_idx1")));
    log_debug_stream(_logger) << "SQS indexes created" << std::endl;
  }

} // namespace AwsMock::Database
