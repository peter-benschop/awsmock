
#include <awsmock/service/common/AbstractHandler.h>

namespace AwsMock::Service {

    http::response<http::string_body> AbstractHandler::HandleGetRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::string_body> AbstractHandler::HandlePutRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::string_body> AbstractHandler::HandlePostRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::string_body> AbstractHandler::HandleDeleteRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::string_body> AbstractHandler::HandleHeadRequest(const http::request<http::string_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::string_body> AbstractHandler::SendOkResponse(const http::request<http::string_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::string_body> response;
        response.version(request.version());
        response.result(http::status::ok);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");
        response.body() = body;
        response.prepare_payload();

        // Copy headers
        if (!headers.empty()) {
            for (const auto &header: headers) {
                response.set(header.first, header.second);
            }
        }

        // Send the response to the client
        return response;
    }

    http::response<http::string_body> AbstractHandler::SendNoContentResponse(const http::request<http::string_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::string_body> response;
        response.version(request.version());
        response.result(http::status::no_content);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");
        response.body() = body;
        response.prepare_payload();

        // Copy headers
        if (!headers.empty()) {
            for (const auto &header: headers) {
                response.set(header.first, header.second);
            }
        }

        // Send the response to the client
        return response;
    }

    http::response<http::string_body> AbstractHandler::SendInternalServerError(const http::request<http::string_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::string_body> response;
        response.version(request.version());
        response.result(http::status::internal_server_error);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");
        response.body() = body;
        response.prepare_payload();

        // Copy headers
        if (!headers.empty()) {
            for (const auto &header: headers) {
                response.set(header.first, header.second);
            }
        }

        // Send the response to the client
        return response;
    }

    http::response<http::string_body> AbstractHandler::SendBadRequestError(const http::request<http::string_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::string_body> response;
        response.version(request.version());
        response.result(http::status::bad_request);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");
        response.body() = body;
        response.prepare_payload();

        // Copy headers
        if (!headers.empty()) {
            for (const auto &header: headers) {
                response.set(header.first, header.second);
            }
        }

        // Send the response to the client
        return response;
    }

    /*    void AbstractHandler::SendRangeResponse(Poco::Net::HTTPServerResponse &response, const std::string &fileName, long min, long max, long size, const HeaderMap &extraHeader) {
        log_trace << "Sending OK response, state: 200, filename: " << fileName << " min: " << min << " max: " << max << " size: " << size;

        if (!Core::MemoryMappedFile::instance().IsMapped()) {
            if (!Core::MemoryMappedFile::instance().OpenFile(fileName)) {
                throw Core::ServiceException("Could not open memory mapped file");
            }
        }

        try {

            // Set headers
            long contentLength = max - min;
            if (contentLength > size) {
                contentLength = size - min;
            }
            SetHeaders(response, contentLength, extraHeader);

            // Set state
            handleHttpStatusCode(response, Poco::Net::HTTPResponse::HTTP_OK);

            // Send response
            std::ostream &os = response.send();

            // Send body
            char *buffer = new char[contentLength + 1];
            Core::MemoryMappedFile::instance().ReadChunk(min, contentLength, (char *) buffer);
            os.write(buffer, contentLength);
            os.flush();
            delete[] buffer;

            // Close file
            if (max >= size) {
                Core::MemoryMappedFile::instance().CloseFile();
            }

        } catch (Poco::Exception &exc) {
            log_error << "Exception: " << exc.message();
            throw Core::ServiceException("Bad request, send range response, exception: " + exc.message());
        }
    }
*/
    /*    void AbstractHandler::SendHeadResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
        log_trace << "Sending Head response, state: 200";
        try {

            // Set headers
            // Extra headers
            if (!extraHeader.empty()) {
                log_trace << "Setting extra header values, count: " << extraHeader.size();
                for (auto &it: extraHeader) {
                    response.set(it.first, it.second);
                }
            }

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
*/
    /* void AbstractHandler::SendDeleteResponse(Poco::Net::HTTPServerResponse &response, const HeaderMap &extraHeader) {
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

    void AbstractHandler::SendErrorResponse(Poco::Net::HTTPServerResponse &response, const std::string &body, const std::map<std::string, std::string> &headers, int status) {

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
            //payload = Dto::S3::RestErrorResponse(exc).ToJsonObject();
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
        response.set("Handler", "awsmock");

        // Extra headers
        if (!extraHeader.empty()) {
            log_trace << "Setting extra header values, count: " << extraHeader.size();
            for (auto &it: extraHeader) {
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
        log_trace << "==================== Request =====================";
        request.write(std::cerr);
        log_trace << "==================================================";
    }

    void AbstractHandler::DumpRequestHeaders(Poco::Net::HTTPServerRequest &request) {
        log_trace << "Dump request headers";
        log_trace << "================ Request Headers =================";
        for (const auto &h: request) {
            log_trace << h.first << ": " << h.second;
        }
        log_trace << "==================================================";
    }

    void AbstractHandler::DumpResponseHeaders(Poco::Net::HTTPServerResponse &response) {
        log_trace << "Dump response headers";
        log_trace << "============== Response Headers ==================";
        for (const auto &h: response) {
            log_trace << h.first << ": " << h.second;
        }
        log_trace << "==================================================";
    }

    void AbstractHandler::DumpResponse(Poco::Net::HTTPServerResponse &response) {
        log_trace << "Dump response";
        log_trace << "==================== Response ====================";
        response.write(std::cerr);
        log_trace << "==================================================";
    }

    [[maybe_unused]] void AbstractHandler::DumpBody(Poco::Net::HTTPServerRequest &request) {
        log_trace << "Dump request body";
        log_trace << "================== Request Body ==================";
        log_trace << request.stream().rdbuf();
        log_trace << "==================================================";
    }

    [[maybe_unused]] void AbstractHandler::DumpPayload(const std::string &payload) {
        log_trace << "Dump request body";
        log_trace << "================== Request Body ==================";
        log_trace << payload;
        log_trace << "==================================================";
    }

    void AbstractHandler::DumpBodyToFile(Poco::Net::HTTPServerRequest &request, const std::string &filename) {
        log_trace << "Dump request body to file: " + filename;
        std::ofstream ofs(filename);
        ofs << request.stream().rdbuf();
        ofs.close();
    }*/
}// namespace AwsMock::Service
