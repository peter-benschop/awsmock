
#include <awsmock/resource/handler/ModuleHandler.h>

namespace AwsMock::Manager {

    ModuleHandler::ModuleHandler(Service::ServerMap &serverMap) : AbstractResource(), _serverMap(serverMap) {

        _moduleService = std::make_shared<Service::ModuleService>(_serverMap);
    }

    void ModuleHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {

        Core::MetricService &_metricService = Core::MetricService::instance();
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricServiceTimer measure(MODULE_GET_TIMER);
        _metricService.IncrementCounter(MODULE_COUNTER, "method", "GET");
        log_debug << "Module GET request, URI: " + request.getURI() << " region: " << region << " user: " + user;

        std::string action = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
        std::string payload = Core::HttpUtils::GetBodyAsString(request);
        log_debug << "Action: " + action;

        if (action == "config") {

            std::string host = _configuration.getString("awsmock.service.gateway.http.host", "localhost");
            int port = _configuration.getInt("awsmock.service.gateway.http.port", 4566);
            std::string endpoint = "http://" + host + ":" + std::to_string(port);
            Dto::Module::GatewayConfig config = {
                    .region = _configuration.getString("awsmock.region", "eu-central-1"),
                    .endpoint = endpoint,
                    .host = host,
                    .port = port,
                    .user = _configuration.getString("awsmock.user", "none"),
                    .accessId = _configuration.getString("awsmock.account.userPoolId", "000000000000"),
                    .clientId = _configuration.getString("awsmock.client.userPoolId", "00000000"),
                    .dataDir = _configuration.getString("awsmock.data.dir", "/tmp/awsmock/data"),
                    .version = Core::Configuration::GetVersion(),
                    .databaseActive = _configuration.getBool("awsmock.mongodb.active", false)};
            SendOkResponse(response, config.ToJson());

        } else if (action == "running") {

            std::string module = Core::HttpUtils::GetPathParameter(request.getURI(), 1);
            bool result = _moduleService->IsRunning(module);

            SendOkResponse(response, result ? "true" : "false");

        } else if (action == "export") {

            bool prettyPrint = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "pretty") == "true";
            bool includeObjects = Core::HttpUtils::GetQueryParameterValueByName(request.getURI(), "includeObjects") == "true";

            Dto::Common::Services services;
            services.FromJson(payload);
            std::string infrastructure = _moduleService->ExportInfrastructure(services, prettyPrint, includeObjects);
            SendOkResponse(response, infrastructure);

        } else if (action == "clean-infrastructure") {

            Dto::Common::Services services;
            services.FromJson(payload);
            _moduleService->CleanInfrastructure(services);
            SendOkResponse(response);

        } else if (action == "clean-objects") {

            Dto::Common::Services services;
            services.FromJson(payload);
            _moduleService->CleanObjects(services);
            SendOkResponse(response);

        } else {

            Database::Entity::Module::ModuleList modules = _moduleService->ListModules();
            std::string body = Dto::Module::Module::ToJson(modules);
            SendOkResponse(response, body);
        }
    }

    void ModuleHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {

        Core::MetricService &_metricService = Core::MetricService::instance();
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricServiceTimer measure(MODULE_PUT_TIMER);
        _metricService.IncrementCounter(MODULE_COUNTER, "method", "PUT");
        log_debug << "Module PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        try {
            std::string name = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
            std::string action = Core::HttpUtils::GetPathParameter(request.getURI(), 1);
            log_info << "Module: " << name << " action: " << action;

            if (action == "start") {

                if (name.empty() || name == "all") {

                    _moduleService->StartAllServices();

                    // Send response
                    SendOkResponse(response, {});

                } else {

                    Database::Entity::Module::Module module = _moduleService->StartService(name);

                    // Send response
                    SendOkResponse(response, module.ToJson());
                }

            } else if (action == "restart") {

                if (name.empty() || name == "all") {

                    _moduleService->RestartAllServices();

                    // Send response
                    SendOkResponse(response, {});

                } else {

                    // Stop single module
                    Database::Entity::Module::Module module = _moduleService->RestartService(name);

                    // Send response
                    SendOkResponse(response, module.ToJson());
                }

            } else if (action == "stop") {

                if (name.empty() || name == "all") {

                    _moduleService->StopAllServices();

                    // Send response
                    SendOkResponse(response, {});

                } else {

                    // Stop single module
                    Database::Entity::Module::Module module = _moduleService->StopService(name);

                    // Send response
                    SendOkResponse(response, module.ToJson());
                }

            } else if (action == "import") {

                std::string payload = Core::HttpUtils::GetBodyAsString(request);

                _moduleService->ImportInfrastructure(payload);
                SendOkResponse(response);

            } else if (action == "loglevel") {

                std::string level = Core::HttpUtils::GetPathParameter(request.getURI(), 2);
                plog::get()->setMaxSeverity(plog::severityFromString(level.c_str()));
                log_info << "Logevel set to '" << level << "'";

                // Send response
                SendOkResponse(response, {});
            }

        } catch (Core::ServiceException &exc) {
            SendErrorResponse("Module", response, exc);
        }
    }

    void ModuleHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
        Core::MetricService &_metricService = Core::MetricService::instance();
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricServiceTimer measure(MODULE_POST_TIMER);
        _metricService.IncrementCounter(MODULE_COUNTER, "method", "POST");
        log_debug << "Module POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        SendOkResponse(response);
    }

    void ModuleHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
        Core::MetricService &_metricService = Core::MetricService::instance();
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricServiceTimer measure(MODULE_DELETE_TIMER);
        _metricService.IncrementCounter(MODULE_COUNTER, "method", "DELETE");
        log_debug << "Module DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user;
        SendOkResponse(response);
    }

    void ModuleHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
        Core::MetricService &_metricService = Core::MetricService::instance();
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricServiceTimer measure(MODULE_HEAD_TIMER);
        _metricService.IncrementCounter(MODULE_COUNTER, "method", "HEAD");
        log_debug << "Module HEAD request, address: " << request.clientAddress().toString();
        SendOkResponse(response);
    }

    void ModuleHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        Core::MetricService &_metricService = Core::MetricService::instance();
        Core::Configuration &_configuration = Core::Configuration::instance();
        Core::MetricServiceTimer measure(MODULE_OPTIONS_TIMER);
        _metricService.IncrementCounter(MODULE_COUNTER, "method", "OPTIONS");
        log_debug << "Module OPTIONS request";

        response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }
}// namespace AwsMock::Manager
