//
// Created by vogje01 on 29/05/2023.
//

#include "awsmock/repository/LambdaDatabase.h"

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    LambdaDatabase::LambdaDatabase() : _memoryDb(LambdaMemoryDb::instance()), _useDatabase(HasDatabase()), _databaseName(GetDatabaseName()) {}

    bool LambdaDatabase::LambdaExists(const std::string &region, const std::string &function, const std::string &runtime) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                int64_t count = _lambdaCollection.count_documents(make_document(kvp("region", region),
                                                                                kvp("function", function),
                                                                                kvp("runtime", runtime)));
                log_trace << "lambda function exists: " << (count > 0 ? "true" : "false");
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            return _memoryDb.LambdaExists(region, function, runtime);
        }
    }

    bool LambdaDatabase::LambdaExists(const Entity::Lambda::Lambda &lambda) {

        return LambdaExists(lambda.region, lambda.function, lambda.runtime);
    }

    bool LambdaDatabase::LambdaExists(const std::string &functionName) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                int64_t count = _lambdaCollection.count_documents(make_document(kvp("function", functionName)));
                log_trace << "lambda function exists: " << (count > 0 ? "true" : "false");
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            return _memoryDb.LambdaExists(functionName);
        }
    }

    bool LambdaDatabase::LambdaExistsByArn(const std::string &arn) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                int64_t count = _lambdaCollection.count_documents(make_document(kvp("arn", arn)));
                log_trace << "lambda function exists: " << (count > 0 ? "true" : "false");
                return count > 0;

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            return _memoryDb.LambdaExistsByArn(arn);
        }
    }

    long LambdaDatabase::LambdaCount(const std::string &region) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];

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
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            return _memoryDb.LambdaCount(region);
        }
        return -1;
    }

    Entity::Lambda::Lambda LambdaDatabase::CreateLambda(const Entity::Lambda::Lambda &lambda) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];

                auto result = _lambdaCollection.insert_one(lambda.ToDocument());
                log_trace << "Bucket created, oid: " << result->inserted_id().get_oid().value.to_string();
                return GetLambdaById(result->inserted_id().get_oid().value);

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            return _memoryDb.CreateLambda(lambda);
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaById(bsoncxx::oid oid) {

        try {

            auto client = GetClient();
            mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
            mongocxx::stdx::optional<bsoncxx::document::value>
                    mResult = _lambdaCollection.find_one(make_document(kvp("_id", oid)));
            if (!mResult) {
                log_error << "Database exception: Lambda not found ";
                throw Core::DatabaseException("Database exception, Lambda not found ", 500);
            }

            Entity::Lambda::Lambda result;
            result.FromDocument(mResult);
            return result;

        } catch (const mongocxx::exception &exc) {
            log_error << "Database exception " << exc.what();
            throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaById(const std::string &oid) {

        if (_useDatabase) {

            return GetLambdaById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetLambdaById(oid);
        }
    }

    Entity::Lambda::Lambda LambdaDatabase::GetLambdaByArn(const std::string &arn) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _lambdaCollection.find_one(make_document(kvp("arn", arn)));
                if (!mResult) {
                    log_error << "Database exception: Lambda not found ";
                    throw Core::DatabaseException("Database exception, Lambda not found ", 500);
                }

                Entity::Lambda::Lambda result;
                result.FromDocument(mResult);
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

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                mongocxx::stdx::optional<bsoncxx::document::value> mResult = _lambdaCollection.find_one(make_document(kvp("region", region), kvp("function", name)));
                if (!mResult.has_value()) {
                    log_error << "Database exception: Lambda not found ";
                    throw Core::DatabaseException("Database exception, Lambda not found ", 500);
                }

                Entity::Lambda::Lambda result;
                result.FromDocument(mResult);
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

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                auto result = _lambdaCollection.replace_one(make_document(kvp("region", lambda.region),
                                                                          kvp("function", lambda.function),
                                                                          kvp("runtime", lambda.runtime)),
                                                            lambda.ToDocument());
                log_trace << "lambda updated: " << lambda.ToString();
                return GetLambdaByArn(lambda.arn);

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            return _memoryDb.UpdateLambda(lambda);
        }
    }

    std::vector<Entity::Lambda::Lambda> LambdaDatabase::ListLambdas(const std::string &region) {

        std::vector<Entity::Lambda::Lambda> lambdas;
        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
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
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            lambdas = _memoryDb.ListLambdas(region);
        }

        log_trace << "Got lamda list, size:" << lambdas.size();
        return lambdas;
    }

    void LambdaDatabase::DeleteLambda(const std::string &functionName) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                auto result = _lambdaCollection.delete_many(make_document(kvp("function", functionName)));
                log_debug << "lambda deleted, function: " << functionName << " count: "
                          << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            _memoryDb.DeleteLambda(functionName);
        }
    }

    void LambdaDatabase::DeleteAllLambdas() {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _lambdaCollection = (*client)[_databaseName]["lambda"];
                auto result = _lambdaCollection.delete_many({});
                log_debug << "All lambdas deleted, count: " << result->deleted_count();

            } catch (const mongocxx::exception &exc) {
                log_error << "Database exception " << exc.what();
                throw Core::DatabaseException("Database exception " + std::string(exc.what()), 500);
            }

        } else {

            _memoryDb.DeleteAllLambdas();
        }
    }

}// namespace AwsMock::Database
