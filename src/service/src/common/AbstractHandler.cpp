
#include "awsmock/service/common/AbstractHandler.h"

namespace AwsMock::Service {

  AbstractHandler::AbstractHandler() : _baseUrl(), _requestURI(), _requestHost() {}

  AbstractHandler::~AbstractHandler() = default;

  void AbstractHandler::handleHttpHeaders(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {

    if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET && request.getMethod() != Poco::Net::HTTPRequest::HTTP_PUT
      && request.getMethod() != Poco::Net::HTTPRequest::HTTP_POST && request.getMethod() != Poco::Net::HTTPRequest::HTTP_DELETE
      && request.getMethod() != Poco::Net::HTTPRequest::HTTP_OPTIONS && request.getMethod() != Poco::Net::HTTPRequest::HTTP_HEAD) {
      log_error << "Invalid request method, method: " << request.getMethod();
      throw Core::ServiceException("The request method is not supported by the manager and cannot be handled.", Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    }

    if (request.has("Accept")) {
      if (!request.get("Accept").empty()) {
        response.setContentType(request.get("Accept"));
      }
    }
  }

  void AbstractHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {

    try {
      handleHttpHeaders(request, response);
    } catch (Core::ServiceException &exception) {

      log_error << "Exception: msg: " << exception.message();

      handleHttpStatusCode(response, exception.code());
      return;
    }

    Poco::URI uri = Poco::URI(request.getURI());

    std::string scheme, authInfo, region, user;
    request.getCredentials(scheme, authInfo);
    GetRegionUser(authInfo, region, user);

    _queryStringParameters = uri.getQueryParameters();
    uri.getPathSegments(_pathParameter);

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET) {
      this->handleGet(request, response, region, user);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT) {
      this->handlePut(request, response, region, user);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST) {
      this->handlePost(request, response, region, user);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE) {
      this->handleDelete(request, response, region, user);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS) {
      this->handleOptions(response);
    }

    if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_HEAD) {
      this->handleHead(request, response, region, user);
    }
  }

  void AbstractHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleGet(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handlePut(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handlePost(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleDelete(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, const Dto::Common::S3ClientCommand &s3ClientCommand) {
    log_trace << "Request, method: " + request.getMethod() << " region: " << s3ClientCommand.region << " user: " << s3ClientCommand.user;
    DumpRequest(request);
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_debug << "S3 OPTIONS request";

    response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
    response.setContentType("text/plain; charset=utf-8");

    handleHttpStatusCode(response, 200);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void AbstractHandler::handleHead([[maybe_unused]]Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response, [[maybe_unused]]const std::string &region, [[maybe_unused]]const std::string &user) {
    log_trace << "Request, method: " << request.getMethod();
    response.setStatusAndReason(
      Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
      Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
    );

    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleHttpStatusCode(Poco::Net::HTTPServerResponse &response, int statusCode, const char *reason) {

    switch (statusCode) {

    case 200:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_OK);
      break;

    case 201:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_CREATED, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_CREATED);
      break;

    case 202:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_ACCEPTED);
      break;

    case 204:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
      break;

    case 205:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_RESET_CONTENT);
      break;

    case 206:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_PARTIAL_CONTENT);
      break;

    case 400:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST);
      log_error << "HTTP state code: 401 message: " << Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST;
      break;

    case 401:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_UNAUTHORIZED);
      log_error << "HTTP state code: 401 message: " << Poco::Net::HTTPResponse::HTTP_REASON_UNAUTHORIZED;
      break;

    case 403:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_FORBIDDEN);
      log_warning << "HTTP state code: 403 message: " << Poco::Net::HTTPResponse::HTTP_REASON_FORBIDDEN;
      break;

    case 404:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);
      log_warning << "HTTP state code: 404 message: " << Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND;
      break;

    case 405:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
      break;

    case 406:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
      break;

    case 409:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_CONFLICT);
      break;

    case 410:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_GONE);
      break;

    case 415:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNSUPPORTEDMEDIATYPE);
      break;

    case 500:
      response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR,
                                  reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR);
      break;

    case Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
      break;

    case 503:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
      break;

      // Validating routines throw exceptions all over the program, but are not able to specify
      // an exception code compatible with HTTP. So, the code is left zero. This routine can catch this.
    default:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
      break;
    }
  }

  std::map<std::string, std::string> AbstractHandler::GetMetadata(Poco::Net::HTTPServerRequest &request) {
    std::map<std::string, std::string> metadata;
    for (const auto &m : request) {
      if (Core::StringUtils::StartsWith(m.first, "x-amz-meta-")) {
        std::string name = Core::StringUtils::StripBeginning(m.first, "x-amz-meta-");
        metadata[name] = m.second;
      }
    }
    return metadata;
  }

  void AbstractHandler::GetRegionUser(const std::string &authorization, std::string &region, std::string &user) {
    Poco::RegularExpression::MatchVec posVec;

    Poco::RegularExpression pattern(R"(Credential=([a-zA-Z0-9]+)\/[0-9]{8}\/([a-zA-Z0-9\-]+)\/[a-zA-Z0-9\-]+\/aws4_request,.*$)");
    if (!pattern.match(authorization, 0, posVec)) {
      throw Core::ResourceNotFoundException("Could not extract region and user");
    }

    user = authorization.substr(posVec[1].offset, posVec[1].length);
    region = authorization.substr(posVec[2].offset, posVec[2].length);
    log_trace << "Found user: " << user << " region: " << region;
  }

  void AbstractHandler::SendOkResponse(Poco::Net::HTTPServerResponse &response, const std::string &payload, const HeaderMap &extraHeader) {
    log_trace << "Sending OK response, state: 200 payload: " << payload;

    // Get content length
    unsigned long contentLength = 0;
    if (!payload.empty()) {
      contentLength = payload.length();
    }

    // Set headers
    SetHeaders(response, contentLength, extraHeader);
    //DumpResponseHeaders(response);

    // Send response
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream &os = response.send();
    if (!payload.empty()) {
      os << payload;
    }
    os.flush();
  }

  void AbstractHandler::SendOkResponse(Poco::Net::HTTPServerResponse &response, const std::string &fileName, long contentLength, const HeaderMap &extraHeader) {
    log_trace << "Sending OK response, state: 200, filename: " << fileName << " contentLength: " << contentLength;
    try {

      // Set headers
      SetHeaders(response, contentLength, extraHeader);

      // Set state
      handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_OK);

      // Send response
      std::ostream &os = response.send();

      // Send body
      std::ifstream ifs(fileName);
      long send = Poco::StreamCopier::copyStream(ifs, os);
      os.flush();
      ifs.close();
      log_info << "Bytes send: " << send;

    } catch (Poco::Exception &exc) {
      log_error << "Exception: " << exc.message();
    }
  }

  void AbstractHandler::SendContinueResponse(Poco::Net::HTTPServerResponse &response) {
    log_trace << "Sending CONTINUE response, state: 100";

    // Send response
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_CONTINUE);
    std::ostream &os = response.send();
    os.flush();
  }

  void AbstractHandler::SendRangeResponse(Poco::Net::HTTPServerResponse &response, const std::string &fileName, long min, long max, long size, const HeaderMap &extraHeader) {
    log_trace << "Sending OK response, state: 200, filename: " << fileName << " min: " << min << " max: " << max;

    if (!_memoryMappedFile.IsMapped()) {
      if (!_memoryMappedFile.OpenFile(fileName)) {
        throw Core::ServiceException("Could not open memory mapped file");
      }
    }

    try {

      // Set headers
      long length = max - min;
      SetHeaders(response, length, extraHeader);

      // Set state
      if (min + length >= size) {
        handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_OK);
      } else {
        handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_PARTIAL_CONTENT);
      }

      // Send response
      std::ostream &os = response.send();

      // Send body
      char *buffer = new char[length];
      _memoryMappedFile.ReadChunk(min, length, (char *) buffer);
      os.write(buffer, length);
      os.flush();
      delete[] buffer;

      // Close file
      if (min + length >= size) {
        _memoryMappedFile.CloseFile();
      }

    } catch (Poco::Exception &exc) {
      log_error << "Exception: " << exc.message();
      throw Core::ServiceException("Bad request, send range response, exception: " + exc.message());
    }
  }

  void AbstractHandler::SendHeadResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
    log_trace << "Sending Head response, state: 200";
    try {

      // Set headers
      // Extra headers
      if (!extraHeader.empty()) {
        log_trace << "Setting extra header values, count: " << extraHeader.size();
        for (auto &it : extraHeader) {
          response.set(it.first, it.second);
        }
      }
      //DumpResponseHeaders(response);

      handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_OK);
      response.send();

    } catch (Poco::Exception &exc) {
      log_error << "Exception: " << exc.message();
    }
  }

  void AbstractHandler::SendNoContentResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
    log_trace << "Sending NO_CONTENT response, state: 204";
    try {

      // Set headers
      SetHeaders(response, 0, extraHeader);

      // Send response
      handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
      response.send();

    } catch (Poco::Exception &exc) {
      log_error << "Exception: " << exc.message();
    }
  }

  void AbstractHandler::SendDeleteResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
    log_trace << "Sending DELETE response, state: 204";

    // Get content length
    unsigned long contentLength = 0;

    // Set headers
    SetHeaders(response, contentLength, extraHeader);

    // Send response
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTPStatus::HTTP_NO_CONTENT);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void AbstractHandler::SendErrorResponse(Poco::Net::HTTPServerResponse &response, const std::string &body, std::map<std::string, std::string> headers, const Poco::Net::HTTPResponse::HTTPStatus &status) {

    SetHeaders(response, body.length(), headers);

    handleHttpStatusCode(response, status);
    std::ostream &outputStream = response.send();
    outputStream << body;
    outputStream.flush();
  }

  void AbstractHandler::SendXmlErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Poco::Exception &exc) {

    Core::ServiceException serviceException = Core::ServiceException(exc.message(), exc.code());
    SendXmlErrorResponse(service, response, serviceException);
  }

  void AbstractHandler::SendXmlErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Core::ServiceException &exc) {

    std::string payload;
    if (service == "SQS") {
      payload = Dto::SQS::RestErrorResponse(exc).ToXml();
    } else if (service == "S3") {
      payload = Dto::S3::RestErrorResponse(exc).ToXml();
    }
    SetHeaders(response, payload.length());

    handleHttpStatusCode(response, exc.code(), exc.message().c_str());
    std::ostream &outputStream = response.send();
    outputStream << payload;
    outputStream.flush();
  }

  void AbstractHandler::SendXmlErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, std::exception &exc) {
    SendXmlErrorResponse(service, response, exc.what());
  }

  void AbstractHandler::SendXmlErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, const std::string &payload) {

    SetHeaders(response, payload.length());

    log_error << "Exception, code: " << response.getStatus() << " message: " << payload;
    handleHttpStatusCode(response, response.getStatus());
    std::ostream &outputStream = response.send();
    outputStream << payload;
    outputStream.flush();
  }

  void AbstractHandler::SendJsonErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Poco::Exception &exc) {

    Core::ServiceException serviceException = Core::ServiceException(exc.message(), exc.code());
    SendJsonErrorResponse(service, response, serviceException);
  }

  void AbstractHandler::SendJsonErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Core::ServiceException &exc) {

    std::string payload = exc.message();
    if (service == "SQS") {
      payload = Dto::SQS::RestErrorResponse(exc).ToJson();
    } else if (service == "S3") {
      //payload = Dto::S3::RestErrorResponse(exc).ToJson();
    }
    SetHeaders(response, payload.length(), {}, "application/json");

    handleHttpStatusCode(response, exc.code(), exc.message().c_str());
    std::ostream &outputStream = response.send();
    outputStream << payload;
    outputStream.flush();
    //DumpResponse(response);
  }

  void AbstractHandler::SetHeaders(Poco::Net::HTTPServerResponse &response, unsigned long contentLength, const HeaderMap &extraHeader, const std::string &contentType) {
    log_trace << "Setting header values, contentLength: " << contentLength;

    // Default headers
    response.set("Date", Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::HTTP_FORMAT));
    response.set("Content-Length", std::to_string(contentLength));
    response.set("Content-Type", contentType);
    response.set("Connection", "keep-alive");
    response.set("Server", "awsmock");

    // Extra headers
    if (!extraHeader.empty()) {
      log_trace << "Setting extra header values, count: " << extraHeader.size();
      for (auto &it : extraHeader) {
        response.set(it.first, it.second);
      }
    }
  }

  std::string AbstractHandler::GetHeaderValue(Poco::Net::HTTPServerRequest &request, const std::string &name, const std::string &defaultValue) {
    log_trace << "Getting header values, name: " << name;
    return request.get(name, defaultValue);
  }

  void AbstractHandler::DumpRequest(Poco::Net::HTTPServerRequest &request) {
    log_trace << "Dump request";
    std::cerr << "==================== Request =====================";
    request.write(std::cerr);
    std::cerr << "==================================================";
  }

  void AbstractHandler::DumpRequestHeaders(Poco::Net::HTTPServerRequest &request) {
    log_trace << "Dump request headers";
    std::cerr << "================ Request Headers =================";
    for (const auto &h : request) {
      std::cerr << h.first << ": " << h.second;
    }
    std::cerr << "==================================================";
  }

  void AbstractHandler::DumpResponseHeaders(Poco::Net::HTTPServerResponse &response) {
    log_trace << "Dump response headers";
    std::cerr << "============== Response Headers ==================";
    for (const auto &h : response) {
      std::cerr << h.first << ": " << h.second;
    }
    std::cerr << "==================================================";
  }

  void AbstractHandler::DumpResponse(Poco::Net::HTTPServerResponse &response) {
    log_trace << "Dump response";
    std::cerr << "==================== Response ====================";
    response.write(std::cerr);
    std::cerr << "==================================================";
  }

  [[maybe_unused]] void AbstractHandler::DumpBody(Poco::Net::HTTPServerRequest &request) {
    log_trace << "Dump request body";
    std::cerr << "================== Request Body ==================";
    std::cerr << request.stream().rdbuf();
    std::cerr << "==================================================";
  }

  [[maybe_unused]] void AbstractHandler::DumpPayload(const std::string &payload) {
    log_trace << "Dump request body";
    std::cerr << "================== Request Body ==================";
    std::cerr << payload;
    std::cerr << "==================================================";
  }

  void AbstractHandler::DumpBodyToFile(Poco::Net::HTTPServerRequest &request, const std::string &filename) {
    log_trace << "Dump request body to file: " + filename;
    std::ofstream ofs(filename);
    ofs << request.stream().rdbuf();
    ofs.close();
  }
}
