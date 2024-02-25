//
// Created by vogje01 on 09/09/2023.
//

#ifndef AWS_MOCK_CORE_HTTP_UTILS_H
#define AWS_MOCK_CORE_HTTP_UTILS_H

// Standard C++ includes
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

// Poco includes
#include <Poco/RegularExpression.h>
#include <Poco/StreamCopier.h>
#include <Poco/Net/HTTPServerRequest.h>

// AwsMock includes
#include <awsmock/core/StringUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Core {

  /**
   * HTTP utilities.
   *
   * @author jens.vogt@opitz-consulting.com
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

  private:
    /**
     * Checks whether the query parameter value is URL encoded
     *
     * @param value HTTP query parameter
     * @return true if value is URL encoded
     */
    static bool IsUrlEncoded(const std::string &value);

  };

} // namespace AwsMock::Core

#endif // AWS_MOCK_CORE_HTTP_UTILS_H
