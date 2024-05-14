//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_COMMON_REQUEST_H
#define AWSMOCK_DTO_SQS_COMMON_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// Poco includes
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include "awsmock/core/exception/ServiceException.h"
#include <awsmock/core/JsonUtils.h>

namespace AwsMock::Dto::SQS {

    struct SqsCommonRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * AWS request ID
         */
        std::string requestId;

        /**
         * Converts the JSON string to DTO.
         *
         * @param jsonString JSON string
         */
        virtual void FromJson(const std::string &jsonString);

        /**
         * Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        virtual std::string ToString() const;

        /**
         * Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const SqsCommonRequest &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_COMMON_REQUEST_H
