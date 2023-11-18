//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/ModuleDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  std::map<std::string, Entity::Module::Module> ModuleDatabase::_existingModules = {
      {"s3", {.name="s3", .status=Entity::Module::ModuleStatus::STOPPED}},
      {"sqs", {.name="sqs", .status=Entity::Module::ModuleStatus::STOPPED}},
      {"sns", {.name="sns", .status=Entity::Module::ModuleStatus::STOPPED}},
      {"lambda", {.name="lambda", .status=Entity::Module::ModuleStatus::STOPPED}},
      {"transfer", {.name="transfer", .status=Entity::Module::ModuleStatus::STOPPED}},
      {"cognito", {.name="cognito", .status=Entity::Module::ModuleStatus::STOPPED}},
      {"gateway", {.name="gateway", .status=Entity::Module::ModuleStatus::STOPPED}},
  };

  ModuleDatabase::ModuleDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("ModuleDatabase")) {

    // Get collections
    _moduleCollection = GetConnection()["module"];

    // Create default modules
    for (auto const &module : _existingModules) {
      if (!ModuleExists(module.first)) {
        CreateModule(module.second);
      }
    }
  }

  bool ModuleDatabase::IsActive(const std::string &name) {

    try {
      auto result = _moduleCollection.find_one(make_document(kvp("name", name)));
      if (result) {
        Entity::Module::Module service;
        service.FromDocument(result);
        log_trace_stream(_logger) << "Module status: " << Entity::Module::ModuleStatusToString(service.status) << std::endl;
        return service.status == Entity::Module::ModuleStatus::RUNNING;
      }
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "IsActive failed, error: " << e.what() << std::endl;
    }
    return false;
  }

  bool ModuleDatabase::ModuleExists(const std::string &module) {
    try {
      int64_t count = _moduleCollection.count_documents(make_document(kvp("name", module)));
      log_trace_stream(_logger) << "Module exists: " << (count > 0 ? "true" : "false") << std::endl;
      return count > 0;
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Module exists failed, error: " << e.what() << std::endl;
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

  Entity::Module::Module ModuleDatabase::GetModuleByName(const std::string &name) {

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
    return {};
  }

  Entity::Module::Module ModuleDatabase::CreateModule(const Entity::Module::Module &module) {

    try {

      auto result = _moduleCollection.insert_one(module.ToDocument().view());
      log_trace_stream(_logger) << "Module created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;
      return GetModuleById(result->inserted_id().get_oid().value);

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Get module by ID failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  Entity::Module::Module ModuleDatabase::UpdateModule(const Entity::Module::Module &module) {
    try {
      auto mResult = _moduleCollection.replace_one(make_document(kvp("name", module.name)), module.ToDocument());
      log_trace_stream(_logger) << "Module updated: " << module.ToString() << std::endl;
      return GetModuleByName(module.name);

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Update module failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  void ModuleDatabase::SetStatus(const std::string &name, const Entity::Module::ModuleStatus &status) {
    try {
      auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)), make_document(kvp("$set", make_document(kvp("status", Entity::Module::ModuleStatusToString(status))))));
      log_trace_stream(_logger) << "Module status updated, name: " << name << " status: " << Entity::Module::ModuleStatusToString(status) << std::endl;
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Set module status failed, error: " << e.what() << std::endl;
    }
  }

  void ModuleDatabase::SetPort(const std::string &name, int port) {
    try {
      auto mResult = _moduleCollection.update_one(make_document(kvp("name", name)), make_document(kvp("$set", make_document(kvp("port", port)))));
      log_trace_stream(_logger) << "Module port updated, name: " << name << " port: " << port << std::endl;
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Set module port failed, error: " << e.what() << std::endl;
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
    try {
      int64_t count = _moduleCollection.count_documents(make_document());
      log_trace_stream(_logger) << "Service status: " << (count > 0 ? "true" : "false") << std::endl;
      return (int) count;
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Service exists failed, error: " << e.what() << std::endl;
    }
    return -1;
  }

  Entity::Module::ModuleList ModuleDatabase::ListModules() {

    Entity::Module::ModuleList modulesList;
    auto serviceCursor = _moduleCollection.find({});
    for (auto service : serviceCursor) {
      Entity::Module::Module result;
      result.FromDocument(service);
      modulesList.push_back(result);
    }

    log_trace_stream(_logger) << "Got module list, size:" << modulesList.size() << std::endl;
    return modulesList;
  }

  void ModuleDatabase::DeleteModule(const Entity::Module::Module &module) {
    try {
      auto result = _moduleCollection.delete_many(make_document(kvp("name", module.name)));
      log_debug_stream(_logger) << "Service deleted, count: " << result->deleted_count() << std::endl;

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Delete module failed, error: " << e.what() << std::endl;
    }
  }

  void ModuleDatabase::DeleteAllModules() {
    try {
      auto result = _moduleCollection.delete_many(make_document());
      log_debug_stream(_logger) << "All module deleted, count: " << result->deleted_count() << std::endl;

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Delete all module failed, error: " << e.what() << std::endl;
    }
  }

} // namespace AwsMock::Database
