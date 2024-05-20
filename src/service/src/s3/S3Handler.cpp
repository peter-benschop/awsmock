
#include <awsmock/service/s3/S3Handler.h>

namespace AwsMock::Service {

    void S3Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "S3 GET request, URI: " + request.getURI() << " region: " << region << " user: " + user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::GET, request, region, user);

        S3CmdHandler::handleGet(request, response, clientCommand);
    }

    void S3Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "S3 PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::PUT, request, region, user);

        S3CmdHandler::handlePut(request, response, clientCommand);
    }

    void S3Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "S3 POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::POST, request, region, user);

        S3CmdHandler::handlePost(request, response, clientCommand);
    }

    void S3Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_debug << "S3 DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::DELETE, request, region, user);

        S3CmdHandler::handleDelete(request, response, clientCommand);
    }

    void S3Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "S3 HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        Dto::Common::S3ClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::HEAD, request, region, user);

        S3CmdHandler::handleHead(request, response, clientCommand);
    }
}// namespace AwsMock::Service
