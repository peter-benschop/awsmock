
#include <awsmock/service/s3/S3Handler.h>

namespace AwsMock::Service {

  S3Handler::S3Handler(Core::Configuration &configuration, Core::MetricService &metricService) : S3CmdHandler(configuration, metricService), _configuration(configuration), _metricService(metricService), _s3Service(configuration) {
  }

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

    try {

      std::string tmp = request.getURI();
      std::string bucket = Core::HttpUtils::GetPathParameter(request.getURI(), 0);
      std::string key = Core::HttpUtils::GetPathParametersFromIndex(request.getURI(), 1);
      log_debug << "S3 HEAD request, bucket: " << bucket << " key: " << key;

      Dto::S3::GetMetadataRequest s3Request = {.region=region, .bucket=bucket, .key=key};
      Dto::S3::GetMetadataResponse s3Response = _s3Service.GetMetadata(s3Request);

      HeaderMap headerMap;
      headerMap["Server"] = "awsmock";
      headerMap["Content-Type"] = "application/octet-stream";
      headerMap["Last-Modified"] = Poco::DateTimeFormatter().format(s3Response.modified, Poco::DateTimeFormat::HTTP_FORMAT);
      headerMap["Content-Length"] = std::to_string(s3Response.size);
      headerMap["ETag"] = "\"" + s3Response.md5Sum + "\"";
      headerMap["accept-ranges"] = "bytes";
      headerMap["x-amz-userPoolId-2"] = Core::StringUtils::GenerateRandomString(30);
      headerMap["x-amz-request-userPoolId"] = Poco::UUIDGenerator().createRandom().toString();
      headerMap["x-amz-version-userPoolId"] = Core::StringUtils::GenerateRandomString(30);

      // User supplied metadata
      for (const auto &m : s3Response.metadata) {
        headerMap["x-amz-meta-" + m.first] = m.second;
      }
      SendHeadResponse(response, headerMap);

    } catch (Poco::Exception &exc) {
      log_warning << exc.message();
      SendXmlErrorResponse("S3", response, exc);
    } catch (std::exception &exc) {
      log_error << exc.what();
    }
  }
}
