//
// Created by vogje01 on 10/22/23.
//

#ifndef AWSMOCK_DB_ENTITY_SERVICE_SERVICESTATUS_H
#define AWSMOCK_DB_ENTITY_SERVICE_SERVICESTATUS_H

// C++ includes
#include <string>
#include <map>

namespace AwsMock::Database::Entity::Service {

  enum class ServiceStatus {
    STOPPED,
    RUNNING,
    SUSPENDED,
    UNKNOWN
  };

  static std::map <ServiceStatus, std::string> ServiceStatusNames{
      {ServiceStatus::STOPPED, "STOPPED"},
      {ServiceStatus::RUNNING, "RUNNING"},
      {ServiceStatus::SUSPENDED, "SUSPENDED"},
      {ServiceStatus::UNKNOWN, "UNKNOWN"},
  };

  [[maybe_unused]] static std::string ServiceStatusToString(ServiceStatus serviceStatus) {
    return ServiceStatusNames[serviceStatus];
  }

  [[maybe_unused]] static ServiceStatus ServiceStatusFromString(const std::string &serviceStatus) {
    for (auto &it : ServiceStatusNames) {
      if (it.second == serviceStatus) {
        return it.first;
      }
    }
    return ServiceStatus::UNKNOWN;
  }

} // AwsMock::Database::Entity::Service

#endif // AWSMOCK_DB_ENTITY_SERVICE_SERVICESTATUS_H
