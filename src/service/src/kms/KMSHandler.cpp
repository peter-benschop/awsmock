
#include <awsmock/service/kms/KMSHandler.h>

namespace AwsMock::Service {

    void KMSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "KMS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << " length: " << response.getContentLength();

        Dto::Common::KMSClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::GET, request, region, user);

        KMSCmdHandler::handlePost(request, response, clientCommand);
    }
}// namespace AwsMock::Service
