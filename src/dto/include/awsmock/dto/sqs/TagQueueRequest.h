//
// Created by vogje01 on 22/012/2023.
//

#ifndef AWSMOCK_DTO_SQS_TAG_QUEUE_REQUEST_H
#define AWSMOCK_DTO_SQS_TAG_QUEUE_REQUEST_H

// C++ standard includes
#include <map>
#include <sstream>
#include <string>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Dto::SQS {

    struct TagQueueRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Queue URL
         */
        std::string queueUrl;

        /**
         * Tags map
         */
        std::map<std::string, std::string> tags;

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
        friend std::ostream &operator<<(std::ostream &os, const TagQueueRequest &r);
    };

    typedef std::map<std::string, std::string> TagList;

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_TAG_QUEUE_REQUEST_H
