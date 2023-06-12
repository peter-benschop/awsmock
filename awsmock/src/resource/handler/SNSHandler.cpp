
#include "awsmock/resource/handler/SNSHandler.h"

namespace AwsMock {

    SNSHandler::SNSHandler(Core::Configuration &configuration, Core::MetricService &metricService)
        : AbstractResource(), _logger(Poco::Logger::get("SNSHandler")), _configuration(configuration), _metricService(metricService), _snsService(configuration) {
    }

    void SNSHandler::handleGet(Poco::Net::HTTPServerRequest &request,
                               Poco::Net::HTTPServerResponse &response,
                               [[maybe_unused]]const std::string &region,
                               [[maybe_unused]]const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_GET_TIMER);
        _logger.debug() << "SNS GET request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        _logger.debug() << "SNS GET request, URI: " << response.getContentLength();
        DumpRequest(request);
    }

    void SNSHandler::handlePut(Poco::Net::HTTPServerRequest &request,
                               Poco::Net::HTTPServerResponse &response,
                               [[maybe_unused]]const std::string &region,
                               [[maybe_unused]]const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        _logger.debug() << "SNS PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        _logger.debug() << "SNS PUT request, URI: " << response.getContentLength();
        DumpRequest(request);
    }

    void SNSHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        _logger.trace() << "SNS POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << " length: " << response.getContentLength();

        //DumpRequest(request);
        //DumpBody(request);

        try {
            std::string endpoint = GetEndpoint(request);
            std::string payload = GetPayload(request);
            std::string action, version;

            GetActionVersion(payload, action, version);

            if (action == "CreateTopic") {

                std::string name = GetStringParameter(payload, "Name");
                _logger.debug() << "Topic name: " << name;

                Dto::SNS::CreateTopicRequest snsRequest = {.region=region, .topicName = name, .owner=user};
                Dto::SNS::CreateTopicResponse snsResponse = _snsService.CreateTopic(snsRequest);
                SendOkResponse(response, snsResponse.ToXml());

            }
        } catch (Core::ServiceException &exc) {
            _logger.error() << "Service exception: " << exc.message();
            SendErrorResponse("SQS", response, exc);
        }
    }

    void SNSHandler::handleDelete(Poco::Net::HTTPServerRequest &request,
                                  Poco::Net::HTTPServerResponse &response,
                                  [[maybe_unused]]const std::string &region,
                                  [[maybe_unused]]const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
        _logger.debug() << "SNS DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user;
        _logger.debug() << "SNS DELETE request, URI: " << response.getContentLength();
        DumpRequest(request);
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

    void SNSHandler::GetActionVersion(const std::string &body, std::string &action, std::string &version) {
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

    std::string SNSHandler::GetStringParameter(const std::string &body, const std::string &name) {
        std::string value;
        std::vector<std::string> bodyParts = Core::StringUtils::Split(body, '&');
        for (auto &it : bodyParts) {
            std::vector<std::string> parts = Core::StringUtils::Split(it, '=');
            if (parts[0] == name) {
                value = Core::StringUtils::UrlDecode(parts[1]);
            }
        }
        _logger.debug() << "Found string parameter, name: " << name << "value: " << value;
        return value;
    }

    std::string SNSHandler::GetEndpoint(Poco::Net::HTTPServerRequest &request) {
        return request.get("Host");
    }
}
