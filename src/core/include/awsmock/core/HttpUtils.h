//
// Created by vogje01 on 09/09/2023.
//

#ifndef AWS_MOCK_CORE_HTTP_UTILS_H
#define AWS_MOCK_CORE_HTTP_UTILS_H

// Standard C++ includes
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/RegularExpression.h>
#include <Poco/StreamCopier.h>

// Boost includes
#include <boost/asio.hpp>
#include <boost/beast.hpp>

// AwsMock includes
#include <awsmock/core/HttpSocketResponse.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/exception/ServiceException.h>

namespace AwsMock::Core {

    namespace http = boost::beast::http;

    /**
     * @brief HTTP utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class HttpUtils {

      public:

        /**
         * Returns the base path of the URI.
         *
         * @brief <p>Removes leading '/'.</p>
         *
         * @param uri HTTP request URI
         * @return base path of the HTTP request URI
         */
        static std::string GetBasePath(const std::string &uri);

        /**
         * @brief Returns a given path parameter by index.
         *
         * @param uri HTTP request URI
         * @param index path parameter index
         * @return path parameter with given index.
         */
        static std::string GetPathParameter(const std::string &uri, int index);

        /**
         * @brief Get the rest of the path after index.
         *
         * @param uri HTTP request URI
         * @param index path parameter index
         * @return rest of the path after index
         */
        static std::string GetPathParametersFromIndex(const std::string &uri, int index);

        /**
         * @brief Returns all path parameters.
         *
         * @param uri HTTP request URI
         * @return path parameters vector.
         */
        static std::vector<std::string> GetPathParameters(const std::string &uri);

        /**
         * @brief Checks whether the path parameter at index exists
         *
         * @param uri HTTP request URI
         * @param index path index
         * @return path parameters vector.
         */
        static bool HasPathParameters(const std::string &uri, int index);

        /**
         * @brief Returns the query string
         *
         * @param uri HTTP request URI
         * @return query string of the HTTP request URI
         */
        static std::string GetQueryString(const std::string &uri);

        /**
         * @brief Count parameters
         *
         * @param uri HTTP request URI
         * @return number of query parameters
         */
        static int CountQueryParameters(const std::string &uri);

        /**
         * @brief Count parameters by name prefix
         *
         * @param uri HTTP request URI
         * @param prefix HTTP parameter prefix
         * @return number of query parameters
         */
        static int CountQueryParametersByPrefix(const std::string &uri, const std::string &prefix);

        /**
         * @brief Returns the parameter value by prefix with the given index
         *
         * @param uri HTTP request URI
         * @param prefix HTTP parameter prefix
         * @param index path parameter index
         * @return number of query parameters
         */
        static std::string GetQueryParameterByPrefix(const std::string &uri, const std::string &prefix, int index);

        /**
         * @brief Adds a bool query parameter to the given URL.
         *
         * @param url url to add to
         * @param name parameter name
         * @param value parameter value
         * @return
         */
        static std::string AddQueryParameter(std::string &url, const std::string &name, bool value);

        /**
         * @brief Adds a string query parameter to the given URL.
         *
         * @param url url to add to
         * @param name parameter name
         * @param value parameter value
         * @return
         */
        static std::string AddQueryParameter(std::string &url, const std::string &name, const std::string &value);

        /**
         * @brief Adds a integer query parameter to the given URL.
         *
         * @param url url to add to
         * @param name parameter name
         * @param value parameter value
         * @return
         */
        static std::string AddQueryParameter(std::string &url, const std::string &name, int value);

        /**
         * @brief Returns an integer parameter
         *
         * @param body HTTP body
         * @param name parameter name
         * @param min minimum value
         * @param max maximum value
         * @param def default value
         * @return integer parameter
         */
        static int GetIntParameter(const std::string &body, const std::string &name, int min, int max, int def);

        /**
         * @brief Returns the name of a query parameter.
         *
         * @param parameter parameter in the form name=value
         * @return name of the parameter
         */
        static std::string GetQueryParameterName(const std::string &parameter);

        /**
         * @brief Returns the value of a query parameter.
         *
         * <p> if the value is URL encoded, the value will be decoded.</p>
         *
         * @param parameter parameter in the form name=value
         * @return value of the parameter
         */
        static std::string GetQueryParameterValue(const std::string &parameter);

        /**
         * @brief Returns a map of all query parameters.
         *
         * The resulting name/value pairs are not URL decoded.
         *
         * @param uri HTTP request URI
         * @return map of query parameters
         */
        static std::map<std::string, std::string> GetQueryParameters(const std::string &uri);

