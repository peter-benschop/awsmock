//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETE_MESSAGE_BATCH_ENTRY_H
#define AWSMOCK_DTO_SQS_DELETE_MESSAGE_BATCH_ENTRY_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/BsonUtils.h>

namespace AwsMock::Dto::SQS {

    struct DeleteMessageBatchEntry {

        /**
         * Entry ID
         */
        std::string id;

        /**
         * Receipt handle
         */
        std::string receiptHandle;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

        /**
         * @brief Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] view_or_value<view, value> ToDocument() const;

        /**
         * @brief Converts the DTO to a string representation.
         *
         * @return DTO as string
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @brief Stream provider.
         *
         * @return output stream
         */
        friend std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchEntry &d);
    };

    typedef std::vector<DeleteMessageBatchEntry> DeleteMessageBatchEntries;

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_DELETE_MESSAGE_BATCH_ENTRY_H
