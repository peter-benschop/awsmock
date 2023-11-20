
#include "awsmock/service/AbstractHandler.h"

namespace AwsMock::Service {

  AbstractHandler::AbstractHandler() : _logger(Poco::Logger::get("AbstractHandler")), _baseUrl(), _requestURI(), _requestHost() {}

  AbstractHandler::~AbstractHandler() = default;

  void AbstractHandler::handleHttpHeaders(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {

    if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET && request.getMethod() != Poco::Net::HTTPRequest::HTTP_PUT
        && request.getMethod() != Poco::Net::HTTPRequest::HTTP_POST && request.getMethod() != Poco::Net::HTTPRequest::HTTP_DELETE
        && request.getMethod() != Poco::Net::HTTPRequest::HTTP_OPTIONS && request.getMethod() != Poco::Net::HTTPRequest::HTTP_HEAD) {
      log_error_stream(_logger) << "Invalid request method, method: " << request.getMethod() << std::endl;
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

      log_error_stream(_logger) << "Exception: msg: " << exception.message() << std::endl;

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

  void AbstractHandler::handleGet([[maybe_unused]]Poco::Net::HTTPServerRequest &request,
                                  Poco::Net::HTTPServerResponse &response,
                                  [[maybe_unused]]const std::string &region,
                                  [[maybe_unused]]const std::string &user) {
    log_trace_stream(_logger) << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user << std::endl;
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handlePut([[maybe_unused]]Poco::Net::HTTPServerRequest &request,
                                  Poco::Net::HTTPServerResponse &response,
                                  [[maybe_unused]]const std::string &region,
                                  [[maybe_unused]]const std::string &user) {
    log_trace_stream(_logger) << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user << std::endl;
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handlePost([[maybe_unused]]Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response,
                                   [[maybe_unused]]const std::string &region,
                                   [[maybe_unused]]const std::string &user) {
    log_trace_stream(_logger) << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user << std::endl;
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleDelete([[maybe_unused]]Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response,
                                     [[maybe_unused]]const std::string &region,
                                     [[maybe_unused]]const std::string &user) {
    log_trace_stream(_logger) << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user << std::endl;
    handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleOptions(Poco::Net::HTTPServerResponse &response) {
    log_trace_stream(_logger) << "Request, method: OPTIONS" << std::endl;
    response.setStatusAndReason(
        Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
        Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
    );

    std::ostream &errorStream = response.send();
    errorStream.flush();
  }

  void AbstractHandler::handleHead([[maybe_unused]]Poco::Net::HTTPServerRequest &request,
                                   Poco::Net::HTTPServerResponse &response,
                                   [[maybe_unused]]const std::string &region,
                                   [[maybe_unused]]const std::string &user) {
    log_trace_stream(_logger) << "Request, method: " << request.getMethod() << std::endl;
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
      log_error_stream(_logger) << "HTTP state code: 401 message: " << Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST << std::endl;
      break;

    case 401:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_UNAUTHORIZED);
      log_error_stream(_logger) << "HTTP state code: 401 message: " << Poco::Net::HTTPResponse::HTTP_REASON_UNAUTHORIZED << std::endl;
      break;

    case 403:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_FORBIDDEN);
      log_warning_stream(_logger) << "HTTP state code: 403 message: " << Poco::Net::HTTPResponse::HTTP_REASON_FORBIDDEN << std::endl;
      break;

    case 404:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);
      log_warning_stream(_logger) << "HTTP state code: 404 message: " << Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND << std::endl;
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

  std::string AbstractHandler::GetQueryParameter(const std::string &parameterKey, bool optional) {

    auto iterator = std::find_if(_queryStringParameters.begin(), _queryStringParameters.end(),
                                 [&parameterKey](const std::pair<std::string, std::string> &item) {
                                   return item.first == parameterKey;
                                 }
    );

    if (iterator == _queryStringParameters.end()) {
      if (optional) {
        return {};
      } else {
        throw Core::ServiceException("MessageAttribute '" + parameterKey + "' is missing in URL.", Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
      }
    }
    return iterator->second;
  }

  bool AbstractHandler::QueryParameterExists(const std::string &parameterKey) {

    auto iterator = std::find_if(_queryStringParameters.begin(), _queryStringParameters.end(),
                                 [&parameterKey](const std::pair<std::string, std::string> &item) {
                                   return item.first == parameterKey;
                                 }
    );

    return iterator != _queryStringParameters.end();
  }

  std::string AbstractHandler::GetPathParameter(int pos) {
    return _pathParameter[pos];
  }

  bool AbstractHandler::HeaderExists(Poco::Net::HTTPServerRequest &request, const std::string &name) {
    return request.has(name);
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

    Poco::RegularExpression pattern(R"(Credential=([a-zA-Z0-9]+)\/[0-9]{8}\/([a-zA-Z0-9\-]+)\/[a-zA-Z0-9]+\/aws4_request,.*$)");
    if (!pattern.match(authorization, 0, posVec)) {
      throw Core::ResourceNotFoundException("Could not extract region and user");
    }

    user = authorization.substr(posVec[1].offset, posVec[1].length);
    region = authorization.substr(posVec[2].offset, posVec[2].length);
    log_trace_stream(_logger) << "Found user: " << user << " region: " << region << std::endl;
  }

  std::string AbstractHandler::GetPayload(Poco::Net::HTTPServerRequest &request) {
    std::string payload;
    Poco::StreamCopier::copyToString(request.stream(), payload);
    log_trace_stream(_logger) << "Request payload: " << payload << std::endl;
    request.stream().clear();
    request.stream().seekg(0);
    return payload;
  }

  void AbstractHandler::GetActionVersion(const std::string &body, std::string &action, std::string &version) {
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
    log_trace_stream(_logger) << "Found action: " << action << " version: " << version << std::endl;
  }

  std::string AbstractHandler::GetStringParameter(const std::string &path, const std::string &name) {
    std::string value;
    std::vector<std::string> bodyParts = Core::StringUtils::Split(path, '&');
    for (auto &it : bodyParts) {
      std::vector<std::string> parts = Core::StringUtils::Split(it, '=');
      if (parts[0] == name) {
        value = Core::StringUtils::UrlDecode(parts[1]);
      }
    }
    log_trace_stream(_logger) << "Found string parameter, name: " << name << " value: " << value << std::endl;
    return value;
  }

  int AbstractHandler::GetIntParameter(const std::string &body, const std::string &name, int min, int max, int def) {
    int value = def;
    std::string parameterValue = GetStringParameter(body, name);
    if (!parameterValue.empty()) {
      value = std::stoi(parameterValue);
      value = value > min && value < max ? value : def;
    }
    log_trace_stream(_logger) << "Found integer name, name: " << name << " value: " << value << std::endl;
    return value;
  }

  int AbstractHandler::GetAttributeCount(const std::string &body, const std::string &name) {
    int count = 0;
    std::string parameters = Core::StringUtils::SubStringAfter(body, "?");
    std::vector<std::string> bodyParts = Core::StringUtils::Split(parameters, '&');
    for (auto &it : bodyParts) {
      if (it.starts_with(name)) {
        count++;
      }
    }
    log_trace_stream(_logger) << "Found attribute count, name: " << name << " count: " << count / 2 << std::endl;
    return count;
  }

  int AbstractHandler::GetAttributeNameCount(const std::string &body, const std::string &name) {
    int count = 0;
    std::vector<std::string> bodyParts = Core::StringUtils::Split(body, '&');
    for (auto &it : bodyParts) {
      if (it.starts_with(name)) {
        count++;
      }
    }
    log_trace_stream(_logger) << "Found attribute count, name: " << name << " count: " << count / 2 << std::endl;
    return count;
  }

  void AbstractHandler::GetVersionActionFromUri(const std::string &uri, std::string &version, std::string &action) {

    Poco::RegularExpression::MatchVec posVec;
    Poco::RegularExpression pattern(R"(/([a-z0-9-.]+)?/?([a-zA-Z0-9-/_.*'()]+)?\??.*$)");
    if (!pattern.match(uri, 0, posVec)) {
      log_error_stream(_logger) << "Invalid URI: " << uri << std::endl;
      throw Core::ResourceNotFoundException("Could not extract version and action");
    }

    if (posVec.size() > 1) {
      version = uri.substr(posVec[1].offset, posVec[1].length);
    }
    if (posVec.size() > 2) {
      action = uri.substr(posVec[2].offset, posVec[2].length);
    }
    log_debug_stream(_logger) << "Found version and action, version: " << version << " action: " << action << std::endl;
  }

  std::string AbstractHandler::GetBodyAsString(Poco::Net::HTTPServerRequest &request) {
    std::stringstream sstream;
    sstream << request.stream().rdbuf();
    return sstream.str();
  }

  std::string AbstractHandler::GetEndpoint(Poco::Net::HTTPServerRequest &request) {
    return request.get("localstack:4566");
  }

  void AbstractHandler::SendOkResponse(Poco::Net::HTTPServerResponse &response, const std::string &payload, const HeaderMap &extraHeader) {
    log_trace_stream(_logger) << "Sending OK response, state: 200 payload: " << payload << std::endl;

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
    os.clear();
  }

  void AbstractHandler::SendOkResponse(Poco::Net::HTTPServerResponse &response, const std::string &fileName, long contentLength, const HeaderMap &extraHeader) {
    log_trace_stream(_logger) << "Sending OK response, state: 200, filename: " << fileName << " contentLength: " << contentLength << std::endl;
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
      log_info_stream(_logger) << "Bytes send: " << send << std::endl;

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Exception: " << exc.message() << std::endl;
    }
  }

  void AbstractHandler::SendRangeResponse(Poco::Net::HTTPServerResponse &response, const std::string &fileName, long min, long max, long size, const HeaderMap &extraHeader) {
    log_trace_stream(_logger) << "Sending OK response, state: 200, filename: " << fileName << " min: " << min << " max: " << max << std::endl;
    try {

      if (!Core::MemoryMappedFile::instance().IsMapped()) {
        Core::MemoryMappedFile::instance().OpenFile(fileName);
      }

      // Set headers
      long range = max - min + 1;
      SetHeaders(response, range, extraHeader);

      //DumpResponseHeaders(response);

      // Set state
      handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_PARTIAL_CONTENT);

      // Send response
      std::ostream &os = response.send();

      // Send body
      if (range > 0) {
        char *buffer = new char[range + 1];
        Core::MemoryMappedFile::instance().ReadChunk(min, range, (char *) buffer);
        os.write(buffer, range);
        os.flush();
        os.clear();
        delete[] buffer;
      }

      // Close file
      if (min + range >= size) {
        Core::MemoryMappedFile::instance().CloseFile();
      }

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Exception: " << exc.message() << std::endl;
    }
  }

  void AbstractHandler::SendHeadResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
    log_trace_stream(_logger) << "Sending Head response, state: 200" << std::endl;
    try {

      // Set headers
      for (auto &it : extraHeader) {
        response.set(it.first, it.second);
      }
      //DumpResponseHeaders(response);

      response.send();

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Exception: " << exc.message() << std::endl;
    }
  }

  void AbstractHandler::SendNoContentResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
    log_trace_stream(_logger) << "Sending NO_CONTENT response, state: 204" << std::endl;
    try {

      // Set headers
      SetHeaders(response, 0, extraHeader);

      // Send response
      handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
      response.send();

    } catch (Poco::Exception &exc) {
      log_error_stream(_logger) << "Exception: " << exc.message() << std::endl;
    }
  }

  void AbstractHandler::SendDeleteResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
    log_trace_stream(_logger) << "Sending DELETE response, state: 204" << std::endl;

    // Get content length
    unsigned long contentLength = 0;

    // Set headers
    SetHeaders(response, contentLength, extraHeader);

    // Send response
    handleHttpStatusCode(response, 204);
    std::ostream &outputStream = response.send();
    outputStream.flush();
  }

