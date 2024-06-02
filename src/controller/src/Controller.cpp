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

    void AwsMockCtl::Initialize(boost::program_options::variables_map vm, const std::vector<std::string> &commands) {
        _commands = commands;
        _vm = vm;
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

        }
#ifdef HAS_SYSTEMD
        else if (std::find(_commands.begin(), _commands.end(), "logs") != _commands.end()) {

            ShowServiceLogs();
        }
#endif
        else if (std::find(_commands.begin(), _commands.end(), "start") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "start" && command != "all") {
                    Dto::Module::Module module;
                    module.name = command;
                    module.status = Database::Entity::Module::ModuleState::RUNNING;
                    modules.emplace_back(module);
                }
            }

            if (modules.empty()) {
                modules = GetAllModules();
            }

            StartService(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "restart") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "restart" && command != "all") {
                    Dto::Module::Module module;
                    module.name = command;
                    modules.emplace_back(module);
                }
            }

            if (modules.empty()) {
                modules = GetAllModules();
            }

            StartService(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "stop") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "stop" && command != "all") {
                    Dto::Module::Module module;
                    module.name = command;
                    module.status = Database::Entity::Module::ModuleState::STOPPED;
                    modules.emplace_back(module);
                }
            }

            if (modules.empty()) {
                modules = GetAllModules();
            }

            StopService(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "import") != _commands.end()) {

            ImportInfrastructure();

        } else if (std::find(_commands.begin(), _commands.end(), "export") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "export" && command != "all") {
                    Dto::Module::Module module;
                    module.name = command;
                    module.status = Database::Entity::Module::ModuleState::STOPPED;
                    modules.emplace_back(module);
                }
            }

            if (modules.empty()) {
                modules = GetAllModules();
            }

            bool pretty = _vm.count("pretty") > 0;
            bool includeObjects = _vm.count("include-objects") > 0;

            ExportInfrastructure(modules, pretty, includeObjects);

        } else if (std::find(_commands.begin(), _commands.end(), "clean") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "clean") {
                    Dto::Module::Module module;
                    module.name = command;
                    modules.emplace_back(module);
                }
            }

            if (modules.empty()) {
                modules = GetAllModules();
            }

            CleanInfrastructure(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "clean-objects") != _commands.end()) {

            std::vector<Dto::Module::Module> modules;
            for (const auto &command: _commands) {
                if (command != "clean-objects") {
                    Dto::Module::Module module;
                    module.name = command;
                    modules.emplace_back(module);
                }
            }
            CleanObjects(modules);

        } else if (std::find(_commands.begin(), _commands.end(), "show-ftp-users") != _commands.end()) {

            std::string serverId = _vm["serverId"].as<std::string>();
            ShowFtpUsers(serverId);
        }
    }

    void AwsMockCtl::ListServices() {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "list-modules");
        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::get, _host, _port, "/", {}, headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not get module list: " << response.statusCode << " body: " << response.body << std::endl;
            return;
        }

        std::vector<Dto::Module::Module> modules = Dto::Module::Module::FromJsonList(response.body);
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
        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
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
        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
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

        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
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
    void AwsMockCtl::ShowServiceLogs() {
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
        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", level, headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not set log level, httpStatus: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }
        std::cout << "Log level set to " << level << std::endl;
    }

    void AwsMockCtl::GetConfig() {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "get-config");
        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::get, _host, _port, "/", {}, headers);
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

    void AwsMockCtl::ExportInfrastructure(Dto::Module::Module::ModuleList &modules, bool pretty, bool includeObjects) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "export");

        // Options headers
        headers["pretty"] = pretty ? "1" : "0";
        headers["includeObjects"] = includeObjects ? "1" : "0";

        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::get, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not export objects, httpStatus: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        std::cout << response.body;
    }

    void AwsMockCtl::ImportInfrastructure() {

        std::string line;
        std::stringstream jsonString;
        while (std::getline(std::cin, line)) {
            jsonString << line;
        }

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "import");

        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::get, _host, _port, "/", jsonString.str(), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not import objects, httpStatus: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }
    }

    void AwsMockCtl::CleanInfrastructure(Dto::Module::Module::ModuleList &modules) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "import");

        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::get, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not clean infrastructure, httpStatus: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }
        std::cout << response.body;
    }

    void AwsMockCtl::CleanObjects(Dto::Module::Module::ModuleList &modules) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "clean-objects");

        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", Dto::Module::Module::ToJson(modules), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Error: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        modules = Dto::Module::Module::FromJsonList(response.body);
        for (const auto &module: modules) {
            std::cout << "Objects of module " << module.name << " cleaned" << std::endl;
        }
    }

    void AwsMockCtl::ShowFtpUsers(const std::string &serverId) {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "show-ftp-users");

        Dto::Transfer::Server server = {.serverId = serverId};

        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::put, _host, _port, "/", server.ToJson(), headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Error: " << response.statusCode << " body:" << response.body << std::endl;
            return;
        }

        std::vector<Dto::Transfer::User> users = Dto::Transfer::User::FromJsonList(response.body);
        for (const auto &user: users) {
            std::cout << "FTP user: " << user.userName << " password: " << user.password << std::endl;
        }
    }

    void AwsMockCtl::AddStandardHeaders(std::map<std::string, std::string> &headers, const std::string &action) {
        headers["User"] = _user;
        headers["Region"] = _region;
        headers["Target"] = "module";
        headers["Action"] = action;
    }

    Dto::Module::Module::ModuleList AwsMockCtl::GetAllModules() {

        std::map<std::string, std::string> headers;
        AddStandardHeaders(headers, "list-modules");
        Core::HttpSocketResponse response = AwsMock::Core::HttpSocket::SendJson(boost::beast::http::verb::get, _host, _port, "/", {}, headers);
        if (response.statusCode != boost::beast::http::status::ok) {
            std::cerr << "Could not get modules list, httpStatus: " << response.statusCode << " body:" << response.body << std::endl;
            return {};
        }

        return Dto::Module::Module::FromJsonList(response.body);
    }

}// namespace AwsMock::Controller