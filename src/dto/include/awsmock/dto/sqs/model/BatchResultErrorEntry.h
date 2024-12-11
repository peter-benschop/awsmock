//
// Created by vogje01 on 7/6/24.
//

#ifndef AWSMOCK_DTO_SQS_MODEL_BATCH_RESULT_ERROR_ENTRY_H
#define AWSMOCK_DTO_SQS_MODEL_BATCH_RESULT_ERROR_ENTRY_H

// C++ includes
#include <string>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/sqs/model/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

    /**
     * @brief Send when a delete batch error occurs.
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct BatchResultErrorEntry {

        /**
         * Id
         */
        std::string id;

        /**
         * Code
         */
        std::string code;

        /**
         * Sender fault
         */
        bool senderFault;

        /**
         * Error message
         */
        std::string message;

        /**
         * @brief Converts the DTO to a JSON string.
         *
         * @return DTO as JSON string.
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Converts the DTO to a JSON representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string for logging.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const BatchResultErrorEntry &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_MODEL_BATCH_RESULT_ERROR_ENTRY_H
