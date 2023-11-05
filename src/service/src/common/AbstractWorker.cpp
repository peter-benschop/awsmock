//
// Created by vogje01 on 03/06/2023.
//

#include "awsmock/service/AbstractWorker.h"

namespace AwsMock::Service {

  AbstractWorker::AbstractWorker(const Core::Configuration &configuration)
      : _logger(Poco::Logger::get("AbstractWorker")), _configuration(configuration) {

    // Create environment
    _region = _configuration.getString("awsmock.region");
    _clientId = _configuration.getString("awsmock.client.id", "00000000");
    _user = _configuration.getString("awsmock.user", "none");

    log_debug_stream(_logger) << "AbstractWorker initialized" << std::endl;
  }

  void AbstractWorker::SendPostRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType) {

    Poco::URI uri(url);
    std::string path(uri.getPathAndQuery());

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPMessage::HTTP_1_1);
    request.add("Content-Type", contentType);
    AddAuthorization(module, request);
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

  void AbstractWorker::SendPutRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType) {

    Poco::URI uri(url);
    std::string path(uri.getPathAndQuery());

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, path, Poco::Net::HTTPMessage::HTTP_1_1);
    request.add("Content-Type", contentType);
    AddAuthorization(module, request);
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

  void AbstractWorker::SendDeleteRequest(const std::string &module, const std::string &url, const std::string &body, const std::string &contentType) {

    Poco::URI uri(url);
    std::string path(uri.getPathAndQuery());

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_DELETE, path, Poco::Net::HTTPMessage::HTTP_1_1);
    request.add("Content-Type", contentType);
    AddAuthorization(module, request);
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

  bool AbstractWorker::SendHeadRequest(const std::string &module, const std::string &url, const std::string &contentType) {

    Poco::URI uri(url);
    std::string path(uri.getPathAndQuery());

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_HEAD, path, Poco::Net::HTTPMessage::HTTP_1_1);
    request.add("Content-Type", contentType);
    AddAuthorization(module, request);
    log_debug_stream(_logger) << "HEAD request created, url: " << url << std::endl;

    // Send request
    session.sendRequest(request);

    // Get the response status
    Poco::Net::HTTPResponse response;
    log_debug_stream(_logger) << "HEAD head request send, status: " << response.getStatus() << std::endl;
    return response.getStatus() == Poco::Net::HTTPResponse::HTTP_OK;
  }

  void AbstractWorker::SendFile(const std::string &module, const std::string &url, const std::string &fileName, const std::map<std::string, std::string> &headers) {

    Poco::URI uri(url);
    std::string path(uri.getPathAndQuery());

    // Create HTTP request and set headers
    Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_PUT, path, Poco::Net::HTTPMessage::HTTP_1_1);
    for (const auto &it : headers) {
      request.add(it.first, it.second);
    }
    AddAuthorization(module, request);
    log_debug_stream(_logger) << "Request send, url: " << url << std::endl;

    // Send request
    std::ifstream ifs(fileName);
    std::ostream &os = session.sendRequest(request);
    long copied = Poco::StreamCopier::copyStream(ifs, os);
    log_debug_stream(_logger) << "Body send, file: " << fileName << " size: " << copied << std::endl;

    // Get the response status
    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);
    if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_OK) {
      log_error_stream(_logger) << "HTTP error, status: " + std::to_string(response.getStatus()) + " reason: " + response.getReason() << std::endl;
    }
    log_debug_stream(_logger) << "Send file request send, status: " << response.getStatus() << std::endl;
  }

  void AbstractWorker::AddAuthorization(const std::string &module, Poco::Net::HTTPRequest &request) {
    request.add("Authorization", Core::AwsUtils::GetAuthorizationHeader(_configuration, module));

  }

} // namespace AwsMock::Worker
