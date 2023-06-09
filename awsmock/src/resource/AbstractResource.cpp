#include <Poco/RegularExpression.h>
#include "awsmock/resource/AbstractResource.h"

namespace AwsMock::Resource {

    AbstractResource::AbstractResource() : _logger(Poco::Logger::get("AbstractResource")), _baseUrl(), _requestURI(), _requestHost() {
        Core::Logger::SetDefaultConsoleLogger("AbstractResource");
    }

    AbstractResource::~AbstractResource() = default;

    void AbstractResource::handleHttpHeaders(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {

        if (request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET && request.getMethod() != Poco::Net::HTTPRequest::HTTP_PUT
            && request.getMethod() != Poco::Net::HTTPRequest::HTTP_POST && request.getMethod() != Poco::Net::HTTPRequest::HTTP_DELETE
            && request.getMethod() != Poco::Net::HTTPRequest::HTTP_OPTIONS && request.getMethod() != Poco::Net::HTTPRequest::HTTP_HEAD) {
            poco_error(_logger, "Invalid request method, method: " + request.getMethod());
            throw HandlerException("Not Implemented", "The request method is not supported by the server and cannot be handled.", 501);
        }

        if (request.has("Accept")) {
            if (!request.get("Accept").empty()) {
                response.setContentType(request.get("Accept"));
            }
        }
        poco_debug(_logger, "Header checked");
    }

    void AbstractResource::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {

        try {
            handleHttpHeaders(request, response);
        } catch (HandlerException &exception) {

            poco_error(_logger, "Exception: msg: " + exception.message());

            handleHttpStatusCode(response, exception.code());

            //AwsMock::JsonAPIErrorBuilder errorBuilder = AwsMock::JsonAPIErrorBuilder(request.getHost());

           /* errorBuilder.sourceAt(request.getURI());
            errorBuilder.withType(exception.type());
            errorBuilder.withStatusCode(exception.code());
            errorBuilder.withDetails(exception.message());

            std::ostream &errorStream = response.send();
            errorStream << errorBuilder.build().toString();

            errorStream.flush();*/
            return;
        }

        Poco::URI uri = Poco::URI(request.getURI());

        _requestURI = request.getURI();
        _requestHost = request.getHost();
        _baseUrl = "http://" + _requestHost + _requestURI;

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
            this->handleOptions(request, response);
        }

        if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_HEAD) {
            this->handleHead(request, response);
        }
    }

    void AbstractResource::handleGet(Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response,
                                     const std::string &region,
                                     const std::string &user) {
        poco_trace(_logger, "Request, method: " + request.getMethod() + " region: " + region + " user: " + user);
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handlePut(Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response,
                                     const std::string &region,
                                     const std::string &user) {
        poco_trace(_logger, "Request, method: " + request.getMethod() + " region: " + region + " user: " + user);
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handlePost(Poco::Net::HTTPServerRequest &request,
                                      Poco::Net::HTTPServerResponse &response,
                                      const std::string &region,
                                      const std::string &user) {
        poco_trace(_logger, "Request, method: " + request.getMethod() + " region: " + region + " user: " + user);
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handleDelete(Poco::Net::HTTPServerRequest &request,
                                        Poco::Net::HTTPServerResponse &response,
                                        const std::string &region,
                                        const std::string &user) {
        poco_trace(_logger, "Request, method: " + request.getMethod() + " region: " + region + " user: " + user);
        handleHttpStatusCode(response, 501);
        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handleOptions(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        poco_trace(_logger, "Request, method: " + request.getMethod());
        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
        );

        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    void AbstractResource::handleHead(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
        poco_trace(_logger, "Request, method: " + request.getMethod());
        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
        );

        std::ostream &errorStream = response.send();
        errorStream.flush();
    }

    Poco::JSON::Object::Ptr AbstractResource::getJsonAttributesSectionObject(const std::string &payload) {

        Poco::JSON::Parser jsonParser;
        Poco::Dynamic::Var parsingResult = jsonParser.parse(payload);
        auto jsonObject = parsingResult.extract<Poco::JSON::Object::Ptr>();

        if (jsonObject->isArray("data")) {
            throw HandlerException(Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                   "This payload can not be represented as a collection.",
                                   Poco::Net::HTTPResponse::HTTP_BAD_REQUEST
            );
        }

        //
        Poco::JSON::Object::Ptr dataObject = jsonObject->getObject("data");

        if (!dataObject->has("sqs")) {
            throw HandlerException(Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                   "The payload has no an 'sqs' section.",
                                   Poco::Net::HTTPResponse::HTTP_BAD_REQUEST
            );
        }

        return dataObject->getObject("sqs");

    }

    void AbstractResource::assertPayloadAttributes(
        const Poco::JSON::Object::Ptr &payloadObject, const std::list<std::string> &attributes) {

        for (auto const &attribute : attributes) {

            if (!payloadObject->has(attribute)) {
                throw HandlerException(
                    Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                    "One or more sqs are is missing at the payload.",
                    Poco::Net::HTTPResponse::HTTP_BAD_REQUEST
                );
            }
        }
    }

    void AbstractResource::handleHttpStatusCode(Poco::Net::HTTPServerResponse &response, int statusCode, const char *reason) {

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

        case 400:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            break;

        case 401:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            break;

        case 403:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_FORBIDDEN);
            break;

        case 404:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
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

        case 501:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED);
            break;

        case 503:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
            break;

            // Validating routines throw exceptions all over the program, but are not able to specify
            // an exception code compatible with HTTP. So, the code is left zero. This routine can catch this.
        default:response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            break;
        }
    }

    std::string AbstractResource::getUrl(const std::string &fragment) {
        return _baseUrl + fragment;
    }

    /*std::string AbstractResource::toJson(const HandlerException &exception) {
        AwsMock::JsonAPIErrorBuilder errorBuilder(_requestHost);

        errorBuilder.withType(exception.type());
        errorBuilder.sourceAt(_requestURI);
        errorBuilder.withStatusCode(exception.code());
        errorBuilder.withDetails(exception.message());

        return errorBuilder.build().toString();
    }

    std::string AbstractResource::toJson(const Core::ServiceException &exception) {
        AwsMock::JsonAPIErrorBuilder errorBuilder(_requestHost);

        errorBuilder.withType("Service");
        errorBuilder.sourceAt(_requestURI);
        errorBuilder.withStatusCode(exception.code());
        errorBuilder.withDetails(exception.message());

        return errorBuilder.build().toString();
    }

    std::string AbstractResource::toJson(const AwsMock::Core::ResourceNotFoundException &exception) {
        poco_error(_logger, "Exception: " + exception.message());

        AwsMock::JsonAPIErrorBuilder errorBuilder(_requestHost);

        errorBuilder.withType("Server exception");
        errorBuilder.sourceAt(_requestURI);
        errorBuilder.withStatusCode(500);
        errorBuilder.withDetails("Resource not found");

        return errorBuilder.build().toString();
    }*/

    std::string AbstractResource::GetQueryParameter(const std::string &parameterKey, bool optional) {

        auto iterator = std::find_if(_queryStringParameters.begin(), _queryStringParameters.end(),
                                     [&parameterKey](const std::pair<std::string, std::string> &item) {
                                       return item.first == parameterKey;
                                     }
        );

        if (iterator == _queryStringParameters.end()) {
            if (optional) {
                return {};
            } else {
                throw HandlerException(Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                                       "MessageAttribute '" + parameterKey + "' is missing at URL.",
                                       Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            }
        }
        return iterator->second;
    }

    bool AbstractResource::QueryParameterExists(const std::string &parameterKey) {

        auto iterator = std::find_if(_queryStringParameters.begin(), _queryStringParameters.end(),
                                     [&parameterKey](const std::pair<std::string, std::string> &item) {
                                       return item.first == parameterKey;
                                     }
        );

        return iterator != _queryStringParameters.end();
    }

    std::string AbstractResource::GetPathParameter(int pos) {
        return _pathParameter[pos];
    }

    void AbstractResource::GetRegionUser(const std::string &authorization, std::string &region, std::string &user) {
        Poco::RegularExpression::MatchVec posVec;

        Poco::RegularExpression pattern(R"(Credential=([a-zA-Z]+)\/[0-9]{8}\/([a-zA-Z0-9\-]+)\/[a-zA-Z0-9]+\/aws4_request,.*$)");
        if (!pattern.match(authorization, 0, posVec)) {
            throw Core::ResourceNotFoundException("Could not extract region and user");
        }

        user = authorization.substr(posVec[1].offset, posVec[1].length);
        region = authorization.substr(posVec[2].offset, posVec[2].length);
        poco_debug(_logger, "Found user: " + user + " region: " + region);
    }

    std::string AbstractResource::GetPayload(Poco::Net::HTTPServerRequest &request) {
        std::string payload;
        Poco::StreamCopier::copyToString(request.stream(), payload);
        poco_trace(_logger, "Request payload: " + payload);
        return payload;
    }

    void AbstractResource::SendOkResponse(Poco::Net::HTTPServerResponse &response, const std::string &payload, HeaderMap *extraHeader) {
        poco_trace(_logger, "Sending OK response, status: 200 payload: " + payload);

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

    void AbstractResource::SendOkResponse(Poco::Net::HTTPServerResponse &response, const std::string &fileName, long contentLength, HeaderMap *extraHeader) {
        poco_trace(_logger, "Sending OK response, status: 200, filename: " + fileName + " contentLength: " + std::to_string(contentLength));
        try {

            // Set headers
            SetHeaders(response, contentLength, extraHeader);

            std::ifstream ifs(fileName);

            // Send response
            handleHttpStatusCode(response, 200);
            std::ostream &outputStream = response.send();
            outputStream << ifs.rdbuf();
            outputStream.flush();
            ifs.close();

        } catch (Poco::Exception &exc) {
            poco_error(_logger, "Exception: " + exc.message());
        }
    }

    void AbstractResource::SendDeleteResponse(Poco::Net::HTTPServerResponse &response, HeaderMap *extraHeader) {
        poco_trace(_logger, "Sending DELETE response, status: 204");

        // Get content length
        unsigned long contentLength = 0;

        // Set headers
        SetHeaders(response, contentLength, extraHeader);

        // Send response
        handleHttpStatusCode(response, 204);
        std::ostream &outputStream = response.send();
        outputStream.flush();
    }

    void AbstractResource::SendErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Poco::Exception &exc) {

        Core::ServiceException serviceException = Core::ServiceException(exc.message(), exc.code());
        SendErrorResponse(service, response, serviceException);
    }

    void AbstractResource::SendErrorResponse(const std::string &service, Poco::Net::HTTPServerResponse &response, Core::ServiceException &exc) {

        std::string payload;
        if (service == "SQS") {
            payload = Dto::SQS::RestErrorResponse(exc).ToXml();
        } else if(service == "S3") {
            payload = Dto::S3::RestErrorResponse(exc).ToXml();
        }
        SetHeaders(response, payload.length());

        poco_error(_logger, "Exception, code: " + std::to_string(exc.code()) + " message: " + exc.message());
        handleHttpStatusCode(response, exc.code());
        std::ostream &outputStream = response.send();
        outputStream << payload;
        outputStream.flush();
    }

    void AbstractResource::SetHeaders(Poco::Net::HTTPServerResponse &response, unsigned long contentLength, HeaderMap *extraHeader) {
        poco_trace(_logger, "Setting header values, contentLength: " + std::to_string(contentLength));

        // Default headers
        response.set("Date", Poco::DateTimeFormatter::format(Poco::DateTime(), Poco::DateTimeFormat::HTTP_FORMAT));
        response.set("Content-Length", std::to_string(contentLength));
        response.set("Content-Type", "text/html; charset=utf-8");
        response.set("Connection", "close");
        response.set("Server", "AmazonS3");

        // Extra headers
        if (extraHeader != nullptr) {
            poco_trace(_logger, "Setting extra header values, count: " + std::to_string(extraHeader->size()));
            for (auto &it : *extraHeader) {
                response.set(it.first, it.second);
            }
        }
    }

    void AbstractResource::DumpRequest(Poco::Net::HTTPServerRequest &request) {
        poco_trace(_logger, "Dump request");
        std::cerr << "==================== Request =====================" << std::endl;
        request.write(std::cerr);
        std::cerr << "==================================================" << std::endl;
    }

    void AbstractResource::DumpResponse(Poco::Net::HTTPServerResponse &response) {
        poco_trace(_logger, "Dump response");
        std::cerr << "==================== Response ====================" << std::endl;
        response.write(std::cerr);
        std::cerr << "==================================================" << std::endl;
    }

    [[maybe_unused]] void AbstractResource::DumpBody(Poco::Net::HTTPServerRequest &request) {
        poco_trace(_logger, "Dump request body");
        std::cerr << "================== Request Body ==================" << std::endl;
        std::cerr << request.stream().rdbuf() << std::endl;
        std::cerr << "==================================================" << std::endl;
    }

    void AbstractResource::DumpBodyToFile(Poco::Net::HTTPServerRequest &request, const std::string &filename) {
        poco_trace(_logger, "Dump request body to file: " + filename);
        std::ofstream ofs(filename);
        ofs << request.stream().rdbuf();
        ofs.close();
    }
}
