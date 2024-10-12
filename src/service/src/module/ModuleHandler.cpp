//
// Created by vogje01 on 5/27/24.
//

#include <awsmock/service/module/ModuleHandler.h>

namespace AwsMock::Service {

    boost::beast::http::response<boost::beast::http::dynamic_body> ModuleHandler::HandleGetRequest(const boost::beast::http::request<boost::beast::http::dynamic_body> &request, const std::string &region, const std::string &user) {

        Core::Configuration &configuration = Core::Configuration::instance();
        Monitoring::MetricServiceTimer measure(MODULE_HTTP_TIMER, "method", "GET");
        Monitoring::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "GET");

        std::string target = request.base()["x-awsmock-target"];
        std::string action = request.base()["x-awsmock-action"];
        std::string payload = Core::HttpUtils::GetBodyAsString(request);
        log_debug << "Found action and target, target: " << target << " action: " << action;

        try {
            if (action == "get-config") {

                std::string host = configuration.getString("awsmock.service.gateway.http.host", "localhost");
                std::string address = configuration.getString("awsmock.service.gateway.http.address", "0.0.0.0");
                int port = configuration.getInt("awsmock.service.gateway.http.port", 4566);
                std::string endpoint = "http://" + host + ":" + std::to_string(port);
                Dto::Module::GatewayConfig config = {
                        .region = configuration.getString("awsmock.region", "eu-central-1"),
                        .endpoint = endpoint,
                        .host = host,
                        .address = address,
                        .port = port,
                        .pid = getppid(),
                        .user = configuration.getString("awsmock.user", "none"),
                        .accessId = configuration.getString("awsmock.account.id", "000000000000"),
                        .clientId = configuration.getString("awsmock.client.id", "00000000"),
                        .dataDir = configuration.getString("awsmock.data.dir", "/tmp/awsmock/data"),
                        .version = Core::Configuration::GetVersion(),
                        .databaseActive = configuration.getBool("awsmock.mongodb.active", false)};
                return SendOkResponse(request, config.ToJson());

            } else if (action == "list-modules") {

                Database::Entity::Module::ModuleList modules = _moduleService.ListModules();
                std::string body = Dto::Module::Module::ToJson(modules);
                return SendOkResponse(request, body);

            } else if (action == "show-ftp-users") {

                Dto::Transfer::Server server;
                server.FromJson(payload);

                Dto::Transfer::ListUsersRequest transferRequest = {.region = region, .serverId = server.serverId};
                Service::TransferService transferService;
                Dto::Transfer::ListUsersResponse transferResponse = transferService.ListUsers(transferRequest);
                return SendOkResponse(request, transferResponse.ToJson());

            } else {

                return SendBadRequestError(request, "Unknown action");
            }

        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        }
    }

    boost::beast::http::response<boost::beast::http::dynamic_body> ModuleHandler::HandlePostRequest(const boost::beast::http::request<boost::beast::http::dynamic_body> &request, const std::string &region, const std::string &user) {
        Monitoring::MetricServiceTimer measure(MODULE_HTTP_TIMER, "method", "POST");
        Monitoring::MetricService::instance().IncrementCounter(MODULE_HTTP_COUNTER, "method", "POST");

        try {

            std::string target = request.base()["x-awsmock-target"];
            std::string action = request.base()["x-awsmock-action"];
            std::string payload = Core::HttpUtils::GetBodyAsString(request);
            log_debug << "Found action and target, target: " << target << " action: " << action;

            if (action == "start-modules") {

                Dto::Module::Module::ModuleList modules = Dto::Module::Module::FromJsonList(payload);
                modules = _moduleService.StartModules(modules);
                return SendOkResponse(request, Dto::Module::Module::ToJson(modules));

            } else if (action == "restart-modules") {

                Dto::Module::Module::ModuleList modules = Dto::Module::Module::FromJsonList(payload);
                modules = _moduleService.StopModules(modules);
                modules = _moduleService.StartModules(modules);
                return SendOkResponse(request, Dto::Module::Module::ToJson(modules));

            } else if (action == "stop-modules") {

                Dto::Module::Module::ModuleList modules = Dto::Module::Module::FromJsonList(payload);
                modules = _moduleService.StopModules(modules);
                return SendOkResponse(request, Dto::Module::Module::ToJson(modules));

            } else if (action == "import") {

                AwsMock::Service::ModuleService::ImportInfrastructure(payload);
                return SendOkResponse(request);

            } else if (action == "set-log-level") {

                plog::get()->setMaxSeverity(plog::severityFromString(payload.c_str()));
                log_info << "Log level set to '" << payload << "'";

                // Send response
                return SendOkResponse(request);

            } else if (action == "clean-objects") {

                // Get request body
                Dto::Module::CleanInfrastructureRequest moduleRequest;
                moduleRequest.FromJson(payload);

                // Get modules
                if (moduleRequest.onlyObjects) {
                    AwsMock::Service::ModuleService::CleanObjects(moduleRequest);
                } else {
                    AwsMock::Service::ModuleService::CleanInfrastructure(moduleRequest);
                }
                return SendOkResponse(request);

            } else if (action == "export") {

                // Get request body
                Dto::Module::ExportInfrastructureRequest moduleRequest;
                moduleRequest.FromJson(payload);

                // Get modules
                Dto::Module::ExportInfrastructureResponse moduleResponse = _moduleService.ExportInfrastructure(moduleRequest);
                if (moduleResponse.ToJson().length() > 10000000) {
                    log_error << "Response > 10MB";
                    return SendBadRequestError(request, "Size > 10 MB.");
                }
                return SendOkResponse(request, moduleResponse.ToJson());

            } else {
                return SendBadRequestError(request, "Unknown action");
            }
        } catch (Core::ServiceException &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        }
    }

}// namespace AwsMock::Service