  void AbstractHandler::SendErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Poco::Exception &exc) {

    Core::ServiceException serviceException = Core::ServiceException(exc.message(), exc.code());
    SendErrorResponse(service, response, serviceException);
  }

  void AbstractHandler::SendErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Core::ServiceException &exc) {

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

  void AbstractHandler::SendErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, const std::string &payload) {

    SetHeaders(response, payload.length());

    log_error_stream(_logger) << "Exception, code: " << response.getStatus() << " message: " << payload << std::endl;
    handleHttpStatusCode(response, response.getStatus());
    std::ostream &outputStream = response.send();
    outputStream << payload;
    outputStream.flush();
  }

  void AbstractHandler::SetHeaders(Poco::Net::HTTPServerResponse &response, unsigned long contentLength, const HeaderMap &extraHeader) {
    log_trace_stream(_logger) << "Setting header values, contentLength: " << contentLength << std::endl;

    // Default headers
    response.set("Date", Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::HTTP_FORMAT));
    response.set("Content-Length", std::to_string(contentLength));
    response.set("Content-Type", "application/xml");
    response.set("Connection", "keep-alive");
    response.set("Server", "awsmock");

    // Extra headers
    if (!extraHeader.empty()) {
      log_trace_stream(_logger) << "Setting extra header values, count: " << extraHeader.size() << std::endl;
      for (auto &it : extraHeader) {
        response.set(it.first, it.second);
      }
    }
  }

  std::string AbstractHandler::GetHeaderValue(Poco::Net::HTTPServerRequest &request, const std::string &name, const std::string &defaultValue) {
    log_trace_stream(_logger) << "Getting header values, name: " << name << std::endl;
    return request.get(name, defaultValue);
  }

  bool AbstractHandler::HasHeaderValue(Poco::Net::HTTPServerRequest &request, const std::string &name) {
    log_trace_stream(_logger) << "Has header value, name: " << name << std::endl;
    return request.has(name);
  }

  void AbstractHandler::DumpRequest(Poco::Net::HTTPServerRequest &request) {
    log_trace_stream(_logger) << "Dump request" << std::endl;
    std::cerr << "==================== Request =====================" << std::endl;
    request.write(std::cerr);
    std::cerr << "==================================================" << std::endl;
  }

  void AbstractHandler::DumpRequestHeaders(Poco::Net::HTTPServerRequest &request) {
    log_trace_stream(_logger) << "Dump request headers" << std::endl;
    std::cerr << "================ Request Headers =================" << std::endl;
    for (const auto &h : request) {
      std::cerr << h.first << ": " << h.second << std::endl;
    }
    std::cerr << "==================================================" << std::endl;
  }

  void AbstractHandler::DumpResponseHeaders(Poco::Net::HTTPServerResponse &response) {
    log_trace_stream(_logger) << "Dump response headers" << std::endl;
    std::cerr << "============== Response Headers ==================" << std::endl;
    for (const auto &h : response) {
      std::cerr << h.first << ": " << h.second << std::endl;
    }
    std::cerr << "==================================================" << std::endl;
  }

  void AbstractHandler::DumpResponse(Poco::Net::HTTPServerResponse &response) {
    log_trace_stream(_logger) << "Dump response" << std::endl;
    std::cerr << "==================== Response ====================" << std::endl;
    response.write(std::cerr);
    std::cerr << "==================================================" << std::endl;
  }

  [[maybe_unused]] void AbstractHandler::DumpBody(Poco::Net::HTTPServerRequest &request) {
    log_trace_stream(_logger) << "Dump request body" << std::endl;
    std::cerr << "================== Request Body ==================" << std::endl;
    std::cerr << request.stream().rdbuf() << std::endl;
    std::cerr << "==================================================" << std::endl;
    request.stream().clear();
    request.stream().seekg(0, std::ios::beg);
  }

  [[maybe_unused]] void AbstractHandler::DumpPayload(const std::string &payload) {
    log_trace_stream(_logger) << "Dump request body" << std::endl;
    std::cerr << "================== Request Body ==================" << std::endl;
    std::cerr << payload << std::endl;
    std::cerr << "==================================================" << std::endl;
  }

  void AbstractHandler::DumpBodyToFile(Poco::Net::HTTPServerRequest &request, const std::string &filename) {
    log_trace_stream(_logger) << "Dump request body to file: " + filename << std::endl;
    std::ofstream ofs(filename);
    ofs << request.stream().rdbuf();
    ofs.close();
  }
}
