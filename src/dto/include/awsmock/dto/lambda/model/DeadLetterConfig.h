//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_LAMBDA_DEAD_LETTER_CONFIG_H
#define AWSMOCK_DTO_LAMBDA_DEAD_LETTER_CONFIG_H

// C++ standard includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::Lambda {

    struct DeadLetterConfig {

        /**
         * Target ARN
         */
        std::string targetArn = {};

        /**
         * Converts the DTO to a JSON representation.
         *
         * @return DTO as string
         */
        view_or_value<view, value> ToDocument() const;
    };

}// namespace AwsMock::Dto::Lambda

#endif// AWSMOCK_DTO_LAMBDA_DEAD_LETTER_CONFIG_H
