//
// Created by vogje01 on 29/05/2023.
//

#ifndef AWSMOCK_REPOSITORY_SERVICEDATABASE_H
#define AWSMOCK_REPOSITORY_SERVICEDATABASE_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/Configuration.h>
#include "awsmock/entity/service/Service.h"
#include <awsmock/repository/Database.h>

namespace AwsMock::Database {

  class ServiceDatabase : public Database {

    public:

      /**
       * Constructor
       *
       * @param configuration configuration properties
       */
      explicit ServiceDatabase(const Core::Configuration &configuration);

      /**
       * Checks the active flag.
       *
       * @param name service name
       * @return true if active
       */
      bool IsActive(const std::string &name);

      /**
       * Check existence of service
       *
       * @param name service name
       * @return created service
       */
      bool ServiceExists(const std::string &service);

      /**
       * Returns the service by id
       *
       * @param oid service oid
       * @return service, if existing
       * @throws DatabaseException
       */
      Entity::Service::Service GetServiceById(const bsoncxx::oid &oid);

      /**
       * Returns the service by id
       *
       * @param name service name
       * @return service, if existing
       * @throws DatabaseException
       */
      Entity::Service::Service GetServiceByName(const std::string &name);

      /**
       * Creates a service
       *
       * @param service service entity
       * @return created service
       */
      Entity::Service::Service CreateService(const Entity::Service::Service &service);

      /**
       * Uupdates a service
       *
       * @param service service entity
       * @return updated service
       */
      Entity::Service::Service UpdateService(const Entity::Service::Service &service);

      /**
       * Creates or updates a service
       *
       * @param service service entity
       * @return updated service
       */
      Entity::Service::Service CreateOrUpdateService(const Entity::Service::Service &service);

      /**
       * Counts the number of services
       *
       * @return total number of services
       */
      int ServiceCount();

      /**
       * @brief Returns a list of all services
       *
       * @return list of all services
       */
      Entity::Service::ServiceList ListServices();

      /**
       * Deletes service
       *
       * @param service service entity
       */
      void DeleteService(const Entity::Service::Service &service);

      /**
       * Deletes all service
       */
      void DeleteAllServices();

    private:

      /**
       * Logger
       */
      Core::LogStream _logger;

      /**
       * Service collection
       */
      mongocxx::collection _serviceCollection{};

  };

} // namespace AwsMock::Database

#endif // AWSMOCK_REPOSITORY_SERVICEDATABASE_H
