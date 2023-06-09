//
// Created by vogje01 on 01/06/2023.
//

#ifndef AWSMOCK_DTO_S3_PUTBUCKETNOTIFICATIONREQUEST_H
#define AWSMOCK_DTO_S3_PUTBUCKETNOTIFICATIONREQUEST_H

// C++ standard includes
#include <string>
#include <sstream>

namespace AwsMock::Dto::S3 {

    /**
     * Process the S3 notification configuration:
     *
     * <p>Notification for a lambda function:
     * <pre>
     * &le;NotificationConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/"&gt;
     *   &le;CloudFunctionConfiguration&gt;
     *     &le;Id&gt;1234567890123&le;/Id&gt;
     *     &le;CloudFunction&gt;arn:aws:lambda:eu-central-1:000000000000:function:ftp-file-copy&le;/CloudFunction&gt;
     *     &le;Event&gt;s3:ObjectCreated:*&le;/Event&gt;
     *   &le;/CloudFunctionConfiguration&gt;
     * &le;/NotificationConfiguration&gt;
     * &le;/pre&gt;
     * &le;/p&gt;
     * &le;p&gt;Notification for a SMS queue event:
     * &le;NotificationConfiguration xmlns=\"http://s3.amazonaws.com/doc/2006-03-01/\"&gt;
	 *   &le;QueueConfiguration&gt;
	 *     &le;Id&gt;1234567890125&le;/Id&gt;
	 *	   &le;Queue&gt;arn:aws:sqs:eu-central-1:000000000000:onix3-tmp-parsing-input-event-queue&le;/Queue&gt;
	 *     &le;Event&gt;s3:ObjectCreated:*&le;/Event&gt;
	 *   &le;/QueueConfiguration&gt;
     * &le;/NotificationConfiguration&gt;
     * </pre>
     * </p>
     */
    struct PutBucketNotificationRequest {

      /**
       * Constructor
       *
       * @param xmlString XML string
       * @param region AWS region name
       * @param bucket AWS S3 bucket name
       */
      explicit PutBucketNotificationRequest(const std::string &xmlString, const std::string &region, const std::string &bucket) {

          this->region = region;
          this->bucket = bucket;

          FromXML(xmlString);
      }

      /**
       * AWS region
       */
      std::string region;

      /**
       * AWS region
       */
      std::string bucket;

      /**
       * Lambda ARN
       */
      std::string lambdaArn;

      /**
       * Queue ARN
       */
      std::string queueArn;

      /**
       * Id
       */
      std::string notificationId;

      /**
       * Event
       */
      std::string event;

      /**
       * Parse the notification XML.
       *
       * @param xmlString notification XML string
       */
      void FromXML(const std::string &xmlString) {

          Poco::XML::DOMParser parser;
          Poco::AutoPtr<Poco::XML::Document> pDoc = parser.parseString(xmlString);

          Poco::XML::Node *cloudNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration");
          if (cloudNode) {
              Poco::XML::Node *idNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Id");
              notificationId = idNode->innerText();

              Poco::XML::Node *functionNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/CloudFunction");
              lambdaArn = functionNode->innerText();

              Poco::XML::Node *eventNode = pDoc->getNodeByPath("/NotificationConfiguration/CloudFunctionConfiguration/Event");
              event = eventNode->innerText();
          }

          Poco::XML::Node *queueNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration");
          if (queueNode) {
              Poco::XML::Node *idNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration/Id");
              notificationId = idNode->innerText();

              Poco::XML::Node *queueArnNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration/Queue");
              queueArn = queueArnNode->innerText();

              Poco::XML::Node *eventNode = pDoc->getNodeByPath("/NotificationConfiguration/QueueConfiguration/Event");
              event = eventNode->innerText();
          }
      }

      /**
       * Converts the DTO to a string representation.
       *
       * @return DTO as string for logging.
       */
      [[nodiscard]] std::string ToString() const {
          std::stringstream ss;
          ss << (*this);
          return ss.str();
      }

      /**
       * Stream provider.
       *
       * @return output stream
       */
      friend std::ostream &operator<<(std::ostream &os, const PutBucketNotificationRequest &r) {
          os << "PutBucketNotificationRequest={region='" + r.region + "' bucket='" + r.bucket + "' queueArn='" + r.queueArn + "' lambdaArn='" + r.lambdaArn +
              "' event='" + r.event + "'id='" + r.notificationId + "'}";
          return os;
      }

    };

} // namespace AwsMock::Dto::S3

#endif // AWSMOCK_DTO_S3_PUTBUCKETNOTIFICATIONREQUEST_H
