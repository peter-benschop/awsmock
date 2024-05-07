//
// Created by vogje01 on 03/06/2023.
//

#ifndef AWSMOCK_DTO_S3_PUT_BUCKET_NOTIFICATION_CONFIGURATION_REQUEST_H
#define AWSMOCK_DTO_S3_PUT_BUCKET_NOTIFICATION_CONFIGURATION_REQUEST_H

// C++ standard includes
#include <string>
#include <vector>

// AwsMock includes
#include <awsmock/core/DateTimeUtils.h>
#include <awsmock/core/JsonException.h>
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/dto/s3/model/LambdaConfiguration.h>
#include <awsmock/dto/s3/model/QueueConfiguration.h>
#include <awsmock/dto/s3/model/TopicConfiguration.h>

namespace AwsMock::Dto::S3 {

    /**
     * S3 Notification configuration
     *
     * Example:
     * @code{.xml}
       <NotificationConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
         <TopicConfiguration>
           <Event>string</Event>
             ...
           <Filter>
             <S3Key>
                <FilterRule>
                  <Name>string</Name>
                  <Value>string</Value>
               </FilterRule>
               ...
             </S3Key>
           </Filter>
           <Id>string</Id>
           <Topic>string</Topic>
         </TopicConfiguration>
         ...
         <QueueConfiguration>
           <Event>string</Event>
           ...
           <Filter>
             <S3Key>
               <FilterRule>
                 <Name>string</Name>
                 <Value>string</Value>
               </FilterRule>
               ...
            </S3Key>
           </Filter>
           <Id>string</Id>
           <Queue>string</Queue>
         </QueueConfiguration>
         ...
         <CloudFunctionConfiguration>
          <Event>string</Event>
          ...
          <Filter>
            <S3Key>
              <FilterRule>
                <Name>string</Name>
                <Value>string</Value>
             </FilterRule>
             ...
            </S3Key>
          </Filter>
          <Id>string</Id>
          <CloudFunction>string</CloudFunction>
         </CloudFunctionConfiguration>
         ...
         <EventBridgeConfiguration>
         </EventBridgeConfiguration>
       </NotificationConfiguration>
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    struct PutBucketNotificationConfigurationRequest {

        /**
         * AWS region
         */
        std::string region;

        /**
         * Bucket
         */
        std::string bucket;

        /**
         * Topic configurations
         */
        std::vector<TopicConfiguration> topicConfigurations;

        /**
         * SQS queue configurations
         */
        std::vector<QueueConfiguration> queueConfigurations;

        /**
         * Lambda function configurations
         */
        std::vector<LambdaConfiguration> lambdaConfigurations;

        /**
          * Convert from XML representation
          *
          * @param xmlString XML string
          */
        void FromXml(const std::string &xmlString);

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
        friend std::ostream &operator<<(std::ostream &os, const PutBucketNotificationConfigurationRequest &r);
    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_PUT_BUCKET_NOTIFICATION_CONFIGURATION_REQUEST_H
