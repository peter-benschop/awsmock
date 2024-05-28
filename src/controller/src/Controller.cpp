//
// Created by vogje01 on 10/23/23.
//

#include <awsmock/controller/Controller.h>

namespace AwsMock::Controller {

    AwsMockCtl::AwsMockCtl() {

        // Initialize database
        Core::Configuration &configuration = Core::Configuration::instance();
        _host = configuration.getString("awsmock.manager.host", AWSMOCKCTL_DEFAULT_HOST);
        _port = configuration.getInt("awsmock.manager.port", AWSMOCKCTL_DEFAULT_PORT);
        _baseUrl = "http://" + _host + ":" + std::to_string(_port);

        // Get user/clientId/region
        _user = configuration.getString("awsmock.user", AWSMOCKCTL_DEFAULT_USER);
        _clientId = configuration.getString("awsmock.client.userPoolId", AWSMOCKCTL_DEFAULT_CLIENT);
        _region = configuration.getString("awsmock.region", AWSMOCKCTL_DEFAULT_REGION);
    }

    void AwsMockCtl::Initialize(const std::vector<std::string> &commands) {
        _commands = commands;
    }

    void AwsMockCtl::Run() {

        if (std::find(_commands.begin(), _commands.end(), "list") != _commands.end()) {

            ListServices();

        } else if (std::find(_commands.begin(), _commands.end(), "config") != _commands.end()) {

            GetConfig();

        } else if (std::find(_commands.begin(), _commands.end(), "loglevel") != _commands.end()) {

            std::string loglevel;
            for (const auto &command: _commands) {
                if (command != "loglevel") {
                    loglevel = command;
                }
            }
            SetLogLevel(loglevel);

        } else if (std::find(_commands.begin(), _commands.end(), "logs") != _commands.end()) {

            //ShowServiceLogs();

        } else if (std::find(_commands.begin(), _commands.end(), "start") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "start") {
                    Dto::Module::Module module;
                    module.name = command;
                    module.status = Database::Entity::Module::ModuleState::RUNNING;
                    modules.emplace_back(module);
                }
            }
            StartService(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "restart") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "restart") {
                    Dto::Module::Module module;
                    module.name = command;
                    modules.emplace_back(module);
                }
            }
            StartService(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "stop") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "stop") {
                    Dto::Module::Module module;
                    module.name = command;
                    module.status = Database::Entity::Module::ModuleState::STOPPED;
                    modules.emplace_back(module);
                }
            }
            StopService(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "cleanobjects") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "cleanobjects") {
                    Dto::Module::Module module;
                    module.name = command;
                    modules.emplace_back(module);
                }
            }
            CleanObjects(modules);
        }
    }

    void AwsMockCtl::ListServices() {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "list-services");
        Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl, headers);

        if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            std::cerr << "Error: " << response.statusReason << std::endl;
            return;
        }

        std::vector<Dto::Module::Module> modules = Dto::Module::Module::FromJsonList(response.output);

        std::cout << "Modules:" << std::endl;
        for (auto const &module: modules) {
            std::string sport = module.port > 0 ? std::to_string(module.port) : "";
            std::cout << "  " << std::setw(16) << std::left << module.name << std::setw(9) << Database::Entity::Module::ModuleStateToString(module.status)
                      << std::setw(9) << " " << std::setw(10) << std::left << sport << std::endl;
        }
    }

    void AwsMockCtl::StartService(std::vector<Dto::Module::Module> &modules) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "start-modules");
        Core::HttpSocketResult response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Error: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        modules = Dto::Module::Module::FromJsonList(response.body);
        for (const auto &module: modules) {
            if (module.port > 0) {
                std::cout << "Module " << module.name << "(" << module.port << ") started" << std::endl;
            } else {
                std::cout << "Module " << module.name << " started" << std::endl;
            }
        }
    }

    void AwsMockCtl::RestartService(std::vector<Dto::Module::Module> &modules) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "restart-modules");
        Core::HttpSocketResult response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Error: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        modules = Dto::Module::Module::FromJsonList(response.body);
        for (const auto &module: modules) {
            if (module.port > 0) {
                std::cout << "Module " << module.name << "(" << module.port << ") restarted" << std::endl;
            } else {
                std::cout << "Module " << module.name << " restarted" << std::endl;
            }
        }
    }

    void AwsMockCtl::StopService(Dto::Module::Module::ModuleList &modules) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "stop-modules");
        Core::HttpSocketResult response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Error: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        modules = Dto::Module::Module::FromJsonList(response.body);
        for (const auto &module: modules) {
            if (module.port > 0) {
                std::cout << "Module " << module.name << "(" << module.port << ") stopped" << std::endl;
            } else {
                std::cout << "Module " << module.name << " stopped" << std::endl;
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

        r = sd_journal_add_match(jd, "_SYSTEMD_UNIT=awsmock.service", 0);
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

    void AwsMockCtl::SetLogLevel(const std::string &level) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "set-log-level");
        Core::HttpSocketResult response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", level, headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not set log level, httpStatus: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }
        std::cout << "Log level set to " << level << std::endl;
    }

    void AwsMockCtl::GetConfig() {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "get-config");
        Core::HttpSocketResult response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::get, _host, _port, "/", {}, headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not set configuration, httpStatus: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        Dto::Module::GatewayConfig gatewayConfig = Dto::Module::GatewayConfig::FromJson(response.body);
        std::cout << "Config: " << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "Version: " << std::setw(32) << gatewayConfig.version << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "Endpoint: " << std::setw(32) << gatewayConfig.endpoint << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "Host: " << std::setw(32) << gatewayConfig.host << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "Port: " << std::setw(32) << gatewayConfig.port << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "Address: " << std::setw(32) << gatewayConfig.address << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "PID: " << std::setw(32) << gatewayConfig.pid << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "User: " << std::setw(32) << gatewayConfig.user << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "AccessId: " << std::setw(32) << gatewayConfig.accessId << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "ClientId: " << std::setw(32) << gatewayConfig.clientId << std::endl;
        std::cout << "  " << std::setw(16) << std::left << "DataDir: " << std::setw(32) << gatewayConfig.dataDir << std::endl;
        if (gatewayConfig.databaseActive) {
            std::cout << "  " << std::setw(16) << std::left << "Database: " << std::setw(32) << "true" << std::endl;
        } else {
            std::cout << "  " << std::setw(16) << std::left << "Database: " << std::setw(32) << "false" << std::endl;
        }
    }

    void AwsMockCtl::ExportInfrastructure(const std::vector<std::string> &services, bool pretty, bool includeObjects) {

        /*Dto::Common::Services exportServices;
        for (const auto &service: services) {
            exportServices.serviceNames.emplace_back(service);
        }

        // Create URL
        std::string url = "/export";
        url = Core::HttpUtils::AddQueryParameter(url, "pretty", pretty);
        url = Core::HttpUtils::AddQueryParameter(url, "includeObjects", includeObjects);

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "export");

        // Send request
        Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl + url, headers, exportServices.ToJson());

        if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            std::cerr << "Error: " << response.statusReason << std::endl;
            return;
        }
        std::cout << response.output;*/
    }

    void AwsMockCtl::ImportInfrastructure() {

        std::string line;
        std::stringstream jsonString;
        while (std::getline(std::cin, line)) {
            jsonString << line;
        }

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "import");
        Core::CurlResponse response = _curlUtils.SendHttpRequest("PUT", _baseUrl + "/all/import", headers, jsonString.str());

        if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            std::cerr << "Error: " << response.statusReason << std::endl;
            return;
        }
        std::cout << response.output;
    }

    void AwsMockCtl::CleanInfrastructure(const std::vector<std::string> &services) {

        /*Dto::Common::Services cleanServices;
        for (const auto &service: services) {
            cleanServices.serviceNames.emplace_back(service);
        }

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "clean");
        Core::CurlResponse response = _curlUtils.SendHttpRequest("GET", _baseUrl + "/clean-infrastructure", headers, cleanServices.ToJson());

        if (response.statusCode != Poco::Net::HTTPResponse::HTTP_OK) {
            std::cerr << "Error: " << response.statusReason << std::endl;
            return;
        }
        std::cout << response.output;*/
    }

    void AwsMockCtl::CleanObjects(Dto::Module::Module::ModuleList &modules) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "clean-objects");
        Core::HttpSocketResult response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Error: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        modules = Dto::Module::Module::FromJsonList(response.body);
        for (const auto &module: modules) {
            std::cout << "Objects of module " << module.name << " cleaned" << std::endl;
        }
    }

    void AwsMockCtl::AddStandardHeaders(std::map<std::string, std::string> &headers, const std::string &action) {
        headers["User"] = _user;
        headers["Region"] = _region;
        headers["Target"] = "module";
        headers["Action"] = action;
    }
}// namespace AwsMock::Controller