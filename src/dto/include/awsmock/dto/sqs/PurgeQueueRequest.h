//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H
#define AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H

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

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SQS {

  struct PurgeQueueRequest {

    /**
     * AWS region
     */
    std::string region;

    /**
     * Queue URL
     */
    std::string queueUrl;

    /**
     * Resource
     */
    std::string resource = "Unknown resource";

    /**
     * Resource
     */
    std::string requestId = Poco::UUIDGenerator().createRandom().toString();

    /**
     * Converts the JSON string to a DTO
     *
     * @param jsonString JSON string
     */
    void FromJson(const std::string &jsonString);

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
    friend std::ostream &operator<<(std::ostream &os, const PurgeQueueRequest &r);

  };

} // namespace AwsMock::Dto::SQS

#endif // AWSMOCK_DTO_SQS_PURGEQUEUEREQUEST_H
