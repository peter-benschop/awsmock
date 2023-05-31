//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_COMMON_RESTERRORRESPONSE_H
#define AWSMOCK_DTO_COMMON_RESTERRORRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>

// Poco includes
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"

namespace AwsMock::Dto::Common {

    class RestErrorResponse {

    public:

      /**
       * Constructor
       *
       * @param code error code
       * @param message error message
       * @param resource resource name
       * @param requestId request ID
       */
      RestErrorResponse(const std::string &code, const std::string &message, const std::string &resource, const std::string &requestId);

      /**
       * Converts the DTO to a XML string representation.
       *
       * @return DTO as XML string.
       */
      std::string ToXml();

    private:

      /**
       * Error code
       */
      std::string _code;

      /**
       * Error message
       */
      std::string _message;

      /**
       * Resource.
       *
       * <p>The bucket or object that is involved in the error.</p>
       */
      std::string _resource;

      /**
       * Request ID
       */
      std::string _requestId;
    };

} // namespace AwsMock::Dto::Common

#endif