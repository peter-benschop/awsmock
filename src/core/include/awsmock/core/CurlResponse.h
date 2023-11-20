//
// Created by vogje01 on 05/09/2023.
//

#ifndef AWSMOCK_DTO_CURL_CURLRESPONSE_H
#define AWSMOCK_DTO_CURL_CURLRESPONSE_H

// C++ includes
#include <string>
#include <sstream>

namespace AwsMock::Core {

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
      os << "CurlResponse={statusCode='" << r.statusCode << "' statusReason='" << r.statusReason << "' output='" << r.output << "'}";
      return os;
    }
  };

} // namespace AwsMock::Dto::Curl
#endif // AWSMOCK_DTO_CURL_CURLRESPONSE_H
