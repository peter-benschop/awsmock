//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_DEAD_LETTER_CONFIG_H
#define AWSMOCK_DTO_LAMBDA_DEAD_LETTER_CONFIG_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

// AwsMock includes
#include "awsmock/core/exception/ServiceException.h"

namespace AwsMock::Dto::Lambda {

    struct DeadLetterConfig {

        /**
         * Target ARN
         */
        std::string targetArn = {};

        /**
         * Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_DEAD_LETTER_CONFIG_H
