//
// Created by vogje01 on 11/19/23.
//

#include <awsmock/memorydb/ModuleMemoryDb.h>

namespace AwsMock::Database {

  ModuleMemoryDb::ModuleMemoryDb() : _logger(Poco::Logger::get("ModuleMemoryDb")) {}

  bool ModuleMemoryDb::ModuleExists(const std::string &name) {

    return find_if(_modules.begin(), _modules.end(), [name](const std::pair<std::string, Entity::Module::Module> &module) {
      return module.second.name == name;
    }) != _modules.end();
  }

  bool ModuleMemoryDb::IsActive(const std::string &name) {

    return find_if(_modules.begin(), _modules.end(), [name](const std::pair<std::string, Entity::Module::Module> &module) {
      return module.second.name == name && module.second.status == Entity::Module::ModuleStatus::ACTIVE;
    }) != _modules.end();
  }

  Entity::Module::Module ModuleMemoryDb::GetModuleById(const std::string &oid) {

    auto it = find_if(_modules.begin(), _modules.end(), [oid](const std::pair<std::string, Entity::Module::Module> &module) {
      return module.first == oid;
    });

    if (it != _modules.end()) {
      it->second.oid = oid;
      return it->second;
    }
    return {};
  }

  Entity::Module::Module ModuleMemoryDb::GetModuleByName(const std::string &name) {

    auto it = find_if(_modules.begin(), _modules.end(), [name](const std::pair<std::string, Entity::Module::Module> &module) {
      return module.second.name == name;
    });

    if (it != _modules.end()) {
      it->second.oid = it->first;
      return it->second;
    }
    return {};
  }

  Entity::Module::Module ModuleMemoryDb::CreateModule(const Entity::Module::Module &module) {
    Poco::ScopedLock lock(_moduleMutex);

    std::string oid = Poco::UUIDGenerator().createRandom().toString();
    _modules[oid] = module;
    log_trace_stream(_logger) << "Module created, oid: " << oid << std::endl;
    return GetModuleById(oid);

  }

  Entity::Module::ModuleList ModuleMemoryDb::ListModules() {

    Entity::Module::ModuleList moduleList;
    for (const auto &module : _modules) {
      moduleList.emplace_back(module.second);
    }

    log_trace_stream(_logger) << "Got module list, size: " << moduleList.size() << std::endl;
    return moduleList;
  }

  Entity::Module::Module ModuleMemoryDb::UpdateModule(const Entity::Module::Module &module) {
    Poco::ScopedLock lock(_moduleMutex);

    std::string name = module.name;
    auto it = find_if(_modules.begin(), _modules.end(), [name](const std::pair<std::string, Entity::Module::Module> &module) {
      return module.second.name == name;
    });
    _modules[it->first] = module;
    return _modules[it->first];
  }

  void ModuleMemoryDb::DeleteModule(const Entity::Module::Module &module) {
    Poco::ScopedLock lock(_moduleMutex);

    std::string name = module.name;
    const auto count = std::erase_if(_modules, [name](const auto &item) {
      auto const &[key, value] = item;
      return value.name == name;
    });
    log_debug_stream(_logger) << "Module deleted, count: " << count << std::endl;
  }

  void ModuleMemoryDb::DeleteAllModules() {
    Poco::ScopedLock lock(_moduleMutex);

    log_debug_stream(_logger) << "All modules deleted, count: " << _modules.size() << std::endl;
    _modules.clear();
  }
}