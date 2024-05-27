
#include "awsmock/core/exception/UnauthorizedException.h"
#include <awsmock/service/dynamodb/DynamoDbHandler.h>

namespace AwsMock::Service {

    DynamoDbHandler::DynamoDbHandler(Core::Configuration &configuration) : DynamoDbCmdHandler(configuration), _configuration(configuration), _dynamoDbService(configuration) {
        _secretAccessKey = _configuration.getString("awsmock.secret.access.key", "none");
    }

    void DynamoDbHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, [[maybe_unused]] const std::string &user) {
        log_trace << "DynamoDb GET request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        try {

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

        } catch (Core::ServiceException &exc) {
            SendXmlErrorResponse("dynamodb", response, exc);
        } catch (Core::NotFoundException &exc) {
            SendXmlErrorResponse("dynamodb", response, exc);
        }
    }

    void DynamoDbHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]] const std::string &region, [[maybe_unused]] const std::string &user) {
        log_trace << "DynamoDb PUT request, URI: " << request.getURI() << " region: " << region << " user: " + user;

        try {

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

        } catch (Poco::Exception &exc) {
            SendXmlErrorResponse("dynamodb", response, exc);
        }
    }

    void DynamoDbHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "DynamoDb POST request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        Dto::Common::DynamoDbClientCommand clientCommand;
        clientCommand.FromRequest(Dto::Common::HttpMethod::POST, request, region, user);

        DynamoDbCmdHandler::handlePost(request, response, clientCommand);
    }

    void DynamoDbHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "DynamoDb DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user;

        try {
            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);
            std::string body = Core::HttpUtils::GetBodyAsString(request);

        } catch (Core::ServiceException &exc) {
            SendXmlErrorResponse("dynamodb", response, exc);
        }
    }

    void DynamoDbHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        log_trace << "DynamoDb OPTIONS request";

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void DynamoDbHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        log_trace << "DynamoDb HEAD request, address: " << request.clientAddress().toString();

        try {

            std::string version, action;
            Core::HttpUtils::GetVersionAction(request.getURI(), version, action);

            HeaderMap headerMap;
            headerMap["Connection"] = "Keep-alive: 300";
            headerMap["Handler"] = "AmazonS3";

            SendOkResponse(response, {}, headerMap);

        } catch (Poco::Exception &exc) {
            SendXmlErrorResponse("dynamodb", response, exc);
        }
    }
}// namespace AwsMock::Service
