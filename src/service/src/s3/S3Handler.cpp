
#include <awsmock/service/S3Handler.h>

namespace AwsMock::Service {

  S3Handler::S3Handler(Core::Configuration &configuration, Core::MetricService &metricService) : S3CliHandler(configuration, metricService), S3CppHandler(configuration, metricService), S3Java2Handler(configuration, metricService),
                                                                                                 _logger(Poco::Logger::get("S3Handler")), _configuration(configuration), _metricService(metricService), _s3Service(configuration) {
  }

  void S3Handler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 GET request, URI: " + request.getURI() << " region: " << region << " user: " + user << std::endl;

      Dto::Common::UserAgent userAgent;
      userAgent.FromRequest(request, "s3");
      //DumpRequest(request);

      switch (userAgent.type) {
      case Dto::Common::UserAgentType::AWS_SDK_CPP:return S3CppHandler::handleGet(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_JAVA1:break;
      case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return S3Java2Handler::handleGet(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_CLI:return S3CppHandler::handleGet(request, response, region, user);
      case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:break;
      }
  }

  void S3Handler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 PUT request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    //DumpRequest(request);
    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "s3");

    switch (userAgent.type) {
    case Dto::Common::UserAgentType::AWS_SDK_CPP:return S3CppHandler::handlePut(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_SDK_JAVA1:break;
    case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return S3Java2Handler::handlePut(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_CLI:return S3CppHandler::handlePut(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:break;
    }
  }

  void S3Handler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 POST request, URI: " << request.getURI() << " region: " << region << " user: " << user << std::endl;

    //DumpRequest(request);
    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "s3");

    switch (userAgent.type) {
    case Dto::Common::UserAgentType::AWS_SDK_CPP:return S3CppHandler::handlePost(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_SDK_JAVA1:break;
    case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return S3Java2Handler::handlePost(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_CLI:return S3CppHandler::handlePost(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:break;
    }
  }

  void S3Handler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
    log_debug_stream(_logger) << "S3 DELETE request, URI: " + request.getURI() << " region: " << region << " user: " << user << std::endl;

    //DumpRequest(request);
    Dto::Common::UserAgent userAgent;
    userAgent.FromRequest(request, "s3");

    switch (userAgent.type) {
    case Dto::Common::UserAgentType::AWS_SDK_CPP:return S3CppHandler::handleDelete(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_SDK_JAVA1:break;
    case Dto::Common::UserAgentType::AWS_SDK_JAVA2: return S3Java2Handler::handleDelete(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_CLI:return S3CppHandler::handleDelete(request, response, region, user);
    case Dto::Common::UserAgentType::AWS_SDK_UNKNOWN:break;
    }
  }

  void S3Handler::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const std::string &region, const std::string &user) {
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

  void S3Handler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug_stream(_logger) << "S3 OPTIONS request" << std::endl;

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }
}
