//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/LambdaDatabase.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    LambdaDatabase::LambdaDatabase() : _memoryDb(LambdaMemoryDb::instance()), _databaseName(GetDatabaseName()), _collectionName("lambda") {}

    bool LambdaDatabase::LambdaExists(const std::string &region, const std::string &function, const std::string &runtime) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                int64_t count = _lambdaCollection.count_documents(make_document(kvp("region", region),
                                                                                kvp("function", function),
                                                                                kvp("runtime", runtime)));
                log_trace << "lambda function exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.LambdaExists(region, function, runtime);
        }
    }

    bool LambdaDatabase::LambdaExists(const Entity::Lambda::Lambda &lambda) {

        return LambdaExists(lambda.region, lambda.function, lambda.runtime);
    }

    bool LambdaDatabase::LambdaExists(const std::string &functionName) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                int64_t count = _lambdaCollection.count_documents(make_document(kvp("function", functionName)));
                log_trace << "lambda function exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.LambdaExists(functionName);
        }
    }

    bool LambdaDatabase::LambdaExistsByArn(const std::string &arn) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                int64_t count = _lambdaCollection.count_documents(make_document(kvp("arn", arn)));
                log_trace << "lambda function exists: " << std::boolalpha << count;
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.LambdaExistsByArn(arn);
        }
    }

    int LambdaDatabase::LambdaCount(const std::string &region) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];

                long count = 0;
                if (region.empty()) {
                    count = _lambdaCollection.count_documents({});
                } else {
                    count = _lambdaCollection.count_documents(make_document(kvp("region", region)));
                }

                log_trace << "lambda count: " << count;
                return count;

            } catch (mongocxx::exception::system_error &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.LambdaCount(region);
        }
        return -1;
    }

    Entity::Lambda::Lambda LambdaDatabase::CreateLambda(const Entity::Lambda::Lambda &lambda) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];

                auto result = _lambdaCollection.insert_one(lambda.ToDocument());
                log_trace << "Bucket created, oid: " << result->inserted_id().get_oid().value.to_string();
                return GetLambdaById(result->inserted_id().get_oid().value);

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.CreateLambda(lambda);
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaById(bsoncxx::oid oid) {

        try {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
            mongocxx::stdx::optional<bsoncxx::document::value> mResult = _lambdaCollection.find_one(make_document(kvp("_id", oid)));
            if (!mResult) {
                log_error << "Database exception: Lambda not found ";
                throw Core::DatabaseException("Database exception, Lambda not found ");
            }

            Entity::Lambda::Lambda result;
            result.FromDocument(mResult->view());
            return result;

        } catch (const mongocxx::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException("Database exception " + std::string(exc.what()));
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaById(const std::string &oid) {

        if (HasDatabase()) {

            return GetLambdaById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetLambdaById(oid);
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaByArn(const std::string &arn) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _lambdaCollection.find_one(make_document(kvp("arn", arn)));
                if (!mResult) {
                    log_error << "Database exception: Lambda not found ";
                    throw Core::DatabaseException("Database exception, Lambda not found ");
                }

                Entity::Lambda::Lambda result;
                result.FromDocument(mResult->view());
                return result;

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Get lambda by ARN failed, error: " << e.what();
            }

        } else {

            return _memoryDb.GetLambdaByArn(arn);
        }
        return {};
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaByName(const std::string &region, const std::string &name) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _lambdaCollection.find_one(make_document(kvp("region", region), kvp("function", name)));
                if (!mResult) {
                    log_error << "Database exception: Lambda not found ";
                    throw Core::DatabaseException("Database exception, Lambda not found ");
                }

                Entity::Lambda::Lambda result;
                result.FromDocument(mResult->view());
                return result;

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Get lambda by ARN failed, error: " << e.what();
            }

        } else {

            return _memoryDb.GetLambdaByName(region, name);
        }
        return {};
    }

    Entity::Lambda::Lambda LambdaDatabase::CreateOrUpdateLambda(const Entity::Lambda::Lambda &lambda) {

        if (LambdaExists(lambda)) {
            return UpdateLambda(lambda);
        } else {
            return CreateLambda(lambda);
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::UpdateLambda(const Entity::Lambda::Lambda &lambda) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                auto result = _lambdaCollection.replace_one(make_document(kvp("region", lambda.region),
                                                                          kvp("function", lambda.function),
                                                                          kvp("runtime", lambda.runtime)),
                                                            lambda.ToDocument());
                log_trace << "lambda updated: " << lambda.ToString();
                return GetLambdaByArn(lambda.arn);

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            return _memoryDb.UpdateLambda(lambda);
        }
    }

    void LambdaDatabase::SetInstanceStatus(const std::string &containerId, const Entity::Lambda::LambdaInstanceStatus &status) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                _lambdaCollection.update_one(make_document(kvp("instances.containerId", containerId)),
                                             make_document(kvp("$set",
                                                               make_document(kvp("instances.$.status", Entity::Lambda::LambdaInstanceStatusToString(status))))));

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Get lambda by ARN failed, error: " << e.what();
            }

        } else {

            _memoryDb.SetInstanceStatus(containerId, status);
        }
    }

    void LambdaDatabase::SetAverageRuntime(const std::string &oid, long millis) {

        if (HasDatabase()) {

            auto client = ConnectionPool::instance().GetConnection();
            mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                Database::Entity::Lambda::Lambda lambda = GetLambdaById(oid);
                lambda.invocations++;
                lambda.averageRuntime = static_cast<long>(std::round((lambda.averageRuntime + millis) / lambda.invocations));

                _lambdaCollection.find_one_and_update(make_document(kvp("_id", bsoncxx::oid(oid))), lambda.ToDocument());
                session.commit_transaction();
                log_debug << "Lambda counters updated, oid: " << oid;

            } catch (mongocxx::exception::system_error &e) {
                session.abort_transaction();
                log_error << "Get lambda by ARN failed, error: " << e.what();
            }

        } else {

            //  _memoryDb.SetInstanceStatus(containerId, status);
        }
    }

    std::vector<Entity::Lambda::Lambda> LambdaDatabase::ListLambdas(const std::string &region) {

        std::vector<Entity::Lambda::Lambda> lambdas;
        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                if (region.empty()) {

                    auto lambdaCursor = _lambdaCollection.find({});
                    for (auto lambda: lambdaCursor) {
                        Entity::Lambda::Lambda result;
                        result.FromDocument(lambda);
                        lambdas.push_back(result);
                    }
                } else {
                    auto lambdaCursor = _lambdaCollection.find(make_document(kvp("region", region)));
                    for (auto lambda: lambdaCursor) {
                        Entity::Lambda::Lambda result;
                        result.FromDocument(lambda);
                        lambdas.push_back(result);
                    }
                }

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            lambdas = _memoryDb.ListLambdas(region);
        }

        log_trace << "Got lambda list, size:" << lambdas.size();
        return lambdas;
    }

    std::vector<Entity::Lambda::Lambda> LambdaDatabase::ListLambdaCounters(const std::string &region, const std::string &prefix, long maxResults, long skip, const std::vector<Core::SortColumn> &sortColumns) {

        std::vector<Entity::Lambda::Lambda> lambdas;
        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];

                mongocxx::options::find opts;
                if (!sortColumns.empty()) {
                    bsoncxx::builder::basic::document sort = {};
                    for (const auto &sortColumn: sortColumns) {
                        sort.append(kvp(sortColumn.column, sortColumn.sortDirection));
                    }
                    opts.sort(sort.extract());
                }
                if (skip > 0) {
                    opts.skip(skip);
                }
                if (maxResults > 0) {
                    opts.limit(maxResults);
                }

                bsoncxx::builder::basic::document query = {};
                if (!region.empty()) {
                    query.append(kvp("region", region));
                }
                if (!prefix.empty()) {
                    query.append(kvp("functionName", make_document(kvp("$regex", "^" + prefix))));
                }

                auto lambdaCursor = _lambdaCollection.find(query.extract(), opts);
                for (auto lambda: lambdaCursor) {
                    Entity::Lambda::Lambda result;
                    result.FromDocument(lambda);
                    lambdas.push_back(result);
                }

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }
        }

        log_trace << "Got lambda counter list, size:" << lambdas.size();
        return lambdas;
    }

    std::vector<Entity::Lambda::Lambda> LambdaDatabase::ListLambdasWithEventSource(const std::string &eventSourceArn) {

        std::vector<Entity::Lambda::Lambda> lambdas;
        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                auto lambdaCursor = _lambdaCollection.find(make_document(kvp("eventSources.eventSourceArn", eventSourceArn)));
                for (auto lambda: lambdaCursor) {
                    Entity::Lambda::Lambda result;
                    result.FromDocument(lambda);
                    lambdas.push_back(result);
                }

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            lambdas = _memoryDb.ListLambdasWithEventSource(eventSourceArn);
        }

        log_trace << "Got lambda list, size:" << lambdas.size();
        return lambdas;
    }

    void LambdaDatabase::DeleteLambda(const std::string &functionName) {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                auto result = _lambdaCollection.delete_many(make_document(kvp("function", functionName)));
                log_debug << "lambda deleted, function: " << functionName << " count: "
                          << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteLambda(functionName);
        }
    }

    void LambdaDatabase::DeleteAllLambdas() {

        if (HasDatabase()) {

            try {

                auto client = ConnectionPool::instance().GetConnection();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName][_collectionName];
                auto result = _lambdaCollection.delete_many({});
                log_debug << "All lambdas deleted, count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()));
            }

        } else {

            _memoryDb.DeleteAllLambdas();
        }
    }

}// namespace AwsMock::Database
