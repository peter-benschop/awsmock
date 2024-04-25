//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTEREQUEST_H
#define AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTEREQUEST_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

namespace AwsMock::Dto::SQS {

    struct GetQueueAttributesRequest {

        /**
     * AWS region
     */
        std::string region;

        /**
     * Queue URL
     */
        std::string queueUrl;

        /**
     * UserAttribute names list
     */
        std::vector<std::string> attributeNames;

        /**
     * Resource
     */
        std::string resource = "SQS";

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
        friend std::ostream &operator<<(std::ostream &os, const GetQueueAttributesRequest &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_GETQUEUEATTRIBUTEREQUEST_H
