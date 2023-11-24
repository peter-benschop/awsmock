//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/ModuleDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  std::map<std::string, Entity::Module::Module> ModuleDatabase::_existingModules = {
      {"s3", {.name="s3", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}},
      {"sqs", {.name="sqs", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}},
      {"sns", {.name="sns", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}},
      {"lambda", {.name="lambda", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}},
      {"transfer", {.name="transfer", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}},
      {"cognito", {.name="cognito", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}},
      {"gateway", {.name="gateway", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}},
      {"database", {.name="database", .state=Entity::Module::ModuleState::STOPPED, .status=Entity::Module::ModuleStatus::INACTIVE}}
  };

  ModuleDatabase::ModuleDatabase(Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("ModuleDatabase")), _configuration(configuration) {

    if (HasDatabase()) {

      // Get collections
      _moduleCollection = GetConnection()["module"];

      // Create default modules
      for (auto const &module : _existingModules) {
        if (!ModuleExists(module.first)) {
          CreateModule(module.second);
        }
      }

    } else {

      for (auto &module : _existingModules) {
        module.second.status = _configuration.getBool("awsmock.service." + module.first + ".active", false) ? Entity::Module::ModuleStatus::ACTIVE : Entity::Module::ModuleStatus::INACTIVE;
        module.second.state = _configuration.getBool("awsmock.service." + module.first + ".active", false) ? Entity::Module::ModuleState::RUNNING : Entity::Module::ModuleState::STOPPED;
        _memoryDb.CreateModule(module.second);
      }

    }
  }

  bool ModuleDatabase::IsActive(const std::string &name) {

    if (HasDatabase()) {

      try {
        auto result = _moduleCollection.find_one(make_document(kvp("name", name)));
        if (result) {
          Entity::Module::Module module;
          module.FromDocument(result);
          log_trace_stream(_logger) << "Module state: " << Entity::Module::ModuleStateToString(module.state) << std::endl;
          return module.status == Entity::Module::ModuleStatus::ACTIVE;
        }
      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "IsActive failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.IsActive(name);

    }
    return false;
  }

  bool ModuleDatabase::ModuleExists(const std::string &name) {

    if (HasDatabase()) {

      try {
        int64_t count = _moduleCollection.count_documents(make_document(kvp("name", name)));
        log_trace_stream(_logger) << "Module exists: " << (count > 0 ? "true" : "false") << std::endl;
        return count > 0;
      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Module exists failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.ModuleExists(name);

    }
    return false;
  }

  Entity::Module::Module ModuleDatabase::GetModuleById(const bsoncxx::oid &oid) {

    try {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _moduleCollection.find_one(make_document(kvp("_id", oid)));
      if (mResult) {
        Entity::Module::Module modules;
        modules.FromDocument(mResult);
        return modules;
      }

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Get module by ID failed, error: " << e.what() << std::endl;
    }
    return {};

  }

  Entity::Module::Module ModuleDatabase::GetModuleById(const std::string &oid) {

    if (HasDatabase()) {

      try {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _moduleCollection.find_one(make_document(kvp("_id", oid)));
        if (mResult) {
          Entity::Module::Module modules;
          modules.FromDocument(mResult);
          return modules;
        }

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get module by ID failed, error: " << e.what() << std::endl;
      }
      return {};

    } else {

      return _memoryDb.GetModuleById(oid);

    }
  }

  Entity::Module::Module ModuleDatabase::GetModuleByName(const std::string &name) {

    if (HasDatabase()) {

      try {

        mongocxx::stdx::optional<bsoncxx::document::value> mResult = _moduleCollection.find_one(make_document(kvp("name", name)));
        if (mResult) {
          Entity::Module::Module modules;
          modules.FromDocument(mResult);
          return modules;
        }

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get module by name failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.GetModuleByName(name);

    }
    return {};
  }

  Entity::Module::Module ModuleDatabase::CreateModule(const Entity::Module::Module &module) {

    if (HasDatabase()) {

      try {

        auto result = _moduleCollection.insert_one(module.ToDocument().view());
        log_trace_stream(_logger) << "Module created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;
        return GetModuleById(result->inserted_id().get_oid().value);

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Get module by ID failed, error: " << e.what() << std::endl;
        throw Core::DatabaseException("Get module by ID failed, error: " + std::string(e.what()));
      }

    } else {

      return _memoryDb.CreateModule(module);

    }
  }

  Entity::Module::Module ModuleDatabase::UpdateModule(const Entity::Module::Module &module) {

    if (HasDatabase()) {

      try {
        auto mResult = _moduleCollection.replace_one(make_document(kvp("name", module.name)), module.ToDocument());
        log_trace_stream(_logger) << "Module updated: " << module.ToString() << std::endl;
        return GetModuleByName(module.name);

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Update module failed, error: " << e.what() << std::endl;
        throw Core::DatabaseException("Update module failed, error: " + std::string(e.what()));
      }

    } else {

      return _memoryDb.UpdateModule(module);

    }
    return {};
  }

  void ModuleDatabase::SetState(const std::string &name, const Entity::Module::ModuleState &state) {

    if (HasDatabase()) {

      try {
        auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)), make_document(kvp("$set", make_document(kvp("state", Entity::Module::ModuleStateToString(state))))));
        log_trace_stream(_logger) << "Module state updated, name: " << name << " state: " << Entity::Module::ModuleStateToString(state) << std::endl;
      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Set module state failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.SetState(name, state);

    }
  }

  void ModuleDatabase::SetStatus(const std::string &name, const Entity::Module::ModuleStatus &status) {

    if (HasDatabase()) {

      try {
        auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)), make_document(kvp("$set", make_document(kvp("status", Entity::Module::ModuleStatusToString(status))))));
        log_trace_stream(_logger) << "Module status updated, name: " << name << " state: " << Entity::Module::ModuleStatusToString(status) << std::endl;
      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Set module status failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.SetStatus(name, status);

    }
  }

  void ModuleDatabase::SetPort(const std::string &name, int port) {

    if (HasDatabase()) {

      try {
        auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)), make_document(kvp("$set", make_document(kvp("port", port)))));
        log_trace_stream(_logger) << "Module port updated, name: " << name << " port: " << port << std::endl;
      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Set module port failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.SetPort(name, port);

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

    if (HasDatabase()) {

      try {

        int64_t count = _moduleCollection.count_documents(make_document());
        log_trace_stream(_logger) << "Service state: " << (count > 0 ? "true" : "false") << std::endl;
        return static_cast<int>(count);

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Service exists failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.ModuleCount();

    }
    return -1;
  }

  Entity::Module::ModuleList ModuleDatabase::ListModules() {

    Entity::Module::ModuleList modulesList;
    if (HasDatabase()) {

      auto serviceCursor = _moduleCollection.find({});
      for (auto service : serviceCursor) {
        Entity::Module::Module result;
        result.FromDocument(service);
        modulesList.push_back(result);
      }

    } else {

      modulesList = _memoryDb.ListModules();

    }

    log_trace_stream(_logger) << "Got module list, size:" << modulesList.size() << std::endl;
    return modulesList;
  }

  void ModuleDatabase::DeleteModule(const Entity::Module::Module &module) {

    if (HasDatabase()) {

      try {

        auto result = _moduleCollection.delete_many(make_document(kvp("name", module.name)));
        log_debug_stream(_logger) << "Service deleted, count: " << result->deleted_count() << std::endl;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Delete module failed, error: " << e.what() << std::endl;
      }

    } else {

      _memoryDb.DeleteModule(module);

    }
  }

  void ModuleDatabase::DeleteAllModules() {

    if (HasDatabase()) {

      try {

        auto result = _moduleCollection.delete_many(make_document());
        log_debug_stream(_logger) << "All module deleted, count: " << result->deleted_count() << std::endl;

      } catch (mongocxx::exception::system_error &e) {
        log_error_stream(_logger) << "Delete all module failed, error: " << e.what() << std::endl;
      }

    } else {

      return _memoryDb.DeleteAllModules();

    }
  }

} // namespace AwsMock::Database
