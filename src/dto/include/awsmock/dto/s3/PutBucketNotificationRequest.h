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
   * <p>
   * Notification for a lambda function:
   * @verbatim
   * <NotificationConfiguration xmlns="http://s3.amazonaws.com/doc/2006-03-01/">
   *   <CloudFunctionConfiguration>
   *     <Id>1234567890123</Id>
   *     <CloudFunction>arn:aws:lambda:eu-central-1:000000000000:function:ftp-file-copy</CloudFunction>
   *     <Event>s3:ObjectCreated:*</Event>
   *   </CloudFunctionConfiguration>
   * </NotificationConfiguration>
   * </pre>
   * </p>
   * <p>Notification for a SQS queue event:
   * <pre>
   * <NotificationConfiguration xmlns=\"http://s3.amazonaws.com/doc/2006-03-01/\">
   *   <QueueConfiguration>
   *     <Id>1234567890125</Id>
   *	   <Queue>arn:aws:sqs:eu-central-1:000000000000:onix3-tmp-parsing-input-event-queue</Queue>
   *     <Event>s3:ObjectCreated:*</Event>
   *   </QueueConfiguration>
   * </NotificationConfiguration>
   * @endverbatim
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
     * lambda ARN
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
