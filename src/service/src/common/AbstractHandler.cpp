
#include <awsmock/service/common/AbstractHandler.h>

namespace AwsMock::Service {

    http::response<http::dynamic_body> AbstractHandler::HandleGetRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::dynamic_body> AbstractHandler::HandlePutRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::dynamic_body> AbstractHandler::HandlePostRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::dynamic_body> AbstractHandler::HandleDeleteRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::dynamic_body> AbstractHandler::HandleHeadRequest(const http::request<http::dynamic_body> &request, const std::string &region, const std::string &user) {
        log_error << "Real method not implemented";
        return {};
    }

    http::response<http::dynamic_body> AbstractHandler::SendOkResponse(const http::request<http::dynamic_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::dynamic_body> response;
        response.version(request.version());
        response.result(http::status::ok);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");

        // Body
        boost::beast::ostream(response.body()) << body;
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

    http::response<http::dynamic_body> AbstractHandler::SendOkResponse(const http::request<http::dynamic_body> &request, const std::string &fileName, long contentLength, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::dynamic_body> response;
        response.version(request.version());
        response.result(http::status::ok);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");
        response.set(http::field::content_length, std::to_string(contentLength));

        // Body
        std::ifstream ifs(fileName);
        boost::beast::ostream(response.body()) << ifs.rdbuf();
        ifs.close();
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

    http::response<http::dynamic_body> AbstractHandler::SendNoContentResponse(const http::request<http::dynamic_body> &request, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::dynamic_body> response;
        response.version(request.version());
        response.result(http::status::no_content);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");

        // Copy headers
        if (!headers.empty()) {
            for (const auto &header: headers) {
                response.set(header.first, header.second);
            }
        }

        // Send the response to the client
        return response;
    }

    http::response<http::dynamic_body> AbstractHandler::SendInternalServerError(const http::request<http::dynamic_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        return Core::HttpUtils::InternalServerError(request, body);
    }

    http::response<http::dynamic_body> AbstractHandler::SendBadRequestError(const http::request<http::dynamic_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::dynamic_body> response;
        response.version(request.version());
        response.result(http::status::bad_request);
        response.set(http::field::server, "awsmock");
        response.set(http::field::content_type, "application/json");

        // Body
        boost::beast::ostream(response.body()) << body;
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

    http::response<http::dynamic_body> AbstractHandler::SendRangeResponse(const http::request<http::dynamic_body> &request, const std::string &fileName, long min, long max, long size, long totalSize, const http::status &status, const std::map<std::string, std::string> &headers) {
        log_trace << "Sending OK response, state: 200, filename: " << fileName << " min: " << min << " max: " << max << " size: " << size;

        if (!Core::MemoryMappedFile::instance().IsMapped()) {
            if (!Core::MemoryMappedFile::instance().OpenFile(fileName)) {
                log_error << "Could not open memory mapped file, filename: " << fileName;
                throw Core::ServiceException("Could not open memory mapped file, filename: " + fileName);
            }
        }

        try {

            // Prepare the response message
            http::response<http::dynamic_body> response;
            response.content_length(size);
            response.version(request.version());
            response.result(status);
            response.set(http::field::server, "awsmock");
            response.set(http::field::content_type, "application/octet-stream");

            // Body
            char *buffer = new char[size];
            Core::MemoryMappedFile::instance().ReadChunk(min, size, (char *) buffer);
            boost::beast::ostream(response.body()) << buffer;
            response.prepare_payload();
            delete[] buffer;

            // Copy headers
            if (!headers.empty()) {
                for (const auto &header: headers) {
                    response.set(header.first, header.second);
                }
            }

            // Close file
            if (max == totalSize - 1) {
                Core::MemoryMappedFile::instance().CloseFile();
                log_debug << "Memory mapped file closed, filename: " << fileName;
            }

            // Send the response to the client
            log_debug << "Range response finished, filename: " << fileName << " size: " << size << " status: " << status;
            return response;

        } catch (Poco::Exception &exc) {
            log_error << exc.message();
            return SendInternalServerError(request, exc.message());
        }
    }
    /*
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
