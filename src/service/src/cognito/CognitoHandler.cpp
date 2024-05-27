
#include <awsmock/service/cognito/CognitoHandler.h>

namespace AwsMock::Service {

    void CognitoHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "Cognito GET request, URI: " + request.getURI() << " region: " << region << " user: " + user;
    }

    void CognitoHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;
    }

    void CognitoHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "Cognito POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;


        Dto::Common::CognitoClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::GET, request, region, user);

        CognitoCmdHandler::handlePost(request, response, clientCommand);
    }

    void CognitoHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "Cognito DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user;
    }

    void CognitoHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "Cognito HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user;
    }

    void CognitoHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        log_debug << "Cognito OPTIONS request";

        response.set("Allow", "GET, PUT, POST, DELETE, HEAD, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }
}// namespace AwsMock::Service
