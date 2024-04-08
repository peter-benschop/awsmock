
#include <awsmock/service/secretsmanager/SecretsManagerHandler.h>

namespace AwsMock::Service {

  SecretsManagerHandler::SecretsManagerHandler(Core::Configuration &configuration, Core::MetricService &metricService, Poco::Condition &condition) : SecretsManagerCmdHandler(configuration, metricService, condition), _logger(Poco::Logger::get("SecretsManagerHandler")) {
  }

  void SecretsManagerHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "SecretsManager POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    Dto::Common::SecretsManagerClientCommand clientCommand;
    clientCommand.FromRequest(Dto::Common::HttpMethod::POST, request, region, user);

    SecretsManagerCmdHandler::handlePost(request, response, clientCommand);
  }
}
