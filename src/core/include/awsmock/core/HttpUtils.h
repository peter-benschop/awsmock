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

// AwsMock includes
#include <awsmock/core/LogStream.h>
#include <awsmock/core/ServiceException.h>
#include <awsmock/core/StringUtils.h>

namespace AwsMock::Core {

    /**
     * HTTP utilities.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    class HttpUtils {

      public:

        /**
         * Returns the base path of the URI.
         *
         * <p>Removes leading '/'.</p>
         *
         * @param uri HTTP request URI
         * @return base path of the HTTP request URI
         */
        static std::string GetBasePath(const std::string &uri);

        /**
         * Returns a given path parameter by index.
         *
         * @param uri HTTP request URI
         * @param index path parameter index
         * @return path parameter with given index.
         */
        static std::string GetPathParameter(const std::string &uri, int index);

        /**
         * Get the rest of the path after index.
         *
         * @param uri HTTP request URI
         * @param index path parameter index
         * @return rest of the path after index
         */
        static std::string GetPathParametersFromIndex(const std::string &uri, int index);

        /**
         * Returns all path parameters.
         *
         * @param uri HTTP request URI
         * @return path parameters vector.
         */
        static std::vector<std::string> GetPathParameters(const std::string &uri);

        /**
         * Checks whether the path parameter at index exists
         *
         * @param uri HTTP request URI
         * @param index path index
         * @return path parameters vector.
         */
        static bool HasPathParameters(const std::string &uri, int index);

        /**
         * Returns the query string
         *
         * @param uri HTTP request URI
         * @return query string of the HTTP request URI
         */
        static std::string GetQueryString(const std::string &uri);

        /**
         * Count parameters
         *
         * @param uri HTTP request URI
         * @return number of query parameters
         */
        static int CountQueryParameters(const std::string &uri);

        /**
         * Count parameters by name prefix
         *
         * @param uri HTTP request URI
         * @param prefix HTTP parameter prefix
         * @return number of query parameters
         */
        static int CountQueryParametersByPrefix(const std::string &uri, const std::string &prefix);

        /**
         * Returns the parameter value by prefix with the given index
         *
         * @param uri HTTP request URI
         * @param prefix HTTP parameter prefix
         * @param index path parameter index
         * @return number of query parameters
         */
        static std::string GetQueryParameterByPrefix(const std::string &uri, const std::string &prefix, int index);

        /**
         * Adds a bool query parameter to the given URL.
         *
         * @param url url to add to
         * @param name parameter name
         * @param value parameter value
         * @return
         */
        static std::string AddQueryParameter(std::string &url, const std::string &name, bool value);

        /**
         * Adds a string query parameter to the given URL.
         *
         * @param url url to add to
         * @param name parameter name
         * @param value parameter value
         * @return
         */
        static std::string AddQueryParameter(std::string &url, const std::string &name, const std::string &value);

        /**
         * Adds a integer query parameter to the given URL.
         *
         * @param url url to add to
         * @param name parameter name
         * @param value parameter value
         * @return
         */
        static std::string AddQueryParameter(std::string &url, const std::string &name, int value);

        /**
         * Returns an integer parameter
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
         * Returns the name of a query parameter.
         *
         * @param parameter parameter in the form name=value
         * @return name of the parameter
         */
        static std::string GetQueryParameterName(const std::string &parameter);

        /**
         * Returns the value of a query parameter.
         *
         * <p> if the value is URL encoded, the value will be decoded.</p>
         *
         * @param parameter parameter in the form name=value
         * @return value of the parameter
         */
        static std::string GetQueryParameterValue(const std::string &parameter);

        /**
         * Returns a vector of query parameter with the given index.
         *
         * @param uri HTTP request URI
         * @param prefix HTTP parameter prefix
         * @return vector of parameters
         */
        static std::vector<std::string> GetQueryParametersByPrefix(const std::string &uri, const std::string &prefix);

        /**
         * Returns the parameter value by prefix with the given index
         *
         * @param uri HTTP request URI
         * @param name HTTP parameter name
         * @return number of query parameters
         */
        static std::string GetQueryParameterValueByName(const std::string &uri, const std::string &name);

        /**
         * Checks for existence of parameter with the given name.
         *
         * @param uri HTTP request URI
         * @param name HTTP parameter name
         * @return true if parameter exists
         */
        static bool HasQueryParameter(const std::string &uri, const std::string &name);

        /**
         * Gets the version and action from an URI.
         *
         * @param uri HTTP request URI
         * @param version AWS request version
         * @param action AWS action
         */
        static void GetVersionAction(const std::string &uri, std::string &version, std::string &action);

        /**
         * Gets the version and action from an URI.
         *
         * @param request HTTP serer request
         * @return HTTP body as string
         */
        static std::string GetBodyAsString(Poco::Net::HTTPServerRequest &request);

        /**
         * Returns a header value by key.
         *
         * <p>
         * Returns an empty string and logs a warning message, in case the request has no value for the given key.
         * </p>
         *
         * @param request HTTP request
         * @param key header key
         * @return header value of empty string.
         */
        [[maybe_unused]] static std::string GetHeaderValue(const Poco::Net::HTTPRequest &request, const std::string &key);

      private:

        /**
         * Checks whether the query parameter value is URL encoded
         *
         * @param value HTTP query parameter
         * @return true if value is URL encoded
         */
        static bool IsUrlEncoded(const std::string &value);

        /**
         * Add query delimiter
         *
         * @param uri HTTP request URL
         * @return URL with delimiter
         */
        static std::string AddQueryDelimiter(std::string &url);
    };

}// namespace AwsMock::Core

#endif// AWS_MOCK_CORE_HTTP_UTILS_H
