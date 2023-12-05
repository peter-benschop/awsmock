//
// Created by vogje01 on 31/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_RESTERRORRESPONSE_H
#define AWSMOCK_DTO_SQS_RESTERRORRESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <iostream>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/DOM/AutoPtr.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Element.h>
#include <Poco/DOM/Text.h>
#include <Poco/DOM/DOMWriter.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/XML/XMLWriter.h>

// AwsMok includes
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SQS {

  struct RestErrorResponse {

    /**
     * Constructor.
     *
     * @param exc module exception
     */
    explicit RestErrorResponse(const Core::ServiceException &exc);

    /**
     * Error code
     */
    int code = 0;

    /**
     * Error message
     */
    std::string message;

    /**
     * Resource.
     *
     * <p>The bucket or object that is involved in the error.</p>
     */
    std::string resource;

    /**
     * Request ID
     */
    std::string requestId;

    /**
     * Converts the DTO to a JSON string representation.
     *
     * @return DTO as JSON string.
     */
    [[nodiscard]] std::string ToJson() const;

    /**
     * Converts the DTO to a XML string representation.
     *
     * @return DTO as XML string.
     */
    [[nodiscard]] std::string ToXml() const;

    /**
     * Converts the DTO to a string representation.
     *
     * @return DTO as string for logging.
     */
    [[nodiscard]] std::string ToString() const;

    /**
     * Stream provider.
     *
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const RestErrorResponse &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_RESTERRORRESPONSE_H