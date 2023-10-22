//
// Created by vogje01 on 29/05/2023.
//

#include <awsmock/repository/ServiceDatabase.h>

namespace AwsMock::Database {

  using bsoncxx::builder::basic::kvp;
  using bsoncxx::builder::basic::make_array;
  using bsoncxx::builder::basic::make_document;

  ServiceDatabase::ServiceDatabase(const Core::Configuration &configuration) : Database(configuration), _logger(Poco::Logger::get("ServiceDatabase")) {

    // Get collections
    _serviceCollection = GetConnection()["service"];
  }

  bool ServiceDatabase::IsActive(const std::string &name) {

    try {
      auto result = _serviceCollection.find_one(make_document(kvp("name", name)));
      if (result) {
        Entity::Service::Service service;
        service.FromDocument(result);
        log_trace_stream(_logger) << "Service status: " << Entity::Service::ServiceStatusToString(service.status) << std::endl;
        return service.status == Entity::Service::ServiceStatus::RUNNING;
      }
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "IsActive failed, error: " << e.what() << std::endl;
    }
    return false;
  }

  bool ServiceDatabase::ServiceExists(const std::string &name) {
    try {
      int64_t count = _serviceCollection.count_documents(make_document(kvp("name", name)));
      log_trace_stream(_logger) << "Service status: " << (count > 0 ? "true" : "false") << std::endl;
      return count > 0;
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Service exists failed, error: " << e.what() << std::endl;
    }
    return false;
  }

  Entity::Service::Service ServiceDatabase::GetServiceById(const bsoncxx::oid &oid) {

    try {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _serviceCollection.find_one(make_document(kvp("_id", oid)));
      if (mResult) {
        Entity::Service::Service service;
        service.FromDocument(mResult);
        return service;
      }

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Get service by ID failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  Entity::Service::Service ServiceDatabase::GetServiceByName(const std::string &name) {

    try {

      mongocxx::stdx::optional<bsoncxx::document::value> mResult = _serviceCollection.find_one(make_document(kvp("name", name)));
      if (mResult) {
        Entity::Service::Service service;
        service.FromDocument(mResult);
        return service;
      }

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Get service by name failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  Entity::Service::Service ServiceDatabase::CreateService(const Entity::Service::Service &service) {

    try {

      auto result = _serviceCollection.insert_one(service.ToDocument().view());
      log_trace_stream(_logger) << "Service created, oid: " << result->inserted_id().get_oid().value.to_string() << std::endl;
      return GetServiceById(result->inserted_id().get_oid().value);

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Get service by ID failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  Entity::Service::Service ServiceDatabase::UpdateService(const Entity::Service::Service &service) {
    try {
      auto mResult = _serviceCollection.replace_one(make_document(kvp("name", service.name)), service.ToDocument());
      log_trace_stream(_logger) << "Service updated: " << service.ToString() << std::endl;
      return GetServiceByName(service.name);

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Update service failed, error: " << e.what() << std::endl;
    }
    return {};
  }

  Entity::Service::Service ServiceDatabase::CreateOrUpdateService(const Entity::Service::Service &service) {
    if (ServiceExists(service.name)) {
      return UpdateService((service));
    } else {
      return CreateService(service);
    }
  }

  int ServiceDatabase::ServiceCount() {
    try {
      int64_t count = _serviceCollection.count_documents(make_document());
      log_trace_stream(_logger) << "Service status: " << (count > 0 ? "true" : "false") << std::endl;
      return (int)count;
    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Service exists failed, error: " << e.what() << std::endl;
    }
    return -1;
  }

  void ServiceDatabase::DeleteService(const Entity::Service::Service &service) {
    try {
      auto result = _serviceCollection.delete_many(make_document(kvp("name", service.name)));
      log_debug_stream(_logger) << "Service deleted, count: " << result->deleted_count() << std::endl;

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Delete service failed, error: " << e.what() << std::endl;
    }
  }

  void ServiceDatabase::DeleteAllServices() {
    try {
      auto result = _serviceCollection.delete_many(make_document());
      log_debug_stream(_logger) << "All service deleted, count: " << result->deleted_count() << std::endl;

    } catch (mongocxx::exception::system_error &e) {
      log_error_stream(_logger) << "Delete all service failed, error: " << e.what() << std::endl;
    }
  }

} // namespace AwsMock::Database
