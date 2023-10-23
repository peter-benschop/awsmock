//
// Created by vogje01 on 10/23/23.
//

#include <awsmock/controller/Controller.h>

namespace AwsMock::Controller {

  Controller::Controller(const Configuration &configuration) : _logger(Poco::Logger::get("Controller")), _configuration(configuration) {

    // Initialize database
    _serviceDatabase = std::make_unique<Database::ServiceDatabase>(_configuration);
  }

  void Controller::ListServices() {

    Database::Entity::Service::ServiceList services = _serviceDatabase->ListServices();

    std::cout << "Services:" << std::endl;
    for (auto const &it : services) {
      std::cout << "  " << std::setw(16) << std::left << it.name << std::setw(9) << Database::Entity::Service::ServiceStatusToString(it.status) << std::endl;
    }
  }

  void Controller::StartService(const std::string &name) {

    Database::Entity::Service::Service service = _serviceDatabase->GetServiceByName(name);
    if (service.name.empty()) {
      std::cerr << "Error, Unknown service: " << name << std::endl;
      exit(1);
    }

    std::string command = "/bin/sh -c \"/usr/bin/" + service.executable + " --level=debug --file /var/log/awsmock/" + name + ".log &\"";

    system(command.c_str());
    std::cout << "Service " << name << " started" << std::endl;
  }
} // namespace AwsMock::Controller