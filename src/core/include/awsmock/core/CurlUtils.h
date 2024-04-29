//
// Created by vogje01 on 23/07/2023.
//

#ifndef AWSMOCK_CORE_CURL_UTILS_H
#define AWSMOCK_CORE_CURL_UTILS_H

// C++ standard includes
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <utility>

// Curl includes
#include <curl/curl.h>

// AwsMock includes
#include <awsmock/core/CurlResponse.h>
#include <awsmock/core/LogStream.h>

#define DOCKER_SOCKET "/var/run/docker.sock"

typedef enum {
    GET,
    POST,
    DELETE,
    PUT
} Methods;

namespace AwsMock::Core {

    /**
     * CURL utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class CurlUtils {

      public:

        /**
         * Constructor
         */
        CurlUtils() = default;

        /**
         * Send request to a HTTP URL
         *
         * @param method HTTP method
         * @param path request path
         * @param extraHeaders header map
         * @param body request body
         * @return Dto::Curl::CurlResponse
         */
        CurlResponse SendHttpRequest(const std::string &method, const std::string &path, const std::map<std::string, std::string> &extraHeaders = {}, const std::string &body = {});

        /**
         * Send request to a HTTP URL
         *
         * @param method HTTP method
         * @param path request path
         * @param fileName name of the file to send
         * @param extraHeaders header map
         * @return Dto::Curl::CurlResponse
         */
        CurlResponse SendFileHttpRequest(const std::string &method, const std::string &path, const std::string &fileName, const std::map<std::string, std::string> &extraHeaders = {});

        /**
         * Send request
         *
         * @param method HTTP method
         * @param path request path
         * @return Dto::Curl::CurlResponse
         */
        CurlResponse SendUnixSocketRequest(const std::string &method, const std::string &path);

        /**
         * Send request
         *
         * @param method HTTP method
         * @param path request path
         * @param body request body
         * @return Dto::Curl::CurlResponse
         */
        CurlResponse SendUnixSocketRequest(const std::string &method, const std::string &path, const std::string &body);

        /**
         * Send a file request using unix sockets
         *
         * @param method HTTP method
         * @param path request path
         * @param header request extra headers
         * @param fileName filename to send as request body
         * @return Dto::Curl::CurlResponse
         */
        CurlResponse SendUnixSocketFileRequest(const std::string &method, const std::string &path, const std::string &header, const std::string &fileName);

      private:

        /**
         * Curl
         */
        CURL *curl{};

        /**
         * Curl response codes
         */
        CURLcode res{};

        /**
         * Host URI
         */
        std::string _apiVersion;

        /**
         * Curl headers
         */
        struct curl_slist *headers = nullptr;

        /**
         * Read buffer
         */
        std::string _readBuffer = {};

        /**
         * Write callback
         *
         * @param contents curl response string
         * @param size size of a single byte
         * @param nmemb number of bytes
         * @param userp user pointer
         * @return string containing message body
         */
        [[maybe_unused]] static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
            if (nmemb > 0) {
                static_cast<std::string *>(userp)->append((char *) contents, size * nmemb);
            }
            return size * nmemb;
        }
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_CURL_UTILS_H
