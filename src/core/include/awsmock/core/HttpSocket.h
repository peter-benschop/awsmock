//
// Created by vogje01 on 5/28/24.
//

#ifndef AWSMOCK_CORE_HTTP_SOCKET_H
#define AWSMOCK_CORE_HTTP_SOCKET_H

// C++ includes
#include <cstring>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <utility>

// Boost includes
#include <boost/asio.hpp>
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/HttpSocketResponse.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    namespace http = boost::beast::http;

    class HttpSocket {

      public:

        /**
         * @brief Constructor
         *
         * @param path domain socket path
         */
        explicit HttpSocket() = default;

        /**
         * @brief Send a JSON string to a HTTP endpoint
         *
         * @param method HTTP method
         * @param host HTTP host
         * @param port HTTP port
         * @param path URL path
         * @param body HTTP body
         * @param headers HTTP headers
         * @return HTTP response
         */
        static HttpSocketResponse SendJson(http::verb method, const std::string &host, int port, const std::string &path, const std::string &body = {}, const std::map<std::string, std::string> &headers = {});

        /**
         * @brief Send a binary to a HTTP endpoint
         *
         * This is usually a file to send ay application/octet-stream.
         *
         * @param method HTTP method
         * @param host HTTP host
         * @param port HTTP port
         * @param path URL path
         * @param filename name of the local file
         * @param headers HTTP headers
         * @return HTTP response
         */
        static HttpSocketResponse SendBinary(http::verb method, const std::string &host, int port, const std::string &filename, const std::string &body = {}, const std::map<std::string, std::string> &headers = {});

      private:

        /**
         * @brief Prepare HTTP message
         *
         * @param method HTTP method
         * @param host host to connect to
         * @param path URL path
         * @param body HTTP body
         * @param headers HTTP headers
         */
        static http::request<http::string_body> PrepareJsonMessage(http::verb method, const std::string &host, const std::string &path, const std::string &body, const std::map<std::string, std::string> &headers);

        /**
         * @brief Prepare HTTP message
         *
         * @param method HTTP method
         * @param path URL path
         * @param filename name of the file to send
         * @param headers HTTP headers
         */
        static http::request<http::file_body> PrepareBinaryMessage(http::verb method, const std::string &path, const std::string &filename, const std::map<std::string, std::string> &headers);

        /**
         * @brief Prepare HTTP response
         *
         * @param result HTTP response
         * @return result struct
         * @see Core::DomainSocketResult
         */
        static HttpSocketResponse PrepareResult(http::response<http::string_body> response);

        /**
         * @brief Prepare HTTP response
         *
         * @param result HTTP response
         * @return result struct
         * @see Core::DomainSocketResult
         */
        static HttpSocketResponse PrepareResult(http::response<http::dynamic_body> response);

        /**
         * Domain socket path
         */
        std::string _path;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_HTTP_SOCKET_H
