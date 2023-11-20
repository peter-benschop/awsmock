//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/repository/Database.h"

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  Database::Database(Core::Configuration &configuration) : _logger(Poco::Logger::get("Database")), _configuration(configuration), _useDatabase(false) {

    _useDatabase = _configuration.getBool("awsmock.mongodb.active", false);

    if (_useDatabase) {

      Initialize();

    } else {

      log_debug_stream(_logger) << "Running without database" << std::endl;
    }
  }

  void Database::Initialize() {

    _name = _configuration.getString("awsmock.mongodb.name", "awsmock");
    _host = _configuration.getString("awsmock.mongodb.host", "localhost");
    _port = _configuration.getInt("awsmock.mongodb.port", 27017);
    _user = _configuration.getString("awsmock.mongodb.user", "admin");
    _password = _configuration.getString("awsmock.mongodb.password", "admin");

    // MongoDB URI
    _uri = mongocxx::uri("mongodb://" + _user + ":" + _password + "@" + _host + ":" + std::to_string(_port) + "/?maxPoolSize=32");
    _client = mongocxx::client{_uri};

    // Update module database
    _client[_name]["module"].update_one(make_document(kvp("name", "database")), make_document(kvp("$set", make_document(kvp("state", "RUNNING")))));

    log_debug_stream(_logger) << "MongoDB connection initialized" << std::endl;
  }

  mongocxx::database Database::GetConnection() {
    return _client[_name];
  }

  mongocxx::client_session Database::GetSession() {
    return _client.start_session();
  }

  bool Database::HasDatabase() const {
    return _configuration.getBool("awsmock.mongodb.active", false);
  }

  void Database::StartDatabase() {

    _useDatabase = true;
    _configuration.SetValue("awsmock.mongodb.active", true);
    Initialize();

    // Update module database
    _client[_name]["module"].update_one(make_document(kvp("name", "database")), make_document(kvp("$set", make_document(kvp("state", "RUNNING")))));
    log_info_stream(_logger) << "Database module started" << std::endl;
  }

  void Database::StopDatabase() {

    // Update module database
    _configuration.SetValue("awsmock.mongodb.active", false);
    _client[_name]["module"].update_one(make_document(kvp("name", "database")), make_document(kvp("$set", make_document(kvp("state", "STOPPED")))));

    _useDatabase = false;
    log_info_stream(_logger) << "Database module stopped" << std::endl;
  }

  void Database::WaitForStartup() {
    while (true) {
      try {
        const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
        _client["awsmock"].run_command(ping_cmd.view());
        break;
      } catch (const std::exception &e) {
      }
      Poco::Thread::sleep(500);
    }
  }

  void Database::CreateIndexes() {

    if (_useDatabase) {

      GetConnection()["sqs_message"].create_index(make_document(kvp("queueUrl", 1), kvp("state", 1), kvp("reset", 1)), make_document(kvp("name", "sqs_queueurl_status_reset_idx1")));
      GetConnection()["sqs_message"].create_index(make_document(kvp("queueUrl", 1), kvp("state", 1), kvp("retries", 1)), make_document(kvp("name", "sqs_queueurl_status_retries_idx2")));
      GetConnection()["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("name", 1)), make_document(kvp("name", "sqs_region_name_idx1")));
      GetConnection()["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("url", 1)), make_document(kvp("name", "sqs_region_url_idx2")));
      GetConnection()["s3_bucket"].create_index(make_document(kvp("region", 1), kvp("name", 1)), make_document(kvp("name", "s3_region_name_idx1")));
      GetConnection()["module"].create_index(make_document(kvp("name", 1), kvp("state", 1)), make_document(kvp("name", "module_name_status_idx1")));
      log_debug_stream(_logger) << "SQS indexes created" << std::endl;
    }
  }

} // namespace AwsMock::Database
