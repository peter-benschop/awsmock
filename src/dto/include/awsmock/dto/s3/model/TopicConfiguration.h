//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_DTO_S3_TOPIC_CONFIGURATION_H
#define AWSMOCK_DTO_S3_TOPIC_CONFIGURATION_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/dto/s3/model/FilterRule.h>
#include <awsmock/dto/s3/model/NotificationEvent.h>

namespace AwsMock::Dto::S3 {

    /**
     * S3 notification configuration for a SNS topic.
     *
     * <p>
     * This configures the S3 module to send a message to the supplied SNS topic. Depending on the event type and the
     * filter rules, the event is executed and a message is send to the provided SNS queue.
     * </p>
     *
     * Example:
     * @verbatim
     *   <TopicConfiguration>
     *     <Event>string</Event>
     *     ...
     *     <Filter>
     *       <S3Key>
     *         <FilterRule>
     *           <Name>string</Name>
     *           <Value>string</Value>
     *         </FilterRule>
     *         ...
     *      </S3Key>
     *     </Filter>
     *     <Id>string</Id>
     *     <Topic>string</Topic>
     *   </TopicConfiguration>
     * @endverbatimindex
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct TopicConfiguration {

        /**
         * ID, optional, if empty a random ID will be generated
         */
        std::string id;

        /**
         * Topic ARN
         */
        std::string topicArn;

        /**
         * S3 filter rules
         */
        std::vector<FilterRule> filterRules;

        /**
         * Notification events
         */
        std::vector<NotificationEventType> events;

        /**
          * Convert from XML representation
          *
          * @param rootNode XML rootNode
          */
        void FromXmlNode(Poco::XML::Node *rootNode);

        /**
         * Convert to a JSON object
         *
         * @return JSON object
         */
        [[nodiscard]] Poco::JSON::Object ToJsonObject() const;

        /**
         * Convert to a JSON string
         *
         * @return JSON string
         */
        [[nodiscard]] std::string ToJson() const;

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
        friend std::ostream &operator<<(std::ostream &os, const TopicConfiguration &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_TOPIC_CONFIGURATION_H
