
#include "awsmock/resource/AbstractResource.h"

namespace AwsMock::Resource {

    AbstractResource::AbstractResource() : _baseUrl(), _requestURI(), _requestHost() {}

    AbstractResource::~AbstractResource() = default;

    void AbstractResource::handleHttpHeaders(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {

        if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET && request.getMethod() != Poco::Net::HTTPRequest::HTTP_PUT && request.getMethod() != Poco::Net::HTTPRequest::HTTP_POST && request.getMethod() != Poco::Net::HTTPRequest::HTTP_DELETE && request.getMethod() != Poco::Net::HTTPRequest::HTTP_OPTIONS && request.getMethod() != Poco::Net::HTTPRequest::HTTP_HEAD) {
            log_error << "Invalid request method, method: " << request.getMethod();
            throw HandlerException("Not Implemented", "The request method is not supported by the manager and cannot be handled.", 501);
        }

        if (request.has("Accept")) {
            if (!request.get("Accept").empty()) {
                response.setContentType(request.get("Accept"));
            }
        }
    }

    void AbstractResource::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {

        try {
            handleHttpHeaders(request, response);
        } catch (HandlerException &exception) {

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

    void AbstractResource::handleGet([[maybe_unused]] Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response,
                                     [[maybe_unused]] const std::string &region,
                                     [[maybe_unused]] const std::string &user) {
        log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handlePut([[maybe_unused]] Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response,
                                     [[maybe_unused]] const std::string &region,
                                     [[maybe_unused]] const std::string &user) {
        log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handlePost([[maybe_unused]] Poco::Net::HTTPServerRequest &request,
                                      Poco::Net::HTTPServerResponse &response,
                                      [[maybe_unused]] const std::string &region,
                                      [[maybe_unused]] const std::string &user) {
        log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handleDelete([[maybe_unused]] Poco::Net::HTTPServerRequest &request,
                                        Poco::Net::HTTPServerResponse &response,
                                        [[maybe_unused]] const std::string &region,
                                        [[maybe_unused]] const std::string &user) {
        log_trace << "Request, method: " + request.getMethod() << " region: " << region << " user: " << user;
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handleOptions(Poco::Net::HTTPServerResponse &response) {
        log_trace << "Request, method: OPTIONS";
        response.setStatusAndReason(
                Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
                Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED);

        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handleHead([[maybe_unused]] Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response,
                                      [[maybe_unused]] const std::string &region,
                                      [[maybe_unused]] const std::string &user) {
        log_trace << "Request, method: " << request.getMethod();
        response.setStatusAndReason(
                Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
                Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED);

        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handleHttpStatusCode(Poco::Net::HTTPServerResponse &response, int statusCode, const char *reason) {

        switch (statusCode) {

            case 200:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_OK, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_OK);
                break;

            case 201:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_CREATED, reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_CREATED);
                break;

            case 202:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_ACCEPTED);
                break;

            case 204:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
                break;

            case 205:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_RESET_CONTENT);
                break;

            case 206:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_PARTIAL_CONTENT);
                break;

            case 400:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                break;

            case 401:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
                break;

            case 403:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
                break;

            case 404:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                break;

            case 405:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED);
                break;

            case 406:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_ACCEPTABLE);
                break;

            case 409:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_CONFLICT);
                break;

            case 410:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_GONE);
                break;

            case 415:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNSUPPORTEDMEDIATYPE);
                break;

