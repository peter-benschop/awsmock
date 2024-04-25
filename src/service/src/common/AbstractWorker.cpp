//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/common/AbstractWorker.h"

namespace AwsMock::Service {

    AbstractWorker::AbstractWorker(const Core::Configuration &configuration) : _configuration(configuration) {

        // Create environment
        _region = _configuration.getString("awsmock.region");
        _clientId = _configuration.getString("awsmock.client.userPoolId", "00000000");
        _user = _configuration.getString("awsmock.user", "none");

        log_debug << "AbstractWorker initialized";
    }

    void AbstractWorker::SendPostRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(module, request);
        log_debug << "Request send, url: " << url;

        // Send request
        std::ostream &os = session.sendRequest(request);
        if (!body.empty()) {
            os << body;
            os.flush();
        }

        // Get the response state
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "HTTP error, state: " + std::to_string(response.getStatus()) + " reason: " + response.getReason();
        }
        log_debug << "POST request send, state: " << response.getStatus();
    }

    void AbstractWorker::SendPutRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(module, request);
        log_debug << "Request send, url: " << url;

        // Send request
        if (body.empty()) {
            session.sendRequest(request);
        } else {
            std::ostream &os = session.sendRequest(request);
            os << body;
            os.flush();
            os.clear();
        }

        // Get the response state
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "HTTP error, state: " + std::to_string(response.getStatus()) + " reason: " + response.getReason();
        }
        log_debug << "PUT request send, state: " << response.getStatus();
    }

    void AbstractWorker::SendDeleteRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_DELETE, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(module, request);
        log_debug << "Request send, url: " << url;

        // Send request
        if (body.empty()) {
            session.sendRequest(request);
        } else {
            std::ostream &os = session.sendRequest(request);
            os << body;
            os.flush();
            os.clear();
        }

        // Get the response state
        Poco::Net::HTTPResponse response;
        if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
            log_error << "HTTP error, state: " + std::to_string(response.getStatus()) + " reason: " + response.getReason();
        }
        log_debug << "DELETE request send, state: " << response.getStatus();
    }

    bool AbstractWorker::SendHeadRequest(const std::string &module, const std::string &url, const std::string &contentType) {

        Poco::URI uri(url);
        std::string path(uri.getPathAndQuery());

        // Create HTTP request and set headers
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_HEAD, path, Poco::Net::HTTPMessage::HTTP_1_1);
        request.add("Content-Type", contentType);
        AddAuthorization(module, request);
        log_debug << "HEAD request created, url: " << url;

        // Send request
        session.sendRequest(request);

        // Get the response state
        Poco::Net::HTTPResponse response;
        log_debug << "HEAD head request send, state: " << response.getStatus();
        return response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK;
    }

    void AbstractWorker::SendFile(const std::string &module, const std::string &url, const std::string &fileName, const std::map<std::string, std::string> &headers) {

        try {
            Core::CurlUtils curlUtils;
            Core::CurlResponse response = curlUtils.SendFileHttpRequest("PUT", url, fileName, headers);
            if (response.statusCode != 200) {
                log_error << "Send file failed, fileName: " << fileName << " status: " << response.statusCode << " output: " << response.output << std::endl;
            }

            // Setup the URI
            /*Poco::URI uri(url);
      std::string path(uri.getPathAndQuery());

      // Create session, timeout 900sec.
      Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
      session.setTimeout(900);
      session.setSendTimeout(900);
      session.setReceiveTimeout(900);

      // Get the content length
      long contentLength = Core::FileUtils::FileSize(fileName);

      // Create HTTP request and set headers
      Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, path, Poco::Net::HTTPMessage::HTTP_1_1);
      request.setChunkedTransferEncoding(true);
      for (const auto &it : headers) {
        request.add(it.first, it.second);
      }
      AddAuthorization(module, request);
      log_debug<< "Request send, url: " << url;

      // Send request
      std::ifstream ifs(fileName);
      std::ostream &os = session.sendRequest(request);
      long copied = Poco::StreamCopier::copyStream(ifs, os);
      log_debug<< "Body send, file: " << fileName << " size: " << copied;

      // Get the response state
      Poco::Net::HTTPResponse response;
      session.receiveResponse(response);
      if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
        log_error << "HTTP error, state: " + std::to_string(response.getStatus()) + " reason: " + response.getReason();
      }
      log_debug<< "Send file request send, state: " << response.getStatus();*/

        } catch (Poco::Exception &exc) {
            log_error << "Send file failed, fileName: " << fileName << " error: " << exc.message();
        }
    }

    void AbstractWorker::AddAuthorization(const std::string &module, Poco::Net::HTTPRequest &request) {
        request.add("Authorization", Core::AwsUtils::GetAuthorizationHeader(_configuration, module));
    }

}// namespace AwsMock::Service
