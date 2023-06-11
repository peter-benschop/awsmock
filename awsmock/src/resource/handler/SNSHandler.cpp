
#include "awsmock/resource/handler/SNSHandler.h"

namespace AwsMock {

    SNSHandler::SNSHandler(Core::Configuration &configuration, Core::MetricService &metricService)
        :  AbstractResource(), _logger(Poco::Logger::get("SNSHandler")), _configuration(configuration), _metricService(metricService) {
    }

    void SNSHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_GET_TIMER);
        _logger.debug() << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        _logger.debug() << "SNS GET request, URI: " << response.getContentLength();

    }

    void SNSHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        _logger.debug() << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        _logger.debug() << "SNS GET request, URI: " << response.getContentLength();
    }

    void SNSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        _logger.debug() << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        _logger.debug() << "SNS GET request, URI: " << response.getContentLength();
    }

    void SNSHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
        _logger.debug() << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        _logger.debug() << "SNS GET request, URI: " << response.getContentLength();
    }

    void SNSHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        _logger.debug() << "S3 OPTIONS request";

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }
}
