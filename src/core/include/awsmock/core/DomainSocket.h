//
// Created by vogje01 on 5/28/24.
//

#ifndef AWSMOCK_CORE_DOMAIN_SOCKET_H
#define AWSMOCK_CORE_DOMAIN_SOCKET_H

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
#include <awsmock/core/DomainSocketResult.h>
#include <awsmock/core/LogStream.h>

namespace AwsMock::Core {

    namespace http = boost::beast::http;

    class DomainSocket {

      public:

        /**
         * @brief Constructor
         *
         * @param path domain socket path
         */
        explicit DomainSocket(std::string path) : _path(std::move(path)){};

        /**
         * @brief Send JSON data
         *
         * This will send a JSON string as boost http request to the domain socket and waits for the response. The call is synchronous and the response is converted
         * to boost http response.
         *
         * @param method HTTP method
         * @param path URL path
         * @param body optional HTTP body
         * @param headers optional HTTP headers
         * @return result struct
         * @see Core::DomainSocketResult
         */
        DomainSocketResult SendJson(http::verb method, const std::string &path, const std::string &body = {}, const std::map<std::string, std::string> &headers = {});

        /**
         * @brief Send binary data
         *
         * This will send a file as boost http request to the domain socket and waits for the response. The call is synchronous and the response is converted
         * to boost http response.
         *
         * @param method HTTP method
         * @param path URL path
         * @param body optional HTTP body
         * @param headers optional HTTP headers
         * @return result struct
         * @see Core::DomainSocketResult
         */
        DomainSocketResult SendBinary(http::verb method, const std::string &path, const std::string &fileName, const std::map<std::string, std::string> &headers = {});

      private:

        /**
         * @brief Prepare HTTP message
         *
         * @param method HTTP method
         * @param path URL path
         * @param body HTTP body
         * @param headers HTTP headers
         */
        static http::request<http::string_body> PrepareJsonMessage(http::verb method, const std::string &path, const std::string &body, const std::map<std::string, std::string> &headers);

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
         * @brief Prepare HTTP message
         *
         * @param result HTTP response
         * @return result struct
         * @see Core::DomainSocketResult
         */
        static DomainSocketResult PrepareResult(http::response<http::string_body> response);

        /**
         * Domain socket path
         */
        std::string _path;
    };

}// namespace AwsMock::Core

#endif// AWSMOCK_CORE_DOMAIN_SOCKET_H
