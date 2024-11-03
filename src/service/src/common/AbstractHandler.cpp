
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
        response.set(http::field::keep_alive, "false");
        response.set(http::field::content_type, "application/json");
        response.set(http::field::date, Core::DateTimeUtils::HttpFormat());
        response.set(http::field::access_control_allow_origin, "*");
        response.set(http::field::access_control_allow_headers, "cache-control,content-type,x-amz-target,x-amz-user-agent");
        response.set(http::field::access_control_allow_methods, "GET,PUT,POST,DELETE,HEAD,OPTIONS");

        // Body
        boost::beast::ostream(response.body()) << body << std::endl;
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
        response.set(http::field::keep_alive, "false");
        response.set(http::field::content_type, "application/json");
        response.set(http::field::content_length, std::to_string(contentLength));
        response.set(http::field::date, Core::DateTimeUtils::HttpFormat());
        response.set(http::field::access_control_allow_origin, "*");
        response.set(http::field::access_control_allow_headers, "cache-control,content-type,x-amz-target,x-amz-user-agent");
        response.set(http::field::access_control_allow_methods, "GET,PUT,POST,DELETE,HEAD,OPTIONS");

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
        response.set(http::field::keep_alive, "false");
        response.set(http::field::content_type, "application/json");
        response.set(http::field::date, Core::DateTimeUtils::HttpFormat());
        response.set(http::field::access_control_allow_origin, "*");
        response.set(http::field::access_control_allow_headers, "cache-control,content-type,x-amz-target,x-amz-user-agent");
        response.set(http::field::access_control_allow_methods, "GET,PUT,POST,DELETE,HEAD,OPTIONS");

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

        // Prepare the response message
        http::response<http::dynamic_body> response;
        response.version(request.version());
        response.result(http::status::internal_server_error);
        response.set(http::field::server, "awsmock");
        response.set(http::field::keep_alive, "false");
        response.set(http::field::content_type, "application/json");
        response.set(http::field::date, Core::DateTimeUtils::HttpFormat());
        response.set(http::field::access_control_allow_origin, "*");
        response.set(http::field::access_control_allow_headers, "cache-control,content-type,x-amz-target,x-amz-user-agent");
        response.set(http::field::access_control_allow_methods, "GET,PUT,POST,DELETE,HEAD,OPTIONS");

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

    http::response<http::dynamic_body> AbstractHandler::SendBadRequestError(const http::request<http::dynamic_body> &request, const std::string &body, const std::map<std::string, std::string> &headers) {

        // Prepare the response message
        http::response<http::dynamic_body> response;
        response.version(request.version());
        response.result(http::status::bad_request);
        response.set(http::field::server, "awsmock");
        response.set(http::field::keep_alive, "false");
        response.set(http::field::content_type, "application/json");
        response.set(http::field::date, Core::DateTimeUtils::HttpFormat());
        response.set(http::field::access_control_allow_origin, "*");
        response.set(http::field::access_control_allow_headers, "cache-control,content-type,x-amz-target,x-amz-user-agent");
        response.set(http::field::access_control_allow_methods, "GET,PUT,POST,DELETE,HEAD,OPTIONS");

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
            response.set(http::field::keep_alive, "false");
            response.set(http::field::content_type, "application/octet-stream");
            response.set(http::field::date, Core::DateTimeUtils::HttpFormat());
            response.set(http::field::access_control_allow_origin, "*");
            response.set(http::field::access_control_allow_headers, "cache-control,content-type,x-amz-target,x-amz-user-agent");
            response.set(http::field::access_control_allow_methods, "GET,PUT,POST,DELETE,HEAD,OPTIONS");

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

}// namespace AwsMock::Service
