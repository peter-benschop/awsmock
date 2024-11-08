//
// Created by vogje01 on 7/6/24.
//

#ifndef AWSMOCK_DTO_SQS_MESSAGE_H
#define AWSMOCK_DTO_SQS_MESSAGE_H

// C++ includes
#include <chrono>
#include <map>
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>
#include <awsmock/dto/sqs/model/MessageAttribute.h>

namespace AwsMock::Dto::SQS {

    using std::chrono::system_clock;

    /**
     * @brief SQS message entry as used by the SendMessageBatch
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct Message {

        /**
         * Region
         */
        std::string region;

        /**
         * Message ID
         */
        std::string messageId;

        /**
         * ID
         */
        std::string id;

        /**
         * Receipt handle
         */
        std::string receiptHandle;

        /**
         * Body
         */
        std::string body;

        /**
         * System attributes
         */
        std::map<std::string, std::string> attributes;

        /**
         * Message attributes
         */
        MessageAttributeList messageAttributes;

        /**
         * MD5 sum
         */
        std::string md5Sum;

        /**
         * Created time stamp
         */
        system_clock::time_point created = Core::DateTimeUtils::LocalDateTimeNow();

        /**
         * Created time stamp
         */
        system_clock::time_point modified;

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
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * @brief Converts a JSON representation to s DTO.
         *
         * @param object JSON object.
         */
        void FromJson(const Poco::JSON::Object::Ptr &object);

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
        friend std::ostream &operator<<(std::ostream &os, const Message &r);
    };

}// namespace AwsMock::Dto::SQS

#endif// AWSMOCK_DTO_SQS_MESSAGE_ENTRY_H
