//
// Created by vogje01 on 23/07/2023.
//

#include <awsmock/core/CurlUtils.h>

namespace AwsMock::Core {

  CurlUtils::CurlUtils() : _logger(Poco::Logger::get("CurlUtils")) {}

  CurlResponse CurlUtils::SendUnixSocketRequest(const std::string &method, const std::string &path) {

    _readBuffer.clear();
    curl = curl_easy_init();
    if (!curl) {
      log_error_stream(_logger) << "Error while initiating curl" << std::endl;
      curl_easy_cleanup(curl);
      return {};
    }

    // Set headers
    headers = curl_slist_append(nullptr, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Set options
    curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, DOCKER_SOCKET);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_readBuffer);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      log_error_stream(_logger) << "Request send failed, url: " << path << " error: " << curl_easy_strerror(res) << std::endl;
    }

    int status = 0;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &status);

    CurlResponse response = {.statusCode = status, .statusReason=curl_easy_strerror(res), .output=_readBuffer};
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return response;
  }

  CurlResponse CurlUtils::SendUnixSocketRequest(const std::string &method, const std::string &path, const std::string &body) {

    _readBuffer.clear();
    curl = curl_easy_init();
    if (!curl) {
      log_error_stream(_logger) << "Error while initiating curl" << std::endl;
      curl_easy_cleanup(curl);
      return {};
    }

    // Set headers
    headers = curl_slist_append(nullptr, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Set options
    curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, DOCKER_SOCKET);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_readBuffer);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      log_error_stream(_logger) << "Request send failed, path: " << path << " error: " << curl_easy_strerror(res) << std::endl;
    }

    int status = 0;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &status);

    CurlResponse response = {.statusCode = status, .statusReason=curl_easy_strerror(res), .output=_readBuffer};
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return response;
  }

  CurlResponse CurlUtils::SendHttpRequest(const std::string &method, const std::string &path, const std::map<std::string, std::string> &extraHeaders, const std::string &body) {

    _readBuffer.clear();
    curl = curl_easy_init();
    if (!curl) {
      log_error_stream(_logger) << "Error while initiating curl" << std::endl;
      curl_easy_cleanup(curl);
      return {};
    }

    // Set headers
    headers = curl_slist_append(nullptr, "Accept: application/json");
    //headers = curl_slist_append(headers, "Content-Type: application/json");
    if (!extraHeaders.empty()) {
      for (const auto &it : extraHeaders) {
        headers = curl_slist_append(headers, (it.first + ": " + it.second).c_str());
      }
    }

    // Set options
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_readBuffer);
    //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    if (!body.empty()) {
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    }

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      log_error_stream(_logger) << "Request send failed, path: " << path << " error: " << curl_easy_strerror(res) << std::endl;
    }

    int status = 0;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &status);

    CurlResponse response = {.statusCode = status, .statusReason=curl_easy_strerror(res), .output=_readBuffer};
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);

    return response;
  }

  CurlResponse CurlUtils::SendUnixSocketFileRequest(const std::string &method, const std::string &path, const std::string &header, const std::string &fileName) {

    _readBuffer.clear();
    curl = curl_easy_init();
    if (!curl) {
      log_error_stream(_logger) << "Error while initiating curl" << std::endl;
      curl_easy_cleanup(curl);
      return {};
    }

    // Open file to send
    FILE *fd;
    fd = fopen(fileName.c_str(), "rb");
    if (!fd) {
      return {};
    }

    // Get the file size
    struct stat fileInfo{};
    if (fstat(fileno(fd), &fileInfo) != 0)
      return {};

    // Set headers
    headers = curl_slist_append(nullptr, "Accept: application/json");
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Set options
    curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, DOCKER_SOCKET);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_readBuffer);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, fd);
    curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t) fileInfo.st_size);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      log_error_stream(_logger) << "Request send failed, url: " << path << " error: " << curl_easy_strerror(res) << std::endl;
    }

    int status = 0;
    curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &status);
    CurlResponse response = {.statusCode = status, .statusReason=curl_easy_strerror(res), .output=_readBuffer};
    log_debug_stream(_logger) << "Request send to docker daemon, state: " << status << std::endl;

    // Cleanup
    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    fclose(fd);

    return response;
  }
}