            case 500:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR,
                                            reason != nullptr ? reason : Poco::Net::HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR);
                break;

            case 501:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
                break;

            case 503:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
                break;

                // Validating routines throw exceptions all over the program, but are not able to specify
                // an exception code compatible with HTTP. So, the code is left zero. This routine can catch this.
            default:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                break;
        }
    }

    void AbstractResource::GetRegionUser(const std::string &authorization, std::string &region, std::string &user) {
        Poco::RegularExpression::MatchVec posVec;

        Poco::RegularExpression pattern(R"(Credential=([a-zA-Z0-9]+)\/[0-9]{8}\/([a-zA-Z0-9\-]+)\/[a-zA-Z0-9]+\/aws4_request,.*$)");
        if (!pattern.match(authorization, 0, posVec)) {
            throw Core::ResourceNotFoundException("Could not extract region and user");
        }

        user = authorization.substr(posVec[1].offset, posVec[1].length);
        region = authorization.substr(posVec[2].offset, posVec[2].length);
        log_trace << "Found user: " << user << " region: " << region;
    }

    std::string AbstractResource::GetPayload(Poco::Net::HTTPServerRequest &request) {
        std::string payload;
        Poco::StreamCopier::copyToString(request.stream(), payload);
        log_trace << "Request payload: " << payload;
        return payload;
    }

    void AbstractResource::SendOkResponse(Poco::Net::HTTPServerResponse &response, const std::string &payload, HeaderMap *extraHeader) {
        log_trace << "Sending OK response, state: 200 payload: " << payload;

        // Get content length
        unsigned long contentLength = 0;
        if (!payload.empty()) {
            contentLength = payload.length();
        }

        // Set headers
        SetHeaders(response, contentLength, extraHeader);

        // Send response
        handleHttpStatusCode(response, 200);
        std::ostream &outputStream = response.send();
        if (!payload.empty()) {
            outputStream << payload;
        }
        outputStream.flush();
    }

    void AbstractResource::SendErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Poco::Exception &exc) {

        Core::ServiceException serviceException = Core::ServiceException(exc.message(), exc.code());
        SendErrorResponse(service, response, serviceException);
    }

    void AbstractResource::SendErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Core::ServiceException &exc) {

        std::string payload = exc.message();
        SetHeaders(response, payload.length());

        log_error << "Exception, code: " << exc.code() << " message: " << exc.message();
        handleHttpStatusCode(response, exc.code(), exc.message().c_str());
        std::ostream &outputStream = response.send();
        outputStream << payload;
        outputStream.flush();
    }

    void AbstractResource::SendErrorResponse(Poco::Net::HTTPServerResponse &response, const std::string &payload) {

        SetHeaders(response, payload.length());

        log_error << "Exception, code: " << response.getStatus() << " message: " << payload;
        handleHttpStatusCode(response, response.getStatus());
        std::ostream &outputStream = response.send();
        outputStream << payload;
        outputStream.flush();
    }

    void AbstractResource::SetHeaders(Poco::Net::HTTPServerResponse &response, unsigned long contentLength, HeaderMap *extraHeader) {
        log_trace << "Setting header values, contentLength: " << contentLength;

        // Default headers
        response.set("Date", Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::HTTP_FORMAT));
        response.set("Content-Length", std::to_string(contentLength));
        response.set("Content-Type", "text/html; charset=utf-8");
        response.set("Connection", "keep-alive");
        response.set("Server", "AmazonS3");

        // Extra headers
        if (extraHeader != nullptr) {
            log_trace << "Setting extra header values, count: " << extraHeader->size();
            for (auto &it: *extraHeader) {
                response.set(it.first, it.second);
            }
        }
    }

    void AbstractResource::SetHeaders(Poco::Net::HTTPServerRequest &request, const std::string &region, const std::string &user) {
        log_trace << "Setting request header values, region: " << region << " user: " << user;

        // Default headers
        request.set("Region", region);
        request.set("User", user);
        request.set("RequestId", Core::AwsUtils::CreateRequestId());
    }

    void AbstractResource::DumpRequest(Poco::Net::HTTPServerRequest &request) {
        log_trace << "Dump request";
        std::cerr << "==================== Request =====================";
        request.write(std::cerr);
        std::cerr << "==================================================";
    }

    void AbstractResource::DumpResponse(Poco::Net::HTTPServerResponse &response) {
        log_trace << "Dump response";
        std::cerr << "==================== Response ====================";
        response.write(std::cerr);
        std::cerr << "==================================================";
    }

    [[maybe_unused]] void AbstractResource::DumpBody(Poco::Net::HTTPServerRequest &request) {
        log_trace << "Dump request body";
        std::cerr << "================== Request Body ==================";
        std::cerr << request.stream().rdbuf();
        std::cerr << "==================================================";
    }

    void AbstractResource::DumpBodyToFile(Poco::Net::HTTPServerRequest &request, const std::string &filename) {
        log_trace << "Dump request body to file: " + filename;
        std::ofstream ofs(filename);
        ofs << request.stream().rdbuf();
        ofs.close();
    }
}// namespace AwsMock::Resource
