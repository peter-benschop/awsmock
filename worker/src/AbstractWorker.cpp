//
// Created by vogje01 on 03/06/2023.
//

#include <awsmock/worker/AbstractWorker.h>

namespace AwsMock::Worker {

    AbstractWorker::AbstractWorker(const Core::Configuration &configuration)
        : _logger(Poco::Logger::get("AbstractWorker")), _configuration(configuration) {

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _clientId = _configuration.getString("awsmock.client.id", "00000000");
        _user = _configuration.getString("awsmock.user", "none");

        log_debug_stream(_logger) << "AbstractWorker initialized" << std::endl;
    }

    void AbstractWorker::SendPostRequest(const std::string &url, const std::string &body, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "Request send, url: " << url << std::endl;

        // Send request
        if (body.empty()) {
            session.sendRequest(request);
        } else {
            std::ostream &os = session.sendRequest(request);
            os << body;
            os.flush();
            os.clear();
        }

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "POST request send, status: " << response.getStatus() << std::endl;

    }

    void AbstractWorker::SendPutRequest(const std::string &url, const std::string &body, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "Request send, url: " << url << std::endl;

        // Send request
        if (body.empty()) {
            session.sendRequest(request);
        } else {
            std::ostream &os = session.sendRequest(request);
            os << body;
            os.flush();
            os.clear();
        }

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "PUT request send, status: " << response.getStatus() << std::endl;

    }

    void AbstractWorker::SendDeleteRequest(const std::string &url, const std::string &body, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_DELETE, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "Request send, url: " << url << std::endl;

        // Send request
        if (body.empty()) {
            session.sendRequest(request);
        } else {
            std::ostream &os = session.sendRequest(request);
            os << body;
            os.flush();
            os.clear();
        }

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "DELETE request send, status: " << response.getStatus() << std::endl;
    }

    bool AbstractWorker::SendHeadRequest(const std::string &url, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_HEAD, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(request);
        log_debug_stream(_logger) << "HEAD request created, url: " << url << std::endl;

        // Send request
        session.sendRequest(request);

        // Get the response status
        Poco::Net::HTTPResponse response;
        log_debug_stream(_logger) << "HEAD head request send, status: " << response.getStatus() << std::endl;
        return response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK;
    }

    void AbstractWorker::SendFile(const std::string &url,
                                  const std::ifstream &ifstream,
                                  const std::string &contentType,
                                  const std::map<std::string, std::string> &headers) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        for (const auto &it : headers) {
            request.add(it.first, it.second);
        }
        AddAuthorization(request);
        log_debug_stream(_logger) << "Request send, url: " << url << std::endl;

        // Send request
        std::ostream &os = session.sendRequest(request);
        os << ifstream.rdbuf();
        os.flush();
        os.clear();

        // Get the response status
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
        }
        log_debug_stream(_logger) << "Send file request send, status: " << response.getStatus() << std::endl;
    }

    void AbstractWorker::AddAuthorization(Poco::Net::HTTPRequest &request) {
        request.add("Authorization",
                    "AWS4-HMAC-SHA256 Credential=" + _user + "/" + _clientId + "/" + _region
                        + "/s3/aws4_request, SignedHeaders=host;x-amz-date;x-amz-security-token, Signature=90d0e45560fa4ce03e6454b7a7f2a949e0c98b46c35bccb47f666272ec572840");

    }

} // namespace AwsMock::Worker
