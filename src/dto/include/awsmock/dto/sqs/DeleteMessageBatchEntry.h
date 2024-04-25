//
// Created by vogje01 on 30/05/2023.
//

#ifndef AWSMOCK_DTO_SQS_DELETE_MESSAGE_BATCH_ENTRY_H
#define AWSMOCK_DTO_SQS_DELETE_MESSAGE_BATCH_ENTRY_H

// C++ standard includes
#include <sstream>
#include <string>
#include <vector>

// Poco includes
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/UUIDGenerator.h>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/ServiceException.h>

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
     * Convert to a JSON string
     *
     * @return JSON string
     */
        [[nodiscard]] std::string ToJson() const;

        /**
     * Convert to a JSON string
     *
     * @return JSON string
     */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

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
        friend std::ostream &operator<<(std::ostream &os, const DeleteMessageBatchEntry &d);
    };

    typedef std::vector<DeleteMessageBatchEntry> DeleteMessageBatchEntries;

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_DELETE_MESSAGE_BATCH_ENTRY_H
