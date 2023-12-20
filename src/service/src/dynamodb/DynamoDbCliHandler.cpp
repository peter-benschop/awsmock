
#include <awsmock/service/DynamoDbCliHandler.h>

namespace AwsMock::Service {

  DynamoDbCliHandler::DynamoDbCliHandler(Core::Configuration &configuration, Core::MetricService &metricService) : AbstractHandler(), _logger(Poco::Logger::get("S3Handler")), _configuration(configuration), _metricService(metricService), _s3Service(configuration) {
  }

  void DynamoDbCliHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");
      //DumpRequest(request);

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCliHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");


    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCliHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");


    } catch (Poco::Exception &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCliHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      // Get user agent
      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");

    } catch (Core::ServiceException &exc) {
      SendXmlErrorResponse("S3", response, exc);
    }
  }

  void DynamoDbCliHandler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_trace_stream(_logger) << "S3 HEAD request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    try {

      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_debug_stream(_logger) << "S3 HEAD request, bucket: " << bucket << " key: " << key << std::endl;

      Dto::S3::GetMetadataRequest s3Request = {.region=region, .bucket=bucket, .key=key};
      Dto::S3::GetMetadataResponse s3Response = _s3Service.GetMetadata(s3Request);

      HeaderMap headerMap;
      headerMap["Server"] = "awsmock";
      headerMap["Content-Type"] = "application/json";
      headerMap["Last-Modified"] = Poco::DateTimeFormatter().format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);
      headerMap["Content-Length"] = std::to_string(s3Response.size);
      headerMap["ETag"] = "\"" + s3Response.md5Sum + "\"";
      headerMap["accept-ranges"] = "bytes";
      headerMap["x-amz-id-2"] = Core::StringUtils::GenerateRandomString(30);
      headerMap["x-amz-request-id"] = Poco::UUIDGenerator().createRandom().toString();
      headerMap["x-amz-version-id"] = Core::StringUtils::GenerateRandomString(30);

      // User supplied metadata
      for (const auto &m : s3Response.metadata) {
        headerMap["x-amz-meta-" + m.first] = m.second;
      }
      SendHeadResponse(response, headerMap);

    } catch (Poco::Exception &exc) {
      log_warning_stream(_logger) << exc.message() << std::endl;
      SendXmlErrorResponse("S3", response, exc);
    } catch (std::exception &exc) {
      log_error_stream(_logger) << exc.what() << std::endl;
    }
  }

  void DynamoDbCliHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "S3 OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
