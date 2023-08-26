
#include "awsmock/service/TransferHandler.h"

namespace AwsMock::Service {

    TransferHandler::TransferHandler(Core::Configuration &configuration, Core::MetricService &metricService)
        : AbstractHandler(), _logger("LambdaServiceHandler"), _configuration(configuration), _metricService(metricService), _transferService(configuration) {
    }

    void TransferHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, [[maybe_unused]]const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_GET_TIMER);
        log_trace_stream(_logger) << "Lambda GET request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

        try {

            // TODO: Remove or fix
/*            std::string version, action;
            GetVersionActionFromUri(request.getURI(), version, action);

            if(action == "functions/") {

                Dto::Lambda::ListFunctionResponse lambdaResponse = _lambdaService.ListFunctionConfiguration(region);
                SendOkResponse(response, lambdaResponse.ToJson());
            }*/

        } catch (Core::ServiceException &exc) {
            SendErrorResponse("S3", response, exc);
        } catch (Core::ResourceNotFoundException &exc) {
            SendErrorResponse("Lambda", response, exc);
        }
    }

    void TransferHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_PUT_TIMER);
        log_trace_stream(_logger) << "Lambda PUT request, URI: " << request.getURI() << " region: " << region << " user: " + user << std::endl;

        try {
            std::string version, action;
            GetVersionActionFromUri(request.getURI(), version, action);

        } catch (Poco::Exception &exc) {
            SendErrorResponse("Lambda", response, exc);
        }
    }

    void TransferHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_POST_TIMER);
        log_trace_stream(_logger) << "Lambda POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

        try {
            std::string body = GetBodyAsString(request);

            Dto::Transfer::CreateTransferRequest transferRequest = {.region=region};
            Dto::Transfer::CreateTransferResponse transferResponse = _transferService.CreateTransferServer(transferRequest);
            SendOkResponse(response, transferResponse.ToJson());

        } catch (Poco::Exception &exc) {
            SendErrorResponse("Lambda", response, exc);
        }
    }

    void TransferHandler::handleDelete(Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response,
                                     [[maybe_unused]]const std::string &region,
                                     [[maybe_unused]]const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_DELETE_TIMER);
        log_trace_stream(_logger) << "Lambda DELETE request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

        try {
            std::string version, action;
            GetVersionActionFromUri(request.getURI(), version, action);

        } catch (Core::ServiceException &exc) {
            SendErrorResponse("Lambda", response, exc);
        }
    }

    void TransferHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
        Core::MetricServiceTimer measure(_metricService, HTTP_OPTIONS_TIMER);
        log_trace_stream(_logger) << "Lambda OPTIONS request" << std::endl;

        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void TransferHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response,
                                   [[maybe_unused]]const std::string &region,
                                   [[maybe_unused]]const std::string &user) {
        Core::MetricServiceTimer measure(_metricService, HTTP_HEAD_TIMER);
        log_trace_stream(_logger) << "Lambda HEAD request, address: " << request.clientAddress().toString() << std::endl;

        try {

            std::string version, action;
            GetVersionActionFromUri(request.getURI(), version, action);

            HeaderMap headerMap;
            headerMap.emplace_back("Connection", "closed");
            headerMap.emplace_back("Server", "AmazonS3");

            SendOkResponse(response, {}, &headerMap);

        } catch (Poco::Exception &exc) {
            SendErrorResponse("Lambda", response, exc);
        }
    }
}
