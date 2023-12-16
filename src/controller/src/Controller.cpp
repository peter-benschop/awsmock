//
// Created by vogje01 on 10/23/23.
//

#include <awsmock/controller/Controller.h>

namespace AwsMock::Controller {

  Controller::Controller(const Configuration &configuration) : _logger(Poco::Logger::get("Controller")), _configuration(configuration) {

    // Initialize database
    _host = configuration.getString("awsmock.manager.host", AWSMOCKCTL_DEFAULT_HOST);
    _port = configuration.getInt("awsmock.manager.port", AWSMOCKCTL_DEFAULT_PORT);
    _baseUrl = "http://" + _host + ":" + std::to_string(_port);

    // Get user/clientId/region
    _user = _configuration.getString("awsmock.user", AWSMOCKCTL_DEFAULT_USER);
    _clientId = _configuration.getString("awsmock.client.id", AWSMOCKCTL_DEFAULT_CLIENT);
    _region = _configuration.getString("awsmock.region", AWSMOCKCTL_DEFAULT_REGION);
  }

  void Controller::ListServices() {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl, headers);

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }

    std::vector<Dto::Module::Module> modules = Dto::Module::Module::FromJsonList(response.output);

    std::cout << "Modules:" << std::endl;
    for (auto const &module : modules) {
      std::string sport = module.port > 0 ? std::to_string(module.port) : "";
      std::cout << "  " << std::setw(16) << std::left << module.name << std::setw(9) << Database::Entity::Module::ModuleStateToString(module.status)
                << std::setw(9) << " " << std::setw(10) << std::left << sport << std::endl;
    }
  }

  void Controller::StartService(const std::string &name) {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _baseUrl + "/" + name + "/start", headers);

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }

    if (name == "all") {

      std::cout << "All modules started" << std::endl;

    } else {
      Dto::Module::Module module = Dto::Module::Module::FromJson(response.output);
      if (response.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {
        if (module.port > 0) {
          std::cout << "Module " << module.name << "(" << module.port << ") started" << std::endl;
        } else {
          std::cout << "Module " << module.name << " started" << std::endl;
        }
      } else {
        std::cout << "Module " << name << " could not be started: " << response.output << std::endl;
      }
    }
  }

  void Controller::RestartService(const std::string &name) {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _baseUrl + "/" + name + "/restart", headers);

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }

    if (name == "all") {

      std::cout << "All modules restarted" << std::endl;

    } else {
      Dto::Module::Module module = Dto::Module::Module::FromJson(response.output);
      if (response.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {
        if (module.port > 0) {
          std::cout << "Module " << module.name << "(" << module.port << ") restarted" << std::endl;
        } else {
          std::cout << "Module " << module.name << " restarted" << std::endl;
        }
      } else {
        std::cout << "Module " << name << " could not be restarted: " << response.output << std::endl;
      }
    }
  }

  void Controller::StopService(const std::string &name) {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _baseUrl + "/" + name + "/stop", headers);

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }

    if (name == "all") {

      std::cout << "All modules stopped" << std::endl;

    } else {
      Dto::Module::Module module = Dto::Module::Module::FromJson(response.output);
      if (response.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {
        if (module.port > 0) {
          std::cout << "Module " << module.name << "(" << module.port << ") stopped" << std::endl;
        } else {
          std::cout << "Module " << module.name << " stopped" << std::endl;
        }
      } else {
        std::cout << "Module " << name << " could not be stopped: " << response.output << std::endl;
      }
    }
  }

