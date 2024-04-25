
#include <awsmock/service/sqs/SQSHandler.h>

namespace AwsMock::Service {

    void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "SQS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        Dto::Common::SQSClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::POST, request, region, user);

        SQSCmdHandler::handlePost(request, response, clientCommand);
    }
}// namespace AwsMock::Service
