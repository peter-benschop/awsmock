
#include <awsmock/service/DynamoDbCppHandler.h>

namespace AwsMock::Service {

  DynamoDbCppHandler::DynamoDbCppHandler(Core::Configuration &configuration, Core::MetricService &metricService)
    : AbstractHandler(), _logger(Poco::Logger::get("S3Handler")), _configuration(configuration), _metricService(metricService), _dynamoDbService(configuration, metricService) {
  }

  void DynamoDbCppHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    try {

      // Strange behaviour of the S3CRT client
      std::string uri = request.getURI();
      std::string bucket = Core::HttpUtils::GetPathParameter(uri, 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(uri, 1);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("S3", response, exc);
    } catch (Core::ResourceNotFoundException &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCppHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_debug_stream(_logger) << "Found bucket/key, bucket: " << bucket << " key: " << key << std::endl;

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCppHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      //DumpRequest(request);
      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCppHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {
      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCppHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "S3 HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_debug_stream(_logger) << "S3 HEAD request, bucket: " << bucket << " key: " << key << std::endl;

    } catch (Poco::Exception &exc) {
      log_warning_stream(_logger) << exc.message() << std::endl;
      SendXmlErrorResponse("S3", response, exc);
    } catch (std::exception &exc) {
      log_error_stream(_logger) << exc.what() << std::endl;
    }
  }

  void DynamoDbCppHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "S3 OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
