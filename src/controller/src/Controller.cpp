//
// Created by vogje01 on 10/23/23.
//

#include <awsmock/controller/Controller.h>

namespace AwsMock::Controller {

  Controller::Controller(const Configuration &configuration) : _logger(Poco::Logger::get("Controller")), _configuration(configuration) {

    // Initialize database
    _serviceDatabase = std::make_unique<Database::ModuleDatabase>(_configuration);
    _host= configuration.getString("awsmock.manager.host", AWSMOCKCTL_DEFAULT_HOST);
    _port= configuration.getInt("awsmock.manager.port", AWSMOCKCTL_DEFAULT_PORT);
    _baseUrl = "http://" + _host + ":" + std::to_string(_port);
  }

  void Controller::ListServices() {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl, headers);

    std::vector<Dto::Module::Module> modules = Dto::Module::Module::FromJsonList(response.output);

    std::cout << "Modules:" << std::endl;
    for (auto const &module : modules) {
      std::cout << "  " << std::setw(16) << std::left << module.name << std::setw(9) << Database::Entity::Module::ModuleStatusToString(module.status)
                << std::setw(9) << " " << std::setw(10) << std::left << module.port << std::endl;
    }
  }

  void Controller::StartService(const std::string &name) {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _baseUrl + "/" + name + "/start", headers);

    Dto::Module::Module module = Dto::Module::Module::FromJson(response.output);
    if (response.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {
      std::cout << "Module " << module.name << "(" << module.port << ")" << " started" << std::endl;
    } else {
      std::cout << "Module " << name << " could not be started: " << response.output << std::endl;
    }
  }

  void Controller::StopService(const std::string &name) {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _baseUrl + "/" + name + "/stop", headers);

    Dto::Module::Module module = Dto::Module::Module::FromJson(response.output);
    if (response.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {
      std::cout << "Module " << module.name << "(" << module.port << ")" << " stopped" << std::endl;
    } else {
      std::cout << "Module " << name << " could not be stopped: " << response.output << std::endl;
    }
  }

  void Controller::AddAuthorization(std::map<std::string, std::string> &headers) {
    headers["Authorization"] = "AWS4-HMAC-SHA256 Credential=XXX/00000000/eu-central-1/module/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840";
  }
} // namespace AwsMock::Controller