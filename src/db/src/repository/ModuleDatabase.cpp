//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/ModuleDatabase.h>

namespace AwsMock::Database {

    using bsoncxx::builder::basic::kvp;
    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;

    std::map<std::string, Entity::Module::Module> ModuleDatabase::_existingModules = {
            {"s3", {.name = "s3", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"sqs", {.name = "sqs", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"sns", {.name = "sns", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"lambda", {.name = "lambda", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"transfer", {.name = "transfer", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"cognito", {.name = "cognito", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"dynamodb", {.name = "dynamodb", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"secretsmanager", {.name = "secretsmanager", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"kms", {.name = "kms", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"gateway", {.name = "gateway", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}},
            {"database", {.name = "database", .state = Entity::Module::ModuleState::STOPPED, .status = Entity::Module::ModuleStatus::INACTIVE}}};

    ModuleDatabase::ModuleDatabase() : _useDatabase(HasDatabase()), _databaseName(GetDatabaseName()), _moduleCollectionName("module") {
    }

    void ModuleDatabase::Initialize() {

        for (const auto &module: _existingModules) {
            if (_useDatabase) {

                if (!ModuleExists(module.first)) {
                    CreateModule(module.second);
                }

            } else {

                if (!_memoryDb.ModuleExists(module.first)) {
                    _memoryDb.CreateModule(module.second);
                }
            }
        }
    }

    bool ModuleDatabase::IsActive(const std::string &name) {

        if (HasDatabase()) {

            try {

                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                auto result = _moduleCollection.find_one(make_document(kvp("name", name)));
                if (result) {
                    Entity::Module::Module module;
                    module.FromDocument(result->view());
                    log_trace << "Module state: " << Entity::Module::ModuleStateToString(module.state);
                    return module.status == Entity::Module::ModuleStatus::ACTIVE;
                }

            } catch (mongocxx::exception::system_error &e) {
                log_error << "IsActive failed, module: " << name << " error: " << e.what();
            }

        } else {

            return _memoryDb.IsActive(name);
        }
        return false;
    }

    bool ModuleDatabase::ModuleExists(const std::string &name) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                int64_t count = _moduleCollection.count_documents(make_document(kvp("name", name)));
                log_trace << "Module exists: " << (count > 0 ? "true" : "false");
                return count > 0;

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Module exists failed, error: " << e.what();
            }

        } else {

            return _memoryDb.ModuleExists(name);
        }
        return false;
    }

    Entity::Module::Module ModuleDatabase::GetModuleById(const bsoncxx::oid &oid) {

        try {

            auto client = GetClient();
            mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];

            mongocxx::stdx::optional<bsoncxx::document::value>
                    mResult = _moduleCollection.find_one(make_document(kvp("_id", oid)));
            if (mResult) {
                Entity::Module::Module module;
                module.FromDocument(mResult->view());
                return module;
            }

        } catch (mongocxx::exception::system_error &e) {
            log_error << "Get module by ID failed, error: " << e.what();
            throw Core::DatabaseException("Module not found, oid: " + oid.to_string());
        }
        return {};
    }

    Entity::Module::Module ModuleDatabase::GetModuleById(const std::string &oid) {

        if (_useDatabase) {

            return GetModuleById(bsoncxx::oid(oid));

        } else {

            return _memoryDb.GetModuleById(oid);
        }
    }

    Entity::Module::Module ModuleDatabase::GetModuleByName(const std::string &name) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                auto mResult = _moduleCollection.find_one(make_document(kvp("name", name)));
                if (mResult) {
                    Entity::Module::Module modules;
                    modules.FromDocument(mResult->view());
                    return modules;
                }

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Get module by name failed, name: " << name << " error: " << e.what();
            }
        } else {

            return _memoryDb.GetModuleByName(name);
        }
        return {};
    }

    Entity::Module::Module ModuleDatabase::CreateModule(const Entity::Module::Module &module) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                auto result = _moduleCollection.insert_one(module.ToDocument());
                log_trace << "Module created, oid: " << result->inserted_id().get_oid().value.to_string();
                return GetModuleById(result->inserted_id().get_oid().value);

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Create module failed, error: " << e.what();
                throw Core::DatabaseException("Create module failed, error: " + std::string(e.what()));
            }

        } else {

            return _memoryDb.CreateModule(module);
        }
    }

    Entity::Module::Module ModuleDatabase::UpdateModule(const Entity::Module::Module &module) {

        if (_useDatabase) {

            try {
                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                auto mResult = _moduleCollection.replace_one(make_document(kvp("name", module.name)), module.ToDocument());
                log_trace << "Module updated: " << module.ToString();
                return GetModuleByName(module.name);

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Update module failed, error: " << e.what();
                throw Core::DatabaseException("Update module failed, error: " + std::string(e.what()));
            }

        } else {

            return _memoryDb.UpdateModule(module);
        }
    }

    Entity::Module::Module ModuleDatabase::SetState(const std::string &name, const Entity::Module::ModuleState &state) {

        if (_useDatabase) {

            auto client = GetClient();
            mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
            auto session = client->start_session();

            try {

                session.start_transaction();
                auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)),
                                                            make_document(kvp("$set",
                                                                              make_document(kvp("state",
                                                                                                Entity::Module::ModuleStateToString(
                                                                                                        state))))));
                log_trace << "Module state updated, name: " << name << " state: "
                          << Entity::Module::ModuleStateToString(state);
                session.commit_transaction();

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Set module state failed, error: " << e.what();
                session.abort_transaction();
            }
            return GetModuleByName(name);

        } else {

            return _memoryDb.SetState(name, state);
        }
    }

    void ModuleDatabase::SetStatus(const std::string &name, const Entity::Module::ModuleStatus &status) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)),
                                                            make_document(kvp("$set",
                                                                              make_document(kvp("status",
                                                                                                Entity::Module::ModuleStatusToString(
                                                                                                        status))))));
                log_trace << "Module status updated, name: " << name << " state: "
                          << Entity::Module::ModuleStatusToString(status);

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Set module status failed, error: " << e.what();
            }

        } else {

            _memoryDb.SetStatus(name, status);
        }
    }

    void ModuleDatabase::SetPort(const std::string &name, int port) {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)),
                                                            make_document(kvp("$set", make_document(kvp("port", port)))));
                log_trace << "Module port updated, name: " << name << " port: " << port;

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Set module port failed, error: " << e.what();
            }

        } else {

            _memoryDb.SetPort(name, port);
        }
    }

    Entity::Module::Module ModuleDatabase::CreateOrUpdateModule(const Entity::Module::Module &modules) {

        if (ModuleExists(modules.name)) {
            return UpdateModule((modules));
        } else {
            return CreateModule(modules);
        }
    }

    int ModuleDatabase::ModuleCount() {

        if (_useDatabase) {

            try {

                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
                int64_t count = _moduleCollection.count_documents(make_document());
                log_trace << "Service state: " << (count > 0 ? "true" : "false");
                return static_cast<int>(count);

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Service exists failed, error: " << e.what();
            }

        } else {

            return _memoryDb.ModuleCount();
        }
        return -1;
    }

    Entity::Module::ModuleList ModuleDatabase::ListModules() {

        Entity::Module::ModuleList modulesList;
        if (_useDatabase) {

            auto client = GetClient();
            mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];
            auto serviceCursor = _moduleCollection.find({});
            for (auto service: serviceCursor) {
                Entity::Module::Module result;
                result.FromDocument(service);
                modulesList.push_back(result);
            }

        } else {

            modulesList = _memoryDb.ListModules();
        }

        log_trace << "Got module list, size:" << modulesList.size();
        return modulesList;
    }

    void ModuleDatabase::DeleteModule(const Entity::Module::Module &module) {

        if (_useDatabase) {

            try {
                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];

                auto result = _moduleCollection.delete_many(make_document(kvp("name", module.name)));
                log_info << "Service deleted, count: " << result->deleted_count();

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Delete module failed, error: " << e.what();
            }

        } else {

            _memoryDb.DeleteModule(module);
        }
    }

    void ModuleDatabase::DeleteAllModules() {

        if (_useDatabase) {

            try {
                auto client = GetClient();
                mongocxx::collection _moduleCollection = (*client)[_databaseName][_moduleCollectionName];

                auto result = _moduleCollection.delete_many(make_document());
                log_info << "All module deleted, count: " << result->deleted_count();

            } catch (mongocxx::exception::system_error &e) {
                log_error << "Delete all module failed, error: " << e.what();
            }

        } else {

            return _memoryDb.DeleteAllModules();
        }
    }

}// namespace AwsMock::Database