#ifdef HAS_SYSTEMD
  void Controller::ShowServiceLogs() {
    sd_journal *jd;
    int r = sd_journal_open(&jd, SD_JOURNAL_LOCAL_ONLY);
    if (r != 0) {
      std::cerr << "Failed to open journal:" << strerror(r) << std::endl;
      return;
    }

    r = sd_journal_add_match(jd, "_SYSTEMD_UNIT=aws-mock.service", 0);
    if (r != 0) {
      std::cerr << "Failed to set matching entries: " << strerror(r) << std::endl;
      return;
    }

    r = sd_journal_seek_tail(jd);
    if (r != 0) {
      std::cerr << "Failed to got to end of journal:" << strerror(r) << std::endl;
      return;
    }

    for (;;) {
      const void *d;
      size_t l;
      r = sd_journal_next(jd);
      if (r < 0) {
        std::cerr << "Failed to iterate to next entry: " << strerror(-r) << std::endl;
        break;
      }
      if (r == 0) {
        // Reached the end, let's wait for changes, and try again
        r = sd_journal_wait(jd, (uint64_t) -1);
        if (r < 0) {
          std::cerr << "Failed to wait for changes: " << strerror(-r) << std::endl;
          break;
        }
        continue;
      }
      r = sd_journal_get_data(jd, "MESSAGE", &d, &l);
      if (r < 0) {
        std::cerr << "Failed to read message field: " << strerror(-r) << std::endl;
        continue;
      }
      printf("%.*s\n", (int) l, (const char *) d + 8);
    }
    sd_journal_close(jd);
  }
#endif

  void Controller::SetLogLevel(const std::string &level) {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _baseUrl + "/manager/loglevel/" + level, headers);

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }

    Dto::Module::Module module = Dto::Module::Module::FromJson(response.output);
    if (response.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {
      std::cout << "Log level set to " << level << std::endl;
    } else {
      std::cout << "Could not set log level: " << response.output << std::endl;
    }
  }

  void Controller::GetDefaults() {

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl + "/config/", headers);

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }

    Dto::Module::GatewayConfig gatewayConfig = Dto::Module::GatewayConfig::FromJson(response.output);
    if (response.statusCode == Poco::Net::HTTPResponse::HTTP_OK) {
      std::cout << "Config: " << std::endl;
      std::cout << "  " << std::setw(16) << std::left << "Endpoint: " << std::setw(32) << gatewayConfig.endpoint << std::endl;
      std::cout << "  " << std::setw(16) << std::left << "Host: " << std::setw(32) << gatewayConfig.host << std::endl;
      std::cout << "  " << std::setw(16) << std::left << "Port: " << std::setw(32) << gatewayConfig.port << std::endl;
      std::cout << "  " << std::setw(16) << std::left << "User: " << std::setw(32) << gatewayConfig.user << std::endl;
      std::cout << "  " << std::setw(16) << std::left << "AccessId: " << std::setw(32) << gatewayConfig.accessId << std::endl;
      std::cout << "  " << std::setw(16) << std::left << "ClientId: " << std::setw(32) << gatewayConfig.clientId << std::endl;
      std::cout << "  " << std::setw(16) << std::left << "DataDir: " << std::setw(32) << gatewayConfig.dataDir << std::endl;
    } else {
      std::cout << "Could not set log level: " << response.output << std::endl;
    }
  }

  void Controller::ExportInfrastructure(const std::vector<std::string> &services, bool pretty) {

    Dto::Common::Services exportServices;
    for (const auto &service : services) {
      exportServices.serviceNames.emplace_back(service);
    }

    std::string url = pretty ? "/export?pretty=true" : "/export?pretty=false";
    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl + url, headers, exportServices.ToJson());

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }
    std::cout << response.output;
  }

  void Controller::ImportInfrastructure() {

    std::string line;
    std::stringstream jsonString;
    while (std::getline(std::cin, line)) {
      jsonString << line;
    }

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl + "/import", headers, jsonString.str());

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }
    std::cout << response.output;
  }

  void Controller::CleanInfrastructure(const std::vector<std::string> &services) {

    Dto::Common::Services exportServices;
    for (const auto &service : services) {
      exportServices.serviceNames.emplace_back(service);
    }

    std::map<std::string, std::string> headers;
    AddAuthorization(headers);
    Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl + "/clean", headers, exportServices.ToJson());

    if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
      std::cerr << "Error: " << response.statusReason << std::endl;
      return;
    }
    std::cout << response.output;
  }

  void Controller::AddAuthorization(std::map<std::string, std::string> &headers) {
    headers["Authorization"] = Core::AwsUtils::GetAuthorizationHeader(_configuration, "module");
  }
} // namespace AwsMock::Controller