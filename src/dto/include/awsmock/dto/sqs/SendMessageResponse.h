//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_CREATEMESSAGERESPONSE_H
#define AWSMOCK_DTO_SQS_CREATEMESSAGERESPONSE_H

// C++ standard includes
#include <string>
#include <sstream>
#include <iostream>
#include <utility>

// Poco includes
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/DOM/AutoPtr.h"
#include "Poco/DOM/Document.h"
#include "Poco/DOM/Element.h"
#include "Poco/DOM/DOMParser.h"
#include "Poco/DOM/Text.h"
#include "Poco/DOM/DOMWriter.h"
#include "Poco/XML/XMLWriter.h"
#include <Poco/JSON/Object.h>

// AwsMock includes
#include <awsmock/dto/sqs/MessageAttribute.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SQS {

  struct SendMessageResponse {

    /**
     * ID
     */
    long id;

    /**
     * Queue URL
     */
    std::string queueUrl;

    /**
     * Message ID
     */
    std::string messageId;

    /**
     * Receipt handle
     */
    std::string receiptHandle;

    /**
     * MD5 sum of body
     */
    std::string md5Body;

    /**
     * MD5 sum of sqs
     */
    std::string md5Attr;

    /**
     * Request ID
     */
    std::string requestId;

    /**
     * Convert to JSON representation
     *
     * @return JSON string
     */
    [[nodiscard]] std::string ToJson();

    /**
     * Convert to XML representation
     *
     * @return XML string
     */
    [[nodiscard]] std::string ToXml() const;

    /**
     * Convert from XML representation
     *
     * @param xmlString  XML string
     */
    void FromXml(const std::string &xmlString);

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
    friend std::ostream &operator<<(std::ostream &os, const SendMessageResponse &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_CREATEMESSAGERESPONSE_H
