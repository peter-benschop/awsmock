//
// Created by vogje01 on 10/22/23.
//

#ifndef AWSMOCK_DB_ENTITY_MODULE_MODULESTATUS_H
#define AWSMOCK_DB_ENTITY_MODULE_MODULESTATUS_H

// C++ includes
#include <string>
#include <map>

namespace AwsMock::Database::Entity::Module {

  enum class ModuleState {
    STOPPED,
    STARTING,
    RUNNING,
    SUSPENDED,
    UNKNOWN
  };

  static std::map<ModuleState, std::string> ModuleStateNames{
      {ModuleState::STOPPED, "STOPPED"},
      {ModuleState::STARTING, "STARTING"},
      {ModuleState::RUNNING, "RUNNING"},
      {ModuleState::SUSPENDED, "SUSPENDED"},
      {ModuleState::UNKNOWN, "UNKNOWN"},
  };

  [[maybe_unused]] static std::string ModuleStateToString(ModuleState serviceStatus) {
    return ModuleStateNames[serviceStatus];
  }

  [[maybe_unused]] static ModuleState ModuleStateFromString(const std::string &serviceStatus) {
    for (auto &it : ModuleStateNames) {
      if (it.second == serviceStatus) {
        return it.first;
      }
    }
    return ModuleState::UNKNOWN;
  }

  enum class ModuleStatus {
    INACTIVE,
    ACTIVE,
    UNKNOWN
  };

  static std::map<ModuleStatus, std::string> ModuleStatusNames{
      {ModuleStatus::INACTIVE, "INACTIVE"},
      {ModuleStatus::ACTIVE, "ACTIVE"},
      {ModuleStatus::UNKNOWN, "UNKNOWN"}
  };

  [[maybe_unused]] static std::string ModuleStatusToString(ModuleStatus modulesStatus) {
    return ModuleStatusNames[modulesStatus];
  }

  [[maybe_unused]] static ModuleStatus ModuleStatusFromString(const std::string &modulesStatus) {
    for (auto &it : ModuleStatusNames) {
      if (it.second == modulesStatus) {
        return it.first;
      }
    }
    return ModuleStatus::UNKNOWN;
  }

} // AwsMock::Database::Entity::Module

#endif // AWSMOCK_DB_ENTITY_MODULE_MODULESTATUS_H
