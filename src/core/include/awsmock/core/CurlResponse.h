//
// Created by vogje01 on 05/09/2023.
//

#ifndef AWS_MOCK_DTO_CURL_CURL_RESPONSE_H
#define AWS_MOCK_DTO_CURL_CURL_RESPONSE_H

// C++ includes
#include <sstream>
#include <string>

namespace AwsMock::Core {

    /**
   * Curl library response structure
   *
   * @author jens.vogt\@opitz-consulting.com
   */
    struct CurlResponse {

        /**
     * HTTP state code
     */
        int statusCode;

        /**
     * HTTP state reason
     */
        std::string statusReason;

        /**
     * Command output
     */
        std::string output;

        /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
        [[nodiscard]] std::string ToString() const {
            std::stringstream ss;
            ss << (*this);
            return ss.str();
        }

        /**
     * Stream provider.
     *
     * @return output stream
     */
        friend std::ostream &operator<<(std::ostream &os, const CurlResponse &r) {
            os << "CurlResponse={statusCode='" << r.statusCode << "', statusReason='" << r.statusReason << "', output='" << r.output << "'}";
            return os;
        }
    };

}// namespace AwsMock::Core

#endif// AWS_MOCK_DTO_CURL_CURL_RESPONSE_H
