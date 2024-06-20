//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_document;

    DatabaseBase::DatabaseBase() : _useDatabase(false) {

        _useDatabase = Core::Configuration::instance().getBool("awsmock.mongodb.active", false);
        _name = Core::Configuration::instance().getString("awsmock.mongodb.name", "awsmock");
    }

    mongocxx::database DatabaseBase::GetConnection() {
        mongocxx::pool::entry _client = _pool->acquire();
        return (*_client)[_name];
    }

    bool DatabaseBase::HasDatabase() const {
        return _useDatabase;
    }

    std::string DatabaseBase::GetDatabaseName() const {
        return _name;
    }

    void DatabaseBase::StartDatabase() {

        _useDatabase = true;
        Core::Configuration::instance().SetValue("awsmock.mongodb.active", true);

        // Update module database
        mongocxx::pool::entry _client = _pool->acquire();
        (*_client)[_name]["module"].update_one(make_document(kvp("name", "database")), make_document(kvp("$set", make_document(kvp("state", "RUNNING")))));
        log_info << "Database module started";
    }

    void DatabaseBase::StopDatabase() {

        // Update module database
        Core::Configuration::instance().SetValue("awsmock.mongodb.active", false);
        mongocxx::pool::entry _client = _pool->acquire();
        (*_client)[_name]["module"].update_one(make_document(kvp("name", "database")),
                                               make_document(kvp("$set", make_document(kvp("state", "STOPPED")))));

        _useDatabase = false;
        log_info << "Database module stopped";
    }

    void DatabaseBase::CreateIndexes() const {

        if (_useDatabase) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::database database = (*client)[_name];

            // SQS
            database["sqs_message"].create_index(make_document(kvp("queueUrl", 1), kvp("status", 1), kvp("reset", 1)),
                                                 make_document(kvp("name", "sqs_message_idx1")));
            database["sqs_message"].create_index(make_document(kvp("queueUrl", 1), kvp("status", 1), kvp("retries", 1)),
                                                 make_document(kvp("name", "sqs_message_idx2")));
            database["sqs_message"].create_index(make_document(kvp("receiptHandle", 1)),
                                                 make_document(kvp("name", "sqs_message_idx3")));
            database["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("name", 1)),
                                               make_document(kvp("name", "sqs_queue_idx1")));
            database["sqs_queue"].create_index(make_document(kvp("region", 1), kvp("url", 1)),
                                               make_document(kvp("name", "sqs_queue_idx2")));

            // SNS
            database["sns_topic"].create_index(make_document(kvp("region", 1), kvp("arn", 1)),
                                               make_document(kvp("name", "sns_topic_idx1")));
            database["sns_message"].create_index(make_document(kvp("region", 1), kvp("topicArn", 1)),
                                                 make_document(kvp("name", "sns_message_idx2")));

            // S3
            database["s3_bucket"].create_index(make_document(kvp("region", 1), kvp("name", 1)),
                                               make_document(kvp("name", "s3_idx1")));
            database["s3_object"].create_index(make_document(kvp("region", 1), kvp("bucket", 1), kvp("key", 1)),
                                               make_document(kvp("name", "s3_idx2")));

            // Module
            database["module"].create_index(make_document(kvp("name", 1), kvp("state", 1)),
                                            make_document(kvp("name", "module_idx1")));

            // KMS
            database["kms_key"].create_index(make_document(kvp("region", 1)),
                                             make_document(kvp("name", "kms_idx1")));
            database["kms_key"].create_index(make_document(kvp("keyId", 1)),
                                             make_document(kvp("name", "kms_idx2")));
            database["kms_key"].create_index(make_document(kvp("keyState", 1)),
                                             make_document(kvp("name", "kms_idx3")));
            log_debug << "SQS indexes created";
        }
    }

}// namespace AwsMock::Database
