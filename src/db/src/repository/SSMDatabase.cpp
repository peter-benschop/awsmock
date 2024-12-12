//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/SSMDatabase.h>

namespace AwsMock::Database {

    bool SSMDatabase::ParameterExists(const std::string &name) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _parameterCollection = (*client)[_databaseName][_parameterCollectionName];
                int64_t count = _parameterCollection.count_documents(make_document(kvp("name", name)));
                log_trace << "Parameter exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "SSM database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.ParameterExists(name);
        }
    }

    Entity::SSM::Parameter SSMDatabase::GetParameterById(bsoncxx::oid oid) {

        try {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _topicCollection = (*client)[_databaseName][_parameterCollectionName];
            std::optional<bsoncxx::document::value> mResult = _topicCollection.find_one(make_document(kvp("_id", oid)));
            if (mResult->empty()) {
                log_error << "ssm parameter not found, oid" << oid.to_string();
                throw Core::DatabaseException("ssm parameter not found, oid" + oid.to_string());
            }

            Entity::SSM::Parameter result;
            result.FromDocument(mResult->view());
            return result;


        } catch (const mongocxx::exception &exc) {
            log_error << "SSM database exception " << exc.what();
            throw Core::DatabaseException(exc.what());
        }
    }

    Entity::SSM::Parameter SSMDatabase::GetParameterById(const std::string &oid) {

        if (HasDatabase()) {

            return GetParameterById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetParameterById(oid);
        }
    }

    Entity::SSM::Parameter SSMDatabase::GetParameterByName(const std::string &name) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _parameterCollection = (*client)[_databaseName][_parameterCollectionName];

            try {

                std::optional<bsoncxx::document::value> mResult = _parameterCollection.find_one(make_document(kvp("name", name)));
                if (mResult->empty()) {
                    log_error << "SSM parameter not found, name: " << name;
                    throw Core::DatabaseException("ssm parameter not found, name" + name);
                }

                Entity::SSM::Parameter result;
                result.FromDocument(mResult->view());
                return result;


            } catch (const mongocxx::exception &exc) {
                log_error << "SSM database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }
        } else {

            return _memoryDb.GetParameterByName(name);
        }
    }

    Entity::SSM::ParameterList SSMDatabase::ListParameters(const std::string &region) {

        Entity::SSM::ParameterList parameterList;
        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _parameterCollection = (*client)[_databaseName][_parameterCollectionName];

            if (region.empty()) {

                auto parameterCursor = _parameterCollection.find({});
                for (const auto &parameter: parameterCursor) {
                    Entity::SSM::Parameter result;
                    result.FromDocument(parameter);
                    parameterList.push_back(result);
                }
            } else {

                auto parameterCursor = _parameterCollection.find(make_document(kvp("region", region)));
                for (const auto &parameter: parameterCursor) {
                    Entity::SSM::Parameter result;
                    result.FromDocument(parameter);
                    parameterList.push_back(result);
                }
            }

        } else {

            parameterList = _memoryDb.ListParameters(region);
        }

        log_trace << "Got parameter list, size:" << parameterList.size();
        return parameterList;
    }

    long SSMDatabase::CountParameters() {

        if (HasDatabase()) {

            try {
                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _parameterCollection = (*client)[_databaseName][_parameterCollectionName];

                long count = _parameterCollection.count_documents(make_document());
                log_trace << "Parameter count: " << count;
                return count;

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Parameter count failed, error: " << e.what();
            }

        } else {

            return _memoryDb.CountParameters();
        }
        return -1;
    }

    Entity::SSM::Parameter SSMDatabase::CreateParameter(Entity::SSM::Parameter &parameter) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _parameterCollection = (*client)[_databaseName][_parameterCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto result = _parameterCollection.insert_one(parameter.ToDocument());
                session.commit_transaction();
                log_trace << "Parameter created, oid: " << result->inserted_id().get_oid().value.to_string();

                parameter.oid = result->inserted_id().get_oid().value.to_string();
                return parameter;

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "SSM database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.CreateParameter(parameter);
        }
    }

    Entity::SSM::Parameter SSMDatabase::UpdateParameter(Entity::SSM::Parameter &parameter) {

        if (HasDatabase()) {

            mongocxx::options::find_one_and_update opts{};
            opts.return_document(mongocxx::options::return_document::k_after);

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _parameterCollection = (*client)[_databaseName][_parameterCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto mResult = _parameterCollection.find_one_and_update(make_document(kvp("name", parameter.parameterName)), parameter.ToDocument(), opts);
                log_trace << "Parameter updated: " << parameter.ToString();
                session.commit_transaction();

                if (mResult) {
                    parameter.FromDocument(mResult->view());
                    return parameter;
                }
                return {};

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "SSM database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            return _memoryDb.UpdateParameter(parameter);
        }
    }

    Entity::SSM::Parameter SSMDatabase::UpsertParameter(Entity::SSM::Parameter &parameter) {

        if (ParameterExists(parameter.parameterName)) {

            return UpdateParameter(parameter);

        } else {

            return CreateParameter(parameter);
        }
    }

    void SSMDatabase::DeleteParameter(const Entity::SSM::Parameter &parameter) const {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _bucketCollection = (*client)[_databaseName][_parameterCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto delete_many_result = _bucketCollection.delete_one(make_document(kvp("name", parameter.parameterName)));
                session.commit_transaction();
                log_debug << "ssm parameter deleted, count: " << delete_many_result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "SSM database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteParameter(parameter);
        }
    }

    void SSMDatabase::DeleteAllParameters() {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _bucketCollection = (*client)[_databaseName][_parameterCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto delete_many_result = _bucketCollection.delete_many({});
                session.commit_transaction();
                log_debug << "All ssm parameters deleted, count: " << delete_many_result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                session.abort_transaction();
                log_error << "SSM database exception " << exc.what();
                throw Core::DatabaseException(exc.what());
            }

        } else {

            _memoryDb.DeleteAllParameters();
        }
    }

}// namespace AwsMock::Database
