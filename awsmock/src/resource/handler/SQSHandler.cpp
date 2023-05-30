
#include "awsmock/resource/handler/SQSHandler.h"

namespace AwsMock {

    SQSHandler::SQSHandler(Core::Configuration &configuration, Core::MetricService &metricService)
        : AbstractResource(), _logger(Poco::Logger::get("SQSHandler")), _configuration(configuration), _metricService(metricService) {
    }

    void SQSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_GET_TIMER);
        poco_debug(_logger, "S3 GET request, address: " + request.clientAddress().toString());

        try {
            /*std::string lieferantenId = getPathParameter(2);
            std::string fileName = getPathParameter(3);
            poco_debug(_logger, "Handling image GET request, key: " + lieferantenId + " fileName: " + fileName);

            Database::ImageEntity entity = _database->findByLieferantenIdFileName(lieferantenId, fileName);

            std::string key = lieferantenId + "/" + fileName;
            long contentLength = _s3Adapter->GetContentLength(_bucket, key);

            response.setContentType(Poco::Net::MediaType("image", Poco::toLower(entity.getFormat())));
            response.setContentLength((std::streamsize) contentLength);

            handleHttpStatusCode(200, response);
            std::ostream &outputStream = response.send();

            Aws::IOStream &stream = _s3Adapter->GetObjectStream(_configuration.GetS3OutputBucket(), lieferantenId + "/" + fileName);
            outputStream << stream.rdbuf();
            outputStream.flush();*/

        } catch (AwsMock::HandlerException &exception) {
            poco_error(_logger, "Server error, exception: " + exception.message());
            handleHttpStatusCode(exception.code(), response);
            std::ostream &outputStream = response.send();
            outputStream << toJson(exception);
        } catch (Core::ResourceNotFoundException &exception) {
            poco_error(_logger, "Server error, exception: " + exception.displayText());
            handleHttpStatusCode(500, response);
            std::ostream &outputStream = response.send();
            outputStream << toJson(exception);
        }
    }

    void SQSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        poco_debug(_logger, "S3 PUT request, address: " + request.clientAddress().toString());

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

    void SQSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        poco_debug(_logger, "S3 POST request, address: " + request.clientAddress().toString());

        try {

            std::string jsonPayload;
            std::istream &inputStream = request.stream();
            Poco::StreamCopier::copyToString(inputStream, jsonPayload);

            auto attributesSectionObject = getJsonAttributesSectionObject(jsonPayload);

            std::list<std::string> attributesNames = {"starts_at", "ends_at", "details", "label", "text", "options"};
            assertPayloadAttributes(attributesSectionObject, attributesNames);

            //auto assembledQuestion = _entityAssembler.assembleEntity(attributesSectionObject);
            //std::string newQuestionIdentity = _imageApplicationService->newQuestion(assembledQuestion);

            //response.set("Location", getUrl("?question_id=" + newQuestionIdentity));
            //response.set("Content-Location", getUrl("?question_id=" + newQuestionIdentity));

            handleHttpStatusCode(201, response);
            std::ostream &outputStream = response.send();
            outputStream.flush();

        } catch (HandlerException &exception) {

            handleHttpStatusCode(exception.code(), response);
            std::ostream &outputStream = response.send();
            //outputStream << toJson(exception);
            outputStream.flush();
        }
    }

    void SQSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
        poco_debug(_logger, "SQS DELETE request, address: " + request.clientAddress().toString());

        try {
            std::string lieferantenId = getPathParameter(2);
            std::string fileName = getPathParameter(3);
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
        poco_debug(_logger, "S3 OPTIONS request, address: " + request.clientAddress().toString());

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(200, response);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }
}
