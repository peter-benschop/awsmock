//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DTO_S3_PUT_BUCKET_NOTIFICATION_REQUEST_H
#define AWSMOCK_DTO_S3_PUT_BUCKET_NOTIFICATION_REQUEST_H

// C++ standard includes
#include <sstream>
#include <string>

// AwsMock includes
#include <awsmock/core/JsonUtils.h>
#include <awsmock/core/LogStream.h>
#include <awsmock/core/XmlUtils.h>
#include <awsmock/core/exception/JsonException.h>

namespace AwsMock::Dto::S3 {

    /**
     * Process the S3 notification configuration:
     *
     * <p>
     * Notification for a lambda function:
     * </p>
     * Example:
     * @code{.xml}
     * <NotificationConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
     *   <CloudFunctionConfiguration>
     *     <Id>1234567890123</Id>
     *     <CloudFunction>arn:aws:lambda:eu-central-1:000000000000:function:ftp-file-copy</CloudFunction>
     *     <Event>s3:ObjectCreated:*</Event>
     *   </CloudFunctionConfiguration>
     * </NotificationConfiguration>
     * @endcode
     * </p>
     * <p>Notification for a SQS queue event:
     * @code{.xml}
     * <NotificationConfiguration xmlns=\"http://s3.amazonaws.com/doc/2006-03-01/\">
     *   <QueueConfiguration>
     *     <Id>1234567890125</Id>
     *	   <Queue>arn:aws:sqs:eu-central-1:000000000000:onix3-tmp-parsing-input-event-queue</Queue>
     *     <Event>s3:ObjectCreated:*</Event>
     *   </QueueConfiguration>
     * </NotificationConfiguration>
     * @endcode
     *
     * @author jens.vogt\@opitz-consulting.com
     */
    //    struct PutBucketNotificationRequest {
    //
    //        /**
    //         * AWS region
    //         */
    //        std::string region;
    //
    //        /**
    //         * AWS region
    //         */
    //        std::string bucket;
    //
    //        /**
    //         * lambda ARN
    //         */
    //        std::string lambdaArn;
    //
    //        /**
    //         * Queue ARN
    //         */
    //        std::string queueArn;
    //
    //        /**
    //         * Topic ARN
    //         */
    //        std::string topicArn;
    //
    //        /**
    //         * Id
    //         */
    //        std::string notificationId;
    //
    //        /**
    //         * Event
    //         */
    //        std::string event;
    //
    //        /**
    //         * Parse the notification XML.
    //         *
    //         * @param xmlString notification XML string
    //         */
    //        void FromXML(const std::string &xmlString);
    //
    //        /**
    //         * Converts the DTO to a string representation.
    //         *
    //         * @return DTO as string for logging.
    //         */
    //        [[nodiscard]] std::string ToString() const;
    //
    //        /**
    //         * Stream provider.
    //         *
    //         * @return output stream
    //         */
    //        friend std::ostream &operator<<(std::ostream &os, const PutBucketNotificationRequest &r);
    //    };

}// namespace AwsMock::Dto::S3

#endif// AWSMOCK_DTO_S3_PUT_BUCKET_NOTIFICATION_REQUEST_H
