
#include "awsmock/resource/handler/SQSHandler.h"

namespace AwsMock {

    SQSHandler::SQSHandler(Core::Configuration &configuration, Core::MetricService &metricService)
        : AbstractResource(), _logger(Poco::Logger::get("SQSHandler")), _configuration(configuration), _metricService(metricService), _sqsService(configuration) {
        Core::Logger::SetDefaultConsoleLogger("SQSHandler");
    }

    void SQSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_GET_TIMER);
        poco_debug(_logger, "SQS GET request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        DumpRequest(request);

        try {

        } catch (Core::ServiceException &exc) {
            SendErrorResponse(response, exc);
        } catch (Core::ResourceNotFoundException &exc) {
            SendErrorResponse(response, exc);
        }
    }

    void SQSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        poco_debug(_logger, "SQS PUT request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {
            std::string jsonPayload;
            std::istream &inputStream = request.stream();
            Poco::StreamCopier::copyToString(inputStream, jsonPayload);

            auto attributesSectionObject = getJsonAttributesSectionObject(jsonPayload);

            std::list<std::string> attributesNames = {"starts_at", "ends_at", "details", "label", "text"};
            assertPayloadAttributes(attributesSectionObject, attributesNames);

            //auto assembledQuestion = _entityAssembler.assembleEntity(attributesSectionObject);
            //_imageApplicationService->changeQuestion(assembledQuestion);

            handleHttpStatusCode(200, response);
            std::ostream &outputStream = response.send();
            outputStream.flush();

        } catch (HandlerException &exception) {

            handleHttpStatusCode(exception.code(), response);
            std::ostream &outputStream = response.send();
            //outputStream << toJson(exception);
            outputStream.flush();
        }
    }

    void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        poco_debug(_logger, "SQS POST request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {

            std::string endpoint = GetEndpoint(request);
            std::string payload = GetPayload(request);
            std::string action, version;

            GetActionVersion(payload, action, version);

            if (action == "CreateQueue") {

                std::string name, nameParameter = "QueueName";
                GetParameter(payload, nameParameter, name);
                Dto::SQS::CreateQueueRequest sqsRequest = {.name = name, .region=region, .owner=user, .url="http://" + endpoint + "/" + DEFAULT_USERID + "/" + name};

                Dto::SQS::CreateQueueResponse sqsResponse = _sqsService.CreateQueue(sqsRequest);
                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "ListQueues") {

                Dto::SQS::ListQueueResponse sqsResponse = _sqsService.ListQueues(region);
                SendOkResponse(response, sqsResponse.ToXml());

            } else if (action == "DeleteQueue") {

                std::string url, urlParameter = "QueueUrl";
                GetParameter(payload, urlParameter, url);
                url = Core::StringUtils::UrlDecode(url);

                Dto::SQS::DeleteQueueRequest sqsRequest = {.url=url};
                Dto::SQS::DeleteQueueResponse sqsResponse = _sqsService.DeleteQueue(sqsRequest);
                SendOkResponse(response, sqsResponse.ToXml());
            }

        } catch (Core::ServiceException &exc) {
            SendErrorResponse(response, exc);
        }
    }

    void SQSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
        poco_debug(_logger, "SQS DELETE request, URI: " + request.getURI() + " region: " + region + " user: " + user);

        try {
            std::string lieferantenId = GetPathParameter(2);
            std::string fileName = GetPathParameter(3);
            poco_debug(_logger, "Handling image DELETE request, lieferantenId: " + lieferantenId + " fileName: " + fileName);

            /*Database::ImageEntity entity = _database->findByLieferantenIdFileName(lieferantenId, fileName);

            _database->deleteEntity(entity);*/

            handleHttpStatusCode(204, response);
            std::ostream &outputStream = response.send();
            outputStream.flush();

        } catch (HandlerException &exception) {
            handleHttpStatusCode(exception.code(), response);
            std::ostream &outputStream = response.send();
            //outputStream << toJson(exception);
            outputStream.flush();
        }
    }

    void SQSHandler::handleOptions(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        poco_debug(_logger, "SQS OPTIONS request, address: " + request.clientAddress().toString());

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(200, response);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void SQSHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        poco_debug(_logger, "SQS HEAD request, address: " + request.clientAddress().toString());

        handleHttpStatusCode(200, response);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void SQSHandler::GetActionVersion(const std::string &body, std::string &action, std::string &version) {
        std::vector<std::string> bodyParts = Core::StringUtils::Split(body, '&');
        for (auto &it : bodyParts) {
            std::vector<std::string> parts = Core::StringUtils::Split(it, '=');
            if (parts.size() < 2) {
                throw Core::ServiceException("Invalid request body", 400);
            }
            if (parts[0] == "Action") {
                action = parts[1];
            }
            if (parts[0] == "Version") {
                version = parts[1];
            }
        }
    }

    void SQSHandler::GetParameter(const std::string &body, std::string &name, std::string &value) {
        std::vector<std::string> bodyParts = Core::StringUtils::Split(body, '&');
        for (auto &it : bodyParts) {
            std::vector<std::string> parts = Core::StringUtils::Split(it, '=');
            if (parts[0] == name) {
                value = parts[1];
            }
        }
    }

    std::string SQSHandler::GetEndpoint(Poco::Net::HTTPServerRequest &request) {
        return request.get("Host");
    }
}