        /**
         * @brief Returns a vector of query parameter with the given index.
         *
         * @param uri HTTP request URI
         * @param prefix HTTP parameter prefix
         * @return vector of parameters
         */
        static std::vector<std::string> GetQueryParametersByPrefix(const std::string &uri, const std::string &prefix = {});

        /**
         * @brief Returns the parameter value by prefix with the given index
         *
         * @param uri HTTP request URI
         * @param name HTTP parameter name
         * @return number of query parameters
         */
        static std::string GetQueryParameterValueByName(const std::string &uri, const std::string &name);

        /**
         * @brief Checks for existence of parameter with the given name.
         *
         * @param uri HTTP request URI
         * @param name HTTP parameter name
         * @return true if parameter exists
         */
        static bool HasQueryParameter(const std::string &uri, const std::string &name);

        /**
         * @brief Gets the version and action from an URI.
         *
         * @param uri HTTP request URI
         * @param version AWS request version
         * @param action AWS action
         */
        static void GetVersionAction(const std::string &uri, std::string &version, std::string &action);

        /**
         * @brief Gets the version and action from an URI.
         *
         * @param request HTTP serer request
         * @return HTTP body as string
         */
        static std::string GetBodyAsString(const http::request<http::string_body> &request);

        /**
         * @brief Gets the body as string from a boost dynamic_body
         *
         * @param request HTTP serer request
         * @return HTTP body as string
         */
        static std::string GetBodyAsString(const http::request<http::dynamic_body> &request);

        /**
         * @brief Checks whether a header exists.
         *
         * @param request HTTP request
         * @param key header key
         * @return header value of empty string.
         */
        static bool HasHeader(const http::request<http::dynamic_body> &request, const std::string &key);

        /**
         * @brief Returns a header value by key.
         *
         * <p>
         * Returns an empty string and logs a warning message, in case the request has no value for the given key.
         * </p>
         *
         * @param request HTTP request
         * @param key header key
         * @return header value of empty string.
         */
        static std::string GetHeaderValue(const Poco::Net::HTTPRequest &request, const std::string &key);

        /**
         * @brief Returns a header value by key.
         *
         * <p>
         * Returns the default value, if existent, otherwise logs a warning message, in case the request has no value for the given key.
         * </p>
         *
         * @param request HTTP request
         * @param key header key
         * @param defaultValue returned when the key was not found
         * @return header value of empty string.
         */
        static std::string GetHeaderValue(const http::request<http::dynamic_body> &request, const std::string &key, const std::string &defaultValue = {});

        /**
         * @brief Returns a header value by key.
         *
         * <p>
         * Returns the default value, if existent, otherwise logs a warning message, in case the request has no value for the given key.
         * </p>
         *
         * @param request HTTP request
         * @param key header key
         * @param defaultValue returned when the key was not found
         * @return header value of empty string.
         */
        static std::string GetHeaderValue(const http::request<http::string_body> &request, const std::string &key, const std::string &defaultValue = {});

        /**
         * @brief Returns the headers as a map of strings
         *
         * @param request HTTP request
         * @return map of strings
         */
        static std::map<std::string, std::string> GetHeaders(const Poco::Net::HTTPRequest &request);

        /**
         * @brief Returns the headers as a map of strings
         *
         * @param request HTTP request
         * @return map of strings
         */
        static std::map<std::string, std::string> GetHeaders(const http::request<http::dynamic_body> &request);

        /**
         * @brief Dumps the headers to the logger as info messages
         *
         * @param request HTTP request
         */
        static void DumpHeaders(const http::request<http::dynamic_body> &request);

        /**
         * @brief Returns the content type
         *
         * @param request HTTP request
         * @return reduced content type, either 'json' or 'xml.
         */
        static std::string GetContentType(const Poco::Net::HTTPRequest &request);

        /**
         * @brief Returns the content type
         *
         * @param request HTTP request
         * @return reduced content type, either 'json' or 'xml.
         */
        static std::string GetContentType(const http::request<http::dynamic_body> &request);

        /**
         * @brief Returns the content length
         *
         * @param request HTTP request
         * @return content length in bytes
         */
        static long GetContentLength(const Poco::Net::HTTPRequest &request);

        /**
         * @brief Returns the content length
         *
         * @param request HTTP request
         * @return content length in bytes
         */
        static long GetContentLength(const http::request<http::dynamic_body> &request);

      private:

        /**
         * @brief Checks whether the query parameter value is URL encoded
         *
         * @param value HTTP query parameter
         * @return true if value is URL encoded
         */
        static bool IsUrlEncoded(const std::string &value);

        /**
         * @brief Add query delimiter
         *
         * @param url HTTP request URL
         * @return URL with delimiter
         */
        static std::string AddQueryDelimiter(std::string &url);
    };

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_HTTP_UTILS_H
