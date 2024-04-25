
#include <awsmock/service/secretsmanager/SecretsManagerHandler.h>

namespace AwsMock::Service {

    SecretsManagerHandler::SecretsManagerHandler(Core::Configuration &configuration) : SecretsManagerCmdHandler(configuration) {
    }

    void SecretsManagerHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "SecretsManager POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        Dto::Common::SecretsManagerClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::POST, request, region, user);

        SecretsManagerCmdHandler::handlePost(request, response, clientCommand);
    }
}// namespace AwsMock::Service
