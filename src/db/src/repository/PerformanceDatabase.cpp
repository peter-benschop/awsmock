//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/PerformanceDatabase.h>

namespace AwsMock::Database {

    void PerformanceDatabase::AddData(const std::string &key, double value) {

        Database::Entity::Performance::PerformanceValue performanceEntity;
        performanceEntity.key = key;
        performanceEntity.perfValue = value;

        auto client = ConnectionPool::instance().GetConnection();
        mongocxx::collection _performanceCollection = (*client)[_databaseName][_performanceCollectionName];
        auto session = client->start_session();

        try {

            session.start_transaction();
            auto result = _performanceCollection.insert_one(performanceEntity.ToDocument());
            log_trace << "Performance value created, oid: " << result->inserted_id().get_oid().value.to_string();
            session.commit_transaction();

        } catch (mongocxx::exception &e) {
            session.abort_transaction();
            log_error << "Add performance value failed, error: " << e.what();
            throw Core::DatabaseException("Add performance value failed, key: " + performanceEntity.key + " error: " + e.what());
        }
    }

}// namespace AwsMock::Database
