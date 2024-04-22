
#include "awsmock/service/sns/SNSHandler.h"

namespace AwsMock::Service {

    void SNSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "SNS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << " length: " << response.getContentLength();

        Dto::Common::SNSClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::GET, request, region, user);

        SNSCmdHandler::handlePost(request, response, clientCommand);
    }
}
