//
// Created by vogje01 on 23/07/2023.
//

#include <awsmock/core/CurlUtils.h>

namespace AwsMock::Core {

    CurlUtils::CurlUtils() : _logger(Poco::Logger::get("CurlUtils")), _hostUri("http:/v1.24") {

        _isRemote = false;
        curl_global_init(CURL_GLOBAL_ALL);
        log_debug_stream(_logger) << "Curl utilities initialized" << std::endl;
    }

    CurlUtils::CurlUtils(std::string host) : _logger(Poco::Logger::get("DockerService")), _hostUri(std::move(host)) {
        curl_global_init(CURL_GLOBAL_ALL);
        _isRemote = true;
    }

    CurlUtils::~CurlUtils() {
        curl_global_cleanup();
    }

    std::string CurlUtils::SendRequest(const std::string &method, const std::string &path) {

        _readBuffer={};
        curl = curl_easy_init();
        if (!curl) {
            log_error_stream(_logger) << "Error while initiating curl" << std::endl;
            curl_global_cleanup();
            return {};
        }

        // Set headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set options
        curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, DOCKER_SOCKET);
        curl_easy_setopt(curl, CURLOPT_URL, (_hostUri + path).c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            log_error_stream(_logger) << "Request send failed, error: " << curl_easy_strerror(res) << std::endl;
        }

        unsigned status = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &status);

       // curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return _readBuffer;
    }

    std::string CurlUtils::SendRequest(const std::string &method, const std::string &path, const std::string &body) {

        _readBuffer={};
        curl = curl_easy_init();
        if (!curl) {
            log_error_stream(_logger) << "Error while initiating curl" << std::endl;
            curl_global_cleanup();
            return {};
        }

        // Set headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set options
        curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, DOCKER_SOCKET);
        curl_easy_setopt(curl, CURLOPT_URL, (_hostUri + path).c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_readBuffer);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            log_error_stream(_logger) << "Request send failed, error: " << curl_easy_strerror(res) << std::endl;
        }

        unsigned status = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &status);

        //curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return _readBuffer;
    }

    std::string CurlUtils::SendFileRequest(const std::string &method, const std::string &path, const std::string &header, const std::string &fileName) {

        _readBuffer={};
        curl = curl_easy_init();
        if (!curl) {
            log_error_stream(_logger) << "Error while initiating curl" << std::endl;
            curl_global_cleanup();
            return {};
        }

        FILE *fd;
        fd = fopen(fileName.c_str(), "rb");
        if(!fd) {
            return {};
        }

        /* to get the file size */
        struct stat fileInfo{};
        if(fstat(fileno(fd), &fileInfo) != 0)
            return {};

        // Set headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set options
        curl_easy_setopt(curl, CURLOPT_UNIX_SOCKET_PATH, DOCKER_SOCKET);
        curl_easy_setopt(curl, CURLOPT_URL, (_hostUri + path).c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &_readBuffer);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, fd);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fileInfo.st_size);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            log_error_stream(_logger) << "Request send failed, error: " << curl_easy_strerror(res) << std::endl;
        }

        unsigned status = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &status);

       // curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        return _readBuffer;
    }
}