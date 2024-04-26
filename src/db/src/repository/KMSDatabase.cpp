//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/KMSDatabase.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    using bsoncxx::builder::stream::document;

    KMSDatabase::KMSDatabase() : _memoryDb(KMSMemoryDb::instance()), _useDatabase(HasDatabase()), _databaseName(GetDatabaseName()), _keyCollectionName("kms_key") {}

    bool KMSDatabase::KeyExists(const std::string &arn) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _topicCollection = (*client)[_databaseName][_keyCollectionName];
                int64_t count = _topicCollection.count_documents(make_document(kvp("arn", arn)));
                log_trace << "Topic exists: " << (count > 0 ? "true" : "false");
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "KMS Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.KeyExists(arn);
        }
    }

    bool KMSDatabase::KeyExists(const std::string &region, const std::string &topicName) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _topicCollection = (*client)[_databaseName][_keyCollectionName];
                int64_t count = _topicCollection.count_documents(make_document(kvp("region", region), kvp("topicName", topicName)));
                log_trace << "Topic exists: " << (count > 0 ? "true" : "false");
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "KMS Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.KeyExists(region, topicName);
        }
    }

    Entity::KMS::Key KMSDatabase::GetKeyById(bsoncxx::oid oid) {

        try {

            auto client = GetClient();
            mongocxx::collection _topicCollection = (*client)[_databaseName][_keyCollectionName];
            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _topicCollection.find_one(make_document(kvp("_id", oid)));
            if (!mResult.has_value()) {
                log_error << "KMS key not found, oid" << oid.to_string();
                throw Core::DatabaseException("KMS key not found, oid" + oid.to_string());
            }

            Entity::KMS::Key result;
            result.FromDocument(mResult);
            return result;


        } catch (const mongocxx::exception &exc) {
            log_error << "KMS Database exception " << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    Entity::KMS::Key KMSDatabase::GetKeyById(const std::string &oid) {

        if (_useDatabase) {

            return GetKeyById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetKeyById(oid);
        }
    }

    Entity::KMS::Key KMSDatabase::GetKeyByKeyId(const std::string &keyId) {

        if (_useDatabase) {

            auto client = GetClient();
            mongocxx::collection _topicCollection = (*client)[_databaseName][_keyCollectionName];

            try {

                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _topicCollection.find_one(make_document(kvp("keyId", keyId)));
                if (!mResult.has_value()) {
                    log_error << "KMS key not found, keyId: " << keyId;
                    throw Core::DatabaseException("KMS key not found, keyId" + keyId);
                }

                Entity::KMS::Key result;
                result.FromDocument(mResult);
                return result;


            } catch (const mongocxx::exception &exc) {
                log_error << "KMS Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {

            return _memoryDb.GetKeyByKeyId(keyId);
        }
    }

    Entity::KMS::Key KMSDatabase::CreateKey(const Entity::KMS::Key &key) {

        if (_useDatabase) {

            auto client = GetClient();
            mongocxx::collection _topicCollection = (*client)[_databaseName][_keyCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _topicCollection.insert_one(key.ToDocument());
                session.commit_transaction();
                log_trace << "Key created, oid: " << result->inserted_id().get_oid().value.to_string();

                return GetKeyById(result->inserted_id().get_oid().value);

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "KMS Database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.CreateKey(key);
        }
    }

}// namespace AwsMock::Database
