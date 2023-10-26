//
// Created by vogje01 on 10/22/23.
//

#ifndef AWSMOCK_DB_ENTITY_MODULE_MODULESTATUS_H
#define AWSMOCK_DB_ENTITY_MODULE_MODULESTATUS_H

// C++ includes
#include <string>
#include <map>

namespace AwsMock::Database::Entity::Module {

  enum class ModuleStatus {
    STOPPED,
    RUNNING,
    SUSPENDED,
    UNKNOWN
  };

  static std::map<ModuleStatus, std::string> ModuleStatusNames{
      {ModuleStatus::STOPPED, "STOPPED"},
      {ModuleStatus::RUNNING, "RUNNING"},
      {ModuleStatus::SUSPENDED, "SUSPENDED"},
      {ModuleStatus::UNKNOWN, "UNKNOWN"},
  };

  [[maybe_unused]] static std::string ModuleStatusToString(ModuleStatus serviceStatus) {
    return ModuleStatusNames[serviceStatus];
  }

  [[maybe_unused]] static ModuleStatus ModuleStatusFromString(const std::string &serviceStatus) {
    for (auto &it : ModuleStatusNames) {
      if (it.second == serviceStatus) {
        return it.first;
      }
    }
    return ModuleStatus::UNKNOWN;
  }

} // AwsMock::Database::Entity::Module

#endif // AWSMOCK_DB_ENTITY_MODULE_MODULESTATUS_H
